#include <Editor/Graphic/Voxel.h>

Voxel::Voxel(unsigned int* VAO)
{
    m_position = glm::vec3(0);
    m_model = glm::mat4(1.0f);

    // size of voxel
    float vertices[] = {
        // back face
        -0.1f, -0.1f, -0.1f, 0.0f,  0.0f, 	-1.0f,
        0.1f, 0.1f, -0.1f, 0.0f,  0.0f, 	-1.0f,
        0.1f, -0.1f, -0.1f, 0.0f,  0.0f, 	-1.0f,
        0.1f, 0.1f, -0.1f, 0.0f,  0.0f, 	-1.0f,
        -0.1f, -0.1f, -0.1f, 0.0f,  0.0f, 	-1.0f,
        -0.1f, 0.1f, -0.1f, 0.0f,  0.0f, 	-1.0f,
        // front face
        -0.1f, -0.1f, 0.1f,   0.0f,  0.0f, 	 1.0f,
        0.1f, -0.1f, 0.1f,   0.0f,  0.0f, 	 1.0f,
        0.1f, 0.1f, 0.1f,   0.0f,  0.0f, 	 1.0f,
        0.1f, 0.1f, 0.1f,   0.0f,  0.0f, 	 1.0f,
        -0.1f, 0.1f, 0.1f,   0.0f,  0.0f, 	 1.0f,
        -0.1f, -0.1f, 0.1f,   0.0f,  0.0f, 	 1.0f,
        // left face
        -0.1f, 0.1f, 0.1f,  -1.0f,  0.0f, 	 0.0f,
        -0.1f, 0.1f, -0.1f,  -1.0f,  0.0f, 	 0.0f,
        -0.1f, -0.1f, -0.1f,  -1.0f,  0.0f,  0.0f,
        -0.1f, -0.1f, -0.1f,  -1.0f,  0.0f,  0.0f,
        -0.1f, -0.1f, 0.1f,  -1.0f,  0.0f, 	 0.0f,
        -0.1f, 0.1f, 0.1f,  -1.0f,  0.0f, 	 0.0f,
        // right face
        0.1f, 0.1f, 0.1f,   1.0f,  0.0f, 	 0.0f,
        0.1f, -0.1f, -0.1f,   1.0f,  0.0f, 	 0.0f,
        0.1f, 0.1f, -0.1f,   1.0f,  0.0f, 	 0.0f,
        0.1f, -0.1f, -0.1f,   1.0f,  0.0f, 	 0.0f,
        0.1f, 0.1f, 0.1f,   1.0f,  0.0f, 	 0.0f,
        0.1f, -0.1f, 0.1f,   1.0f,  0.0f, 	 0.0f,
        // bottom face
        -0.1f, -0.1f, -0.1f, 0.0f, -1.0f, 	 0.0f,
        0.1f, -0.1f, -0.1f, 0.0f, -1.0f, 	 0.0f,
        0.1f, -0.1f, 0.1f, 0.0f, -1.0f, 	 0.0f,
        0.1f, -0.1f, 0.1f, 0.0f, -1.0f, 	 0.0f,
        -0.1f, -0.1f, 0.1f, 0.0f, -1.0f, 	 0.0f,
        -0.1f, -0.1f, -0.1f, 0.0f, -1.0f, 	 0.0f,
        // top face
        -0.1f, 0.1f, -0.1f,   0.0f,  1.0f, 	 0.0f,
        0.1f, 0.1f, 0.1f,   0.0f,  1.0f, 	 0.0f,
        0.1f, 0.1f, -0.1f,   0.0f,  1.0f, 	 0.0f,
        0.1f, 0.1f, 0.1f,   0.0f,  1.0f, 	 0.0f,
        -0.1f, 0.1f, -0.1f,   0.0f,  1.0f, 	 0.0f,
        -0.1f, 0.1f, 0.1f,  0.0f,  1.0f, 	 0.0f
    };


    //walls and cornes of walls
    int tmp = 0;
    for (int j = 0; j < 36*6; j += 6)
    {
        if (j == 18 or j == 24 or 
            j == 54 or j == 66 or
            j == 90 or j == 102 or
            j == 126 or j == 132 or
            j == 162 or j == 174 or
            j == 198 or j == 204)
            ;
        else
        {
            //std::cout << "sciana nr: " << tmp / 4 << " --- corner nr: " << tmp % 4 << "    " << j << " " << vertices[j] << " --- " << j + 1 << " " << vertices[j + 1] << " --- " << j + 2 << " " << vertices[j + 2] << std::endl;
            m_walls[tmp / 4].corner[tmp % 4] = glm::vec3(vertices[j], vertices[j + 1], vertices[j + 2]);
            tmp++;
        }
    }

    glGenVertexArrays(1, VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

glm::vec3 Voxel::getPosition()
{
    return m_position;
}

void Voxel::setPosition(glm::vec3 pos)
{
    glm::vec3 moveDir = pos - m_position;
    m_position = pos;
    m_model = glm::mat4(1.0f);

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            m_walls[i].corner[j] += moveDir;
        }
        m_walls[i].calibrate();
    }
    
    calibrate();
    m_model = glm::translate(m_model, m_position);
}


