#ifndef MINIGL_WINDOW_H
#define MINIGL_WINDOW_H

#include <string>
#include <glm/glm.hpp>
#include "Color.h"

class GLFWwindow;

namespace mngl
{
    class Window
    {
        GLFWwindow* m_win;
        double m_deltaTime;
        double m_lastFrame;

        static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

    public:
        Window(int _width, int _height, std::string _name);
        ~Window();
        bool IsOpen();
        float GetDeltaTime();
        void Clear(const Color& _color);
        void Display();
        glm::i32vec2 GetSize();
    };
}

#endif // MINIGL_WINDOW_H