#pragma once

#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texCoord;

    Vertex(const glm::vec3& positionParam, const glm::vec3& colorParam, const glm::vec2& texCoordParam)
    {
        position = positionParam;
        texCoord = texCoordParam;
        color = colorParam;
    }
};
