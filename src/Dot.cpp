#include <Editor/Graphic/Dot.h>

Dot::Dot(unsigned int* VAO)
{
	m_dot = glm::vec3(0);
    m_model = glm::mat4(1.0f);

    glGenVertexArrays(1, VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_dot), &m_dot, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Dot::setPosition(glm::vec3 pos)
{
    m_dot = pos;
    m_model = glm::mat4(1.0f);
    m_model = glm::translate(m_model, pos);
}

glm::vec3 Dot::getPosition()
{
	return m_dot;
}

glm::mat4 Dot::getModel()
{
    return m_model;
}

glm::vec3 Dot::getColor()
{
    return m_color;
}
