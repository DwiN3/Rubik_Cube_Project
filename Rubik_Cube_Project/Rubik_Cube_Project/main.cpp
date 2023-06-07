#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <C:/LIB/stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <C:/LIB/assets/camera.h>

#include <C:/LIB/assets/shader.h>

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <random>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <filesystem>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

//#include <experimental/filesystem> // Header file for pre-standard implementation
using namespace std::experimental::filesystem;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
unsigned int loadCubemap();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void turn_cube_up_to_down(int which, int each, bool game);
void turn_cube_down_to_up(int which, int each, bool game);

void turn_cube_left_to_right(int which, int each, bool game);
void turn_cube_right_to_left(int which, int each, bool game);

void mix_the_cube(int mode);
void turn_cube_to_full();
void print_cube_color();
void cube_arranged(bool skip);
void set_best_scores();
void show_best_scores();
void show_options();
bool is_cube_solved();
void show_solve();

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 1.0f, 8.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timer
chrono::time_point<chrono::high_resolution_clock> start_timer;
chrono::time_point<chrono::high_resolution_clock> end_timer;
chrono::duration<double> duration;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// best score
const int TOP_SCORES_COUNT = 5;
double top_scores[TOP_SCORES_COUNT] = { 0.0 };

// choose color
int color = 1;

// arranging blocking
bool arranging = false;

// count moves
int count_moves = 0;
int random_moves = 0;

//  show solve
string solve = "";
bool isSolved = true;

// load and create a texture 
unsigned int textureClassic1, textureClassic2, textureClassic3, textureClassic4, textureClassic5, textureClassic6;
unsigned int textureDeuteranopia1, textureDeuteranopia2, textureDeuteranopia3, textureDeuteranopia4, textureDeuteranopia5, textureDeuteranopia6;
unsigned int textureTritanopia1, textureTritanopia2, textureTritanopia3, textureTritanopia4, textureTritanopia5, textureTritanopia6;

void dataTextureLoad() {
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
}

