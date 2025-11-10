//
// Created by kolyne on 10/27/25.
//

#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <minigl/Window.h>
#include <minigl/Color.h>

#include <minigl/Cube.h>
#include <minigl/Texture.h>
#include <minigl/Light.h>


int main(int argc, char** argv)
{
    mngl::Window win(800, 600, "minigl - Demo");

    mngl::Texture cat("assets/potichat.jpg", true, true);

    mngl::Cube c;
    mngl::Cube light;
    light.SetScale({0.1f, 0.1f, 0.1f});
    mngl::Light mainLight = win.GetCurrentLight();

    mngl::Material m = c.GetMaterial();
    m.SetDiffuseTexture(&cat);
    c.SetMaterial(m);


    c.SetRotation({1.f, 1.f, 1.f});
    c.SetScale({0.5, 0.5, 0.5});

    while (win.IsOpen())
    {
        mngl::Input input = win.GetInput();
        mngl::Camera camera = win.GetCurrentCamera();
        float dt = win.GetDeltaTime();

        if (input.IsKeyPressed(mngl::Input::W)) {
            camera.Move(camera.Forward() * 10.f * dt);
        }
        if (input.IsKeyPressed(mngl::Input::S)) {
            camera.Move(camera.Forward() * -10.f * dt);
        }
        if (input.IsKeyPressed(mngl::Input::D)) {
            camera.Move(camera.Right() * 10.f * dt);
        }
        if (input.IsKeyPressed(mngl::Input::A)) {
            camera.Move(camera.Right() * -10.f * dt);
        }
        if (input.IsKeyPressed(mngl::Input::SPACE)) {
            camera.Move(camera.Up() * 10.f * dt);
        }
        if (input.IsKeyPressed(mngl::Input::LEFT_SHIFT)) {
            camera.Move(camera.Up() * -10.f * dt);
        }
        if (input.IsKeyPressed(mngl::Input::UP)) {
            camera.Rotate({glm::pi<float>() * 0.5f * dt, 0, 0});
        }
        if (input.IsKeyPressed(mngl::Input::DOWN)) {
            camera.Rotate({glm::pi<float>() * -0.5f * dt, 0, 0});
        }
        if (input.IsKeyPressed(mngl::Input::LEFT)) {
            camera.Rotate({0, glm::pi<float>() * 0.5f * dt, 0});
        }
        if (input.IsKeyPressed(mngl::Input::RIGHT)) {
            camera.Rotate({0, glm::pi<float>() * -0.5f * dt, 0});
        }
        win.SetCamera(camera);

        //c.Rotate(glm::vec3({1.0f, 1.f, 0}) * glm::radians(45.f * (float)win.GetDeltaTime()));

        light.SetPosition({cos(glfwGetTime()) * 1.0f, sin(glfwGetTime()) * 1.0f, -1});
        mainLight.SetPosition(light.GetPosition());
        win.SetLight(mainLight);

        win.Clear(mngl::Color::Black);
        win.Draw(c);
        win.Draw(light);
        win.Display();
    }
    return 0;
}
