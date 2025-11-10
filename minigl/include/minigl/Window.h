#ifndef MINIGL_WINDOW_H
#define MINIGL_WINDOW_H

#include <string>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Color.h"
#include "Drawable.h"
#include "Input.h"
#include "Light.h"

class GLFWwindow;

namespace mngl
{
    class Window
    {
        GLFWwindow* m_win;
        double m_deltaTime;
        double m_lastFrame;

        Shader* m_shader;
        Camera m_camera;
        Light m_light;
        Input m_input;

        static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
        static void SetKeyCallback(GLFWwindow *_window, int _key, int _scancode, int _action, int _mode);
        static void SetMouseButtonCallback(GLFWwindow *_window, int _butto, int _action, int _mode);

    public:
        Window(int _width, int _height, std::string _name);
        ~Window();

        bool IsOpen();
        float GetDeltaTime();
        glm::i32vec2 GetSize();
        Shader* GetDefaultShader();

        void SetCamera(const Camera& _camera);
        const Camera& GetCurrentCamera();
        Camera GetDefaultCamera();

        void SetLight(const Light& _light);
        const Light& GetCurrentLight();

        const Input& GetInput();
        void SetCursorMode(bool _hide);

        void Clear(const Color& _color);
        void Display();
        void Draw(const Drawable& _draw, RenderState _renderState = {glm::mat4(1.f), nullptr}) const;
    };
}

#endif // MINIGL_WINDOW_H