void loadData(unsigned char* data, int width, int height) {
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void loadTextures() {
    int width, height, nrChannels;

    // textureClassic1
    glGenTextures(1, &textureClassic1);
    glBindTexture(GL_TEXTURE_2D, textureClassic1);
    dataTextureLoad();
    unsigned char* dataClassic = stbi_load("colors/classic/red.png", &width, &height, &nrChannels, 0);
    loadData(dataClassic, width, height);


    // textureClassic2
    glGenTextures(1, &textureClassic2);
    glBindTexture(GL_TEXTURE_2D, textureClassic2);
    dataTextureLoad();
    dataClassic = stbi_load("colors/classic/green.png", &width, &height, &nrChannels, 0);
    loadData(dataClassic, width, height);


    // textureClassic3
    glGenTextures(1, &textureClassic3);
    glBindTexture(GL_TEXTURE_2D, textureClassic3);
    dataTextureLoad();
    dataClassic = stbi_load("colors/classic/blue.png", &width, &height, &nrChannels, 0);
    loadData(dataClassic, width, height);


    // textureClassic4
    glGenTextures(1, &textureClassic4);
    glBindTexture(GL_TEXTURE_2D, textureClassic4);
    dataTextureLoad();
    dataClassic = stbi_load("colors/classic/yellow.png", &width, &height, &nrChannels, 0);
    loadData(dataClassic, width, height);


    // textureClassic5
    glGenTextures(1, &textureClassic5);
    glBindTexture(GL_TEXTURE_2D, textureClassic5);
    dataTextureLoad();
    dataClassic = stbi_load("colors/classic/orange.png", &width, &height, &nrChannels, 0);
    loadData(dataClassic, width, height);


    // textureClassic6 
    glGenTextures(1, &textureClassic6);
    glBindTexture(GL_TEXTURE_2D, textureClassic6);
    dataTextureLoad();
    dataClassic = stbi_load("colors/classic/white.png", &width, &height, &nrChannels, 0);
    loadData(dataClassic, width, height);



    // textureDeuteranopia1
    glGenTextures(1, &textureDeuteranopia1);
    glBindTexture(GL_TEXTURE_2D, textureDeuteranopia1);
    dataTextureLoad();
    unsigned char* dataDeuteranopia = stbi_load("colors/deuteranopia/red.png", &width, &height, &nrChannels, 0);
    loadData(dataDeuteranopia, width, height);


    // textureDeuteranopia2
    glGenTextures(1, &textureDeuteranopia2);
    glBindTexture(GL_TEXTURE_2D, textureDeuteranopia2);
    dataTextureLoad();
    dataDeuteranopia = stbi_load("colors/deuteranopia/green.png", &width, &height, &nrChannels, 0);
    loadData(dataDeuteranopia, width, height);


    // textureDeuteranopia3
    glGenTextures(1, &textureDeuteranopia3);
    glBindTexture(GL_TEXTURE_2D, textureDeuteranopia3);
    dataTextureLoad();
    dataDeuteranopia = stbi_load("colors/deuteranopia/blue.png", &width, &height, &nrChannels, 0);
    loadData(dataDeuteranopia, width, height);


    // textureDeuteranopia4
    glGenTextures(1, &textureDeuteranopia4);
    glBindTexture(GL_TEXTURE_2D, textureDeuteranopia4);
    dataTextureLoad();
    dataDeuteranopia = stbi_load("colors/deuteranopia/yellow.png", &width, &height, &nrChannels, 0);
    loadData(dataDeuteranopia, width, height);


    // textureDeuteranopia5
    glGenTextures(1, &textureDeuteranopia5);
    glBindTexture(GL_TEXTURE_2D, textureDeuteranopia5);
    dataTextureLoad();
    dataDeuteranopia = stbi_load("colors/deuteranopia/orange.png", &width, &height, &nrChannels, 0);
    loadData(dataDeuteranopia, width, height);


    // textureDeuteranopia6
    glGenTextures(1, &textureDeuteranopia6);
    glBindTexture(GL_TEXTURE_2D, textureDeuteranopia6);
    dataTextureLoad();
    dataDeuteranopia = stbi_load("colors/deuteranopia/white.png", &width, &height, &nrChannels, 0);
    loadData(dataDeuteranopia, width, height);


    // textureTritanopia1
    glGenTextures(1, &textureTritanopia1);
    glBindTexture(GL_TEXTURE_2D, textureTritanopia1);
    dataTextureLoad();
    unsigned char* dataTritanopia = stbi_load("colors/tritanopia/red.png", &width, &height, &nrChannels, 0);
    loadData(dataTritanopia, width, height);


    // textureTritanopia2
    glGenTextures(1, &textureTritanopia2);
    glBindTexture(GL_TEXTURE_2D, textureTritanopia2);
    dataTextureLoad();
    dataTritanopia = stbi_load("colors/tritanopia/green.png", &width, &height, &nrChannels, 0);
    loadData(dataTritanopia, width, height);


    // textureTritanopia3
    glGenTextures(1, &textureTritanopia3);
    glBindTexture(GL_TEXTURE_2D, textureTritanopia3);
    dataTextureLoad();
    dataTritanopia = stbi_load("colors/tritanopia/blue.png", &width, &height, &nrChannels, 0);
    loadData(dataTritanopia, width, height);


    // textureTritanopia4
    glGenTextures(1, &textureTritanopia4);
    glBindTexture(GL_TEXTURE_2D, textureTritanopia4);
    dataTextureLoad();
    dataTritanopia = stbi_load("colors/tritanopia/yellow.png", &width, &height, &nrChannels, 0);
    loadData(dataTritanopia, width, height);


    // textureTritanopia5
    glGenTextures(1, &textureTritanopia5);
    glBindTexture(GL_TEXTURE_2D, textureTritanopia5);
    dataTextureLoad();
    dataTritanopia = stbi_load("colors/tritanopia/orange.png", &width, &height, &nrChannels, 0);
    loadData(dataTritanopia, width, height);


    // textureTritanopia6
    glGenTextures(1, &textureTritanopia6);
    glBindTexture(GL_TEXTURE_2D, textureTritanopia6);
    dataTextureLoad();
    dataTritanopia = stbi_load("colors/tritanopia/white.png", &width, &height, &nrChannels, 0);
    loadData(dataTritanopia, width, height);

}


int sideCube[27][6] = {
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6},
    {1,2,3,4,5,6}
};


