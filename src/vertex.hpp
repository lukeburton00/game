#pragma once

#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texCoord;

    Vertex(glm::vec3 positionParam, glm::vec3 colorParam, glm::vec2 texCoordParam)
    {
        position = positionParam;
        texCoord = texCoordParam;
        color = colorParam;
    }
};
