#include "cube.h"

/// <summary>
/// Ustawienie parametrów dla tekstur.
/// </summary>
void dataTextureLoad() {
    // ustawianie parametrów wrap oraz repeat
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // ustawienie filtrowania oraz liniowej tekstury.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true); // odwrócenie tekstury 
}

/// <summary>
/// LoadData generuje oraz zwraca teksture.
/// </summary>
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

/// <summary>
/// Funkcja ³aduj¹ca textury które s¹ nak³adane na kostkê
/// </summary>
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