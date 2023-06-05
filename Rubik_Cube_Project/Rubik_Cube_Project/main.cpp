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


//#include <experimental/filesystem> // Header file for pre-standard implementation
using namespace std::experimental::filesystem;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
unsigned int loadCubemap();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void turn_cube_up_to_down(int which, int each);
void turn_cube_down_to_up(int which, int each);

void turn_cube_left_to_right(int which, int each);
void turn_cube_right_to_left(int which, int each);

void turn_cube_to_full();
void print_cube_color();

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

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
    glm::vec3(-2.0f,  0.0f,  -5.0f), // FRONT - LEFT - UP
    glm::vec3(-1.0f,  0.0f,  -5.0f), // FRONT - CENTER UP
    glm::vec3(0.0f,   0.0f,  -5.0f),

    glm::vec3(-2.0f, -1.0f,  -5.0f),
    glm::vec3(-1.0f, -1.0f,  -5.0f),
    glm::vec3(0.0f,  -1.0f,  -5.0f),

    glm::vec3(-2.0f, -2.0f,  -5.0f),
    glm::vec3(-1.0f, -2.0f,  -5.0f),
    glm::vec3(0.0f,  -2.0f,  -5.0f),

    // 2 side
    glm::vec3(-2.0f,  0.0f,  -6.0f),
    glm::vec3(-1.0f,  0.0f,  -6.0f),
    glm::vec3(0.0f,   0.0f,  -6.0f),

    glm::vec3(-2.0f, -1.0f,  -6.0f),
    glm::vec3(-1.0f, -1.0f,  -6.0f),
    glm::vec3(0.0f,  -1.0f,  -6.0f),

    glm::vec3(-2.0f, -2.0f,  -6.0f),
    glm::vec3(-1.0f, -2.0f,  -6.0f),
    glm::vec3(0.0f,  -2.0f,  -6.0f),

    // 3 side
    glm::vec3(-2.0f,  0.0f,  -7.0f),
    glm::vec3(-1.0f,  0.0f,  -7.0f),
    glm::vec3(0.0f,   0.0f,  -7.0f),

    glm::vec3(-2.0f, -1.0f,  -7.0f),
    glm::vec3(-1.0f, -1.0f,  -7.0f),
    glm::vec3(0.0f,  -1.0f,  -7.0f),

    glm::vec3(-2.0f, -2.0f,  -7.0f),
    glm::vec3(-1.0f, -2.0f,  -7.0f),
    glm::vec3(0.0f,  -2.0f,  -7.0f),

};

int main()
{
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

    

    // load and create a texture 
    unsigned int texture1, texture2, texture3, texture4, texture5, texture6;
    // texture 1
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // flipped texture?
    unsigned char* data = stbi_load("colors/red.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    // texture 2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    //data = stbi_load("C:/LIB/assets/container.png", &width, &height, &nrChannels, 0);
    data = stbi_load("colors/green.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
 
    // texture 3
    glGenTextures(1, &texture3);
    glBindTexture(GL_TEXTURE_2D, texture3);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(true); // flipped texture
    data = stbi_load("colors/blue.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    // texture 4
    glGenTextures(1, &texture4);
    glBindTexture(GL_TEXTURE_2D, texture4);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(true); // flipped texture
    data = stbi_load("colors/yellow.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
   
    // texture 5
    glGenTextures(1, &texture5);
    glBindTexture(GL_TEXTURE_2D, texture5);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(true); // flipped texture
    data = stbi_load("colors/white.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // texture 6
    glGenTextures(1, &texture6);
    glBindTexture(GL_TEXTURE_2D, texture6);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    stbi_set_flip_vertically_on_load(true); // flipped texture
    data = stbi_load("colors/orange.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

   
   
   
 
  

    // sampler
    //ourShader.use();
    //ourShader.setInt("texture1", 0);
    //ourShader.setInt("texture2", 1);

    

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
                // activited special texture for each side   
                if (sideCube[i][j] == 1)        // red
                {
                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_2D, texture1);
                    ourShader.setInt("texture1", 0);
                }
                else if (sideCube[i][j] == 2)   // green
                {
                    glActiveTexture(GL_TEXTURE2);
                    glBindTexture(GL_TEXTURE_2D, texture2);
                    ourShader.setInt("texture1", 1);
                }
                else if (sideCube[i][j] == 3)   //blue
                {
                    glActiveTexture(GL_TEXTURE3);
                    glBindTexture(GL_TEXTURE_2D, texture3);
                    ourShader.setInt("texture1", 2);
                }
                else if (sideCube[i][j] == 4)   // yellow
                {
                    glActiveTexture(GL_TEXTURE4);
                    glBindTexture(GL_TEXTURE_2D, texture4);
                    ourShader.setInt("texture1", 3);
                }
                else if (sideCube[i][j] == 5)   // white
                {
                    glActiveTexture(GL_TEXTURE5);
                    glBindTexture(GL_TEXTURE_2D, texture5);
                    ourShader.setInt("texture1", 4);
                }
                else if(sideCube[i][j] == 6) {  // orange
                    glActiveTexture(GL_TEXTURE6);
                    glBindTexture(GL_TEXTURE_2D, texture6);
                    ourShader.setInt("texture1", 5);
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
        else if ( i == 1)
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
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        turn_cube_to_full();
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
        turn_cube_up_to_down(0, 3);
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
        turn_cube_up_to_down(1, 3);
    if (key == GLFW_KEY_3 && action == GLFW_PRESS)
        turn_cube_up_to_down(2, 3);
    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
        turn_cube_down_to_up(0, 3);
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        turn_cube_down_to_up(1, 3);
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
        turn_cube_down_to_up(2, 3);
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        turn_cube_left_to_right(0, 9);
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        turn_cube_left_to_right(3, 9);
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
        turn_cube_left_to_right(6, 9);
    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
        turn_cube_right_to_left(0, 9);
    if (key == GLFW_KEY_X && action == GLFW_PRESS)
        turn_cube_right_to_left(3, 9);
    if (key == GLFW_KEY_C && action == GLFW_PRESS)
        turn_cube_right_to_left(6, 9);

    
    // checking here for stop timing if all is complete
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


void turn_cube_up_to_down(int which, int each)
{
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
}


void turn_cube_down_to_up(int which, int each)
{
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

        sideCube[which + 2 * each][i] = sideCube[which + 2 * each + 2 *9][i];
        sideCube[which + each][i] = sideCube[which + 2 * each + 9][i];
        sideCube[which][i] = sideCube[which + 2 * each][i];

        sideCube[which + 2 * each + 2 * 9][i] = sideCube[which + 2 * 9][i];
        sideCube[which + 2 * each + 9][i] = sideCube[which + each + 2 * 9][i];
        sideCube[which + 2 * each][i] = sideCube[which + 2 * each + 2 * 9][i];

        sideCube[which + 2 * 9][i] = a;
        sideCube[which + each + 2 * 9][i] = b;
        sideCube[which + 2 * each + 2 * 9][i] = c;
    }
}
void turn_cube_left_to_right(int which, int each)
{
    int a, b, c;

    a = sideCube[which][2];
    b = sideCube[which + each][2];
    c = sideCube[which + 2* each][2];

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
}

void turn_cube_right_to_left(int which, int each) {
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
}
 
void print_cube_color() {
    for (int i = 0; i < 27; i++)
    {
        std::cout << i << ": " << sideCube[i][0] << sideCube[i][1] << sideCube[i][2] << sideCube[i][3] << sideCube[i][4] << sideCube[i][5] << std::endl;
    }
}
