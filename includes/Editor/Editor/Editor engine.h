#pragma once

#include "Editor/Graphic/Graphic engine.h"
#include "Editor/Editor/Collider.h"
#include "Editor/Editor/Project Menager.h"

class EditorEngine
{
	public:
		void run();
		void update();

		void processInputs(GLFWwindow* window);
		void resolveCollsions();

	private:	

		GraphicEngine	m_graphicEngine;
		Camera			m_camera;
		Inputs			m_inputs;
		VoxelHandler	m_voxelHandler;
		Collider		m_collider;

		ProjectMenager  m_projectMenager;

		int				m_tmp = 0;


		float m_delta = 0;
};