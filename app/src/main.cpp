//
// Created by kolyne on 10/27/25.
//

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
    c.SetTexture(&cat);

    while (win.IsOpen())
    {
        c.Rotate(glm::vec3({1.0f, 1.f, 0}) * glm::radians(45.f * (float)win.GetDeltaTime()));

        win.Clear(mngl::Color::Black);
        win.Draw(c);
        win.Display();
    }
    return 0;
}