glm::vec3 cubePositions[] = {
    //x               y      z

     // 1 side
        glm::vec3(-1.0f,  0.0f,  -1.0f), // FRONT - LEFT - UP
        glm::vec3(0.0f,  0.0f,  -1.0f), // FRONT - CENTER UP
        glm::vec3(1.0f,   0.0f,  -1.0f),

        glm::vec3(-1.0f, -1.0f,  -1.0f),
        glm::vec3(0.0f, -1.0f,  -1.0f),
        glm::vec3(1.0f,  -1.0f,  -1.0f),

        glm::vec3(-1.0f, -2.0f,  -1.0f),
        glm::vec3(0.0f, -2.0f,  -1.0f),
        glm::vec3(1.0f,  -2.0f,  -1.0f),

        // 2 side
        glm::vec3(-1.0f,  0.0f,  -2.0f),
        glm::vec3(0.0f,  0.0f,  -2.0f),
        glm::vec3(1.0f,   0.0f,  -2.0f),

        glm::vec3(-1.0f, -1.0f,  -2.0f),
        glm::vec3(0.0f, -1.0f,  -2.0f),
        glm::vec3(1.0f,  -1.0f,  -2.0f),

        glm::vec3(-1.0f, -2.0f,  -2.0f),
        glm::vec3(0.0f, -2.0f,  -2.0f),
        glm::vec3(1.0f,  -2.0f,  -2.0f),

        // 3 side
        glm::vec3(-1.0f,  0.0f,  -3.0f),
        glm::vec3(0.0f,  0.0f,  -3.0f),
        glm::vec3(1.0f,   0.0f,  -3.0f),

        glm::vec3(-1.0f, -1.0f,  -3.0f),
        glm::vec3(0.0f, -1.0f,  -3.0f),
        glm::vec3(1.0f,  -1.0f,  -3.0f),

        glm::vec3(-1.0f, -2.0f,  -3.0f),
        glm::vec3(0.0f, -2.0f,  -3.0f),
        glm::vec3(1.0f,  -2.0f,  -3.0f),

};


