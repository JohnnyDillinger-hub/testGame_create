#ifndef POST_PROCESSOR_H
#define POST_PROCESSOR_H

#include <glad/glad.h>
#include <glm.hpp>

#include <iostream>

#include "texture.h"
#include "sprite_renderer.h"
#include "shader.h"


// Класс PostProcessor содержит все используемые в игре "Breakout" эффекты постобработки. 
// Он производит рендеринг игры в текстурированный прямоугольник,
// после чего мы можем задействовать определенные эффекты типа Shake, Confuse или Chaos.
// Для работы класса перед рендерингом игры требуется вызвать функцию BeginRender(), 
// а в конце рендеринга - функцию EndRender()
class PostProcessor
{
public:

	PostProcessor(Shader shader, unsigned int width, unsigned int height);

	// Подготовка операций фреймбуфера постпроцессора перед рендерингом игры
	void BeginRender();

	// Фукнция должна вызываться после рендеринга игры, все визуализированные данные сохраняются в текстуре
	void EndRender();

	// Рендерим текстуру объекта класса PostProcessor (в качестве большого, охватывающего экран, спрайта)
	void Render(float time);

	void SetShake(bool shake);
	void SetConfuse(bool confuse);
	void SetChaos(bool chaos);

	bool GetShake();
	bool GetConfuse();
	bool GetChaos();

	
private:

	unsigned int MSFBO, FBO; // MSFBO = Мультисэмплированный фреймбуфер (FBO)
	unsigned int RBO; // RBO используется для мультисэмплированного цветового буфера
	unsigned int VAO;

	// Опции
	bool Confuse, Chaos, Shake;

	// Состояние
	Shader PostProcessingShader;
	Texture2D Texture;
	unsigned int Width, Height;

	

	// Инициализация прямоугольника для рендеринга текстуры постобработки
	void initRenderData();

};

#endif POST_PROCESSOR_H