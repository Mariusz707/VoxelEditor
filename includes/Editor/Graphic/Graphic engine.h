#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>

#include <Editor/Editor/Voxel handler.h>
#include "Shaders.h"
#include "Camera.h"
#include "Voxel.h"
#include "Material.h"
#include "Inputs.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class GraphicEngine
{
	public:
		~GraphicEngine();
		void createWindow();
		void update();
		void clear();
		void display(VoxelHandler& voxels, Camera& camera);

		void createMaterials();

		int isOpen();
		unsigned int* getStaticVoxelVAO();
		unsigned int* getDynamicVoxelVAO();
		unsigned int* getDotVAO();
		unsigned int* getLightVAO();
		unsigned int* getGUIVAO();
		GLFWwindow* getWindow();

	private:
		GLFWwindow* m_window = nullptr;
		Material*	m_materials[11];

		Shaders m_voxelShader;
		Shaders m_dotShader;
		Shaders m_GUIShader;

		unsigned int m_staticVoxelVAO = 0;
		unsigned int m_dynamicVoxelVAO = 1;
		unsigned int m_dotVAO = 2;
		unsigned int m_lightVAO = 3;
		unsigned int m_GUIVAO = 4;
};

