#include <GL/glew.h>
#include <GL/gl.h>
#include "Circle.h"
#include <cmath>
#include <iostream>
#define M_PI 3.1415926535897932384626433832795
#define N 100


Circle *Circle::createCircle(float centerX, float centerY, float radi, ShaderProgram &program)
{
	Circle *circle = new Circle(centerX, centerY, radi, program);

	return circle;
}


Circle::Circle(float centerX, float centerY, float radi, ShaderProgram &program)
{
	float vertices[N*6];
	float xPrev, yPrev;

	xPrev = centerX + radi;
	yPrev = centerY;
	for (int i = 0; i < N*6; i+=6){
		float angle = 2 * M_PI * (i+6) / (N*6);
		float x = cos(angle);
		float y = sin(angle);

		std::cout << "x: " << x << " y: " << y << std::endl;

		vertices[i] = centerX;
		vertices[i+1] = centerY;
		vertices[i+2] = x;
		vertices[i+3] = y;
		vertices[i+4] = xPrev;
		vertices[i+5] = yPrev;

		xPrev = x;
		yPrev = y;
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 6*N*sizeof(float), vertices, GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2);
}

void Circle::render() const
{
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glDrawArrays(GL_TRIANGLES, 0, 3*N);
}

void Circle::free()
{
	glDeleteBuffers(1, &vbo);
}
