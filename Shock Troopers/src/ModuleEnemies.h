#ifndef __MODULE_ENEMIES_H__
#define __MODULE_ENEMIES_H__

#include "Module.h"

#define MAX_ENEMIES 100

enum class Enemy_Type
{
	NO_TYPE,
	INFANTRY_SOLDIER,
	FLYING_BATTLESHIP,
	BRIDGE,
	CRATE,
	TANK_BOSS,
	TANK,
	SANDBAG,
	LANDMINE,
	BARREL,
	BARRELGROUP,
	CAR,
};

struct EnemySpawnpoint
{
	Enemy_Type type = Enemy_Type::NO_TYPE;
	int x, y;
	bool isFalling;
};

class Enemy;
struct SDL_Texture;

class ModuleEnemies : public Module
{
public:
	// Constructor
	ModuleEnemies(bool startEnabled);

	// Destructor
	~ModuleEnemies();

	// Called when the module is activated
	// Loads the necessary textures for the enemies
	bool Start() override;

	// Called at the beginning of the application loop
	// Removes all enemies pending to delete
	Update_Status PreUpdate() override;

	// Called at the middle of the application loop
	// Handles all enemies logic and spawning/despawning
	Update_Status Update() override;

	// Called at the end of the application loop
	// Iterates all the enemies and draws them
	Update_Status PostUpdate() override;

	// Called on application exit
	// Destroys all active enemies left in the array
	bool CleanUp() override;

	// Called when an enemi collider hits another collider
	// The enemy is destroyed and an explosion particle is fired
	void OnCollision(Collider* c1, Collider* c2) override;

	// Add an enemy into the queue to be spawned later
	bool AddEnemy(Enemy_Type type, int x, int y);

	bool AddEnemy(Enemy_Type type, int x, int y, bool isFalling);

	// Iterates the queue and checks for camera position
	void HandleEnemiesSpawn();

	// Destroys any enemies that have moved outside the camera limits
	void HandleEnemiesDespawn();

private:
	// Spawns a new enemy using the data from the queue
	void SpawnEnemy(const EnemySpawnpoint& info);

private:
	// A queue with all spawn points information
	EnemySpawnpoint spawnQueue[MAX_ENEMIES];

	// All spawned enemies in the scene
	Enemy* enemies[MAX_ENEMIES] = { nullptr };

public:
	// The enemies sprite sheet
	SDL_Texture* textureTankBoss = nullptr;
	SDL_Texture* textureTank = nullptr;
	SDL_Texture* textureFlyingBattleship = nullptr;
	SDL_Texture* textureInfantrySoldier = nullptr;
	SDL_Texture* textureBridge = nullptr;
	SDL_Texture* textureCrate = nullptr;
	SDL_Texture* textureLandmines = nullptr;
	SDL_Texture* textureSandbags = nullptr;
	SDL_Texture* textureBarrel = nullptr;
	SDL_Texture* textureBarrelGroup = nullptr;
	SDL_Texture* textureCar = nullptr;

	bool winCondition = false;
	bool miniBossKilled = false;

	// Sound effects indices
	uint soldierShot = 0;
	uint soldierKnife = 0;
	uint soldierDamaged1 = 0;
	uint soldierDamaged2 = 0;

	uint tankShot = 0;
	uint tankDestroyed = 0;

	uint flyingBattleshipShot = 0;
	uint flyingBattleshipMissile = 0;

	uint bridgeDestroyed = 0;
	uint bridgeDamaged = 0;
	uint crateDestroyed = 0;
	uint landmineExplosion = 0;
};

#endif // __MODULE_ENEMIES_H__