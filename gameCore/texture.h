#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <glm.hpp>

// Texture2D хранит в себе текстуру и может производить её конфигурирование.
// Он также содержит служебные функции для простоты управления
class Texture2D
{
public:

	// Содержит ID объекта текстуры, используемый для всех операций с конкретной текстурой
	unsigned int ID;

	unsigned int Width, Height; // ширина и высота (в пикселях) загруженного изображения

	unsigned int Internal_Format; // внутренний формат текстуры
	unsigned int Image_Format; // формат загружаемого изображения

	unsigned int Wrap_S; // режим наложения по оси S
	unsigned int Wrap_T; // режим наложения по оси T

	unsigned int Filter_Min; // режим фильтрации, если пикселей текстуры < пикселей экрана
	unsigned int Filter_Max; // режим фильтрации, если пикселей текстуры > пикселей экрана

	Texture2D();

	void Generate(unsigned int width, unsigned int height, unsigned char* data);

	void Bind()	const;

};

#endif TEXTURE_H