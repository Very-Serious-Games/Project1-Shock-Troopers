#ifndef __PICKUP_H__
#define __PICKUP_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

enum class PickUpType
{
	NO_TYPE,
	HP,
	DIAMOND,
	INVENCIBILITY
};

class PickUp
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	PickUp(PickUpType type, int x, int y);

	// Destructor
	virtual ~PickUp();

	// Returns the enemy's collider
	const Collider* GetCollider() const;

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	virtual void DrawColider();

	// Collision response
	virtual void OnCollision(Collider* collider);

	// Sets flag for deletion and for the collider aswell
	virtual void SetToDelete();

public:
	// The current position in the world
	iPoint position;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	// A flag for the enemy removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

	bool despawn = false;
	bool isPicked = false;

	// The pickUp collider
	Collider* collider = nullptr;

	PickUpType type;

	// A ptr to the current animation
	Animation* currentAnim = nullptr;

protected:

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
};

#endif 