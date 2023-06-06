#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include "stb_image.h"

class GUI
{
	public:
		GUI() = default;
		GUI(unsigned int* VAO);
		~GUI() = default;

		void update();
		glm::vec3 getPosition();
		glm::mat4 getModel();
		unsigned int* getTexture();

	private:
		glm::vec3		m_position;
		glm::mat4		m_model;
		unsigned int	m_texture;

		unsigned int	m_VBO = 0;
};

