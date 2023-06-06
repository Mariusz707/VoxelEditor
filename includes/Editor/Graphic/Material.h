#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum MATERIAL_ID
{
	emerald = 0,
	jade,
	obsidian,
	pearl,
	ruby,
	turquoise,
	bronze,
	chrome,
	copper,
	gold,
	silver
};

struct Material
{
	Material() = default;
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
	~Material() = default;

	glm::vec3	m_ambient;
	glm::vec3	m_diffuse;
	glm::vec3	m_specular;
	float		m_shininess;
};

