#ifndef _ENTITY_MAP_INCLUDE
#define _ENTITY_MAP_INCLUDE
#pragma once
#include <glm/glm.hpp>
#include "Sprite.h"
#include "ShaderProgram.h"
#include "Entity.h"

// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.


class EntityMap
{

public:
	// Tile maps can only be created inside an OpenGL context
	static EntityMap *createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);

	EntityMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);
	~EntityMap();

	void render() const;
	void update(int delta);
	void free();
	void interactEntitiesWithActor(GameActor &actor);
	int getTileSize() const { return tileSize; }

private:
	bool loadLevel(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);

private:
	GLint posLocation, texCoordLocation;
	glm::ivec2 position, mapSize, tilesheetSize;
	int tileSize, blockSize;
	glm::vec2 tileTexSize;
	Texture spritesheet;
	std::vector<Entity* > entities;
	//std::vector<Entity> *map;

};


#endif // _ENTITY_MAP_INCLUDE


