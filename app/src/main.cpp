//
// Created by kolyne on 10/27/25.
//

#include <glad/gl.h>
#include <minigl/Window.h>
#include <minigl/Shader.h>
#include <minigl/Color.h>
#include <minigl/VAO.h>

float vertices[]
{
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
};

int main(int argc, char** argv) {
    mngl::Window win(800, 600, "toto");

    mngl::VAO vao(vertices, 3, sizeof(float) * 3, GL_STATIC_DRAW);
    vao.SetAttrib(0, 3, GL_FLOAT, GL_FALSE, 0);

    mngl::Shader shader("./shader/vertex.glsl", "./shader/fragment.glsl");

    while (win.IsOpen())
    {
        win.Clear(mngl::Color::Black);

        shader.Use();
        vao.Draw();
        shader.Shutdown();

        win.Display();
    }
    return 0;
}
