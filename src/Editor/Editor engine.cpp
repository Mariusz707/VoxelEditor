#include <Editor/Editor/Editor engine.h>

void EditorEngine::run()
{
	m_graphicEngine.createWindow();
	m_camera.createCamera(m_graphicEngine.getWindow(), &m_delta);
	m_inputs = Inputs(m_graphicEngine.getWindow());

	m_voxelHandler = VoxelHandler();
	m_collider = Collider(&m_camera, &m_voxelHandler);

	glfwSetWindowUserPointer(m_graphicEngine.getWindow(), &m_inputs);

	m_voxelHandler.createSun(m_graphicEngine.getLightVAO());
	m_voxelHandler.createGUI(m_graphicEngine.getGUIVAO());

	m_voxelHandler.getSun()->setDirection(glm::vec3(-0.2f, -1.0f, 0.3f)); 
	m_voxelHandler.getSun()->setAmbient(glm::vec3(0.05f, 0.05f, 0.05f));
	m_voxelHandler.getSun()->setDiffuse(glm::vec3(0.6f, 0.6f, 0.6f));
	m_voxelHandler.getSun()->setSpecular(glm::vec3(1.f, 1.f, 1.f));

	m_voxelHandler.addLight(m_graphicEngine.getLightVAO(), glm::vec3(-4, 1, 1));
	m_voxelHandler.getAllLights()[0].setAmbient(glm::vec3(0.05f, 0.05f, 0.05f));
	m_voxelHandler.getAllLights()[0].setDiffuse(glm::vec3(0.9f, 0.9f, 0.9f));
	m_voxelHandler.getAllLights()[0].setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
	m_voxelHandler.getAllLights()[0].setConstant(1.0f);
	m_voxelHandler.getAllLights()[0].setLinear(0.09f);
	m_voxelHandler.getAllLights()[0].setQuadratic(0.064f);

	m_voxelHandler.addLight(m_graphicEngine.getLightVAO(), glm::vec3(-2, 1, -2));
	m_voxelHandler.getAllLights()[0].setAmbient(glm::vec3(0.05f, 0.05f, 0.05f));
	m_voxelHandler.getAllLights()[0].setDiffuse(glm::vec3(0.9f, 0.9f, 0.9f));
	m_voxelHandler.getAllLights()[0].setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
	m_voxelHandler.getAllLights()[0].setConstant(1.0f);
	m_voxelHandler.getAllLights()[0].setLinear(0.09f);
	m_voxelHandler.getAllLights()[0].setQuadratic(0.064f);


	//m_voxelHandler.addVoxel(m_graphicEngine.getVoxelVAO(), glm::vec3(0, 0, 0), glm::vec3(1.f, 0.f, 0.f));
	//m_voxelHandler.addVoxel(m_graphicEngine.getVoxelVAO(), glm::vec3(1, 1, 1), glm::vec3(1.f, 0.f, 0.f));
	//m_voxelHandler.addVoxel(m_graphicEngine.getVoxelVAO(), glm::vec3(-1, -1, -1), glm::vec3(1.f, 0.f, 0.f));
	//m_voxelHandler.addVoxel(m_graphicEngine.getVoxelVAO(), glm::vec3(1, -1, 1), glm::vec3(1.f, 0.f, 0.f));


	//m_voxelHandler.addVoxel(m_graphicEngine.getVoxelVAO(), glm::vec3(1, -1, 1),	glm::vec3(1.0f, 0.0f, 0.0f));
	//m_voxelHandler.addVoxel(m_graphicEngine.getVoxelVAO(), glm::vec3(1, -1, -1),	glm::vec3(1.0f, 0.0f, 0.0f));
	//m_voxelHandler.addVoxel(m_graphicEngine.getVoxelVAO(), glm::vec3(-1, -1, 1),	glm::vec3(1.0f, 0.0f, 0.0f));
	//m_voxelHandler.addVoxel(m_graphicEngine.getVoxelVAO(), glm::vec3(-1, -1, -1),	glm::vec3(1.0f, 0.0f, 0.0f));

	//m_voxelHandler.addVoxel(m_graphicEngine.getVoxelVAO(), glm::vec3(1, 1, 1),	glm::vec3(1.0f, 0.0f, 0.0f));
	//m_voxelHandler.addVoxel(m_graphicEngine.getVoxelVAO(), glm::vec3(1, 1, -1),	glm::vec3(1.0f, 0.0f, 0.0f));
	//m_voxelHandler.addVoxel(m_graphicEngine.getVoxelVAO(), glm::vec3(-1, 1, 1),	glm::vec3(1.0f, 0.0f, 0.0f));
	//m_voxelHandler.addVoxel(m_graphicEngine.getVoxelVAO(), glm::vec3(-1, 1, -1),	glm::vec3(1.0f, 0.0f, 0.0f));

	m_voxelHandler.addDot(m_graphicEngine.getDotVAO(), glm::vec3(0));
	m_voxelHandler.addDot(m_graphicEngine.getDotVAO(), glm::vec3(0));
	m_voxelHandler.addDot(m_graphicEngine.getDotVAO(), glm::vec3(0));
	m_voxelHandler.addDot(m_graphicEngine.getDotVAO(), glm::vec3(0));

	m_projectMenager.setProjectName();
	m_projectMenager.loadFromFile(m_graphicEngine.getDynamicVoxelVAO(), &m_voxelHandler);

	while (!m_graphicEngine.isOpen())
	{
		//Input 
		processInputs(m_graphicEngine.getWindow());
		//Game
		update();
		resolveCollsions();
		//Camera
		m_camera.update(m_inputs.getMouseStatus());
		//World
		//GUI
		//AI
		//Audio
		//Render


		m_graphicEngine.update();
		m_graphicEngine.display(m_voxelHandler, m_camera);

		//std::cout << m_inputs.getMouseStatus()->m_scrollValue << std::endl;

		m_delta = (float)glfwGetTime();
		glfwSetTime(0);
		//m_inputs.getMouseStatus()->reset();
	}
}

void EditorEngine::update()
{
}

void EditorEngine::processInputs(GLFWwindow* window)
{
	m_inputs.update();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS and glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		m_projectMenager.saveToFile(&m_voxelHandler);

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS and glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS and glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		m_projectMenager.saveAs(&m_voxelHandler);

	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		m_voxelHandler.getAllLights()[0].setPosition(glm::vec3(-1, 1, 1));

}

void EditorEngine::resolveCollsions()
{
	CollisionID ID = m_collider.checkForCollisions(m_collider.calculateScreenRay(m_inputs.getMouseStatus(), m_camera));

	if (ID.collision == true and m_inputs.getMouseStatus()->m_LMBPressed)
	{
		glm::vec3 wallCenter = m_voxelHandler.getAllVoxels()[ID.closestVoxel].getWalls()[ID.closestWall].m_center - m_voxelHandler.getAllVoxels()[ID.closestVoxel].getPosition();
		glm::vec3 voxelCanter = m_voxelHandler.getAllVoxels()[ID.closestVoxel].getPosition();

		glm::vec3 newVoxelPos = voxelCanter + (wallCenter * 2.f);
		m_voxelHandler.addVoxel(m_graphicEngine.getDynamicVoxelVAO(), newVoxelPos, MATERIAL_ID::obsidian);

		m_inputs.getMouseStatus()->LMBChangeStatus(false);
	}
	if (ID.collision == true and m_inputs.isKeyPressed(GLFW_KEY_2))
	{
		m_voxelHandler.getAllVoxels().erase(m_voxelHandler.getAllVoxels().begin() + ID.closestVoxel);
	}
}
