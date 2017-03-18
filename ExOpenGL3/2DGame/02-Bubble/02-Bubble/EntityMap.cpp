#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "EntityMap.h"


using namespace std;


EntityMap *EntityMap::createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	
	EntityMap *map = new EntityMap(levelFile, minCoords, program);

	return map;
}


EntityMap::EntityMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);	//per a fer servir coordenades negatives i fer mirror
	spritesheet.loadFromFile("images/entities.png", TEXTURE_PIXEL_FORMAT_RGBA);
	loadLevel(levelFile, minCoords, program);
	//prepareArrays(minCoords, program);
}

EntityMap::~EntityMap()
{
	//if (entities != NULL)
		//delete entities;
}

void EntityMap::update(int deltaTime)
{
	for (int i = 0; i < entities.size(); i++){
		entities[i]->update(deltaTime);
	}
}
void EntityMap::render() const
{
	for (int i = 0; i < entities.size(); i++){
		entities[i]->render();
	}
	
}

void EntityMap::free()
{

}

bool EntityMap::loadLevel(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{

	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	char tile;

	fin.open(levelFile.c_str());
	if (!fin.is_open())
		return false;
	getline(fin, line);
	if (line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize >> blockSize;
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetFile;
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);
	//map = new Entity[mapSize.x * mapSize.y];
	
	for (int j = 0; j<mapSize.y; j++)
	{
		for (int i = 0; i<mapSize.x; i++)
		{
			fin.get(tile);
			//if (tile != ' ') map[j*mapSize.x + i].init(minCoords, program, tile - int('0'));
			if (tile == '1' || tile == '2' || tile == '3' || tile == '4' || tile == '5') {
				Entity *ent = new Entity();
				ent->init(minCoords, glm::ivec2(i *tileSize, j * tileSize), program,spritesheet, tile - int('0'));
				entities.push_back(ent);
			}
		}
		fin.get(tile);
#ifndef _WIN32
		fin.get(tile);
#endif
	}
	fin.close();
	
	return true;
}
