glm::mat4 Voxel::getModel()
{
    return m_model;
}

glm::vec3 Voxel::getColor()
{
    return m_color;
}

Walls* Voxel::getWalls()
{
    return m_walls;
}

glm::vec3 Voxel::getMax()
{
    return m_max;
}

glm::vec3 Voxel::getMin()
{
    return m_min;
}

void Voxel::setMaterialID(MATERIAL_ID materialID)
{
    m_materialID = materialID;
}

MATERIAL_ID Voxel::getMaterialID()
{
    return m_materialID;
}

void Voxel::calibrate()
{
    // they must have some value
    m_max = glm::vec3(-100000000);
    m_min = glm::vec3(100000000);


    //max's and min's of coordinates
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (m_max.x < m_walls[i].corner[j].x)
                m_max.x = m_walls[i].corner[j].x;

            if (m_max.y < m_walls[i].corner[j].y)
                m_max.y = m_walls[i].corner[j].y;

            if (m_max.z < m_walls[i].corner[j].z)
                m_max.z = m_walls[i].corner[j].z;

            if (m_min.x > m_walls[i].corner[j].x)
                m_min.x = m_walls[i].corner[j].x;

            if (m_min.y > m_walls[i].corner[j].y)
                m_min.y = m_walls[i].corner[j].y;

            if (m_min.z > m_walls[i].corner[j].z)
                m_min.z = m_walls[i].corner[j].z;
        }
    }

 /*   std::cout << "xMax: " << m_max.x << std::endl;
    std::cout << "xMin: " << m_min.x << std::endl;

    std::cout << "yMax: " << m_max.y << std::endl;
    std::cout << "yMin: " << m_min.y << std::endl;

    std::cout << "zMax: " << m_max.z << std::endl;
    std::cout << "zMin: " << m_min.z << std::endl;*/
}

void Voxel::setColor(glm::vec3 color)
{
    m_color = color;
}

void Walls::calibrate()
{
    // they must have some value
    m_max = glm::vec3(-100000000);
    m_min = glm::vec3(100000000);


    //max's and min's of coordinates
    for (int j = 0; j < 4; j++)
    {
        if (m_max.x < corner[j].x)
            m_max.x = corner[j].x;

        if (m_max.y < corner[j].y)
            m_max.y = corner[j].y;

        if (m_max.z < corner[j].z)
            m_max.z = corner[j].z;

        if (m_min.x > corner[j].x)
            m_min.x = corner[j].x;

        if (m_min.y > corner[j].y)
            m_min.y = corner[j].y;

        if (m_min.z > corner[j].z)
            m_min.z = corner[j].z;
    }

    m_center = (m_max + m_min) / 2.f;
    //std::cout << m_center.x << " --- " << m_center.y << " --- " << m_center.z << std::endl;
}