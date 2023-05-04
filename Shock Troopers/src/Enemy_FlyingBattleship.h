#ifndef __ENEMY_FLYINGBATTLESHIP_H__
#define __ENEMY_FLYINGBATTLESHIP_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_FlyingBattleship : public Enemy {
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_FlyingBattleship(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	// The path that will define the position in the world
	Path path;

	SDL_Texture* texture = nullptr;

	// Enemy animations
	Animation spawnAnim;
	Animation idleAnim;
	Animation deathAnim;

};

#endif // __ENEMY_FLYINGBATTLESHIP_H__