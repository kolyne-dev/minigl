#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "../include/Window.h"

#include <iostream>

void mngl::Window::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

mngl::Window::Window(int _width, int _height, std::string _name)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_win = glfwCreateWindow(_width, _height, _name.c_str(), NULL, NULL);

    if (m_win == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(m_win);
    glfwSetFramebufferSizeCallback(m_win, FrameBufferSizeCallback);

    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }
}

mngl::Window::~Window()
{
    glfwTerminate();
}

bool mngl::Window::IsOpen()
{
    return !glfwWindowShouldClose(m_win);
}

void mngl::Window::Clear(const Color& _color)
{
    glClearColor(_color.r, _color.g, _color.b, _color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void mngl::Window::Display()
{
    glfwSwapBuffers(m_win);
    glfwPollEvents();
}
