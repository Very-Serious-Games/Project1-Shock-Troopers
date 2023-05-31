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
	HIT,
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

	virtual void move();

	virtual void deathAnimation();

	virtual void spawnAnimation();

	virtual void idleAnimation();

	virtual void idleAnimation(int direction);

	virtual void idleAnimation(int direction, int directionBelow);

	virtual void moveAnimation();

	virtual void attackAnimation(int direction);

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Collision response
	virtual void OnCollision(Collider* collider);

	// Sets flag for deletion and for the collider aswell
	virtual void SetToDelete();

	// Check if the player is near
	bool PlayerIsNear();

	bool PlayerIsAttackRange();

	// Check if the player is mele
	bool PlayerIsMele();

	virtual int GetPlayerDirection();

	virtual int GetPlayerDirectionBelow();

public:
	Enemy_State state = Enemy_State::SPAWN;

	// The current position in the world
	fPoint position;

	// The position relative to the start of the path
	fPoint relativePosition = fPoint(0.0f, 0.0f);

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	// A flag for the enemy removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

	int health = 100;

	int delay = 15;
	int delayShoot = 700;
	int delayCanon= 700;
	int delayKnife = 500;
	int deathAnimDelay = 50;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;
	Animation* topCurrentAnim = nullptr;
	Animation* midCurrentAnim = nullptr;
	Animation* botCurrentAnim = nullptr;

	Animation deathAnim;
	Animation spawnAnim;
	Animation idleAnim;
	Animation attackAnim;
	Animation moveAnim;

	// The enemy's collider
	Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	fPoint spawnPos;

	// Trigger area
	Collider* triggerArea = nullptr;
};

#endif // __ENEMY_H__