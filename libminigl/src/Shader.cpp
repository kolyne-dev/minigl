//
// Created by kolyne on 10/28/25.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <minigl/Shader.h>
#include <glm/gtc/type_ptr.hpp>
#include <glad/gl.h>
#include <minigl/Color.h>
#include <minigl/Texture.h>

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

void mngl::Shader::SetInt(const std::string& _name, int _value) const
{
    Use();
    glUniform1d(glGetUniformLocation(m_id, _name.c_str()), _value);
    Shutdown();
}

void mngl::Shader::SetFloat(const std::string& _name, float _value) const
{
    Use();
    glUniform1f(glGetUniformLocation(m_id, _name.c_str()), _value);
    Shutdown();
}

void mngl::Shader::SetColor(const std::string& _name, const Color& _value) const
{
    Use();
    glUniform4f(glGetUniformLocation(m_id, _name.c_str()), _value.r, _value.g, _value.b, _value.a);
    Shutdown();
}

void mngl::Shader::SetTexture(const std::string& _name, const Texture& _value) const
{
    SetInt(_name, _value.m_textureID);
}

void mngl::Shader::SetMatrix4(const std::string& _name, const glm::mat4& _value) const
{
    Use();
    glUniformMatrix4fv(glGetUniformLocation(m_id, _name.c_str()), 1, GL_FALSE, glm::value_ptr(_value));
    Shutdown();
}
