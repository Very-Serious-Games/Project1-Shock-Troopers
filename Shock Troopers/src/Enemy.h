#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"
#include "Application.h"
#include "Particle.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"

struct SDL_Texture;
struct Collider;

// TODO revisar estados de enemigo
enum class Enemy_State
{
	SPAWN,
	IDLE,
	ATTACK,
	MOVE,
	DEATH,
};

class Enemy
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Enemy(int x, int y);

	// Destructor
	virtual ~Enemy();

	// Returns the enemy's collider
	const Collider* GetCollider() const;

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	virtual void StateMachine();

	virtual void Attack();
	virtual void SpecialAttack();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Collision response
	virtual void OnCollision(Collider* collider);

	// Sets flag for deletion and for the collider aswell
	virtual void SetToDelete();

	// Check if the player is near
	bool PlayerIsNear();

public:
	Enemy_State state = Enemy_State::SPAWN;

	// The current position in the world
	iPoint position;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	// A flag for the enemy removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

	int health = 100;

	int delay = 15;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	// The enemy's collider
	Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;

	// Trigger area
	Collider* triggerArea = nullptr;
};

#endif // __ENEMY_H__