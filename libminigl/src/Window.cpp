#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <minigl/Window.h>
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
        const char* description;
        int code = glfwGetError(&description);
        std::cout << "Failed to create GLFW window: " << description << std::endl;
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

    glEnable(GL_DEPTH_TEST);

    m_lastFrame = glfwGetTime();
}

mngl::Window::~Window()
{
    glfwTerminate();
}

bool mngl::Window::IsOpen()
{
    double currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;
    return !glfwWindowShouldClose(m_win);
}

float mngl::Window::GetDeltaTime()
{
    return m_deltaTime;
}

void mngl::Window::Clear(const Color& _color)
{
    glClearColor(_color.r, _color.g, _color.b, _color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void mngl::Window::Display()
{
    glfwSwapBuffers(m_win);
    glfwPollEvents();
}

glm::i32vec2 mngl::Window::GetSize()
{
    glm::i32vec2 ret;
    glfwGetWindowSize(m_win, &ret.x, &ret.y);
    return ret;
}
