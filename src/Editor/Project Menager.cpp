#include <Editor/Editor/Project Menager.h>

void ProjectMenager::setProjectName()
{
	//std::cin >> m_projectName;
	m_projectName = "test";
}

bool ProjectMenager::loadFromFile(unsigned int* voxelVao, VoxelHandler* voxelHandler)
{
	m_file.open(m_projectName, std::fstream::in);

	if (m_file.good())
	{
		std::string::size_type shit;

		while (!m_file.eof())
		{
			float tmp[6];
			std::string line;

			for (int i = 0; i < 6; i++)
			{
				std::getline(m_file, line, ',');

				tmp[i] = std::stof(line, &shit);
			}

			voxelHandler->addVoxel(voxelVao, glm::vec3(tmp[0], tmp[1], tmp[2]), MATERIAL_ID::obsidian);
			std::cout << tmp[0] << " - " << tmp[1] << " - " << tmp[2] << "    " << tmp[3] << " - " << tmp[4] << " - " << tmp[5] << std::endl;;
		}

		m_file.close();
	}
	else
		std::cout << "Project loading failed - creating new file" << std::endl;

		return false;
}

bool ProjectMenager::saveToFile(VoxelHandler* voxelHandler)
{
	m_file.open(m_projectName, std::fstream::out);

	for (int i = 0; i < voxelHandler->getAllVoxels().size(); i++)
	{
		std::string line;

		line = std::to_string(voxelHandler->getAllVoxels()[i].getPosition().x); line += ",";
		line += std::to_string(voxelHandler->getAllVoxels()[i].getPosition().y); line += ",";
		line += std::to_string(voxelHandler->getAllVoxels()[i].getPosition().z); line += ",";
		line += std::to_string(voxelHandler->getAllVoxels()[i].getColor().x); line += ",";
		line += std::to_string(voxelHandler->getAllVoxels()[i].getColor().y); line += ",";
		if (i != voxelHandler->getAllVoxels().size() - 1)
		{
			line += std::to_string(voxelHandler->getAllVoxels()[i].getColor().z); line += ",\n";
		}
		else
		{
			line += std::to_string(voxelHandler->getAllVoxels()[i].getColor().z); line += "\n";
		}
		
		m_file << line;
	}

	m_file.close();
	std::cout << "Project is saved successfully" << std::endl;

	return false;
}

bool ProjectMenager::saveAs(VoxelHandler* voxelHandler)
{
	std::cout << "Podaj nazwe pliku do ktorego chcesz zapisac: " << std::endl;
	setProjectName();
	saveToFile(voxelHandler);
	return false;
}
