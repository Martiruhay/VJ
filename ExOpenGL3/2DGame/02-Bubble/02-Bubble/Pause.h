#ifndef _PAUSE_INCLUDE
#define _PAUSE_INCLUDE
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Sprite.h"
class Pause
{
public:
	Pause();
	~Pause();
	void init(ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
private:
	void initShaders();
	ShaderProgram texProgram;
	glm::mat4 projection;
	Texture menu_tex;
	Sprite *sprite;
};

#endif // _PAUSE_INCLUDE
