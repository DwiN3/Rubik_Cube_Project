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