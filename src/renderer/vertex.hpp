#pragma once

#include "glm/glm.hpp"

struct Vertex
{
    glm::vec2 position;
    glm::vec2 texCoord;
    glm::vec4 color;

    Vertex(glm::vec2 pos, glm::vec2 tex, glm::vec4 col)
    {
        position = pos;
        texCoord = tex;
        color = col;
    }
};