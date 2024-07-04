#include "renderer.hpp"

#include "GLFW/glfw3.h"

#include "log.hpp"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{
	glDeleteBuffers(1, &VBO);
}

void Renderer::init()
{
	//									position						  color						  texCoord
	vertices.push_back(Vertex(glm::vec3(0.5f, 0.5f, 0.f),		glm::vec3(1.f, 0.f, 0.f),	glm::vec2(1.f, 1.f)));
	vertices.push_back(Vertex(glm::vec3(0.5f, -0.5f, 0.f),		glm::vec3(0.f, 1.f, 0.f),	glm::vec2(1.f, 0.f)));
	vertices.push_back(Vertex(glm::vec3(-0.5f, -0.5f, 0.f),		glm::vec3(0.f, 0.f, 1.f),	glm::vec2(0.f, 0.f)));
	vertices.push_back(Vertex(glm::vec3(-0.5f, 0.5f, 0.f),		glm::vec3(0.f, 0.f, 0.f),	glm::vec2(0.f, 1.f)));

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
}

void Renderer::render()
{
	float timeVal = glfwGetTime();
	float greenValue = (sin(timeVal / 2.f) + 0.5f);
	shader->Use();
	shader->SetVec4("sinColor", glm::vec4(0.f, greenValue, 0.f, 0.f));
	
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}