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
    Model ourModel("D:/EPN SEMESTRES/ComputacionGrafica/OpenGL/OpenGL/model/aftertherain/aftertherain.obj");
    Model ourModel2("D:/EPN SEMESTRES/ComputacionGrafica/OpenGL/OpenGL/model/mounstro/mounstro.obj");
    Model ourModel3("D:/EPN SEMESTRES/ComputacionGrafica/OpenGL/OpenGL/model/armaconlinterna/arma.obj");
    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // lighting
     float a = 6.2;
     glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
     glm::vec3 dirLightDirection((238.684, 554.131, 374.902));
     glm::vec3 pointLightPositions[] = {
         glm::vec3(67.4885, a, -24.4653),
         glm::vec3(50.1336, a, -40.9756),
         glm::vec3(57.476, a, -24.4264),
         glm::vec3(35.7485, a, -23.374),
         glm::vec3(42.0412, a, -6.00715),
         glm::vec3(26.2719, a, -9.03249),
         glm::vec3(33.732, a, 8.56284),
         glm::vec3(28.8901, a, 25.8085),
         glm::vec3(15.2973, a, 25.6666),
         glm::vec3(26.6795, a, 42.8372),
         glm::vec3(13.1852, a, 42.5504),
         glm::vec3(13.232, a, 59.9155),
         glm::vec3(26.1219, a, 60.4521),
         glm::vec3(26.1037, a, 77.6029),
         glm::vec3(15.595, a, 94.5348),
         glm::vec3(26.1621, a, 96.3266),
         glm::vec3(36.1572, a, 96.3039),
         glm::vec3(26.1296, a, 112.234),
         glm::vec3(15.5845, a, 114.604),
         glm::vec3(15.5379, a, 132.134),
         glm::vec3(26.1238, a, 131.606),
         glm::vec3(26.156, a, 148.905),
         glm::vec3(15.5635, a, 148.835),
         glm::vec3(26.1346, a, 165.79),
         glm::vec3(15.533, a, 168.69),
         glm::vec3(26.4672, a, 182.651),
         glm::vec3(16.0294, a, 198.721),
         glm::vec3(26.931, a, 202.744),
         glm::vec3(16.0296, a, 220.602),
         glm::vec3(16.063, a, 235.319),
         glm::vec3(29.3722, a, 234.931),
         glm::vec3(16.4238, a, 252.448),
         glm::vec3(29.2886, a, 254.391),
         glm::vec3(14.6747, a, 269.381),
         glm::vec3(27.8113, a, 271.905),
         glm::vec3(23.8671, a, 288.899),
         glm::vec3(10.5307, a, 286.794),
         glm::vec3(17.0886, a, 306.348),
         glm::vec3(1.57443, a, 304.232),
         glm::vec3(6.06977, a, 323.443),
         glm::vec3(-12.3373, a, 321.888),
         glm::vec3(-6.37879, a, 338.864),
         glm::vec3(-22.3302, a, 321.898)
     };
   
    

    camera.MovementSpeed = 10; //Optional. Modify the speed of the camera
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
        ourShader.setVec3("viewPos", camera.Position);
        ourShader.setFloat("material.shininess", 32.0f);

        // set light properties
        
        // directional light ******LUZ DE LA LUNA
        ourShader.setVec3("dirLight.direction", dirLightDirection);
        ourShader.setVec3("dirLight.ambient", 0.1f, 0.1f, 0.1f);  ///AUMENTAR VALORES PARA MAS BRILLO AMBIENTAL
        ourShader.setVec3("dirLight.diffuse", 0.1f, 0.1f, 0.25f);
        ourShader.setVec3("dirLight.specular", 0.1f, 0.1f, 0.25f);
        
         
        // point lights****PARA LAS LAMPARAS
        for (unsigned int i = 0; i < 43; i++)
        {
            ourShader.setVec3("pointLights[" + std::to_string(i) + "].position", pointLightPositions[i]);
            ourShader.setVec3("pointLights[" + std::to_string(i) + "].ambient", 0.0f, 0.0f, 0.0f);
            ourShader.setVec3("pointLights[" + std::to_string(i) + "].diffuse", 1.0f, 1.0f, 1.0f);
            ourShader.setVec3("pointLights[" + std::to_string(i) + "].specular", 1.0f, 1.0f, 1.0f);
            ourShader.setFloat("pointLights[" + std::to_string(i) + "].constant", 0.8f);
            ourShader.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09f);
            ourShader.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.032f);
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
        //Mounstro
        glm::mat4 model2 = glm::mat4(1.0f);
        model2 = glm::translate(model2, glm::vec3(23.0f, 10.0f, -28.0f));
        model2 = glm::scale(model2, glm::vec3(100.0f, 100.0f, 100.0f));
        float angle = glm::radians(45.0f);
        model2 = glm::rotate(model2, angle, glm::vec3(0.0f, 1.0f, 0.0f));
        ourShader.use();
        ourShader.setMat4("model", model2);
        ourModel2.Draw(ourShader);
        //Arma
        glm::mat4 gunModel = glm::mat4(1.0f);
        glm::vec3 gunPosition = camera.Position + camera.Front * 5.0f + camera.Right * (1.5f + gunOffsetX) + camera.Up * (-0.8f + gunOffsetY);
        gunModel = glm::translate(gunModel, gunPosition);
        gunModel = glm::rotate(gunModel, glm::radians(-camera.Yaw + 270), glm::vec3(0.0f, 1.0f, 0.0f));
        gunModel = glm::rotate(gunModel, glm::radians(camera.Pitch), glm::vec3(1.0f, 0.0f, 0.0f));
        gunModel = glm::rotate(gunModel, gunOffsetX * 0.5f, glm::vec3(0.0f, 1.0f, 0.0f));
        gunModel = glm::rotate(gunModel, gunOffsetY * 0.5f, glm::vec3(1.0f, 0.0f, 0.0f));

        gunModel = glm::scale(gunModel, glm::vec3(0.1f, 0.1f, 0.1f));
        ourShader.setMat4("model", gunModel);
        ourModel3.Draw(ourShader);
        
        // Print the camera position
        //COMENTAR ESTA PARTE PARA QUE NO SE IMPRIMAN COORDENADAS
    
        if (camera.Position != lastCameraPos)
        {
            std::cout << "Camera Position: ("
                << camera.Position.x << ", "
                << camera.Position.y << ", "
                << camera.Position.z << ")\n";
            lastCameraPos = camera.Position;
        }
    
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
    const float sensitivity = 0.001f; 
    gunOffsetX += xoffset * sensitivity;
    gunOffsetY += yoffset * sensitivity;
    gunOffsetX = glm::clamp(gunOffsetX, -0.1f, 0.1f);
    gunOffsetY = glm::clamp(gunOffsetY, -0.1f, 0.1f);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
