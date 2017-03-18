#include "Pause.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include <iostream>
#include <sstream>
Pause::Pause()
{
}


Pause::~Pause()
{
}

void Pause::init(ShaderProgram &shaderProgram)
{
	texProgram = shaderProgram;
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	menu_tex.loadFromFile("images/pause.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(SCREEN_WIDTH/2, SCREEN_HEIGHT/4), glm::vec2(1.f, 1.f), &menu_tex, &texProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));


	sprite->changeAnimation(0);
	
	sprite->setPosition(glm::vec2(float(SCREEN_WIDTH / 2 - SCREEN_WIDTH / 4), float(SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 8)));

}


void Pause::update(int deltaTime)
{
	sprite->update(deltaTime);
}

void Pause::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	sprite->render();
	texProgram.free();

}