int main()
{
    // show options
    show_options();
    // set best time score
    set_best_scores();

    // glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "RubikCube", NULL, NULL);
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

    // glfw capture mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad load function
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);

    // build shader
    Shader ourShader("assets/camera.vs", "assets/camera.fs");
    Shader skyboxShader("assets/skybox.vs", "assets/skybox.fs");

    // set up vertex
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    };


    // skybox

    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
    /*cubetest = cubePositions[0];*/
    // skybox VAO
    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    unsigned int cubemapTexture = loadCubemap();
    skyboxShader.use();
    skyboxShader.setInt("skybox", 0);

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1); //0?


    loadTextures();


    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(window);

        // render
        // activate shader
        ourShader.use();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //// pass projection matrix to shader
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

        int count = 6;
        // render boxes (27 boxes)
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 27; i++)
        {
            ourShader.use();
            for (unsigned int j = 0; j < 6; j++)
            {
                // 0 - white
                // 1 - red
                // 2 - green
                // 3 - blue
                // 4 - yellow
                // 5 - orange
                // activited special texture for each side   
                if (sideCube[i][j] == 1) {
                    glActiveTexture(GL_TEXTURE1);
                    if (color == 1)
                        glBindTexture(GL_TEXTURE_2D, textureClassic1);
                    else if (color == 2)
                        glBindTexture(GL_TEXTURE_2D, textureDeuteranopia1);
                    else if (color == 3)
                        glBindTexture(GL_TEXTURE_2D, textureTritanopia1);
                    ourShader.setInt("texture1", 5);

                }
                else if (sideCube[i][j] == 2) {
                    glActiveTexture(GL_TEXTURE2);
                    if (color == 1)
                        glBindTexture(GL_TEXTURE_2D, textureClassic2);
                    else if (color == 2)
                        glBindTexture(GL_TEXTURE_2D, textureDeuteranopia2);
                    else if (color == 3) {
                        glBindTexture(GL_TEXTURE_2D, textureTritanopia2);
                    }
                    ourShader.setInt("texture1", 1);

                }
                else if (sideCube[i][j] == 3) {
                    glActiveTexture(GL_TEXTURE3);
                    if (color == 1)
                        glBindTexture(GL_TEXTURE_2D, textureClassic3);
                    else if (color == 2)
                        glBindTexture(GL_TEXTURE_2D, textureDeuteranopia3);
                    else if (color == 3)
                        glBindTexture(GL_TEXTURE_2D, textureTritanopia3);
                    ourShader.setInt("texture1", 2);

                }
                else if (sideCube[i][j] == 4) {
                    glActiveTexture(GL_TEXTURE4);
                    if (color == 1)
                        glBindTexture(GL_TEXTURE_2D, textureClassic4);
                    else if (color == 2)
                        glBindTexture(GL_TEXTURE_2D, textureDeuteranopia4);
                    else if (color == 3)
                        glBindTexture(GL_TEXTURE_2D, textureTritanopia4);
                    ourShader.setInt("texture1", 3);

                }

                else if (sideCube[i][j] == 5) {
                    glActiveTexture(GL_TEXTURE5);
                    if (color == 1)
                        glBindTexture(GL_TEXTURE_2D, textureClassic5);
                    else if (color == 2)
                        glBindTexture(GL_TEXTURE_2D, textureDeuteranopia5);
                    else if (color == 3)
                        glBindTexture(GL_TEXTURE_2D, textureTritanopia5);
                    ourShader.setInt("texture1", 4);

                }
                else if (sideCube[i][j] == 6) {
                    glActiveTexture(GL_TEXTURE6);
                    if (color == 1)
                        glBindTexture(GL_TEXTURE_2D, textureClassic6);
                    else if (color == 2)
                        glBindTexture(GL_TEXTURE_2D, textureDeuteranopia6);
                    else if (color == 3)
                        glBindTexture(GL_TEXTURE_2D, textureTritanopia6);
                    ourShader.setInt("texture1", 0);

                }

                // calculate the model matrix for each object and pass it to shader before drawing
                glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
                model = glm::translate(model, cubePositions[i]);
                model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                //model = glm::rotate(model, 0, glm::vec3(1.0f, 0.0f, 0.0f));
                ourShader.setMat4("model", model);

                // count is the number of who manny triangles sholud to create with selected texture  (6 - one side, 36 - all cube)
                glDrawArrays(GL_TRIANGLES, 0, count);
                count += 6;
            }
            // reseting after one cube
            if (count >= 35)
                count = 6;
            //angle = 0.0f;


        }

        // draw skybox as last
        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
        skyboxShader.use();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
        skyboxShader.setMat4("view", view);
        skyboxShader.setMat4("projection", projection);
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default

        glfwSetKeyCallback(window, key_callback);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteBuffers(1, &skyboxVBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// process all input
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}


// glfw: whenever the window size changed 
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

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

// mouse scroll
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

