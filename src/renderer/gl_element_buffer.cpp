#include "gl_element_buffer.hpp"

GLElementBuffer::GLElementBuffer()
{
	m_Indices.reserve(400000);
}

GLElementBuffer::~GLElementBuffer()
{
	Unbind();
	glDeleteBuffers(1, &m_ID);
}

void GLElementBuffer::Init()
{
	glGenBuffers(1, &m_ID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 6000000, nullptr, GL_DYNAMIC_DRAW);
}

void GLElementBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void GLElementBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLElementBuffer::Push(uint32_t index)
{
	m_Indices.push_back(index);
	m_NumIndices++;
}

void GLElementBuffer::Flush()
{
	m_Indices.clear();
	m_NumIndices = 0;
}

void GLElementBuffer::BufferData()
{
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(uint32_t) * m_Indices.size(), m_Indices.data());
}