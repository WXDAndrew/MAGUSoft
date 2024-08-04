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
    //Model ourModel("D:/EPN SEMESTRES/ComputacionGrafica/OpenGL/OpenGL/model/mezcla4/mezcla4.obj");
    Model ourModel0("D:/EPN SEMESTRES/ComputacionGrafica/OpenGL/OpenGL/model/aftertherain/aftertherain.obj");
    Model ourModel1("D:/EPN SEMESTRES/ComputacionGrafica/OpenGL/OpenGL/model/armaconlinterna/arma.obj");
    //Model ourModel2("C:/Users/fiall/Documents/Visual Studio 2022/P1_E1_BlackWindow/P1_E1_BlackWindow/model/escombros/escombros.obj");
    //Model ourModel3("C:/Users/fiall/Documents/Visual Studio 2022/P1_E1_BlackWindow/P1_E1_BlackWindow/model/carroviejo1/carroviejo.obj");
    //Model ourModel4("C:/Users/fiall/Documents/Visual Studio 2022/P1_E1_BlackWindow/P1_E1_BlackWindow/model/blackcar/blackcar.obj");
    //Model ourModel5("C:/Users/fiall/Documents/Visual Studio 2022/P1_E1_BlackWindow/P1_E1_BlackWindow/model/damagecar/damagecar.obj");
    Model ourModel6("D:/EPN SEMESTRES/ComputacionGrafica/OpenGL/OpenGL/model/portal3/portal3.obj");
    Model ourModel7("D:/EPN SEMESTRES/ComputacionGrafica/OpenGL/OpenGL/model/dragon/dragon.obj");
    Model ourModel8("D:/EPN SEMESTRES/ComputacionGrafica/OpenGL/OpenGL/model/godzilla/godzilla.obj");
    Model ourModel9("D:/EPN SEMESTRES/ComputacionGrafica/OpenGL/OpenGL/model/soldado1/soldado1.obj");
    Model ourModel10("D:/EPN SEMESTRES/ComputacionGrafica/OpenGL/OpenGL/model/monster/monster.obj");
    Model ourModel11("D:/EPN SEMESTRES/ComputacionGrafica/OpenGL/OpenGL/model/helicopter1/helicopter.obj");
    
    
    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    // lighting
     float a = 6.2;
     glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
     glm::vec3 dirLightDirection((238.684, 554.131, 374.902));
     
    //POSICION DE LAS LAMPARAS
    glm::vec3 pointLightPositions[] = {
        glm::vec3(57.4836, a, -24.4376),
        glm::vec3(40.1429, a, -40.9804),
        glm::vec3(25.7346, a, -23.3442),
        glm::vec3(42.052, a, -5.97245),
        glm::vec3(16.2731, a, -9.01616),
        glm::vec3(33.7424, a, 8.56258),
        glm::vec3(28.9109, a, 25.806),
        glm::vec3(5.33113, a, 25.6271),
        glm::vec3(3.19505, a, 42.544),
        glm::vec3(26.677, a, 42.8471),
        glm::vec3(26.1763, a, 60.4384),
        glm::vec3(3.18732, a, 59.9176),
        glm::vec3(26.1534, a, 77.5773),
        glm::vec3(26.1683, a, 96.3224),
        glm::vec3(5.52788, a, 94.6095),
        glm::vec3(5.51493, a, 114.647),
        glm::vec3(26.1719, a, 112.191),
        glm::vec3(26.161, a, 131.569),
        glm::vec3(5.51548, a, 132.177),
        glm::vec3(5.52469, a, 148.866),
        glm::vec3(26.1643, a, 148.877),
        glm::vec3(26.1828, a, 165.764),
        glm::vec3(5.5171, a, 168.731),
        glm::vec3(26.5008, a, 182.634),
        glm::vec3(26.9515, a, 202.725),
        glm::vec3(6.03625, a, 198.751),
        glm::vec3(6.03916, a, 220.63),
        glm::vec3(6.03529, a, 235.315),
        glm::vec3(29.3727, a, 234.874),
        glm::vec3(29.3436, a, 254.407),
        glm::vec3(6.38009, a, 252.469),
        glm::vec3(4.65171, a, 269.408),
        glm::vec3(27.8027, a, 271.896),
        glm::vec3(23.862, a, 288.88),
        glm::vec3(0.50749, a, 286.789),
        glm::vec3(-8.46366, a, 304.207),
        glm::vec3(17.0845, a, 306.298),
        glm::vec3(6.11738, a, 323.436),
        glm::vec3(-6.3792, a, 338.899),
        glm::vec3(-22.3739, a, 321.873)
    };
   
     glm::vec3 carPositions[] = {
         //carroviejo
         glm::vec3(18.0f, 1.7f, -28.0f),
         glm::vec3(9.0f, 0.0f, 20.0f),
         glm::vec3(9.0f, 0.01f, 110.0f),
         glm::vec3(4.5f,  1.7f, 150.0f),
         //blackcar
         glm::vec3(6.7f,  1.58f, 0.0f),
         glm::vec3(6.7f,  -0.1f, 80.0f),
         glm::vec3(16.0f, 1.7f, 140.0f),
         glm::vec3(-6.0f, 0.0f, 170.0f),
     };

     glm::vec3 rotationAngles[] = {
         //carroviejo
         glm::vec3(10.0f, 0.0f, 180.0f), // Ángulos para el primer modelo
         glm::vec3(0.0f,  0.0f, 0.01f), // Ángulos para el segundo modelo
         glm::vec3(0.0f,  0.0f, 0.01f), // Ángulos para el tercer modelo
         glm::vec3(0.0f,  0.0f, 130.0f), // Ángulos para el cuarto modelo
         //blackcar
         glm::vec3(50.0f, 90.0f, 90.0f),
         glm::vec3(0.0f,  0.0f, 0.01f),
         glm::vec3(-102.0f, 0.0f, 60.0f),
         glm::vec3(0.0f,  0.0f, 0.01f),
     };

     glm::vec3 escombrosPosition[] = {
         glm::vec3(16.0f, 1.2f, 87.0f),
         glm::vec3(16.0f, 1.2f, 45.0f),
         glm::vec3(16.0f, 1.2f, 25.0f),
         glm::vec3(-6.0f, 1.2f, 137.0f)
     };
     glm::vec3 soldierPositions[] = {
       glm::vec3(25.0f, 0.0f, -25.0f),
       glm::vec3(13.0f, 0.0f, 20.0f),
       glm::vec3(5.0f, 0.0f, 110.0f),
       glm::vec3(4.5f,  0.0f, 140.0f),
       glm::vec3(10.0f,  0.0f, 0.0f),
       glm::vec3(10.0f,  0.0f, 80.0f),
       glm::vec3(12.0f, 0.0f, 140.0f),
       glm::vec3(-3.0f, 0.0f, 150.0f),
     };
     glm::vec3 monsterPositions[] = {
         glm::vec3(-3.0f, 0.0f, 160.0f),
         glm::vec3(-5.0f, 0.0f, 165.0f),
         glm::vec3(-2.0f, 0.0f, 155.0f),
         glm::vec3(0.0f, 0.0f, 160.0f),
         glm::vec3(2.0f, 0.0f, 165.0f),
     };
     glm::vec3 helicopterPositions[] = {
       glm::vec3(30.0f, 50.0f, -25.0f),
       glm::vec3(5.0f, 50.0f, 20.0f),
       glm::vec3(-10.0f, 65.0f, 80.0f),
       glm::vec3(5.0f,  50.0f, 130.0f),
       glm::vec3(20.0f,  40.0f, 10.0f),
       glm::vec3(10.0f,  40.0f, 80.0f),
       glm::vec3(-12.0f,40.0f, 140.0f),
       glm::vec3(-3.0f, 450.0f, 150.0f),
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
        for (unsigned int i = 0; i < 40; i++)
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
        
        // Renderizar el escenario
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));    // it's a bit too big for our scene, so scale it down
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);

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
        
        //Escombros
        for (int j = 0; j < 4; ++j) {
            glm::mat4 escombros = glm::mat4(1.0f);
            // Posicionar el modelo en la posición de la luz
            escombros = glm::translate(escombros, escombrosPosition[j]);
            // Escalar el modelo
            escombros = glm::scale(escombros, glm::vec3(0.1f, 0.1f, 0.1f));
            ourShader.use();
            ourShader.setMat4("model", escombros);
            ourModel2.Draw(ourShader);
        }
        // soldados
        for (int j = 0; j < 8; ++j) {
            glm::mat4 soldados = glm::mat4(1.0f);
            // Posicionar el modelo en la posición de la luz
            soldados = glm::translate(soldados, soldierPositions[j]);
            // Escalar el modelo
            soldados = glm::scale(soldados, glm::vec3(0.04f, 0.04f, 0.04f));
            ourShader.use();
            ourShader.setMat4("model", soldados);
            ourModel9.Draw(ourShader);
        }
        //monster
        for (int j = 0; j < 8; ++j) {
            glm::mat4 monster = glm::mat4(1.0f);
            // Posicionar el modelo en la posición de la luz
            monster = glm::translate(monster, monsterPositions[j]);
            monster = glm::rotate(monster, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotar 35 grados alrededor del eje X
            // Escalar el modelo
            monster = glm::scale(monster, glm::vec3(0.2f, 0.2f, 0.2f));
            ourShader.use();
            ourShader.setMat4("model", monster);
            ourModel10.Draw(ourShader);
        }
        //helicopter
        for (int j = 0; j < 8; ++j) {
            glm::mat4 helicopter = glm::mat4(1.0f);
            // Posicionar el modelo en la posición de la luz
            helicopter = glm::translate(helicopter, helicopterPositions[j]);
            helicopter = glm::rotate(helicopter, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotar 35 grados alrededor del eje X
            // Escalar el modelo
            helicopter = glm::scale(helicopter, glm::vec3(0.01f, 0.01f, 0.01f));
            ourShader.use();
            ourShader.setMat4("model", helicopter);
            ourModel11.Draw(ourShader);
        }
        // Bucle para renderizar un modelo en cada posición del arreglo
        for (int i = 0; i < 4; ++i) {

            //carroviejo
            glm::mat4 model1 = glm::mat4(1.0f);
            // Posicionar el modelo en la posición de la luz
            model1 = glm::translate(model1, carPositions[i]);
            // Aplicar una rotación diferente a cada modelo
            float angleX = glm::radians(rotationAngles[i].x);
            float angleY = glm::radians(rotationAngles[i].y);
            float angleZ = glm::radians(rotationAngles[i].z);
            // Combinar rotaciones en los tres ejes
            model1 = glm::rotate(model1, angleX, glm::vec3(1.0f, 0.0f, 0.0f)); // Rotación alrededor del eje X
            model1 = glm::rotate(model1, angleY, glm::vec3(0.0f, 1.0f, 0.0f)); // Rotación alrededor del eje Y
            model1 = glm::rotate(model1, angleZ, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotación alrededor del eje Z
            // Escalar el modelo
            model1 = glm::scale(model1, glm::vec3(0.01f, 0.01f, 0.01f));
            ourShader.use();
            ourShader.setMat4("model", model1);
            ourModel3.Draw(ourShader);

            //blackcar
            glm::mat4 black = glm::mat4(1.0f);
            black = glm::translate(black, carPositions[i + 4]);
            float angle1 = glm::radians(rotationAngles[i+4].x);
            float angle2 = glm::radians(rotationAngles[i+4].y);
            float angle3 = glm::radians(rotationAngles[i+4].z);
            black = glm::rotate(black, angle1, glm::vec3(1.0f, 0.0f, 0.0f)); // Rotación alrededor del eje X
            black = glm::rotate(black, angle2, glm::vec3(0.0f, 1.0f, 0.0f)); // Rotación alrededor del eje Y
            black = glm::rotate(black, angle3, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotación alrededor del eje Z
            black = glm::scale(black, glm::vec3(1.0f, 1.0f, 1.0f));
            ourShader.use();
            ourShader.setMat4("model", black);
            ourModel4.Draw(ourShader);
        }
        //damagecar
        glm::mat4 damage = glm::mat4(1.0f);
        damage = glm::translate(damage, glm::vec3(6.5f, -0.1f, 40.0f));
        damage = glm::scale(damage, glm::vec3(1.0f, 1.0f, 1.0f));
        ourShader.use();
        ourShader.setMat4("model", damage);
        ourModel5.Draw(ourShader);
        
      //portal
        float angle = glfwGetTime() * 50.0f; // Ángulo de rotación negativo para girar en sentido horario
        glm::mat4 modelP = glm::mat4(1.0f);
        modelP = glm::translate(modelP, glm::vec3(-5.0f, 15.0f, 0.0f)); // Mantener en el centro de la escena
        modelP = glm::rotate(modelP, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotación alrededor del eje Y
        modelP = glm::scale(modelP, glm::vec3(1.0f, 1.0f, 1.0f)); // Escala normal para el primer modelo
        ourShader.use(); // Asegúrate de usar el shader correcto
        ourShader.setMat4("model", modelP);
        ourModel6.Draw(ourShader);
        //dragon
        float time = glfwGetTime(); // Obtén el tiempo actual
        float amplitude = 5.0f; // Amplitud del movimiento hacia arriba y hacia abajo
        float frequency = 2.5f; // Frecuencia del movimiento (cuán rápido oscila)

        glm::mat4 modelD = glm::mat4(1.0f);
        float yOffset = amplitude * sin(frequency * time); // Cálculo del desplazamiento en Y basado en una función seno
        modelD = glm::translate(modelD, glm::vec3(-5.0f, 25.0f + yOffset, -1.0f)); // Mantener en el centro de la escena con movimiento oscilante
        modelD = glm::rotate(modelD, glm::radians(35.0f), glm::vec3(1.0f, 1.0f, 0.0f)); // Rotar 35 grados alrededor del eje X
        modelD = glm::scale(modelD, glm::vec3(5.0f, 5.0f, 5.0f)); // Escala normal para el primer modelo
        ourShader.use(); // Asegúrate de usar el shader correcto
        ourShader.setMat4("model", modelD);
        ourModel7.Draw(ourShader);
        //godzilla
        glm::mat4 modelG = glm::mat4(1.0f);
        float yOffset1 = 2.5 * sin(2 * glfwGetTime()); // Cálculo del desplazamiento en Y basado en una función seno
        modelG = glm::translate(modelG, glm::vec3(20.0f, -90.0f + yOffset1, -80.0f)); // Mantener en el centro de la escena
        modelG = glm::rotate(modelG, glm::radians(45.0f), glm::vec3(.0f, 1.0f, 0.0f)); // Rotar 35 grados alrededor del eje X
        modelG = glm::scale(modelG, glm::vec3(85.0f, 85.0f, 85.0f)); // Escala normal para el primer modelo
        ourShader.use(); // Asegúrate de usar el shader correcto
        ourShader.setMat4("model", modelG);
        ourModel8.Draw(ourShader);
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
