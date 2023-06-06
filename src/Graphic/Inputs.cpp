#include <Editor/Graphic/Inputs.h>
#include <Editor/Graphic/Camera.h>

Inputs::Inputs(GLFWwindow* window)
{
	m_window = window;
	glfwSetKeyCallback(window, key_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	m_mouseStatus = new MouseStatus();
		
	m_mouseStatus->m_mousePosition = glm::dvec2(0, 0);
	m_mouseStatus->m_mousePrevPosition = glm::dvec2(0, 0);
	m_mouseStatus->m_mouseMoveValue = glm::dvec2(0, 0);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}

bool Inputs::isKeyPressed(unsigned int key)
{
	if (glfwGetKey(m_window, key) == GLFW_PRESS)
	{
		return true;
	}
	else
		return false;
}

void Inputs::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

void Inputs::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Inputs* obj = (Inputs*)glfwGetWindowUserPointer(window);

	obj->getMouseStatus()->setScrollValue(yoffset);
}

void Inputs::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	Inputs* obj = (Inputs*)glfwGetWindowUserPointer(window);

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		obj->getMouseStatus()->RMBChangeStatus(true);
	else
		obj->getMouseStatus()->RMBChangeStatus(false);

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		obj->getMouseStatus()->LMBChangeStatus(true);
	else
		obj->getMouseStatus()->LMBChangeStatus(false);

	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
		obj->getMouseStatus()->MMBChangeStatus(true);
	else
		obj->getMouseStatus()->MMBChangeStatus(false);
}

void Inputs::update()
{
	glfwGetCursorPos(m_window, &m_mouseStatus->m_mousePosition[0], &m_mouseStatus->m_mousePosition[1]);

	if (m_mouseStatus->m_mousePosition != m_mouseStatus->m_mousePrevPosition)
	{
		m_mouseStatus->m_mouseMoveValue = m_mouseStatus->m_mousePosition - m_mouseStatus->m_mousePrevPosition;
		//std::cout << m_mouseMoveValue[0] << " --- " << m_mouseMoveValue[1] << std::endl;
	}
	else
		m_mouseStatus->m_mouseMoveValue = glm::dvec2(0, 0);

	m_mouseStatus->m_mousePrevPosition = m_mouseStatus->m_mousePosition;
}

MouseStatus* Inputs::getMouseStatus()
{
	return m_mouseStatus;
}

void MouseStatus::LMBChangeStatus(bool status)
{
	m_LMBPressed = status;
}

void MouseStatus::RMBChangeStatus(bool status)
{
	m_RMBPressed = status;
}

void MouseStatus::MMBChangeStatus(bool status)
{
	m_MMBPressed = status;
}

void MouseStatus::setScrollValue(double value)
{
	m_scrollValue = value;
}

void MouseStatus::reset()
{
	m_scrollValue = 0;
}
