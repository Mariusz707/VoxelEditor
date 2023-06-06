#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Dot
{
	public:

		Dot() = default;
		Dot(unsigned int* VAO);

		void setPosition(glm::vec3 pos);
		glm::vec3 getPosition();
		glm::mat4 getModel();
		glm::vec3 getColor();

	private:

		glm::vec3 m_dot;

		glm::vec3 m_color = glm::vec3(0.f, 1.f, 0.f);
		glm::mat4 m_model;

		unsigned int m_VBO = 1;

};

