#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shaders.h"
#include "Inputs.h"

class Camera
{
	public:
		Camera() = default;
		void createCamera(GLFWwindow* window, float* delta);
		void update(MouseStatus* mouseStatus);

		void move(glm::vec3 dir);
		void moveDir(glm::vec3 dir);
		virtual void moveCameraForward(double dir);

		glm::vec3 getPosition();
		glm::vec3 getDirection();
		glm::mat4 getView();
		glm::mat4 getProjection();
		

		void changeStatus();

	private:
		GLFWwindow* m_window = nullptr;
		glm::mat4	m_view;
		glm::mat4	m_projection;

		glm::vec3	m_pos;
		glm::vec3	m_direction;
		float		m_yaw;
		float		m_pitch;

		float*		m_delta;

		bool		m_FPPMode = false;
};

