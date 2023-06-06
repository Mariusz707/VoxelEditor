#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "Voxel handler.h"

class ProjectMenager
{
	public:

		ProjectMenager() = default;

		void setProjectName();
		bool loadFromFile(unsigned int* voxelVao, VoxelHandler* voxelHandler);
		bool saveToFile(VoxelHandler* voxelHandler);
		bool saveAs(VoxelHandler* voxelHandler);

	private:

		std::string	 m_projectName;

		std::fstream m_file;
};

