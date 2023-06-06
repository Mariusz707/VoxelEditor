#include <Editor/Graphic/Camera.h>

void Camera::createCamera(GLFWwindow* window, float* delta)
{
    m_window = window;
    m_delta = delta;

    m_pos = glm::vec3(0.0f, 0.0f, -4.0f);
    m_view = glm::mat4(1.0f);
    m_projection = glm::mat4(1.0f);
    m_projection = glm::perspective(glm::radians(80.0f), (float)800 / (float)600, 0.1f, 100.0f);
    m_view = glm::translate(m_view, m_pos);

    m_yaw = 90;
    m_pitch = 0;
}

void Camera::update(MouseStatus* mouseStatus)
{
    if (!m_FPPMode)
    {
        if (mouseStatus->m_RMBPressed and (mouseStatus->m_mouseMoveValue[0] != 0 or mouseStatus->m_mouseMoveValue[1] != 0))
        {
            float radius = glm::distance(m_pos, glm::vec3(0));

            m_yaw += mouseStatus->m_mouseMoveValue[0] / 5.f;
            m_pitch -= mouseStatus->m_mouseMoveValue[1] / 5.f;

            if (m_pitch > 89.0f)
                m_pitch = 89.0f;
            if (m_pitch < -89.0f)
                m_pitch = -89.0f;

            m_pos.x = -cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)) * radius;
            m_pos.y = -sin(glm::radians(m_pitch)) * radius;
            m_pos.z = -sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)) * radius;

        }
    }
    else
    {
        m_yaw += mouseStatus->m_mouseMoveValue[0] / 4.f;
        m_pitch -=  mouseStatus->m_mouseMoveValue[1] / 4.f;

        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;

        glm::vec3 left = glm::normalize(glm::cross(m_direction, glm::vec3(0, 1, 0)));
        glm::vec3 right = glm::normalize(glm::cross(m_direction, glm::vec3(0, 1, 0)));
        glm::vec3 up = glm::normalize(glm::cross(-m_direction, left));
        glm::vec3 down = glm::normalize(glm::cross(-m_direction, left));

        if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
            m_pos += up * 0.05f;
        if (glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            m_pos -= down * 0.05f;
        if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
            m_pos += left * 0.05f;
        if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
            m_pos -= right * 0.05f;
        if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
            m_pos += m_direction * 0.05f;
        if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
            m_pos -= m_direction * 0.05f;

    }

    m_direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_direction.y = sin(glm::radians(m_pitch));
    m_direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_direction = glm::normalize(m_direction);

    moveCameraForward(mouseStatus->m_scrollValue);
    mouseStatus->m_scrollValue = 0.f;

    m_view = glm::lookAt(m_pos,
        m_pos + m_direction,
        glm::vec3(0, 1, 0));

    if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS)
        m_view = glm::lookAt(   m_pos,
                                glm::vec3(0),
                                glm::vec3(0, 1, 0));
    if (mouseStatus->m_MMBPressed)
    {
        changeStatus();
        mouseStatus->MMBChangeStatus(false);
    }

}

void Camera::move(glm::vec3 dir)
{
    m_pos += dir;
}

void Camera::moveDir(glm::vec3 dir)
{
    m_direction += dir;
}

void Camera::moveCameraForward(double dir)
{
    if (dir > 0)
        m_pos += m_direction * 0.5f;
    else if (dir < 0)
        m_pos -= m_direction * 0.5f;
    else;
}


glm::vec3 Camera::getPosition()
{
    return m_pos;
}

glm::vec3 Camera::getDirection()
{
    return m_direction;
}

glm::mat4 Camera::getView()
{
    return m_view;
}

glm::mat4 Camera::getProjection()
{
    return m_projection;
}

void Camera::changeStatus()
{
    if (!m_FPPMode)
    {
        m_FPPMode = true;
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        std::cout << "Current mode: FPP" << std::endl;
    }
    else
    {
        m_FPPMode = false;
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        std::cout << "Current mode: rotate" << std::endl;
    }
}
