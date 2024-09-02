#include "static_batch.hpp"
#include "log.hpp"

StaticBatch::StaticBatch()
{
	m_Texture = nullptr;
	m_Shader = nullptr;
}

StaticBatch::~StaticBatch()
{
	flush();
	m_VAO.Unbind();
}

void StaticBatch::init(std::shared_ptr<Texture> texture, std::shared_ptr<Shader> shader)
{ 
	m_VAO.Init();
	m_VAO.Bind();
	m_VBO.Init();
	m_EBO.Init();
	m_EBO.Bind();
	m_VAO.Unbind();

	m_Texture = texture;
	m_Shader = shader;
}

void StaticBatch::push(glm::vec2 position, glm::vec2 scale, glm::vec4 color, glm::vec2 textureCoords, glm::vec2 textureScale)
{
	m_EBO.Push(m_VBO.numVertices + 0);
	m_EBO.Push(m_VBO.numVertices + 1);
	m_EBO.Push(m_VBO.numVertices + 3);
	m_EBO.Push(m_VBO.numVertices + 1);
	m_EBO.Push(m_VBO.numVertices + 2);
	m_EBO.Push(m_VBO.numVertices + 3);

	m_VBO.Push(Vertex(glm::vec2(position.x + scale.x, position.y),				glm::vec2(((textureCoords.x + 1) * textureScale.x) / m_Texture->width, ((textureCoords.y + 1) * textureScale.y) / m_Texture->height), color));
	m_VBO.Push(Vertex(glm::vec2(position.x + scale.x, position.y + scale.y),	glm::vec2(((textureCoords.x + 1) * textureScale.x) / m_Texture->width, ((textureCoords.y) * textureScale.y) / m_Texture->height), color));
	m_VBO.Push(Vertex(glm::vec2(position.x, position.y + scale.y),				glm::vec2(((textureCoords.x) * textureScale.x) / m_Texture->width, ((textureCoords.y) * textureScale.y) / m_Texture->height), color));
	m_VBO.Push(Vertex(glm::vec2(position.x, position.y),						glm::vec2(((textureCoords.x) * textureScale.x) / m_Texture->width, ((textureCoords.y + 1) * textureScale.y) / m_Texture->height), color));
}

void StaticBatch::bufferData()
{
	m_VAO.Bind();

	m_VBO.BufferData();
	m_EBO.BufferData();
}

void StaticBatch::draw(const glm::mat4& projection, const glm::mat4& view)
{
	m_VAO.Bind();
	//m_VBO.BufferData();
	//m_EBO.BufferData();

	m_Texture->Bind();
	m_Shader->Use();
	m_Shader->SetMat4("projection", projection);
	m_Shader->SetMat4("view", view);

	glDrawElements(GL_TRIANGLES, m_EBO.GetIndexCount(), GL_UNSIGNED_INT, 0);
}

void StaticBatch::flush()
{
	m_VBO.Flush();
	m_EBO.Flush();
}
