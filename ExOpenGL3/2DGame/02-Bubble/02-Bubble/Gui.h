#pragma once
#include "Sprite.h"
#include "Player.h"
class Gui
{
public:
	Gui();
	void init(Player *pl, ShaderProgram &shaderProgram);
	~Gui();
	void render();
	void update(int deltaTime, glm::vec2 proj_position);
	Player *player;
	Sprite *hearts;
	Texture spritesheet;
	glm::vec2 position;
};

