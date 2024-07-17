#include "renderer.hpp"

#include <glad/glad.h>

Renderer::Renderer()
{

}

Renderer::~Renderer()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

void Renderer::init()
{
	//									position						  color						  texCoord
	vertices.push_back(Vertex(glm::vec3(0.5f, 0.5f, 0.f),		glm::vec3(1.f, 0.f, 0.f),	glm::vec2(1.f, 1.f)));
	vertices.push_back(Vertex(glm::vec3(0.5f, -0.5f, 0.f),		glm::vec3(0.f, 1.f, 0.f),	glm::vec2(1.f, 0.f)));
	vertices.push_back(Vertex(glm::vec3(-0.5f, -0.5f, 0.f),		glm::vec3(0.f, 0.f, 1.f),	glm::vec2(0.f, 0.f)));
	vertices.push_back(Vertex(glm::vec3(-0.5f, 0.5f, 0.f),		glm::vec3(1.f, 1.f, 0.f),	glm::vec2(0.f, 1.f)));

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),	(void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),	(void*)offsetof(Vertex, texCoord));
	glEnableVertexAttribArray(2);

	uint32_t indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),	(void*)offsetof(Vertex, position));

	glBindVertexArray(0);

	shader = Shader::LoadFromFile("../../assets/vertex.glsl", "../../assets/fragment.glsl");
	texture = Texture::LoadFromFile("../../assets/container.jpg");
	texture2 = Texture::LoadFromFile("../../assets/awesomeface.jpg");
}

void Renderer::render()
{
	shader->Use();
	shader->SetInt("outTexture", 0);
	shader->SetInt("outTexture2", 1);

	glActiveTexture(GL_TEXTURE0);
	texture->Bind();
	glActiveTexture(GL_TEXTURE1);
	texture2->Bind();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
