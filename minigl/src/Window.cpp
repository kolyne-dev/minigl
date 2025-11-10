#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <minigl/Window.h>
#include <iostream>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "minigl/Texture.h"

void mngl::Window::FrameBufferSizeCallback(GLFWwindow* _window, int _width, int _height)
{
    glViewport(0, 0, _width, _height);
    Window* self = static_cast<Window *>(glfwGetWindowUserPointer(_window));
    Camera c = self->GetCurrentCamera();
    c.SetAspectRatio((float)_width / (float)_height);
    self->SetCamera(c);
}

void mngl::Window::SetKeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mode)
{
    if (_action == GLFW_REPEAT)
        return;
    Window* self = static_cast<Window *>(glfwGetWindowUserPointer(_window));
    self->m_input.UpdateKey(static_cast<Input::EKeyCode>(_key), _action == GLFW_PRESS ? Input::JUST_PRESSED : Input::JUST_RELEASED);
}
void mngl::Window::SetMouseButtonCallback(GLFWwindow* _window, int _button, int _action, int _mode)
{
    if (_action == GLFW_REPEAT)
        return;
    Window* self = static_cast<Window *>(glfwGetWindowUserPointer(_window));
    self->m_input.UpdateMouse(static_cast<Input::EKeyMouseCode>(_button), _action == GLFW_PRESS ? Input::JUST_PRESSED : Input::JUST_RELEASED);
}

mngl::Window::Window(int _width, int _height, std::string _name)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
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
    glfwSetWindowUserPointer(m_win, this);
    glfwMakeContextCurrent(m_win);
    glfwSetFramebufferSizeCallback(m_win, FrameBufferSizeCallback);
    glfwSetKeyCallback(m_win, SetKeyCallback);
    glfwSetMouseButtonCallback(m_win, SetMouseButtonCallback);

    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }

    Texture::Default = new Texture("./shader/none.png", true, true);

    glEnable(GL_DEPTH_TEST);

    m_shader = new Shader("./shader/vertex.glsl", "./shader/fragment.glsl");
    m_camera = GetDefaultCamera();

    m_lastFrame = glfwGetTime();
}

mngl::Window::~Window()
{
    delete Texture::Default;
    delete m_shader;
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

mngl::Camera mngl::Window::GetDefaultCamera()
{
    Camera ret;
    ret.SetFOV(glm::radians(75.f));
    glm::i32vec2 size = GetSize();
    ret.SetAspectRatio((float)size.x / (float)size.y);
    ret.SetPosition({0, 0, -3.f});
    return ret;
}

void mngl::Window::SetLight(const Light &_light) {
    m_light = _light;
}

const mngl::Light& mngl::Window::GetCurrentLight() {
    return m_light;
}

const mngl::Input& mngl::Window::GetInput() {
    return m_input;
}

void mngl::Window::SetCursorMode(bool _hide) {
    glfwSetInputMode(m_win, GLFW_CURSOR, _hide ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

void mngl::Window::Clear(const Color& _color)
{
    glClearColor(_color.r, _color.g, _color.b, _color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void mngl::Window::Display()
{
    glfwSwapBuffers(m_win);
    m_input.Update(m_win);
    glfwPollEvents();
}

void mngl::Window::Draw(const Drawable& _draw, RenderState _renderState) const
{
    if (_renderState.shader == nullptr)
    {
        _renderState.shader = m_shader;
        _renderState.shader->SetMatrix4("_projection", m_camera.GetPerspectiveTransform());
        _renderState.shader->SetMatrix4("_view", m_camera.GetTransform());
        _renderState.shader->SetLight("_mainLight", m_light);
    }
    _draw.Draw(*this, _renderState);
}

glm::i32vec2 mngl::Window::GetSize()
{
    glm::i32vec2 ret;
    glfwGetWindowSize(m_win, &ret.x, &ret.y);
    return ret;
}

mngl::Shader* mngl::Window::GetDefaultShader()
{
    return m_shader;
}

void mngl::Window::SetCamera(const Camera& _camera)
{
    m_camera = _camera;
}

const mngl::Camera& mngl::Window::GetCurrentCamera()
{
    return m_camera;
}
