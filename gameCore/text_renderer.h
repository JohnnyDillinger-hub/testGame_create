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

// ���������� � ��������� �������, ������������ � ������� ���������� FreeType
struct Character {
    unsigned int TextureID; // ID �������� �����
    unsigned int Advance; // �������������� �������� ��� �������� � ���������� �����

    glm::ivec2 Size; // ������ �����
    glm::ivec2 Bearing; // �������� �� ����� ������ �� �������� ������ ���� �����
};

// ����� TextRenderer ������������ ��� ���������� ������, ������������� �������, 
// ����������� � ������� ���������� FreeType. ����������� ����� �������������� � 
// ����������� ��� ������������ ���������� � ���� ������ ��������
class TextRenderer
{
public:

    TextRenderer(unsigned int width, unsigned int height);

    // ������ �������������� ���������������� �������� �� ��������� ������
    void Load(std::string font, unsigned int fontSize);

    // ��������� ������ ������ � �������������� �������������� ����������������� ������ ��������
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));

private:

    unsigned int VAO, VBO;

    // ������ �������������� ���������������� ��������
    std::map<char, Character> Characters;

    // ������, ������������ ��� ���������� ������
    Shader TextShader;

};


#endif TEX_RENDERER_H