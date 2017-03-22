#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define STEP 32;


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{

	float stepX = 1.0f / 15.0f;
	float stepY = 1.0f / 20.0f;

	health = 3;
	max_health = 4;
	bJumping = false;
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);	//per a fer servir coordenades negatives i fer mirror
	spritesheet.loadFromFile("images/Prince.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(stepX, stepY), &spritesheet, &shaderProgram);
	
	sprite->setNumberAnimations(20);
	
		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(-1*stepX, 0.f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
		
		sprite->setAnimationSpeed(RUN_LEFT, 15);
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-1 *stepX, 0.f));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-1* stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-2* stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-3* stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-4* stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-5* stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-6* stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-7* stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-8* stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-9* stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-10*stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-11*stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-12*stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-13*stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-14*stepX, stepY));

		sprite->setAnimationSpeed(RUN_RIGHT, 15);
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(0*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(1*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(2*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(3*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(4*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(5*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(6*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(7*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(8*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(9*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(10*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(11*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(12*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(13*stepX, stepY));

		sprite->setAnimationSpeed(WALK_RIGHT, 12);
		sprite->addKeyframe(WALK_RIGHT, glm::vec2(0 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_RIGHT, glm::vec2(1 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_RIGHT, glm::vec2(2 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_RIGHT, glm::vec2(3 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_RIGHT, glm::vec2(4 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_RIGHT, glm::vec2(5 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_RIGHT, glm::vec2(6 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_RIGHT, glm::vec2(7 * stepX, 3 * stepY));

		sprite->setAnimationSpeed(WALK_LEFT, 12);
		sprite->addKeyframe(WALK_LEFT, glm::vec2(-1 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_LEFT, glm::vec2(-2 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_LEFT, glm::vec2(-3 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_LEFT, glm::vec2(-4 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_LEFT, glm::vec2(-5 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_LEFT, glm::vec2(-6 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_LEFT, glm::vec2(-7 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_LEFT, glm::vec2(-8 * stepX, 3 * stepY));


		sprite->setAnimationSpeed(JUMP_RUN_RIGHT, 6);
		sprite->addKeyframe(JUMP_RUN_RIGHT, glm::vec2(0*stepX, 2*stepY));
		sprite->addKeyframe(JUMP_RUN_RIGHT, glm::vec2(1*stepX, 2*stepY));
		sprite->addKeyframe(JUMP_RUN_RIGHT, glm::vec2(2*stepX, 2*stepY));
		sprite->addKeyframe(JUMP_RUN_RIGHT, glm::vec2(3*stepX, 2*stepY));
		sprite->addKeyframe(JUMP_RUN_RIGHT, glm::vec2(4*stepX, 2*stepY));
		sprite->addKeyframe(JUMP_RUN_RIGHT, glm::vec2(5*stepX, 2*stepY));
		sprite->addKeyframe(JUMP_RUN_RIGHT, glm::vec2(6*stepX, 2*stepY));
		sprite->addKeyframe(JUMP_RUN_RIGHT, glm::vec2(7*stepX, 2*stepY));
		sprite->addKeyframe(JUMP_RUN_RIGHT, glm::vec2(8*stepX, 2*stepY));
		sprite->addKeyframe(JUMP_RUN_RIGHT, glm::vec2(9*stepX, 2*stepY));
		
		sprite->setAnimationSpeed(JUMP_RUN_LEFT, 6);
		sprite->addKeyframe(JUMP_RUN_LEFT, glm::vec2(-1 * stepX, 2 * stepY));
		sprite->addKeyframe(JUMP_RUN_LEFT, glm::vec2(-2 * stepX, 2 * stepY));
		sprite->addKeyframe(JUMP_RUN_LEFT, glm::vec2(-3 * stepX, 2 * stepY));
		sprite->addKeyframe(JUMP_RUN_LEFT, glm::vec2(-4 * stepX, 2 * stepY));
		sprite->addKeyframe(JUMP_RUN_LEFT, glm::vec2(-5 * stepX, 2 * stepY));
		sprite->addKeyframe(JUMP_RUN_LEFT, glm::vec2(-6 * stepX, 2 * stepY));
		sprite->addKeyframe(JUMP_RUN_LEFT, glm::vec2(-7 * stepX, 2 * stepY));
		sprite->addKeyframe(JUMP_RUN_LEFT, glm::vec2(-8 * stepX, 2 * stepY));
		sprite->addKeyframe(JUMP_RUN_LEFT, glm::vec2(-9 * stepX, 2 * stepY));
		sprite->addKeyframe(JUMP_RUN_LEFT, glm::vec2(-10 *stepX, 2 * stepY));

		sprite->setAnimationSpeed(TURN_RIGHT, 10);
		sprite->addKeyframe(TURN_RIGHT, glm::vec2(0 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_RIGHT, glm::vec2(1 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_RIGHT, glm::vec2(2 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_RIGHT, glm::vec2(3 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_RIGHT, glm::vec2(4 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_RIGHT, glm::vec2(4 * stepX, 4 * stepY)); //copy

		sprite->setAnimationSpeed(TURN_LEFT, 10);
		sprite->addKeyframe(TURN_LEFT, glm::vec2(-1 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_LEFT, glm::vec2(-2 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_LEFT, glm::vec2(-3 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_LEFT, glm::vec2(-4 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_LEFT, glm::vec2(-5 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_LEFT, glm::vec2(-5 * stepX, 4 * stepY)); //copy

		sprite->setAnimationSpeed(STOP_RIGHT, 10);
		sprite->addKeyframe(STOP_RIGHT, glm::vec2(0 * stepX, 5 * stepY));
		sprite->addKeyframe(STOP_RIGHT, glm::vec2(1 * stepX, 5 * stepY));
		sprite->addKeyframe(STOP_RIGHT, glm::vec2(2 * stepX, 5 * stepY));
		sprite->addKeyframe(STOP_RIGHT, glm::vec2(3 * stepX, 5 * stepY));
		sprite->addKeyframe(STOP_RIGHT, glm::vec2(4 * stepX, 5 * stepY));
		sprite->addKeyframe(STOP_RIGHT, glm::vec2(5 * stepX, 5 * stepY));
		sprite->addKeyframe(STOP_RIGHT, glm::vec2(5 * stepX, 5 * stepY)); //copy

		sprite->setAnimationSpeed(STOP_LEFT, 10);
		sprite->addKeyframe(STOP_LEFT, glm::vec2(-1 * stepX, 5 * stepY));
		sprite->addKeyframe(STOP_LEFT, glm::vec2(-2 * stepX, 5 * stepY));
		sprite->addKeyframe(STOP_LEFT, glm::vec2(-3 * stepX, 5 * stepY));
		sprite->addKeyframe(STOP_LEFT, glm::vec2(-4 * stepX, 5 * stepY));
		sprite->addKeyframe(STOP_LEFT, glm::vec2(-5 * stepX, 5 * stepY));
		sprite->addKeyframe(STOP_LEFT, glm::vec2(-6 * stepX, 5 * stepY));
		sprite->addKeyframe(STOP_LEFT, glm::vec2(-6 * stepX, 5 * stepY)); //copy

		sprite->setAnimationSpeed(DOWN_RIGHT, 10);
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(1 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(2 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(3 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(4 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(5 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(6 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(7 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(8 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(9 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(10* stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(11* stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(11 * stepX, 0 * stepY)); //copy

		sprite->setAnimationSpeed(DOWN_LEFT, 10);
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(-2 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(-3 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(-4 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(-5 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(-6 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(-7 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(-8 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(-9 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(-10* stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(-11* stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(-12* stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(-13* stepX, 0 * stepY)); //copy

		sprite->setAnimationSpeed(JUMP_STAND_RIGHT, 20);
		sprite->addKeyframe(JUMP_STAND_RIGHT, glm::vec2(0 * stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_RIGHT, glm::vec2(1 * stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_RIGHT, glm::vec2(2 * stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_RIGHT, glm::vec2(3 * stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_RIGHT, glm::vec2(4 * stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_RIGHT, glm::vec2(5 * stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_RIGHT, glm::vec2(6 * stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_RIGHT, glm::vec2(7 * stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_RIGHT, glm::vec2(8 * stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_RIGHT, glm::vec2(9 * stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_RIGHT, glm::vec2(9 * stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_RIGHT, glm::vec2(8 * stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_RIGHT, glm::vec2(10* stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_RIGHT, glm::vec2(11* stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_RIGHT, glm::vec2(11* stepX, 8 * stepY)); //copy

		sprite->setAnimationSpeed(JUMP_STAND_LEFT, 10);
		sprite->addKeyframe(JUMP_STAND_LEFT, glm::vec2(-1 * stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_LEFT, glm::vec2(-2 * stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_LEFT, glm::vec2(-3 * stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_LEFT, glm::vec2(-4 * stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_LEFT, glm::vec2(-5 * stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_LEFT, glm::vec2(-6 * stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_LEFT, glm::vec2(-7 * stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_LEFT, glm::vec2(-8 * stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_LEFT, glm::vec2(-9 * stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_LEFT, glm::vec2(-10* stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_LEFT, glm::vec2(-10* stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_LEFT, glm::vec2(-9* stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_LEFT, glm::vec2(-11* stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_LEFT, glm::vec2(-12* stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_LEFT, glm::vec2(-12 * stepX, 8 * stepY)); //copy

		//TODO
		sprite->setAnimationSpeed(FALL_RIGHT, 10);
		sprite->addKeyframe(FALL_RIGHT, glm::vec2(8 * stepX, 8 * stepY));

		sprite->setAnimationSpeed(FALL_LEFT, 10);
		sprite->addKeyframe(FALL_LEFT, glm::vec2(-9 * stepX, 8 * stepY));

		sprite->setAnimationSpeed(TURN_RUN_RIGHT, 10);
		sprite->addKeyframe(TURN_RUN_RIGHT, glm::vec2(0 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_RIGHT, glm::vec2(1 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_RIGHT, glm::vec2(2 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_RIGHT, glm::vec2(3 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_RIGHT, glm::vec2(4 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_RIGHT, glm::vec2(5 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_RIGHT, glm::vec2(6 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_RIGHT, glm::vec2(7 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_RIGHT, glm::vec2(8 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_RIGHT, glm::vec2(9 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_RIGHT, glm::vec2(10* stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_RIGHT, glm::vec2(11* stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_RIGHT, glm::vec2(11* stepX, 7 * stepY)); //copy

		sprite->setAnimationSpeed(TURN_RUN_LEFT, 10);
		sprite->addKeyframe(TURN_RUN_LEFT, glm::vec2(0 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_LEFT, glm::vec2(1 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_LEFT, glm::vec2(2 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_LEFT, glm::vec2(3 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_LEFT, glm::vec2(4 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_LEFT, glm::vec2(5 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_LEFT, glm::vec2(6 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_LEFT, glm::vec2(7 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_LEFT, glm::vec2(8 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_LEFT, glm::vec2(9 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_LEFT, glm::vec2(10 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_LEFT, glm::vec2(11 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_LEFT, glm::vec2(11 * stepX, 7 * stepY)); //copy

		//END ANIMATIONS

		setAnimation(FALL_RIGHT);
		setState(FALLING_RIGHT);

	tileMapDispl = glm::vec2(0,0);;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	size = glm::vec2(float(11), float(42));
	position_col = glm::vec2(float(posPlayer.x + 16), float(posPlayer.y + 16));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	input();
	
	switch (state) {
	case STANDING_RIGHT:
		if (right && shift) {
			setState(WALKING_RIGHT);
			setAnimation(WALK_RIGHT);
		}
		else if (right) {
			setState(RUNING_RIGHT);
			setAnimation(RUN_RIGHT);
		}
		else if (left) {
			setState(TURNING_LEFT);
			setAnimation(TURN_LEFT);
		}
		else if (up) {
			state = JUMP_STANDING_RIGHT;
			setAnimation(JUMP_STAND_RIGHT);
		}
		else if (down) {
			state = DOWNING_RIGHT;
			setAnimation(DOWN_RIGHT);
		}
		break;
	case STANDING_LEFT:
		if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 64), &posPlayer.y)) {
			setState(FALLING_LEFT);
			setAnimation(FALL_RIGHT);
		}
		else if (left && shift) {
			setState(WALKING_LEFT);
			setAnimation(WALK_LEFT);
		}
		else if (left) {
			setState(RUNING_LEFT);
			setAnimation(RUN_LEFT);
		}
		else if (right) {
			setState(TURNING_RIGHT);
			setAnimation(TURN_RIGHT);
		}
		else if (up) {
			state = JUMP_STANDING_LEFT;
			setAnimation(JUMP_STAND_LEFT);
		}
		else if (down) {
			state = DOWNING_LEFT;
			setAnimation(DOWN_LEFT);
		}
		break;
	case RUNING_LEFT:
		if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 64), &posPlayer.y)) {
			setState(FALLING_LEFT);
			cout << "DOWN" << endl;
			setAnimation(FALL_RIGHT);
		}
		else if (posPlayer.x % 64 == 0 && posPlayer != posStartAnim && !left) {
			if (right) {
				setState(STANDING_RIGHT);
				setAnimation(STAND_RIGHT);
			}
			else if (up) {
				setState(JUMPING_LEFT);
				setAnimation(JUMP_RUN_LEFT);
			}
			else if (!left) {
				//frenada
				setState(STOPING_LEFT);
				setAnimation(STOP_LEFT);
			}
		}
		else {
			posPlayer.x -= 2;
			if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 64))) {
				posPlayer.x += 2;
				setState(STANDING_LEFT);
				setAnimation(STAND_LEFT);
			}
		}
		break;
	case RUNING_RIGHT:
		/*if (!map->collisionMoveDown(posPlayer, glm::ivec2(32, 64), &posPlayer.y)) {
			setState(FALLING_RIGHT);
			//setAnimation(FALL_RIGHT); //TODO
		}*/
		if (posPlayer.x % 64 == 0 && posPlayer != posStartAnim && !right) {
			if (left) {
				setState(TURN_RUNING_RIGHT);
				setAnimation(TURN_RUN_RIGHT);
			}
			else if (up) {
				setState(JUMPING_RIGHT);
				setAnimation(JUMP_RUN_RIGHT);
			}
			else {
				//frenada
				setAnimation(STOP_RIGHT);
				setState(STOPING_RIGHT);
			}
		}
		else {
			posPlayer.x += 2;
			if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 64)))
			{
				posPlayer.x -= 2;
				setAnimation(STAND_RIGHT);
				setState(STANDING_RIGHT);
			}
		}
		break;
	case WALKING_RIGHT:
		if (posPlayer.x % 32 == 0 && posPlayer != posStartAnim) {
			setAnimation(STAND_RIGHT);
			setState(STANDING_RIGHT);
		}
		else {
			posPlayer.x += 1;
			if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 64)))
			{
				posPlayer.x -= 1;
				setAnimation(STAND_RIGHT);
				setState(STANDING_RIGHT);
			}
		}
		break;
	case WALKING_LEFT:
		if (posPlayer.x % 32 == 0 && posPlayer != posStartAnim && !right) {
			setAnimation(STAND_LEFT);
			setState(STANDING_LEFT);
		}
		else {
			posPlayer.x -= 1;
			if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 64)))
			{
				posPlayer.x += 1;
				setAnimation(STAND_LEFT);
				setState(STANDING_LEFT);
			}
		}
		break;

	case JUMPING_RIGHT:
		if (right) {
			setState(STANDING_RIGHT);
			setAnimation(STAND_RIGHT);
		}
		break;
	case JUMPING_LEFT:
		if (left) {
			setState(STANDING_LEFT);
			setAnimation(STAND_LEFT);
		}
		break;
	case TURNING_RIGHT:
		if (sprite->getCurrentKeyframe() >= 5) {
			setState(STANDING_RIGHT);
			setAnimation(STAND_RIGHT);
		}
		else {
			frame++;
		}
		break;
	case TURNING_LEFT:
		if (sprite->getCurrentKeyframe() >= 5) {
			setState(STANDING_LEFT);
			setAnimation(STAND_LEFT);
		}
		else {
			frame++;
		}
		break;
	case STOPING_RIGHT:
		if (sprite->getCurrentKeyframe() >= 6) {
			setState(STANDING_RIGHT);
			setAnimation(STAND_RIGHT);
		}
		else {
			frame++;
		}
		break;
	case STOPING_LEFT:
		if (sprite->getCurrentKeyframe() >= 6) {
			setState(STANDING_LEFT);
			setAnimation(STAND_LEFT);
		}
		else {
			frame++;
		}
		break;
	case FALLING_RIGHT:
		posPlayer.y += FALL_STEP;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 64), &posPlayer.y))
		{
			//ajupir
			setState(DOWNING_RIGHT);
			setAnimation(DOWN_RIGHT);
		}
		break;
	case FALLING_LEFT:
		posPlayer.y += FALL_STEP;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 64), &posPlayer.y)){
			//ajupir
			setState(DOWNING_LEFT);
			setAnimation(DOWN_LEFT);
		}
		break;
	case DOWNING_RIGHT:
		if (sprite->getCurrentKeyframe() >= 11) {
			setState(STANDING_RIGHT);
			setAnimation(STAND_RIGHT);
		}
		break;
	case DOWNING_LEFT:
		if (sprite->getCurrentKeyframe() >= 11) {
			setState(STANDING_LEFT);
			setAnimation(STAND_LEFT);
		}
		break;
	case JUMP_STANDING_RIGHT:
		jumpAngle += JUMP_ANGLE_STEP;
		posPlayer.y = int(posStartAnim.y - 96 * sin(3.14159f * jumpAngle / 180.f));
		if (jumpAngle > 90) {
			setState(FALLING_RIGHT);
			setAnimation(FALL_RIGHT);
		}
		if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 64), &posPlayer.y)) {
			setState(DOWNING_RIGHT);
			setAnimation(DOWN_RIGHT);
		}
		if (sprite->getCurrentKeyframe() >= 13) {
			//
		}
		break;
	case JUMP_STANDING_LEFT:
		if (sprite->getCurrentKeyframe() >= 13) {
			setState(DOWNING_LEFT);
			setAnimation(DOWN_LEFT);
		}
		break;
	case TURN_RUNING_RIGHT:
		if (sprite->getCurrentKeyframe() >= 12) {
			setState(RUNING_LEFT);
			setAnimation(RUN_LEFT);
		}
		break;
	}


	//YOLO
	/*if (bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if (jumpAngle > 90)
				if (bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 64), &posPlayer.y)) {
					if (facingRight) sprite->changeAnimation(STAND_RIGHT);
					else sprite->changeAnimation(STAND_LEFT);
				}

		}
	}

	/*	
	IF !BJUMPING
	{
		posPlayer.y += FALL_STEP;
		if(map->collisionMoveDown(posPlayer, glm::ivec2(32, 64), &posPlayer.y))
		{
			if(up)
			{
				if (sprite->animation() != JUMP_RUNNING_RIGHT) sprite->changeAnimation(JUMP_RUNNING_RIGHT);
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
	}*/
	
	sprite->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	position_col = glm::vec2(float(posPlayer.x+24), float(posPlayer.y + 22));
	//std::cout << "player " << posPlayer.x << " " << posPlayer.y << " to " << posPlayer.x + 64 << " " << posPlayer.y + 64 << std::endl;
	//std::cout << "player " << position_col.x << " " << position_col.y << " to " << position_col.x + size.x << " " << position_col.y + size.y << std::endl;
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	position_col = glm::vec2(float(posPlayer.x + tileMapDispl.x + 24), float(posPlayer.y + tileMapDispl.y + 22));
	std::cout << "player " << posPlayer.x << " " << posPlayer.y << " to " << position_col.x + size.x << " " << position_col.y + size.y << std::endl;
	std::cout << "player " << position_col.x << " " << position_col.y << " to " << position_col.x + size.x << " " << position_col.y + size.y << std::endl;
	//std::cout << position_col.x << " " << position_col.y << std::endl;
}

glm::vec2 Player::getPosition()
{
	return posPlayer;
}

void Player::input() {
	left = Game::instance().getSpecialKey(GLUT_KEY_LEFT);
	right = Game::instance().getSpecialKey(GLUT_KEY_RIGHT);
	up = Game::instance().getSpecialKey(GLUT_KEY_UP);
	down = Game::instance().getSpecialKey(GLUT_KEY_DOWN);
	shift = Game::instance().getSpecialKey(112);
}

void Player::setState(PlayerState newState) {
	state = newState;
}

void Player::setAnimation(PlayerAnims newAnim) {
	sprite->changeAnimation(newAnim);
	posStartAnim = posPlayer;
	jumpAngle = 0;
	frame = 0;
}

void Player::DIE() {
	//TODO
}


