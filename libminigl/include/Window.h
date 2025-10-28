#ifndef MINIGL_WINDOW_H
#define MINIGL_WINDOW_H

#include <string>

#include "Color.h"

class GLFWwindow;

namespace mngl
{
    class Window
    {
        GLFWwindow* m_win;

        static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

    public:
        Window(int _width, int _height, std::string _name);
        ~Window();
        bool IsOpen();
        void Clear(const Color& _color);
        void Display();
    };
}

#endif // MINIGL_WINDOW_H