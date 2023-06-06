#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

class Light
{
	public:

		Light() = default;
		Light(unsigned int* VAO);

		void setPosition(glm::vec3 pos);
		void setColor(glm::vec3 color);
		glm::vec3 getPosition();
		glm::vec3 getColor();

		void setDirection(glm::vec3 direction);
		void setAmbient(glm::vec3	ambient);
		void setDiffuse(glm::vec3	diffuse);
		void setSpecular(glm::vec3	specular);
		void setConstant(float		constant);
		void setLinear(float		linear);
		void setQuadratic(float		quadratic);

		glm::mat4 getModel();
		glm::vec3 getDirection();
		glm::vec3 getAmbient();
		glm::vec3 getDiffuse();
		glm::vec3 getSpecular();
		float getConstant();
		float getLinear();
		float getQuadratic();

	private:

		glm::mat4 m_model;

		glm::vec3	m_position;
		glm::vec3	m_direction;
		glm::vec3	m_ambient;
		glm::vec3	m_diffuse;
		glm::vec3	m_specular;
		float		m_constant;
		float		m_linear;
		float		m_quadratic;

		glm::vec3 m_color = glm::vec3(1.f, 1.f, 1.f);

		unsigned int m_VBO = 0;
};