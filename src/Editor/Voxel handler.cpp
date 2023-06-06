#include <Editor/Editor/Voxel handler.h>

void VoxelHandler::addVoxel(unsigned int* VAO, glm::vec3 pos, MATERIAL_ID id)
{
    m_voxels.push_back(Voxel(VAO));

    m_voxels[m_voxels.size() - 1].setPosition(pos);
    m_voxels[m_voxels.size() - 1].setMaterialID(id);
}

void VoxelHandler::addDot(unsigned int* VAO, glm::vec3 pos)
{
    m_dots.push_back(Dot(VAO));
    m_dots[m_dots.size() - 1].setPosition(pos);
}

void VoxelHandler::addLight(unsigned int* VAO, glm::vec3 pos)
{
    m_lights.push_back(Light(VAO));
    m_lights[m_lights.size() - 1].setPosition(pos);
}

void VoxelHandler::createSun(unsigned int* VAO)
{
    m_sun = Light(VAO);
}

void VoxelHandler::createGUI(unsigned int* VAO)
{
    m_GUI = GUI(VAO);
}

void VoxelHandler::setPositionOfVoxel(int number, glm::vec3 pos)
{
    m_voxels[number].setPosition(pos);
}

void VoxelHandler::setPositionOfDot(int number, glm::vec3 pos)
{
    m_dots[number].setPosition(pos);
}

void VoxelHandler::setPositionOfLight(int number, glm::vec3 pos)
{
    m_lights[number].setPosition(pos);
}

Light* VoxelHandler::getSun()
{
    return &m_sun;
}

GUI* VoxelHandler::getGUI()
{
    return &m_GUI;
}

std::vector<Voxel>& VoxelHandler::getAllVoxels()
{
    return m_voxels;
}

std::vector<Dot>& VoxelHandler::getAllDots()
{
    return m_dots;
}

std::vector<Light>& VoxelHandler::getAllLights()
{
    return m_lights;
}
