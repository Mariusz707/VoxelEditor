#include <Editor/Graphic/Shaders.h>

bool Shaders::loadShader(std::string vertexName, std::string FragmentName)
{
	if (loadVertexShader(vertexName) && loadFragmentShader(FragmentName))
	{
		m_shaderProgram = glCreateProgram();

		std::cout << "Shader load succsefully" << std::endl;

		glAttachShader(m_shaderProgram, m_vertexShader);
		glAttachShader(m_shaderProgram, m_fragmentShader);
		glLinkProgram(m_shaderProgram);

		int success;
		char infoLog[512];
		glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
		if (!success) 
		{
			glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
			return 0;
		}
		else
		{
			std::cout << "Shader compile succsefully" << std::endl;
			return 1;
		}
	}
	else
		return 0;
}

bool Shaders::loadVertexShader(std::string fileName)
{
	std::ifstream file(fileName);

	if (file.good())
	{
		std::string shader((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());

		const char* shaderr = shader.c_str();

		m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(m_vertexShader, 1, &shaderr, NULL);
		glCompileShader(m_vertexShader);

		int success;
		char infoLog[512];
		glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(m_vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
				infoLog << std::endl;

			return 0;
		}

		return 1;
	}
	else
	{
		std::cout << "Failed to load vertex shader: " << fileName << std::endl;

		return 0;
	}
	

}

bool Shaders::loadFragmentShader(std::string fileName)
{
	std::ifstream file(fileName);

	if (file.good())
	{
		std::string shader((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());

		const char* shaderr = shader.c_str();

		m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(m_fragmentShader, 1, &shaderr, NULL);
		glCompileShader(m_fragmentShader);

		int success;
		char infoLog[512];
		glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(m_fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::FRAGMENT::VERTEX::COMPILATION_FAILED\n" <<
				infoLog << std::endl;

			return 0;
		}

		return 1;
	}
	else
	{
		std::cout << "Failed to load fragment shader: " << fileName << std::endl;

		return 0;
	}
}

unsigned int Shaders::getShaderProgram()
{
	return m_shaderProgram;
}
