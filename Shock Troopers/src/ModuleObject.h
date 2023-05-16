#ifndef __MODULE_OBJECT_H__
#define __MODULE_OBJECT_H__

#include "Module.h"

#define MAX_OBJECT 10

enum class Object_Type
{
	NO_TYPE,
	HP
};

struct ObjectSpawnpoint
{
	Object_Type type = Object_Type::NO_TYPE;
	int x, y;
};

class Object;
struct SDL_Texture;

class ModuleObject : public Module
{
public:
	// Constructor
	ModuleObject(bool startEnabled);

	// Destructor
	~ModuleObject();

	// Called when the module is activated
	// Loads the necessary textures for the Object
	bool Start() override;

	// Called at the beginning of the application loop
	// Removes all Object pending to delete
	Update_Status PreUpdate() override;

	// Called at the middle of the application loop
	// Handles all Object logic and spawning/despawning
	Update_Status Update() override;

	// Called at the end of the application loop
	// Iterates all the Object and draws them
	Update_Status PostUpdate() override;

	// Called on application exit
	// Destroys all active Object left in the array
	bool CleanUp() override;

	// Called when an enemi collider hits another collider
	// The Object is destroyed and an explosion particle is fired
	void OnCollision(Collider* c1, Collider* c2) override;

	// Add an Object into the queue to be spawned later
	bool AddObject(Object_Type type, int x, int y);

	// Iterates the queue and checks for camera position
	void HandleObjectSpawn();

	// Destroys any Object that have moved outside the camera limits
	void HandleObjectDespawn();

	void SpawnObject(const ObjectSpawnpoint& info);

private:
	// A queue with all spawn points information
	ObjectSpawnpoint spawnQueue[MAX_OBJECT];

	// All spawned Object in the scene
	Object* object[MAX_OBJECT] = { nullptr };

	// The Object sprite sheet
	SDL_Texture* texture = nullptr;

	// The audio fx for destroying an Object
	int objectDestroyedFx = 0;
};

#endif