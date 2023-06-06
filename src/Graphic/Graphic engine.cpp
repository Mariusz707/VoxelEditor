#include <Editor/Graphic/Graphic engine.h>

GraphicEngine::~GraphicEngine()
{
    glfwTerminate();
}

void GraphicEngine::createWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    createMaterials();

    m_window = glfwCreateWindow(800, 600, "Editor", NULL, NULL);

    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
 
    m_voxelShader.loadShader("includes/Editor/Shaders/Perspective.vs", "includes/Editor/Shaders/Colors.fs");
    m_dotShader.loadShader("includes/Editor/Shaders/dotPerspective.vs", "includes/Editor/Shaders/dotColors.fs");
    m_GUIShader.loadShader("includes/Editor/Shaders/GUIPerspective.vs", "includes/Editor/Shaders/GUIColors.fs");
    glfwSwapBuffers(m_window);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);
}

void GraphicEngine::update()
{
}

void GraphicEngine::clear()
{

}

void GraphicEngine::display(VoxelHandler& voxels, Camera& camera)
{
    glUseProgram(m_voxelShader.getShaderProgram());

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    unsigned int modelLoc = glGetUniformLocation(m_voxelShader.getShaderProgram(), "model");
    unsigned int viewLoc = glGetUniformLocation(m_voxelShader.getShaderProgram(), "view");
    unsigned int projectionLoc = glGetUniformLocation(m_voxelShader.getShaderProgram(), "projection");

    unsigned int viewPos = glGetUniformLocation(m_voxelShader.getShaderProgram(), "viewPos");

    unsigned int voxelAmbient = glGetUniformLocation(m_voxelShader.getShaderProgram(),      "material.ambient");
    unsigned int voxelDiffuse = glGetUniformLocation(m_voxelShader.getShaderProgram(),      "material.diffuse");
    unsigned int voxelSpecular = glGetUniformLocation(m_voxelShader.getShaderProgram(),     "material.specular");
    unsigned int voxelShininess = glGetUniformLocation(m_voxelShader.getShaderProgram(),    "material.shininess");

    unsigned int sunDirection = glGetUniformLocation(m_voxelShader.getShaderProgram(),      "sunLight.direction");
    unsigned int sunAmbient = glGetUniformLocation(m_voxelShader.getShaderProgram(),        "sunLight.ambient");
    unsigned int sunDiffuse = glGetUniformLocation(m_voxelShader.getShaderProgram(),        "sunLight.diffuse");
    unsigned int sunSpecular = glGetUniformLocation(m_voxelShader.getShaderProgram(),       "sunLight.specular");

    // Multiple point lights

    unsigned int lightsSize = glGetUniformLocation(m_voxelShader.getShaderProgram(), "lightsSize");
    glUniform1i(lightsSize, voxels.getAllLights().size());

    for (int i = 0; i < voxels.getAllLights().size(); i++)
    {
        unsigned int lightPosistion =   glGetUniformLocation(m_voxelShader.getShaderProgram(), std::string("pointLights[" + std::to_string(i) + "].position").c_str());
        unsigned int lightAmbient =     glGetUniformLocation(m_voxelShader.getShaderProgram(), std::string("pointLights[" + std::to_string(i) + "].ambient").c_str());
        unsigned int lightDiffuse =     glGetUniformLocation(m_voxelShader.getShaderProgram(), std::string("pointLights[" + std::to_string(i) + "].diffuse").c_str());
        unsigned int lightSpecular =    glGetUniformLocation(m_voxelShader.getShaderProgram(), std::string("pointLights[" + std::to_string(i) + "].specular").c_str());
        unsigned int lightConstant =    glGetUniformLocation(m_voxelShader.getShaderProgram(), std::string("pointLights[" + std::to_string(i) + "].constant").c_str());
        unsigned int lightLinear =      glGetUniformLocation(m_voxelShader.getShaderProgram(), std::string("pointLights[" + std::to_string(i) + "].linear").c_str());
        unsigned int lightQuadratic =   glGetUniformLocation(m_voxelShader.getShaderProgram(), std::string("pointLights[" + std::to_string(i) + "].quadratic").c_str());

        glUniform3fv(lightPosistion, 1, &(voxels.getAllLights()[i].getPosition()[0]));
        glUniform3fv(lightAmbient, 1, &(voxels.getAllLights()[i].getAmbient()[0]));
        glUniform3fv(lightDiffuse, 1, &(voxels.getAllLights()[i].getDiffuse()[0]));
        glUniform3fv(lightSpecular, 1, &(voxels.getAllLights()[i].getSpecular()[0]));
        glUniform1f(lightConstant, voxels.getAllLights()[i].getConstant());
        glUniform1f(lightLinear, voxels.getAllLights()[i].getLinear());
        glUniform1f(lightQuadratic, voxels.getAllLights()[i].getQuadratic());
    }


    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &camera.getView()[0][0]);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &camera.getProjection()[0][0]);

    glUniform3fv(viewPos, 1, &camera.getPosition()[0]);
    
    glUniform3fv(sunDirection, 1, &voxels.getSun()->getDirection()[0]);
    glUniform3fv(sunAmbient, 1, &voxels.getSun()->getAmbient()[0]);
    glUniform3fv(sunDiffuse, 1, &voxels.getSun()->getDiffuse()[0]);
    glUniform3fv(sunSpecular, 1, &voxels.getSun()->getSpecular()[0]);

    glEnable(GL_DEPTH_TEST);
    glm::vec3 tmp(0.210, 0.85, 0.342);
    glm::vec3 tmp0(0.0210, 0.085, 0.0342);

    if (voxels.getAllVoxels().size() != 0)
    {
        for (int i = 0; i < voxels.getAllVoxels().size(); i++)
        {
            glUniform3fv(voxelAmbient, 1, &(tmp[0]));
            glUniform3fv(voxelDiffuse, 1, &(tmp0[0]));
            glUniform3fv(voxelSpecular, 1, &(m_materials[voxels.getAllVoxels()[i].getMaterialID()]->m_specular[0]));
            glUniform1f(voxelShininess, m_materials[voxels.getAllVoxels()[i].getMaterialID()]->m_ambient[0] * 128);

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &(voxels.getAllVoxels()[i].getModel()[0][0]));

            glBindVertexArray(m_dynamicVoxelVAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }

    glUseProgram(m_dotShader.getShaderProgram());

    modelLoc = glGetUniformLocation(m_dotShader.getShaderProgram(), "model");
    viewLoc = glGetUniformLocation(m_dotShader.getShaderProgram(), "view");
    projectionLoc = glGetUniformLocation(m_dotShader.getShaderProgram(), "projection");
    unsigned int color = glGetUniformLocation(m_dotShader.getShaderProgram(), "color");

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &camera.getView()[0][0]);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &camera.getProjection()[0][0]);

    for (int i = 0; i < voxels.getAllLights().size(); i++)
    {
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &(voxels.getAllLights()[i].getModel()[0][0]));
        glUniform3fv(color, 1, &(voxels.getAllLights()[i].getColor()[0]));

        glBindVertexArray(m_lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glDisable(GL_DEPTH_TEST);

    for (int i = 0; i < voxels.getAllDots().size(); i++)
    {
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &(voxels.getAllDots()[i].getModel()[0][0]));
        glUniform3fv(color, 1, &(voxels.getAllDots()[i].getColor()[0]));

        glBindVertexArray(m_dotVAO);
        glDrawArrays(GL_POINTS, 0, 1);
    }
    //  GUI

    glUseProgram(m_GUIShader.getShaderProgram());
    projectionLoc = glGetUniformLocation(m_GUIShader.getShaderProgram(), "projection");
    modelLoc = glGetUniformLocation(m_GUIShader.getShaderProgram(), "model");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &(voxels.getGUI()->getModel()[0][0]));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &camera.getProjection()[0][0]);

    glBindTexture(GL_TEXTURE_2D, *voxels.getGUI()->getTexture());
    glBindVertexArray(m_GUIVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void GraphicEngine::createMaterials()
{
    m_materials[0] = new Material(glm::vec3(0.0215, 0.1745, 0.0215),    glm::vec3(0.07568, 0.61424, 0.07568),   glm::vec3(0.633, 0.727811, 0.633), 0.6);
    m_materials[1] = new Material(glm::vec3(0.135,  0.2225, 0.1575),    glm::vec3(0.54, 0.89, 0.63),            glm::vec3(0.316228, 0.316228, 0.316228), 0.1);
    m_materials[2] = new Material(glm::vec3(0.05375, 0.05, 0.06625),    glm::vec3(0.18275, 0.17, 0.22525),      glm::vec3(0.332741, 0.328634, 0.346435), 0.3);
    m_materials[3] = new Material(glm::vec3(0.25,   0.20725, 0.20725),  glm::vec3(1, 0.829, 0.829),             glm::vec3(0.296648, 0.296648, 0.296648), 0.088);
    m_materials[4] = new Material(glm::vec3(0.1745, 0.01175, 0.01175),  glm::vec3(0.61424, 0.04136, 0.04136),   glm::vec3(0.727811, 0.626959, 0.626959), 0.6);
    m_materials[5] = new Material(glm::vec3(0.1,    0.18725, 0.1745),   glm::vec3(0.396, 0.74151, 0.69102),     glm::vec3(0.297254, 0.30829, 0.306678), 0.1);
    m_materials[6] = new Material(glm::vec3(0.2125, 0.1275, 0.054),     glm::vec3(0.714, 0.4284, 0.18144),      glm::vec3(0.393548, 0.271906, 0.166721), 0.2);
    m_materials[7] = new Material(glm::vec3(0.25,   0.25, 0.25),        glm::vec3(0.4, 0.4, 0.4),               glm::vec3(0.774597, 0.774597, 0.774597), 0.6);
    m_materials[8] = new Material(glm::vec3(0.19125, 0.0735, 0.0225),   glm::vec3(0.7038, 0.27048, 0.0828),     glm::vec3(0.256777, 0.137622, 0.086014), 0.1);
    m_materials[9] = new Material(glm::vec3(0.24725, 0.1995, 0.0745),   glm::vec3(0.75164, 0.60648, 0.22648),   glm::vec3(0.628281, 0.555802, 0.366065), 0.4);
    m_materials[10] = new Material(glm::vec3(0.19225, 0.19225, 0.19225), glm::vec3(0.50754, 0.50754, 0.50754),  glm::vec3(0.508273, 0.508273, 0.508273), 0.4);
}

int GraphicEngine::isOpen()
{
    return glfwWindowShouldClose(m_window);
}

unsigned int* GraphicEngine::getDynamicVoxelVAO()
{
    return &m_dynamicVoxelVAO;
}

unsigned int* GraphicEngine::getStaticVoxelVAO()
{
    return &m_staticVoxelVAO;
}

unsigned int* GraphicEngine::getDotVAO()
{
    return &m_dotVAO;
}

unsigned int* GraphicEngine::getLightVAO()
{
    return &m_lightVAO;
}

unsigned int* GraphicEngine::getGUIVAO()
{
    return &m_GUIVAO;
}

GLFWwindow* GraphicEngine::getWindow()
{
    return m_window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
