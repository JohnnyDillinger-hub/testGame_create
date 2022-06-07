#ifndef TEX_RENDERER_H
#define TEX_RENDERER_H

#include <map>

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "texture.h"
#include "shader.h"
#include "resource_manager.h"

// Информация о состоянии символа, загруженному с помощью библиотеки FreeType
struct Character {
    unsigned int TextureID; // ID текстуры глифа
    unsigned int Advance; // горизонтальное смещение для перехода к следующему глифу

    glm::ivec2 Size; // размер глифа
    glm::ivec2 Bearing; // смещение от линии шрифта до верхнего левого угла глифа
};

// Класс TextRenderer предназначен для рендеринга текста, отображаемого шрифтом, 
// загруженным с помощью библиотеки FreeType. Загруженный шрифт обрабатывается и 
// сохраняется для последующего рендеринга в виде списка символов
class TextRenderer
{
public:

    TextRenderer(unsigned int width, unsigned int height);

    // Список предварительно скомпилированных символов из заданного шрифта
    void Load(std::string font, unsigned int fontSize);

    // Рендеринг строки текста с использованием предварительно скомпилированного списка символов
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));

private:

    unsigned int VAO, VBO;

    // Список предварительно скомпилированных символов
    std::map<char, Character> Characters;

    // Шейдер, используемый для рендеринга текста
    Shader TextShader;

};


#endif TEX_RENDERER_H