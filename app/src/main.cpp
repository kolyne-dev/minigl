//
// Created by kolyne on 10/27/25.
//

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <minigl/Window.h>
#include <minigl/Color.h>

#include <minigl/Cube.h>
#include <minigl/Texture.h>
#include <minigl/Transformable.h>


int main(int argc, char** argv)
{
    mngl::Window win(800, 600, "minigl - Demo");

    mngl::Texture cat("assets/chat.jpg", true, true);

    mngl::Cube c;
    mngl::Cube light;
    light.SetScale({0.1f, 0.1f, 0.1f});
    c.SetTexture(&cat);

    win.GetDefaultShader()->SetColor("_lightColor", mngl::Color::White);
    win.GetDefaultShader()->SetFloat("_ambientStrength", 0.1f);
    //c.SetPosition({0, 1, 0});
    c.SetRotation({1.f, 1.f, 1.f});
    c.SetScale({0.5, 0.5, 0.5});

    // auto camera = win.GetCurrentCamera();
    // camera.Move({0, 1, 0});
    // win.SetCamera(camera);

    while (win.IsOpen())
    {
        //c.Rotate(glm::vec3({1.0f, 1.f, 0}) * glm::radians(45.f * (float)win.GetDeltaTime()));

        light.SetPosition({cos(glfwGetTime()) * 1.0f, sin(glfwGetTime()) * 1.0f, -1});
        win.GetDefaultShader()->SetVector3("_lightPos", light.GetPosition());

        win.Clear(mngl::Color::Black);
        win.Draw(c);
        win.Draw(light);
        win.Display();
    }
    return 0;
}
