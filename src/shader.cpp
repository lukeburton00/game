#include "shader.hpp"

#include <sstream>
#include <fstream>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "log.hpp"

Shader::Shader(uint32_t id)
{
	mID = id;
}

Shader::~Shader()
{
	glDeleteProgram(mID);
}

void Shader::Use() const
{
	glUseProgram(mID);
}

void Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(mID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(mID, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(mID, name.c_str()), value);
}

void Shader::SetVec2(const std::string& name, glm::vec2 value) const
{
	glUniform2f(glGetUniformLocation(mID, name.c_str()), value.x, value.y);
}

void Shader::SetVec4(const std::string& name, glm::vec4 value) const
{
	glUniform4f(glGetUniformLocation(mID, name.c_str()), value.x, value.y, value.z, value.w);
}

void Shader::SetMat4(const std::string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

std::shared_ptr<Shader> Shader::LoadFromFile(const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;

	vertexShaderFile.open(vertexPath);
	fragmentShaderFile.open(fragmentPath);

	std::stringstream vertexShaderStream, fragmentShaderStream;

	vertexShaderStream << vertexShaderFile.rdbuf();
	fragmentShaderStream << fragmentShaderFile.rdbuf();

	vertexShaderFile.close();
	fragmentShaderFile.close();

	vertexCode = vertexShaderStream.str();
	fragmentCode = fragmentShaderStream.str();

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		LOGERROR("Vertex shader failed to compile: {}", infoLog);
	};

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		LOGERROR("Fragment shader failed to compile: {}", infoLog);
	};

	GLuint shader_id = glCreateProgram();
	glAttachShader(shader_id, vertexShader);
	glAttachShader(shader_id, fragmentShader);
	glLinkProgram(shader_id);

	auto shader = std::make_shared<Shader>(shader_id);

	glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader_id, 512, NULL, infoLog);
		LOGERROR("Shader program failed to link: {}\nVertex shader: {}\n\nFragment shader: {}", infoLog, vertexSource, fragmentSource);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shader;
}