/**
 @qwewqe
*/
unsigned int loadCubemap()
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    int width, height, nrChannels;
    for (unsigned int i = 0; i < 6; i++)
    {
        unsigned char* data = stbi_load("skybox/right.jpg", &width, &height, &nrChannels, 0);
        if (i == 0)
            data = stbi_load("skybox/right.jpg", &width, &height, &nrChannels, 0);
        else if (i == 1)
            data = stbi_load("skybox/left.jpg", &width, &height, &nrChannels, 0);
        else if (i == 2)
            data = stbi_load("skybox/top.jpg", &width, &height, &nrChannels, 0);
        else if (i == 3)
            data = stbi_load("skybox/bottom.jpg", &width, &height, &nrChannels, 0);
        else if (i == 4)
            data = stbi_load("skybox/front.jpg", &width, &height, &nrChannels, 0);
        else if (i == 5)
            data = stbi_load("skybox/back.jpg", &width, &height, &nrChannels, 0);

        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Sterowanie kostką
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
        turn_cube_up_to_down(0, 3, true);
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
        turn_cube_up_to_down(1, 3, true);
    if (key == GLFW_KEY_3 && action == GLFW_PRESS)
        turn_cube_up_to_down(2, 3, true);
    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
        turn_cube_down_to_up(0, 3, true);
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        turn_cube_down_to_up(1, 3, true);
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
        turn_cube_down_to_up(2, 3, true);
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        turn_cube_left_to_right(0, 9, true);
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        turn_cube_left_to_right(3, 9, true);
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
        turn_cube_left_to_right(6, 9, true);
    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
        turn_cube_right_to_left(0, 9, true);
    if (key == GLFW_KEY_X && action == GLFW_PRESS)
        turn_cube_right_to_left(3, 9, true);
    if (key == GLFW_KEY_C && action == GLFW_PRESS)
        turn_cube_right_to_left(6, 9, true);

    // Pokazywanie podpowiedzi
    if ((key == GLFW_KEY_L && action == GLFW_PRESS) && isSolved == false)
        show_solve();

    // Mieszanie
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        mix_the_cube(1);
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        mix_the_cube(2);
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        mix_the_cube(3);

    // Prezentacja ułożenia kostki
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        cube_arranged(true);
        turn_cube_to_full();
    }

    // Zmiana koloru kostki
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
        color = 3;
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
        color = 2;
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
        color = 1;
}

void turn_cube_to_full()
{
    for (int i = 0; i < 27; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            sideCube[i][j] = j + 1;
        }
    }
}


void turn_cube_up_to_down(int which, int each, bool game) {
    if (game) count_moves += 1;
    int a, b, c;
    a = sideCube[which][5];
    b = sideCube[which + 9][5];
    c = sideCube[which + 2 * 9][5];
    sideCube[which][5] = sideCube[which + 2 * 9][0];
    sideCube[which + 9][5] = sideCube[which + 2 * 9 + each][0];
    sideCube[which + 2 * 9][5] = sideCube[which + 2 * 9 + 2 * each][0];

    sideCube[which + 2 * 9][0] = sideCube[which + 2 * each + 2 * 9][4];
    sideCube[which + 2 * 9 + each][0] = sideCube[which + 2 * each + 9][4];
    sideCube[which + 2 * 9 + 2 * each][0] = sideCube[which + 2 * each][4];

    sideCube[which + 2 * each][4] = sideCube[which][1];
    sideCube[which + 2 * each + 9][4] = sideCube[which + each][1];
    sideCube[which + 2 * each + 2 * 9][4] = sideCube[which + 2 * each][1];

    sideCube[which][1] = c;
    sideCube[which + each][1] = b;
    sideCube[which + 2 * each][1] = a;

    for (int i = 2; i < 4; i++)
    {
        a = sideCube[which][i];
        b = sideCube[which + 9][i];
        c = sideCube[which + 2 * 9][i];

        sideCube[which][i] = sideCube[which + 2 * 9][i];
        sideCube[which + 9][i] = sideCube[which + 2 * 9 + each][i];
        sideCube[which + 2 * 9][i] = sideCube[which + 2 * 9 + 2 * each][i];

        sideCube[which + 2 * 9][i] = sideCube[which + 2 * each + 2 * 9][i];
        sideCube[which + 2 * 9 + each][i] = sideCube[which + 2 * each + 9][i];
        sideCube[which + 2 * 9 + 2 * each][i] = sideCube[which + 2 * each][i];


        sideCube[which + 2 * each + 2 * 9][i] = sideCube[which + 2 * each][i];
        sideCube[which + 2 * each + 9][i] = sideCube[which + each][i];
        sideCube[which + 2 * each][i] = sideCube[which][i];

        sideCube[which][i] = c;
        sideCube[which + each][i] = b;
        sideCube[which + 2 * each][i] = a;
    }
    if (is_cube_solved() == true) cube_arranged(false);
}


