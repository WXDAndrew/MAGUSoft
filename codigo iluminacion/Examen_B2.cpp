#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

#include <iostream>
//#include <vector>
#include <thread>   // Para std::this_thread::sleep_for
#include <chrono>   // Para std::chrono::milliseconds

#define STB_IMAGE_IMPLEMENTATION 
#include <learnopengl/stb_image.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//Linterna encendida
glm::vec3 lightF(1.0f, 1.0f, 1.0f); // Color de la luz por defecto
bool lightOn = true; // Estado de la luz


int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Exercise 16 Task 3", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(false);

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // build and compile shaders
    Shader ourShader("shaders/modelo_vertexshader.vs", "shaders/modelo_fragmentshader.fs");
    //Shader lCShader("shaders/lightcube_vertexshader_B2.vs", "shaders/lightcube_fragmentshader_B2.fs");

    // load models
    Model ourModel("C:/Users/Det-Pc/Desktop/Computacion Grafica/OpenGL/OpenGL/model/lamp4/lamp4.obj");

    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // lighting
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    glm::vec3 dirLightDirection(5005.0f, 5005.0f, -5000.0f);
    glm::vec3 pointLightPositions[] = {
        glm::vec3(-0.0266329, 5.87273, 0.0155637),
        glm::vec3(10.0029, 5.6068, 0.0120746),
        glm::vec3(0.0, 50000.0, 0.0),
        glm::vec3(0.0, 50000.0, 0.0)
    };

    camera.MovementSpeed = 1; //Optional. Modify the speed of the camera
    glm::vec3 lastCameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
   
    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(window);

        // render
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // don't forget to enable shader before setting uniforms
        ourShader.use();

        // set material properties
        //ourShader.setInt("material.diffuse", 0);
        //ourShader.setInt("material.specular", 1);
        ourShader.setVec3("viewPos", camera.Position);
        ourShader.setFloat("material.shininess", 32.0f);

        // set light properties
        
        // directional light ******LUZ DE LA LUNA
        ourShader.setVec3("dirLight.direction", dirLightDirection);
        ourShader.setVec3("dirLight.ambient", 0.1f, 0.1f, 0.1f);  ///AUMENTAR VALORES PARA MAS BRILLO AMBIENTAL
        ourShader.setVec3("dirLight.diffuse", 0.1f, 0.1f, 0.1f);
        ourShader.setVec3("dirLight.specular", 0.2f, 0.2f, 0.5f);
        
         
        // point lights****PARA LAS LAMPARAS
        for (unsigned int i = 0; i < 4; i++)
        {
            ourShader.setVec3("pointLights[" + std::to_string(i) + "].position", pointLightPositions[i]);
            ourShader.setVec3("pointLights[" + std::to_string(i) + "].ambient", 0.0f, 0.0f, 0.0f);
            ourShader.setVec3("pointLights[" + std::to_string(i) + "].diffuse", 1.0f, 1.0f, 1.0f);
            ourShader.setVec3("pointLights[" + std::to_string(i) + "].specular", 1.0f, 1.0f, 1.0f);
            ourShader.setFloat("pointLights[" + std::to_string(i) + "].constant", 0.5f);
            ourShader.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.009f);
            ourShader.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.0032f);
        }
        
        // spotlight******LINTERNA
        ourShader.setVec3("spotLight.position", camera.Position);
        ourShader.setVec3("spotLight.direction", camera.Front);
        ourShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        ourShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
        ourShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        ourShader.setVec3("spotLight.diffuse", lightF);
        ourShader.setVec3("spotLight.specular", lightF);
        ourShader.setFloat("spotLight.constant", 1.0f);
        ourShader.setFloat("spotLight.linear", 0.009f);
        ourShader.setFloat("spotLight.quadratic", 0.0032f);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        
        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));    // it's a bit too big for our scene, so scale it down
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);

        glm::mat4 model2 = glm::mat4(1.0f);
        model2 = glm::translate(model2, glm::vec3(10.0f, 0.0f, 0.0f)); // translate it to a different position
        model2 = glm::scale(model2, glm::vec3(2.0f, 2.0f, 2.0f));    // scale it down
        ourShader.setMat4("model", model2);
        ourModel.Draw(ourShader);
        
        // Print the camera position
        //printCameraPosition(camera);
        

        if (camera.Position != lastCameraPos)
        {
            std::cout << "Camera Position: ("
                << camera.Position.x << ", "
                << camera.Position.y << ", "
                << camera.Position.z << ")\n";
            lastCameraPos = camera.Position;
        }
        /*
        // also draw the lamp object
        lightCubeShader.use();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightCubeShader.setMat4("model", model);
        */
        // render the cube
        // lightCube.Draw(lightCubeShader); // You need to have a model for the light cube or render a simple cube here

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        lightOn = !lightOn; // Cambia el estado de la luz
        lightF = lightOn ? glm::vec3(1.0f, 1.0f, 1.0f) : glm::vec3(0.0f, 0.0f, 0.0f); // Prende o apaga la luz la luz
        //*******SI FALLA LA LINTERNA DESCOMENTAR LA SIGUIENTE LINEA
        //std::this_thread::sleep_for(std::chrono::milliseconds(200)); // delay entre clicks
    }
    
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
