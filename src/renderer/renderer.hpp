#pragma once

#include "eventBus.hpp"
#include "camera.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "gl_vertex_array.hpp"
#include "gl_vertex_buffer.hpp"
#include "gl_element_buffer.hpp"

#include "glm/glm.hpp"
#include "static_batch.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void init(const std::shared_ptr<EventBus>& eventBus);

	void beginBatch(Camera& camera);
	void pushStaticQuad(glm::vec2 position, glm::vec2 scale, glm::vec4 color, glm::vec2 textureCoords, glm::vec2 textureScale);
	void pushQuad(glm::vec2 position, glm::vec2 scale, glm::vec4 color, glm::vec2 texCoords, glm::vec2 textureScale);
	void bufferStaticData();
	void flush();

private:
	void setTexture(std::shared_ptr<Texture> texture);

private:
	std::shared_ptr<StaticBatch> m_StaticBatch;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
	std::shared_ptr<Shader> m_Shader;
	std::shared_ptr<Texture> m_Texture;
};