void turn_cube_down_to_up(int which, int each, bool game) {
    if (game) count_moves += 1;
    int a, b, c;
    a = sideCube[which][5];
    b = sideCube[which + 9][5];
    c = sideCube[which + 2 * 9][5];

    sideCube[which][5] = sideCube[which + 2 * each][1];
    sideCube[which + 9][5] = sideCube[which + each][1];
    sideCube[which + 2 * 9][5] = sideCube[which][1];

    sideCube[which][1] = sideCube[which + 2 * each][4];
    sideCube[which + each][1] = sideCube[which + 2 * each + 9][4];
    sideCube[which + 2 * each][1] = sideCube[which + 2 * each + 2 * 9][4];

    sideCube[which + 2 * each][4] = sideCube[which + 2 * 9 + 2 * each][0];
    sideCube[which + 2 * each + 9][4] = sideCube[which + 2 * 9 + each][0];
    sideCube[which + 2 * each + 2 * 9][4] = sideCube[which + 2 * 9][0];

    sideCube[which + 2 * 9][0] = a;
    sideCube[which + 2 * 9 + each][0] = b;
    sideCube[which + 2 * 9 + 2 * each][0] = c;

    for (int i = 2; i < 4; i++)
    {
        a = sideCube[which][i];
        b = sideCube[which + 9][i];
        c = sideCube[which + 2 * 9][i];

        sideCube[which][i] = sideCube[which + 2 * each][i];
        sideCube[which + 9][i] = sideCube[which + each][i];
        sideCube[which + 2 * 9][i] = sideCube[which][i];

        sideCube[which][i] = sideCube[which + 2 * each][i];
        sideCube[which + each][i] = sideCube[which + 2 * each + 9][i];
        sideCube[which + 2 * each][i] = sideCube[which + 2 * each + 2 * 9][i];

        sideCube[which + 2 * each][i] = sideCube[which + 2 * 9 + 2 * each][i];
        sideCube[which + 2 * each + 9][i] = sideCube[which + each + 2 * 9][i];
        sideCube[which + 2 * each + 2 * 9][i] = sideCube[which + 2 * 9][i];

        sideCube[which + 2 * 9][i] = a;
        sideCube[which + each + 2 * 9][i] = b;
        sideCube[which + 2 * each + 2 * 9][i] = c;
    }
    if (is_cube_solved() == true) cube_arranged(false);
}

void turn_cube_left_to_right(int which, int each, bool game) {
    if (game) count_moves += 1;
    int a, b, c;

    a = sideCube[which][2];
    b = sideCube[which + each][2];
    c = sideCube[which + 2 * each][2];

    sideCube[which][2] = sideCube[which + 2 * each][0];
    sideCube[which + each][2] = sideCube[which + 1 + 2 * each][0];
    sideCube[which + 2 * each][2] = sideCube[which + 2 + 2 * each][0];

    sideCube[which + 2 * each][0] = sideCube[which + 2 + 2 * each][3];
    sideCube[which + 1 + 2 * each][0] = sideCube[which + 2 + 1 * each][3];
    sideCube[which + 2 + 2 * each][0] = sideCube[which + 2][3];

    sideCube[which + 2 + 2 * each][3] = sideCube[which + 2][1];
    sideCube[which + 2 + 1 * each][3] = sideCube[which + 1][1];
    sideCube[which + 2][3] = sideCube[which][1];

    sideCube[which + 2][1] = a;
    sideCube[which + 1][1] = b;
    sideCube[which][1] = c;

    for (int i = 4; i < 6; i++)
    {
        a = sideCube[which][i];
        b = sideCube[which + each][i];
        c = sideCube[which + 2 * each][i];

        sideCube[which][i] = sideCube[which + 2 * each][i];
        sideCube[which + each][i] = sideCube[which + 1 + 2 * each][i];
        sideCube[which + 2 * each][i] = sideCube[which + 2 + 2 * each][i];

        sideCube[which + 2 * each][i] = sideCube[which + 2 + 2 * each][i];
        sideCube[which + 1 + 2 * each][i] = sideCube[which + 2 + 1 * each][i];
        sideCube[which + 2 + 2 * each][i] = sideCube[which + 2][i];

        sideCube[which + 2 + 2 * each][i] = sideCube[which + 2][i];
        sideCube[which + 2 + 1 * each][i] = sideCube[which + 1][i];
        sideCube[which + 2][i] = sideCube[which][i];

        sideCube[which + 2][i] = a;
        sideCube[which + 1][i] = b;
        sideCube[which][i] = c;
    }
    if (is_cube_solved() == true) cube_arranged(false);
}

