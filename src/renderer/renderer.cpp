#include "Renderer.hpp"

#include "shader.hpp"

Renderer::Renderer()
{
	m_viewMatrix = glm::mat4(1.f);
	m_projectionMatrix = glm::mat4(1.f);

}

Renderer::~Renderer()
{
}

void Renderer::init(const std::shared_ptr<EventBus>& eventBus)
{
	m_VAO.Init();
	m_VAO.Bind();
	m_VBO.Init();
	m_EBO.Init();
	m_EBO.Bind();
	m_VAO.Unbind();
	m_Texture = Texture::LoadFromFile("container.jpg");
	m_Texture->Bind();
	m_Shader = Shader::LoadFromFile("batchVertex.glsl", "batchFragment.glsl");
	m_Shader->Use();
}

void Renderer::beginBatch(Camera& camera)
{
	m_projectionMatrix = camera.GetProjectionMatrix();
	m_viewMatrix = camera.GetViewMatrix();
}

void Renderer::pushQuad(glm::vec2 position, glm::vec2 scale, glm::vec4 color, glm::vec2 textureCoords, glm::vec2 textureScale)
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

void Renderer::flush()
{
	m_VAO.Bind();
	m_VBO.BufferData();
	m_EBO.BufferData();

	m_Shader->Use();
	m_Shader->SetMat4("projection", m_projectionMatrix);
	m_Shader->SetMat4("view", m_viewMatrix);

	glDrawElements(GL_TRIANGLES, m_EBO.GetIndexCount(), GL_UNSIGNED_INT, 0);

	m_VAO.Unbind();
	m_VBO.Flush();
	m_EBO.Flush();
}

void Renderer::setTexture(std::shared_ptr<Texture> texture)
{
	m_Texture = texture;
	m_Texture->Bind();
}
