#ifndef MINIGL_WINDOW_H
#define MINIGL_WINDOW_H

#include <string>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Color.h"
#include "Drawable.h"

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

        static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

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

        void Clear(const Color& _color);
        void Display();
        void Draw(const Drawable& _draw, RenderState _renderState = {glm::mat4(1.f), nullptr});
    };
}

#endif // MINIGL_WINDOW_H
