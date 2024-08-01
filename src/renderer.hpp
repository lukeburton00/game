#pragma once

#include <vector>

#include "shader.hpp"
#include "texture.hpp"
#include "vertex.hpp"
#include "eventBus.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void init(std::shared_ptr<EventBus> eventBus);
	void render();

private:
	uint32_t VBO;
	uint32_t VAO;
	uint32_t EBO;
	uint32_t m_Width;
	uint32_t m_Height;

	float fov;

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	std::vector<Vertex> vertices;
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Texture> texture2;
};
