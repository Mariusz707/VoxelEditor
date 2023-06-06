#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Material.h"

#include <iostream>

enum WallDir
{
	back = 0,
	front,
	left,
	right,
	bottom,
	up
};

struct Walls
{
	void calibrate();

	glm::vec3 corner[4];

	glm::vec3	m_min;
	glm::vec3	m_max;
	glm::vec3   m_center;
};

class Voxel
{
	public:

		Voxel() = default;
		Voxel(unsigned int* VAO);

		void setPosition(glm::vec3 pos);
		void setColor(glm::vec3 color);
		glm::vec3 getPosition();
		glm::mat4 getModel();
		glm::vec3 getColor();
		Walls* getWalls();

		glm::vec3 getMax();
		glm::vec3 getMin();

		void setMaterialID(MATERIAL_ID materialID);
		MATERIAL_ID getMaterialID();

		void calibrate();

	private:
		
		Walls		m_walls[6];
		glm::vec3	m_min;
		glm::vec3	m_max;

		glm::vec3	m_position;
		glm::mat4	m_model;

		MATERIAL_ID m_materialID;

		glm::vec3 m_color = glm::vec3(0.f, 0.f, 0.f);

		unsigned int m_VBO = 0;
};

