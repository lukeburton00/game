#pragma once

#include <vector>

#include "shader.hpp"
#include "texture.hpp"
#include "vertex.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void init();
	void render();

private:
	uint32_t VBO;
	uint32_t VAO;
	uint32_t EBO;
	std::vector<Vertex> vertices;
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Texture> texture2;
};
