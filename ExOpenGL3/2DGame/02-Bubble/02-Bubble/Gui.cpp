#include "Gui.h"
#include "Player.h"
#include "Game.h"


#define SIZE_HEART 16
Gui::Gui()
{
}
Gui::~Gui()
{
}

enum HeartStatus
{
	FULL_H, EMPTY_H
};
void Gui::init(Player *pl, ShaderProgram &shaderProgram)
{
	player = pl;
	position = glm::vec2(0.f, 0.f);
	spritesheet.loadFromFile("images/hearts.png", TEXTURE_PIXEL_FORMAT_RGBA);
	hearts = Sprite::createSprite(glm::ivec2(SIZE_HEART, SIZE_HEART), glm::vec2(0.5, 1), &spritesheet, &shaderProgram);
	hearts->setNumberAnimations(2);

	hearts->setAnimationSpeed(FULL_H, 8);
	hearts->addKeyframe(FULL_H, glm::vec2(0.f, 0.f));

	hearts->setAnimationSpeed(EMPTY_H, 8);
	hearts->addKeyframe(EMPTY_H, glm::vec2(0.5f, 0.f));

}
void Gui::render()
{
	int num_lives = player->health;
	int max_lives = player->max_health;

	hearts->changeAnimation(FULL_H);
	for (int i = 0; i < num_lives; i++){
		hearts->setPosition(glm::vec2(position.x + SIZE_HEART*i, position.y));
		hearts->render();
	}
	hearts->changeAnimation(EMPTY_H);
	for (int i = num_lives; i < max_lives; i++){
		hearts->setPosition(glm::vec2(position.x + SIZE_HEART*i, position.y));
		hearts->render();
	}
	
}
void Gui::update(int deltaTime, glm::vec2 proj_position)
{
	hearts->update(deltaTime);
	position = proj_position;
}