#pragma once

#include "glad/glad.h"

#include <stdint.h>

struct GLVertexArray
{
public:
    GLVertexArray() = default;
    ~GLVertexArray();

    void Init();

    void Bind();
    void Unbind();

private:
    uint32_t m_ID = 0;
};