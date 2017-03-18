#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "EntityMap.h"
#include "Player.h"
#include "Gui.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	ShaderProgram& getProgram();
private:
	void initShaders();

private:
	EntityMap *entities;
	TileMap *map;
	TileMap *background;
	TileMap *foreground;
	Gui *gui;
	Player *player;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;

};


#endif // _SCENE_INCLUDE