void turn_cube_right_to_left(int which, int each, bool game) {
    if (game) count_moves += 1;
    int a, b, c;

    a = sideCube[which][2];
    b = sideCube[which + each][2];
    c = sideCube[which + 2 * each][2];

    sideCube[which + 2 * each][2] = sideCube[which][1];
    sideCube[which + each][2] = sideCube[which + 1][1];
    sideCube[which][2] = sideCube[which + 2][1];

    sideCube[which][1] = sideCube[which + 2][3];
    sideCube[which + 1][1] = sideCube[which + 2 + each][3];
    sideCube[which + 2][1] = sideCube[which + 2 + 2 * each][3];

    sideCube[which + 2][3] = sideCube[which + 2 + 2 * each][0];
    sideCube[which + 2 + each][3] = sideCube[which + 1 + 2 * each][0];
    sideCube[which + 2 + 2 * each][3] = sideCube[which + 2 * each][0];

    sideCube[which + 2 + 2 * each][0] = c;
    sideCube[which + 1 + 2 * each][0] = b;
    sideCube[which + 2 * each][0] = a;

    for (int i = 4; i < 6; i++)
    {
        a = sideCube[which][i];
        b = sideCube[which + each][i];
        c = sideCube[which + 2 * each][i];

        sideCube[which + 2 * each][i] = sideCube[which][i];
        sideCube[which + each][i] = sideCube[which + 1][i];
        sideCube[which][i] = sideCube[which + 2][i];

        sideCube[which][i] = sideCube[which + 2][i];
        sideCube[which + 1][i] = sideCube[which + 2 + each][i];
        sideCube[which + 2][i] = sideCube[which + 2 + 2 * each][i];

        sideCube[which + 2][i] = sideCube[which + 2 + 2 * each][i];
        sideCube[which + 2 + each][i] = sideCube[which + 1 + 2 * each][i];
        sideCube[which + 2 + 2 * each][i] = sideCube[which + 2 * each][i];

        sideCube[which + 2 + 2 * each][i] = c;
        sideCube[which + 1 + 2 * each][i] = b;
        sideCube[which + 2 * each][i] = a;
    }
    if (is_cube_solved() == true) cube_arranged(false);
}

void print_cube_color() {
    for (int i = 0; i < 27; i++)
    {
        std::cout << i << ": " << sideCube[i][0] << sideCube[i][1] << sideCube[i][2] << sideCube[i][3] << sideCube[i][4] << sideCube[i][5] << std::endl;
    }
}

void mix_the_cube(int mode) {
    if (arranging == false) {
        isSolved = false;
        int number_of_changes = 0;

        // easy mode
        if (mode == 1) {
            number_of_changes = 5;
            random_moves = number_of_changes;
        }

        // medium mode
        if (mode == 2) {
            number_of_changes = 15;
            random_moves = number_of_changes;
        }

        // hard mode
        else if (mode == 3) {
            random_moves = (rand() % 36) + 15;
            number_of_changes = random_moves;
        }
          
        int random;
        for (int i = 0; i < number_of_changes; i++)
        {
            random = rand() % 12;

            switch (random)
            {
            case 0:
                solve += "Q ";
                turn_cube_up_to_down(0, 3, false);
                break;
            case 1:
                solve += "W ";
                turn_cube_up_to_down(1, 3, false);
                break;
            case 2:
                solve += "E ";
                turn_cube_up_to_down(2, 3, false);
                break;
            case 3:
                solve += "1 ";
                turn_cube_down_to_up(0, 3, false);
                break;
            case 4:
                solve += "2 ";
                turn_cube_down_to_up(1, 3, false);
                break;
            case 5:
                solve += "3 ";
                turn_cube_down_to_up(2, 3, false);
                break;
            case 6:
                solve += "Z ";
                turn_cube_left_to_right(0, 9, false);
                break;
            case 7:
                solve += "X ";
                turn_cube_left_to_right(3, 9, false);
                break;
            case 8:
                solve += "C ";
                turn_cube_left_to_right(6, 9, false);
                break;
            case 9:
                solve += "A ";
                turn_cube_right_to_left(0, 9, false);
                break;
            case 10:
                solve += "S ";
                turn_cube_right_to_left(3, 9, false);
                break;
            case 11:
                solve += "D ";
                turn_cube_right_to_left(6, 9, false);
                break;
            default:
                break;
            }
        }
        arranging = true;
        cout << "\n\nStart" << endl;
        start_timer = chrono::high_resolution_clock::now();
    }
}


