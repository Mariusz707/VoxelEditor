#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

struct MouseStatus
{
	void LMBChangeStatus(bool status);
	void RMBChangeStatus(bool status);
	void MMBChangeStatus(bool status);

	void setScrollValue(double value);
	void reset();

	glm::dvec2	m_mousePosition;
	glm::dvec2	m_mouseMoveValue;
	glm::dvec2  m_mousePrevPosition;

	bool		m_LMBPressed = 0;
	bool		m_RMBPressed = 0;
	bool		m_MMBPressed = 0;

	double		m_scrollValue = 0;
};

class Inputs
{
	public:
		Inputs() = default;
		Inputs(GLFWwindow* window);

		bool isKeyPressed(unsigned int key);

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

		void update();
		MouseStatus* getMouseStatus();

		private:

		GLFWwindow* m_window = nullptr;

		MouseStatus*  m_mouseStatus;
};

