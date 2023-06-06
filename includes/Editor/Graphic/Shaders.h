#pragma once

#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Shaders
{
	public:
		bool loadShader(std::string vertexName, std::string FragmentName);
		bool loadVertexShader(std::string fileName);
		bool loadFragmentShader(std::string fileName);

		unsigned int getShaderProgram();

	private:
		unsigned int m_vertexShader;
		unsigned int m_fragmentShader;
		unsigned int m_shaderProgram;
};

