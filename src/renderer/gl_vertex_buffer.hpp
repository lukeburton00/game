#pragma once

#include "vertex.hpp"

#include "glad/glad.h"

#include <vector>

struct GLVertexBuffer
{
public:
	GLVertexBuffer();
	~GLVertexBuffer();

	void Init();

	void Bind();
	void Unbind();

	void Push(Vertex vertex);
	void Flush();
	void BufferData();
	
public:
	uint64_t numVertices = 0;
	
private:
	uint32_t m_ID = 0;
	std::vector<Vertex> m_Vertices;
};