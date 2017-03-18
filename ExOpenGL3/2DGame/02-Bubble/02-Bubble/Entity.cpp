#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Entity.h"
#include "Game.h"



enum Animations
{
	ANIM1, ANIM2
};

Entity::Entity()
{
	type = 0;
}


Entity::~Entity()
{
}
void Entity::init(const glm::ivec2 &tileMapPos, glm::ivec2 &pos, ShaderProgram &shaderProgram, Texture &spritesheet, int tp )
{
	tileMapDispl = tileMapPos;
	position = pos;
	position = glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y));
	type = tp;
	
	sprite = Sprite::createSprite(glm::ivec2(64, 46), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);		//el 46 es superhardcoded
	sprite->setPosition(position);
	
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(ANIM1, 8);
	
	if (type == 1){
		sprite->addKeyframe(ANIM1, glm::vec2(0.f, 0.f));
		col_position = glm::vec2(position.x+16, position.y+8);
		col_size = glm::vec2(32, 38);

	}
	else if (type == 2){
		sprite->setAnimationSpeed(ANIM1, 8);
		sprite->addKeyframe(ANIM1, glm::vec2(0.f, 0.25f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.25f, 0.25f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.5f, 0.25f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.5f, 0.25f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.5f, 0.25f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.5f, 0.25f));
		col_position = glm::vec2(position.x + 16, position.y + 20);
		col_size = glm::vec2(32, 26);
	}
	else if (type == 3){
		position  = glm::vec2(position.x + 3, position.y + 12);
		sprite->setPosition(position);
		sprite->addKeyframe(ANIM1, glm::vec2(0.f, 0.5f));
		col_position = glm::vec2(position.x + 16, position.y + 32);
		col_size = glm::vec2(32, 14);
	}
	else if (type == 4){
		position = glm::vec2(position.x + 3, position.y + 12);
		sprite->setPosition(position);
		sprite->addKeyframe(ANIM1, glm::vec2(0.25f, 0.5f));
		col_position = glm::vec2(position.x + 16, position.y + 32);
		col_size = glm::vec2(32, 14);
	}
	else if (type == 5){
		position = glm::vec2(position.x + 3, position.y + 12);
		sprite->setPosition(position);
		sprite->addKeyframe(ANIM1, glm::vec2(0.5f, 0.5f));
		col_position = glm::vec2(position.x + 16, position.y + 32);
		col_size = glm::vec2(32, 14);
	}
	sprite->changeAnimation(ANIM1);
}

void Entity::update(int deltaTime)
{
	sprite->update(deltaTime);
	
}

void Entity::render()
{
	
	sprite->render();
}






