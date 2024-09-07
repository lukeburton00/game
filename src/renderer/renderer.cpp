#include "renderer.hpp"

#include "shader.hpp"

Renderer::Renderer()
{
	m_viewMatrix = glm::mat4(1.f);
	m_projectionMatrix = glm::mat4(1.f);
	m_StaticBatch = std::make_shared<StaticBatch>();
}

Renderer::~Renderer()
{
}

void Renderer::init(const std::shared_ptr<EventBus>& eventBus)
{
	m_Texture = Texture::LoadFromFile("container.jpg");
	m_Shader = Shader::LoadFromFile("batchVertex.glsl", "batchFragment.glsl");

	m_StaticBatch->init(m_Texture, m_Shader);
}

void Renderer::beginBatch(Camera& camera)
{
	m_projectionMatrix = camera.GetProjectionMatrix();
	m_viewMatrix = camera.GetViewMatrix();
}

void Renderer::pushStaticQuad(glm::vec2 position, glm::vec2 scale, glm::vec4 color, glm::vec2 textureCoords, glm::vec2 textureScale)
{
	m_StaticBatch->push(position, scale, color, textureCoords, textureScale);
}

void Renderer::pushQuad(glm::vec2 position, glm::vec2 scale, glm::vec4 color, glm::vec2 textureCoords, glm::vec2 textureScale)
{

}

void Renderer::bufferStaticData()
{
	m_StaticBatch->bufferData();
}

void Renderer::flush()
{
	m_StaticBatch->draw(m_projectionMatrix, m_viewMatrix);
}

void Renderer::setTexture(std::shared_ptr<Texture> texture)
{
	m_Texture = texture;
	m_Texture->Bind();
}
