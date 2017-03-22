#ifndef _ENTITY_INCLUDE
#define _ENTITY_INCLUDE

#pragma once
#include "Sprite.h"
#include "GameActor.h"

// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Entity
{

public:
	Entity();
	~Entity();
	void init(const glm::ivec2 &tileMapPos, glm::ivec2 &pos, ShaderProgram &shader, Texture &spritesheet , int tp);
	void update(int deltaTime);
	void render();
	bool collides(glm::vec2 pos, glm::vec2 size);
	bool action(GameActor &actor);
	int type;

private:
	bool overlapping1D(glm::vec2 box1, glm::vec2 box2);
	glm::ivec2 tileMapDispl, position, col_position, col_size;
	Sprite *sprite;

};


#endif // _ENTITY_INCLUDE


