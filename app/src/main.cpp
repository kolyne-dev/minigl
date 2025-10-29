//
// Created by kolyne on 10/27/25.
//

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <minigl/Window.h>
#include <minigl/Shader.h>
#include <minigl/Color.h>
#include <minigl/VAO.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <ext/stb_image.h>

#include "minigl/Texture.h"

float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};

int main(int argc, char** argv)
{
    mngl::Window win(800, 600, "toto");

    mngl::VAO vao(vertices, 36, sizeof(float) * 5, GL_STATIC_DRAW);
    vao.SetAttrib(0, 3, GL_FLOAT, GL_FALSE, 0);
    vao.SetAttrib(1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));

    glm::i32vec2 size = win.GetSize();

    glm::mat4 projection = glm::perspective(glm::radians(75.f), (float)size.x / (float)size.y, 0.1f, 100.f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    mngl::Shader shader("./shader/vertex.glsl", "./shader/fragment.glsl");

    shader.SetMatrix4("projection", projection);
    shader.SetMatrix4("view", view);
    shader.SetMatrix4("model", model);
    shader.SetColor("MainColor", mngl::Color::White);

    mngl::Texture cat("assets/chat.jpg", true, true);

    shader.SetTexture("Texture", cat);

    while (win.IsOpen())
    {
        win.Clear(mngl::Color::Black);

        model = glm::rotate(model, glm::radians(45.f * (float)win.GetDeltaTime()), glm::vec3(1.f, 1.f, 0));

        shader.SetMatrix4("model", model);

        shader.Use();
        cat.Use();
        vao.Draw();
        shader.Shutdown();
        cat.Shutdown();

        win.Display();
    }
    return 0;
}
