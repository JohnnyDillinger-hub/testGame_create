#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>


#include <glad/glad.h>

#include "texture.h"
#include "shader.h"

#include "stb_image.h"

// ����������� singleton-����� ResourceManager, ���������� ��������� ������� ��� �������� ������� � ��������. 
// ������ ����������� �������� �/��� ������ ����������� ��� ����������� �������������
class ResourceManager
{
public:

	// ��������� ��������
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Texture2D> Textures;

	// ���� gShaderFile !=  nullptr, �� ����� ����������� � �������������� ������
	static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);

	// �������� ����������� ������
	static Shader GetShader(std::string name);

	// ��������� (� ����������) �������� �� �����
	static Texture2D LoadTexture(const char* file, bool alpha, std::string name);

	// �������� ����������� ��������
	static Texture2D GetTexture(std::string name);

	// ���������� ������������ ������ ���� ����������� ��������
	static void Clear();

private:

	// private-�����������, �.�. �� �� �����, ����� ����������� �������� ������� ��������� ��������. ��� ����� � ������� ������ ���� �������������� (����������)
	ResourceManager() {};

	// ��������� � ���������� ������ �� �����
	static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);

	// ��������� �������� �� �����
	static Texture2D loadTextureFromFile(const char* file, bool alpha);

};

#endif RESOURCE_MANAGER_H	