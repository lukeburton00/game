#include "gl_vertex_buffer.hpp"

GLVertexBuffer::GLVertexBuffer()
{
	m_Vertices.reserve(100000);
}

GLVertexBuffer::~GLVertexBuffer()
{
	Unbind();
	glDeleteBuffers(1, &m_ID);
}

void GLVertexBuffer::Init()
{
	glGenBuffers(1, &m_ID);
	Bind();
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4000000, nullptr, GL_DYNAMIC_DRAW);
}

void GLVertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void GLVertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLVertexBuffer::Push(Vertex vertex)
{
	m_Vertices.push_back(vertex);
	numVertices++;
}

void GLVertexBuffer::Flush()
{
	m_Vertices.clear();
	numVertices = 0;
}

void GLVertexBuffer::BufferData()
{
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * m_Vertices.size(), m_Vertices.data());
}