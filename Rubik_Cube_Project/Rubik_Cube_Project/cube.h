#pragma once
#ifndef CUBE_H
#define CUBE_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include <C:/LIB/stb/stb_image.h>
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
using namespace std::experimental::filesystem;



/// <summary>
/// Szeroko�� okna.
/// </summary>
extern const unsigned int SCR_WIDTH;
/// <summary>
/// Wysoko�� okna.
/// </summary>
extern const unsigned int SCR_HEIGHT;

/// <summary>
/// Ustawienia pozycji pocz�tkowej kamery.
/// </summary>
extern Camera camera;

/// <summary>
/// Poprzednia pozycja X, u�ywana do �ledzenia ruchu myszy.
/// </summary>
extern float lastX;

/// <summary>
/// Poprzednia pozycja Y, u�ywana do �ledzenia ruchu myszy.
/// </summary>
extern float lastY;

/// <summary>
/// Dodaj obs�ug� myszki
/// </summary>
extern bool firstMouse;

/// <summary>
/// Zmienna ustawiaj�ca warto�� pomi�dzy klatkami.
/// </summary>
extern float deltaTime;
/// <summary>
/// Zmienna ustawiaj�ca warto�� ostaniej klatki.
/// </summary>
extern float lastFrame;

/// <summary>
/// Zmienna przyjmuj�ca warto�� startu timera.
/// </summary>
extern chrono::time_point<chrono::high_resolution_clock> start_timer;
/// <summary>
/// Zmienna przyjmuj�ca warto�� zatrzymania timera.
/// </summary>
extern chrono::time_point<chrono::high_resolution_clock> end_timer;
/// <summary>
/// Zmienna przechowywuj�ca czas u�o�enia kostki.
/// </summary>
extern chrono::duration<double> duration;

/// <summary>
/// Zmienna przechowuj�ca ilo�� rekord�w.
/// </summary>
extern const int TOP_SCORES_COUNT;
/// <summary>
/// Ranking czas�w u�o�enia.
/// </summary>
extern double top_scores[5];

/// <summary>
/// Wyb�r koloru odpowiedniego dla danego u�ytkownika.
/// </summary>
extern int color;

/// <summary>
/// Zmiena przechowuj�ca stan uk�adania kostki.
/// </summary>
extern bool arranging;

/// <summary>
/// Zmienne przechowuj�ce wykonane ruchy.
/// </summary>
extern int count_moves;
/// <summary>
/// Zmienne przechowuj�ce wykonane ruchy poprzez mieszanie.
/// </summary>
extern int random_moves;

/// <summary>
/// Zmienne przechowuj�c� podpowied�.
/// </summary>
extern string solve;
/// <summary>
/// Zmienne przechowuj�c� stan u�ycia podpowiedzi.
/// </summary>
extern bool isSolved;

/// <summary>
/// Zmienne przechowuj�ce domy�lne tekstury.
/// </summary>
extern unsigned int textureClassic1, textureClassic2, textureClassic3, textureClassic4, textureClassic5, textureClassic6;
/// <summary>
/// Zmienne przechowuj�ce tekstury z deuteranopii.
/// </summary>
extern unsigned int textureDeuteranopia1, textureDeuteranopia2, textureDeuteranopia3, textureDeuteranopia4, textureDeuteranopia5, textureDeuteranopia6;
/// <summary>
/// Zmienne przechowuj�ce tekstury z tritanopii.
/// </summary>
extern unsigned int textureTritanopia1, textureTritanopia2, textureTritanopia3, textureTritanopia4, textureTritanopia5, textureTritanopia6;



/// <summary>
/// Tablice wy�wietlaj� serce kostki rubika kt�ra zapami�tuje sw�j stan.
/// </summary>
extern int sideCube[27][6];

/// <summary>
/// Pozycje kostek czyli rozmieszczenie kostek aby uformowa�y si� w jedn� kostk� "Rubik's Cube.
/// </summary>
extern glm::vec3 cubePositions[27];


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
void loadTextures();
void loadData(unsigned char* data, int width, int height);
void dataTextureLoad();


#endif // CUBE_H