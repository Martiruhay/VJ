#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"


Scene::Scene()
{
	quad = NULL;
}

Scene::~Scene()
{
	if(quad != NULL)
		delete quad;
	for(int i=0; i<3; i++)
		if(texQuad[i] != NULL)
			delete texQuad[i];
}


void Scene::init()
{
	glm::vec2 geom[2] = {glm::vec2(0.f, 0.f), glm::vec2(128.f, 128.f)};
	glm::vec2 texCoords[2] = {glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f)};

	initShaders();
	quad = Quad::createQuad(0.f, 0.f, CAMERA_WIDTH, CAMERA_HEIGHT, simpleProgram);

	//Bolet
	texCoords[0] = glm::vec2(0.f, 0.5f); texCoords[1] = glm::vec2(0.5f, 1.f);
	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	//Terra
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(5.f, 1.f);
	texQuad[2] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	//Mr.Orange
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	texQuad[3] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	//Mario
	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(128.f, 128.f);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(0.5f, 0.5f);
	texQuad[1] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	//Clouds
	geom[0] = glm::vec2(0.f, 0.f); geom[1] = glm::vec2(CAMERA_WIDTH, CAMERA_HEIGHT);
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	texQuad[4] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	// Load textures
	texs[0].loadFromFile("images/varied.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[1].loadFromFile("images/rocks.jpg", TEXTURE_PIXEL_FORMAT_RGB);
	texs[2].loadFromFile("images/pj4.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[3].loadFromFile("images/clouds.jpg", TEXTURE_PIXEL_FORMAT_RGB);
	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
}

void Scene::render()
{
	float move = sin(currentTime / 1000.f);
	float scale = sin(currentTime / 150.f)/10.f + 0.9f;

	glm::mat4 modelview;

	simpleProgram.use();
	simpleProgram.setUniformMatrix4f("projection", projection);
	simpleProgram.setUniform4f("color", 0.4f, 1.f, 1.f, 1.0f);

	//Cel
	//modelview = glm::translate(glm::mat4(1.0f), glm::vec3(128.f, 48.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	//modelview = glm::rotate(modelview, -currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
	simpleProgram.setUniformMatrix4f("modelview", modelview);
	quad->render();

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	//Clouds
	//modelview = glm::translate(modelview, glm::vec3(CAMERA_WIDTH / 2.f - 64, 304.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	//modelview = glm::scale(modelview, glm::vec3(1.f, 1.f, 1.f));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[4]->render(texs[3]);
	//Terra
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(CAMERA_WIDTH / 2.f - 64.f, 480.f - 128, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	//modelview = glm::rotate(modelview, -currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelview = glm::scale(modelview, glm::vec3(5.f, 1.f, 1.f));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[2]->render(texs[1]);
	//Bolet
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(move*CAMERA_WIDTH / 2.f, 0.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(CAMERA_WIDTH / 2.f - 64, 304.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	//modelview = glm::rotate(modelview, currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelview = glm::scale(modelview, glm::vec3(scale, scale, 1.f));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[0]->render(texs[0]);
	//Mario
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(128.f, 304.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	//modelview = glm::rotate(modelview, currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[1]->render(texs[0]);
	//Mr.Orange
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(512.f, 0.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	modelview = glm::rotate(modelview, 4*currentTime / 1000.f, glm::vec3(0.0f, 0.0f, 1.0f));
	//modelview = glm::scale(modelview, glm::vec3(0.5f, 0.5f, 1.f));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texQuad[3]->render(texs[2]);
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/simple.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/simple.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	simpleProgram.init();
	simpleProgram.addShader(vShader);
	simpleProgram.addShader(fShader);
	simpleProgram.link();
	if(!simpleProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << simpleProgram.log() << endl << endl;
	}
	simpleProgram.bindFragmentOutput("outColor");

	vShader.free();
	fShader.free();
	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
}

