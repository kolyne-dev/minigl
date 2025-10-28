//
// Created by kolyne on 10/28/25.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/Shader.h"
#include <glad/gl.h>

std::string mngl::Shader::GetFileContent(const std::string& _path)
{
    try
    {
        std::ifstream shaderFile;
        shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        shaderFile.open(_path);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        return shaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR: File can't be read" << e.what() << std::endl;
    }
    return "";
}

unsigned int mngl::Shader::Process(const std::string& _shaderCode, bool _isVertex)
{
    unsigned int shaderID;
    if (_isVertex)
    {
        shaderID = glCreateShader(GL_VERTEX_SHADER);
    } else
    {
        shaderID = glCreateShader(GL_FRAGMENT_SHADER);
    }

    const char* shaderCode = _shaderCode.c_str();
    glShaderSource(shaderID, 1, &shaderCode, nullptr);
    glCompileShader(shaderID);

    int success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        std::cout << ((_isVertex) ? "VERTEX" : "FRAGMENT") << " SHADER: COMPILATION FAILED: \n" << infoLog << std::endl;
    }
    return shaderID;
}

mngl::Shader::Shader(const std::string& _vertexPath, const std::string& _fragmentPath)
{
    m_id = glCreateProgram();

    m_vertexShader = Process(GetFileContent(_vertexPath), true);
    m_fragmentShader = Process(GetFileContent(_fragmentPath), false);
    glAttachShader(m_id, m_vertexShader);
    glAttachShader(m_id, m_fragmentShader);
    glLinkProgram(m_id);
    int success;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(m_id, 512, NULL, infoLog);
        std::cout << "SHADER PROGRAM: LINK FAILED: \n" << infoLog << std::endl;
    }
    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);
}

void mngl::Shader::Use() const
{
    glUseProgram(m_id);
}

void mngl::Shader::Shutdown() const
{
    glDeleteProgram(m_id);
}

void mngl::Shader::SetMatrix4(const std::string& _name, const glm::mat4& _value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_id, _name.c_str()), 1, GL_FALSE, &_value[0][0]);
}
