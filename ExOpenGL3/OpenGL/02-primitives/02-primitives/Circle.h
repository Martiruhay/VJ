#include "ShaderProgram.h"
#pragma once

class Circle
{
public:
	static Circle *createCircle(float centerX, float centerY, float radi, ShaderProgram &program);

	Circle(float centerX, float centerY, float radi, ShaderProgram &program);

	void render() const;
	void free();

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation;
};

