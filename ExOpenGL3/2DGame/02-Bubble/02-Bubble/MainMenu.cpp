#include "MainMenu.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include <iostream>
#include <sstream>
MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
}

void MainMenu::init(ShaderProgram &shaderProgram)
{
	menu_status = 0;
	texProgram = shaderProgram;
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	menu_tex.loadFromFile("images/menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1.f, 1.f), &menu_tex, &texProgram);

	menu_tex2.loadFromFile("images/help.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_help = Sprite::createSprite(glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1.f, 1.f), &menu_tex2, &texProgram);

	menu_tex3.loadFromFile("images/credits.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite_credits = Sprite::createSprite(glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1.f, 1.f), &menu_tex3, &texProgram);

	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(0, 8);
	sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(0), float(0)));

	sprite_help->setNumberAnimations(1);
	sprite_help->setAnimationSpeed(0, 8);
	sprite_help->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite_help->changeAnimation(0);
	sprite_help->setPosition(glm::vec2(float(0), float(0)));

	sprite_credits->setNumberAnimations(1);
	sprite_credits->setAnimationSpeed(0, 8);
	sprite_credits->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite_credits->changeAnimation(0);
	sprite_credits->setPosition(glm::vec2(float(0), float(0)));

}


void MainMenu::update(int deltaTime)
{
	sprite->update(deltaTime);
}

void MainMenu::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	if (menu_status == 0) sprite->render();
	else if (menu_status == 1) sprite_help->render();
	else if (menu_status == 2) sprite_credits->render();

}