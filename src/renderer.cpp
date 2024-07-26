#include "renderer.hpp"

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "event.hpp"
#include "game.hpp"
#include "input.hpp"
#include "keycodes.hpp"

Renderer::Renderer()
{
    model = glm::mat4(1.f);
    view = glm::mat4(1.f);
    projection = glm::mat4(1.f);

    fov = 10.f;
}

Renderer::~Renderer()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

void Renderer::init()
{
    width = Game::get().getWindow().getWidth();
    height = Game::get().getWindow().getHeight();

    Game::get().getEventManager().subscribe<WindowResizeEvent>([&](const WindowResizeEvent& event)
    {
        width = event.width;
        height = event.height;
        projection = glm::perspective(glm::radians(fov), (float)event.width / (float)event.height, 0.1f, 100.0f);
    });

	//									position						  color						  texCoord
	vertices.push_back(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec3(1.f, 1.f, 1.f),	glm::vec2(0.f, 0.f)));
	vertices.push_back(Vertex(glm::vec3(0.5f, -0.5f, -0.5f),	glm::vec3(1.f, 1.f, 1.f),	glm::vec2(1.f, 0.f)));
	vertices.push_back(Vertex(glm::vec3(0.5f, 0.5f, -0.5f),	    glm::vec3(1.f, 1.f, 1.f),	glm::vec2(1.f, 1.f)));
	vertices.push_back(Vertex(glm::vec3(0.5f, 0.5f, -0.5f),	    glm::vec3(1.f, 1.f, 1.f),	glm::vec2(1.f, 1.f)));
	vertices.push_back(Vertex(glm::vec3(-0.5f, 0.5f, -0.5f),	glm::vec3(1.f, 1.f, 1.f),	glm::vec2(0.f, 1.f)));
	vertices.push_back(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec3(1.f, 1.f, 1.f),	glm::vec2(0.f, 0.f)));

	vertices.push_back(Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),	glm::vec3(1.f, 1.f, 1.f),	glm::vec2(0.f, 0.f)));
	vertices.push_back(Vertex(glm::vec3(0.5f, -0.5f, 0.5f),		glm::vec3(1.f, 1.f, 1.f),	glm::vec2(1.f, 0.f)));
	vertices.push_back(Vertex(glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec3(1.f, 1.f, 1.f),	glm::vec2(1.f, 1.f)));
	vertices.push_back(Vertex(glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec3(1.f, 1.f, 1.f),	glm::vec2(1.f, 1.f)));
	vertices.push_back(Vertex(glm::vec3(-0.5f, 0.5f, 0.5f),		glm::vec3(1.f, 1.f, 1.f),	glm::vec2(0.f, 1.f)));
	vertices.push_back(Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),	glm::vec3(1.f, 1.f, 1.f),	glm::vec2(0.f, 0.f)));

	vertices.push_back(Vertex(glm::vec3(-0.5f, 0.5f, 0.5f),		glm::vec3(1.f, 1.f, 1.f),	glm::vec2(1.f, 0.f)));
	vertices.push_back(Vertex(glm::vec3(-0.5f, 0.5f, -0.5f),	glm::vec3(1.f, 1.f, 1.f),	glm::vec2(1.f, 1.f)));
	vertices.push_back(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec3(1.f, 1.f, 1.f),	glm::vec2(0.f, 1.f)));
	vertices.push_back(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec3(1.f, 1.f, 1.f),	glm::vec2(0.f, 1.f)));
	vertices.push_back(Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),	glm::vec3(1.f, 1.f, 1.f),	glm::vec2(0.f, 0.f)));
	vertices.push_back(Vertex(glm::vec3(-0.5f, 0.5f, 0.5f),		glm::vec3(1.f, 1.f, 1.f),	glm::vec2(1.f, 0.f)));

	vertices.push_back(Vertex(glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec3(1.f, 1.f, 1.f),	glm::vec2(1.f, 0.f)));
	vertices.push_back(Vertex(glm::vec3(0.5f, 0.5f, -0.5f),		glm::vec3(1.f, 1.f, 1.f),	glm::vec2(1.f, 1.f)));
	vertices.push_back(Vertex(glm::vec3(0.5f, -0.5f, -0.5f),	glm::vec3(1.f, 1.f, 1.f),	glm::vec2(0.f, 1.f)));
	vertices.push_back(Vertex(glm::vec3(0.5f, -0.5f, -0.5f),	glm::vec3(1.f, 1.f, 1.f),	glm::vec2(0.f, 1.f)));
	vertices.push_back(Vertex(glm::vec3(0.5f, -0.5f, 0.5f),		glm::vec3(1.f, 1.f, 1.f),	glm::vec2(0.f, 0.f)));
	vertices.push_back(Vertex(glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec3(1.f, 1.f, 1.f),	glm::vec2(1.f, 0.f)));

	vertices.push_back(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec3(1.f, 1.f, 1.f),	glm::vec2(0.f, 1.f)));
	vertices.push_back(Vertex(glm::vec3(0.5f, -0.5f, -0.5f),	glm::vec3(1.f, 1.f, 1.f),	glm::vec2(1.f, 1.f)));
	vertices.push_back(Vertex(glm::vec3(0.5f, -0.5f, 0.5f),		glm::vec3(1.f, 1.f, 1.f),	glm::vec2(1.f, 0.f)));
	vertices.push_back(Vertex(glm::vec3(0.5f, -0.5f, 0.5f),		glm::vec3(1.f, 1.f, 1.f),	glm::vec2(1.f, 0.f)));
	vertices.push_back(Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),	glm::vec3(1.f, 1.f, 1.f),	glm::vec2(0.f, 0.f)));
	vertices.push_back(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec3(1.f, 1.f, 1.f),	glm::vec2(0.f, 1.f)));

	vertices.push_back(Vertex(glm::vec3(-0.5f, 0.5f, -0.5f),	glm::vec3(1.f, 1.f, 1.f),	glm::vec2(0.f, 1.f)));
	vertices.push_back(Vertex(glm::vec3(0.5f, 0.5f, -0.5f),		glm::vec3(1.f, 1.f, 1.f),	glm::vec2(1.f, 1.f)));
	vertices.push_back(Vertex(glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec3(1.f, 1.f, 1.f),	glm::vec2(1.f, 0.f)));
	vertices.push_back(Vertex(glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec3(1.f, 1.f, 1.f),	glm::vec2(1.f, 0.f)));
	vertices.push_back(Vertex(glm::vec3(-0.5f, 0.5f, 0.5f),		glm::vec3(1.f, 1.f, 1.f),	glm::vec2(0.f, 0.f)));
	vertices.push_back(Vertex(glm::vec3(-0.5f, 0.5f, -0.5f),	glm::vec3(1.f, 1.f, 1.f),	glm::vec2(0.f, 1.f)));

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),	(void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),	(void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),	(void*)offsetof(Vertex, texCoord));
	glEnableVertexAttribArray(2);

	uint32_t indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	glEnable(GL_DEPTH_TEST);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),	(void*)offsetof(Vertex, position));

	glBindVertexArray(0);

	shader = Shader::LoadFromFile("vertex.glsl", "fragment.glsl");
	texture = Texture::LoadFromFile("container.jpg");
	texture2 = Texture::LoadFromFile("awesomeface.jpg");

	shader->Use();
	shader->SetInt("outTexture", 0);
	shader->SetInt("outTexture2", 1);

	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 100.0f);
}

void Renderer::render()
{
    if (Input::isKeyPressed(Input::KeyCode::W))
    {
        fov++;
        LOGINFO(fov);
    }

    if (Input::isKeyPressed(Input::KeyCode::S))
    {
        fov--;
        LOGINFO(fov);
    }

    std::vector<glm::vec3> cubePositions = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, 15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, 12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, 5.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, 1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

   	glBindVertexArray(VAO);
   	shader->Use();

   	shader->SetMat4("view", view);

   	projection = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 100.0f);
   	shader->SetMat4("projection", projection);

   	glActiveTexture(GL_TEXTURE0);
   	texture->Bind();
   	glActiveTexture(GL_TEXTURE1);
   	texture2->Bind();


    for (int i = 0; i < 10; i++)
    {
        model = glm::mat4(1.f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.f, 1.f, 0.f));
       	model = glm::translate(model, cubePositions[i]);

       	shader->SetMat4("model", model);
       	glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glBindVertexArray(0);
}
