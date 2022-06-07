#ifndef POST_PROCESSOR_H
#define POST_PROCESSOR_H

#include <glad/glad.h>
#include <glm.hpp>

#include <iostream>

#include "texture.h"
#include "sprite_renderer.h"
#include "shader.h"


// ����� PostProcessor �������� ��� ������������ � ���� "Breakout" ������� �������������. 
// �� ���������� ��������� ���� � ���������������� �������������,
// ����� ���� �� ����� ������������� ������������ ������� ���� Shake, Confuse ��� Chaos.
// ��� ������ ������ ����� ����������� ���� ��������� ������� ������� BeginRender(), 
// � � ����� ���������� - ������� EndRender()
class PostProcessor
{
public:

	PostProcessor(Shader shader, unsigned int width, unsigned int height);

	// ���������� �������� ����������� �������������� ����� ����������� ����
	void BeginRender();

	// ������� ������ ���������� ����� ���������� ����, ��� ����������������� ������ ����������� � ��������
	void EndRender();

	// �������� �������� ������� ������ PostProcessor (� �������� ��������, ������������� �����, �������)
	void Render(float time);

	void SetShake(bool shake);
	void SetConfuse(bool confuse);
	void SetChaos(bool chaos);

	bool GetShake();
	bool GetConfuse();
	bool GetChaos();

	
private:

	unsigned int MSFBO, FBO; // MSFBO = �������������������� ���������� (FBO)
	unsigned int RBO; // RBO ������������ ��� ��������������������� ��������� ������
	unsigned int VAO;

	// �����
	bool Confuse, Chaos, Shake;

	// ���������
	Shader PostProcessingShader;
	Texture2D Texture;
	unsigned int Width, Height;

	

	// ������������� �������������� ��� ���������� �������� �������������
	void initRenderData();

};

#endif POST_PROCESSOR_H