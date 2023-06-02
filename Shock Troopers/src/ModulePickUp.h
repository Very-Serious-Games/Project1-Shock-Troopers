#ifndef __MODULE_PICKUP_H__
#define __MODULE_PICKUP_H__

#include "Module.h"
#include "Animation.h"

#define MAX_PICKUP 10

enum class PickUp_Type
{
	NO_TYPE,
	HP,
	DIAMOND,
	INVENCIBILIDAD
};


struct PickUpSpawnpoint
{
	PickUp_Type type = PickUp_Type::NO_TYPE;
	int x, y;
	bool despawn;
};

class PickUp;
struct SDL_Texture;

class ModulePickUp : public Module
{
public:
	// Constructor
	ModulePickUp(bool startEnabled);

	// Destructor
	~ModulePickUp();

	// Called when the module is activated
	// Loads the necessary textures for the PickUp
	bool Start() override;

	// Called at the beginning of the application loop
	// Removes all PickUp pending to delete
	Update_Status PreUpdate() override;

	// Called at the middle of the application loop
	// Handles all PickUp logic and spawning/despawning
	Update_Status Update() override;

	// Called at the end of the application loop
	// Iterates all the PickUp and draws them
	Update_Status PostUpdate() override;

	// Called on application exit
	// Destroys all active PickUp left in the array
	bool CleanUp() override;

	// Called when an enemi collider hits another collider
	// The PickUp is destroyed and an explosion particle is fired
	void OnCollision(Collider* c1, Collider* c2) override;

	// Add an PickUp into the queue to be spawned later
	bool AddPickUp(PickUp_Type type, int x, int y);

	// Iterates the queue and checks for camera position
	void HandlePickUpSpawn();

	// Destroys any PickUp that have moved outside the camera limits
	void HandlePickUpDespawn();

	void SpawnPickUp(const PickUpSpawnpoint& info);

private:

	// All spawned PickUp in the scene
	PickUp* pickUp[MAX_PICKUP] = { nullptr };

	// The audio fx for destroying an PickUp
	int pickUpDestroyedFx = 0;

	Animation Medkit;
	Animation PickedMedkit;
	Animation Diamond;
	Animation PickedDiamond;
	Animation NoDamage;
	Animation PickedNoDamage;

public:
	// The PickUp sprite sheet
	SDL_Texture* texture = nullptr;
};

#endif // __MODULE_PickUp_H__