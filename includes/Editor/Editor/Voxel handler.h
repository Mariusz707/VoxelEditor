#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "Editor/Graphic/Dot.h"
#include "Editor/Graphic/Voxel.h"
#include "Editor/Graphic/Light.h"
#include "Editor/Graphic/GUI/GUI.h"

class VoxelHandler
{
	public:

		void addVoxel(unsigned int* VAO, glm::vec3 pos, MATERIAL_ID id);
		void addDot(unsigned int* VAO, glm::vec3 pos);
		void addLight(unsigned int* VAO, glm::vec3 pos);
		void createSun(unsigned int* VAO);
		void createGUI(unsigned int* VAO);

		void setPositionOfVoxel(int number, glm::vec3 pos);
		void setPositionOfDot(int number, glm::vec3 pos);
		void setPositionOfLight(int number, glm::vec3 pos);

		std::vector<Voxel>& getAllVoxels();
		std::vector<Dot>& getAllDots();
		std::vector<Light>& getAllLights();
		Light* getSun();
		GUI* getGUI();

	private:
		std::vector<Voxel>	m_voxels;
		std::vector<Dot>	m_dots;
		std::vector<Light>	m_lights;
		Light				m_sun;
		GUI					m_GUI;
};

