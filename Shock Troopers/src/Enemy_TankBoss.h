#ifndef __ENEMY_TANKBOSS_H__
#define __ENEMY_TANKBOSS_H__

#include "Enemy.h"
#include "Path.h"
#include "Module.h"

class Enemy_TankBoss : public Enemy {
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_TankBoss(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	void OnCollision(Collider* collider) override;

	void deathAnimation() override;

	void idleAnimation(int direction, int directionBelow) override;

	void hitAnimation(int direction, int directionBelow);

	void StateMachine() override;

	void Attack() override;

	void canon();

	void shot();

	void grenade();

private:
	// The path that will define the position in the world
	Path path;

	bool isHitted = false;

	SDL_Texture* textureTankBoss = nullptr;

	Animation emptyAnimation;

	Animation topAnimDown;
	Animation topAnimUp;
	Animation topAnimLeft;
	Animation topAnimRight;
	Animation topAnimDownLeft;
	Animation topAnimDownRight;
	Animation topAnimUpLeft;
	Animation topAnimUpRight;

	Animation hitTopAnimDown;
	Animation hitTopAnimUp;
	Animation hitTopAnimLeft;
	Animation hitTopAnimRight;
	Animation hitTopAnimDownLeft;
	Animation hitTopAnimDownRight;
	Animation hitTopAnimUpLeft;
	Animation hitTopAnimUpRight;

	Animation midAnimDown;
	Animation midAnimLeft;
	Animation midAnimRight;
	Animation midAnimDownLeft;
	Animation midAnimDownRight;
	Animation midAnimDownLeftDiagonal;
	Animation midAnimDownRightDiagonal;

	Animation hitMidAnimDown;
	Animation hitMidAnimLeft;
	Animation hitMidAnimRight;
	Animation hitMidAnimDownLeft;
	Animation hitMidAnimDownRight;
	Animation hitMidAnimDownLeftDiagonal;
	Animation hitMidAnimDownRightDiagonal;

	Animation botAnimMoving;

	Animation hitBotAnimMoving;
	Animation deathAnim;

};

#endif // __ENEMY_TANKBOSS_H__