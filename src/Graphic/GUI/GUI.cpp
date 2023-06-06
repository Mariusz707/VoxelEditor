#define STB_IMAGE_IMPLEMENTATION

#include <Editor/Graphic/GUI/GUI.h>

GUI::GUI(unsigned int* VAO)
{
	m_position = glm::vec3(0);
	m_model = glm::mat4(1.0f);
    m_model = glm::translate(m_model, m_position);

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	// set the texture wrapping/filtering options (on currently bound texture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load("Assets/GUI/addIcon.png", &width, &height,
		&nrChannels, 3);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
			GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	//stbi_image_free(data);

    float vertices[] = {
        // pos             // tex
        -1.0f, 1.0f,     0.0f, 1.0f,
        1.0f, -1.0f,     1.0f, 0.0f,
        -1.0f, -1.0f,     0.0f, 0.0f,

        -1.0f, 1.0f,     0.0f, 1.0f,
        1.0f, 1.0f,     1.0f, 1.0f,
        1.0f, -1.0f,     1.0f, 0.0f
    };

    glGenVertexArrays(1, VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GUI::update()
{
}

glm::vec3 GUI::getPosition()
{
	return m_position;
}

glm::mat4 GUI::getModel()
{
	return m_model;
}

unsigned int* GUI::getTexture()
{
	return &m_texture;
}
