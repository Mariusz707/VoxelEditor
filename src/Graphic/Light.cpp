#include <Editor/Graphic/Light.h>

Light::Light(unsigned int* VAO)
{
    m_position = glm::vec3(0);
    m_model = glm::mat4(1.0f);

	float vertices[] = {
		// back face
		-0.1f, -0.1f, -0.1f,
		 0.1f,  0.1f, -0.1f,
		 0.1f, -0.1f, -0.1f,
		 0.1f,  0.1f, -0.1f,
		-0.1f, -0.1f, -0.1f,
		-0.1f,  0.1f, -0.1f,
		// front face
		-0.1f, -0.1f, 0.1f,
		 0.1f, -0.1f, 0.1f,
		 0.1f,  0.1f, 0.1f,
		 0.1f,  0.1f, 0.1f,
		-0.1f,  0.1f, 0.1f,
		-0.1f, -0.1f, 0.1f,
		// left face
		-0.1f, 0.1f, 0.1f,
		-0.1f, 0.1f, -0.1f,
		-0.1f, -0.1f, -0.1f,
		-0.1f, -0.1f, -0.1f,
		-0.1f, -0.1f, 0.1f,
		-0.1f, 0.1f, 0.1f,
		// right face
		0.1f, 0.1f, 0.1f,
		0.1f, -0.1f, -0.1f,
		0.1f, 0.1f, -0.1f,
		0.1f, -0.1f, -0.1f,
		0.1f, 0.1f, 0.1f,
		0.1f, -0.1f, 0.1f,
		// bottom face
		-0.1f, -0.1f, -0.1f,
		0.1f, -0.1f, -0.1f,
		0.1f, -0.1f, 0.1f,
		0.1f, -0.1f, 0.1f,
		-0.1f, -0.1f, 0.1f,
		-0.1f, -0.1f, -0.1f,
		// top face
		-0.1f, 0.1f, -0.1f,
		0.1f, 0.1f, 0.1f,
		0.1f, 0.1f, -0.1f,
		0.1f, 0.1f, 0.1f,
		-0.1f, 0.1f, -0.1f,
		-0.1f, 0.1f, 0.1f
	};


    glGenVertexArrays(1, VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Light::setPosition(glm::vec3 pos)
{
    m_position = pos;
    m_model = glm::mat4(1.0f);

    m_model = glm::translate(m_model, m_position);
}

void Light::setDirection(glm::vec3 direction)
{
    m_direction = direction;
}

void Light::setAmbient(glm::vec3 ambient)
{
    m_ambient = ambient;
}

void Light::setDiffuse(glm::vec3 diffuse)
{
    m_diffuse = diffuse;
}

void Light::setSpecular(glm::vec3 specular)
{
    m_specular = specular;
}

void Light::setConstant(float constant)
{
    m_constant = constant;
}

void Light::setLinear(float linear)
{
    m_linear = linear;
}

void Light::setQuadratic(float quadratic)
{
    m_quadratic = quadratic;
}

void Light::setColor(glm::vec3 color)
{
    m_color = color;
}

glm::vec3 Light::getPosition()
{
    return m_position;
}

glm::mat4 Light::getModel()
{
    return m_model;
}

glm::vec3 Light::getDirection()
{
    return m_direction;
}

glm::vec3 Light::getAmbient()
{
    return m_ambient;
}

glm::vec3 Light::getDiffuse()
{
    return m_diffuse;
}

glm::vec3 Light::getSpecular()
{
    return m_specular;
}

float Light::getConstant()
{
    return m_constant;
}

float Light::getLinear()
{
    return m_linear;
}

float Light::getQuadratic()
{
    return m_quadratic;
}

glm::vec3 Light::getColor()
{
    return m_color;
}
