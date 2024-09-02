#pragma once

#include "shader.hpp"
#include "texture.hpp"
#include "gl_vertex_array.hpp"
#include "gl_vertex_buffer.hpp"
#include "gl_element_buffer.hpp"

#include "glm/glm.hpp"
#include "vertex.hpp"

class StaticBatch
{
public:
	StaticBatch();
	~StaticBatch();

	void init(std::shared_ptr<Texture> texture, std::shared_ptr<Shader> shader);

	void push(glm::vec2 position, glm::vec2 scale, glm::vec4 color, glm::vec2 textureCoords, glm::vec2 textureScale);
	void bufferData();
	void draw(const glm::mat4& projection, const glm::mat4& view);
	void flush();

private:
	std::shared_ptr<Shader> m_Shader;
	std::shared_ptr<Texture> m_Texture;

	GLVertexArray m_VAO;
	GLVertexBuffer m_VBO;
	GLElementBuffer m_EBO;
};