void cube_arranged(bool skip) {
    if (arranging == true) {
        chrono::high_resolution_clock::time_point end_timer = std::chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end_timer - start_timer;
        if(skip == false) cout << "Czas trwania: " << duration.count() << " sekundy" << endl;
        else count_moves += random_moves;
        cout << "Ilosc ruchow: " << count_moves << endl << endl;

        arranging = false;
        if (duration.count() < top_scores[TOP_SCORES_COUNT - 1] && skip == false) {
            cout << "Gratulacje, udalo ci sie pobic rekord!!!\n" << endl;

            top_scores[TOP_SCORES_COUNT - 1] = duration.count();
            sort(top_scores, top_scores + TOP_SCORES_COUNT);

            ofstream file("best_score.txt");
            if (file.good()) {
                for (int i = 0; i < TOP_SCORES_COUNT; i++) {
                    file << fixed << setprecision(2) << top_scores[i] << endl;
                }
                file.close();
            }
            else {
                cout << "Nie mozna zapisac do pliku" << endl;
            }
        }
        isSolved = true;
        show_best_scores();
        cout << endl << endl;
        show_options();
        random_moves = 0;
        count_moves = 0;
        solve = "";
    }
}

void set_best_scores() {
    ifstream file("best_score.txt");
    if (!file.good()) {
        cout << "\nNie mozna otworzyc pliku" << endl;
        file.close();
    }
    else {
        for (int i = 0; i < TOP_SCORES_COUNT; i++) {
            if (!(file >> top_scores[i])) break;
        }
        file.close();
        show_best_scores();
    }
}

void show_best_scores() {
    std::cout << "Najlepsze wyniki:" << std::endl;
    for (int i = 0; i < TOP_SCORES_COUNT; i++) {
        int total_seconds = static_cast<int>(top_scores[i]);
        int minutes = total_seconds / 60;
        int seconds = total_seconds % 60;
        int milliseconds = static_cast<int>((top_scores[i] - total_seconds) * 1000);
        std::cout << "  " << i + 1 << ". " << minutes << ":" << std::setw(2) << std::setfill('0') << seconds << "." << std::setw(2) << std::setfill('0') << milliseconds / 10 << std::endl;
    }
}

void show_options() {
    cout << "Ruchy na kosce:" << endl;
    cout << "  1 - F    2 - S    3 - B'" << endl;
    cout << "  Q - F'   W - S'   E - B" << endl;
    cout << "  A - U'   S - E    D - D" << endl;
    cout << "  Z - U    X - E'   C - D'" << endl << endl;

    cout << "Opcje aplikacji:" << endl;
    cout << "  I     - pomieszanie kostki easy (5  iteracji)" << endl;
    cout << "  O     - pomieszanie kostki medium (15  iteracji)" << endl;
    cout << "  P     - pomieszanie kostki hard (15+ iteracji)" << endl;
    cout << "  L     - wyswietlenie podpowiedzi" << endl;
    cout << "  SPACE - symulacja ulozenie kostki" << endl;
    cout << "  0     - domyslny wyglad kostki" << endl;
    cout << "  9     - tryb dla daltonistow (duteranopia)" << endl;
    cout << "  8     - tryb dla daltonistow (tritanopia)" << endl << endl;
}

bool is_cube_solved()
{
    for (int i = 0; i < 27; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (sideCube[i][j] != j + 1) return false;

        }
    }
    return true;
}

void show_solve() {
    isSolved = true;
    cout << "Solve: " << solve << "  <-----\n";
}