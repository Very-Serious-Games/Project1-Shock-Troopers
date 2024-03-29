#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "Enemy.h"
#include "Enemy_InfantrySoldier.h"
#include "Enemy_FlyingBattleship.h"
#include "Enemy_Bridge.h"
#include "Enemy_Crate.h"
#include "Enemy_TankBoss.h"
#include "Enemy_Tank.h"
#include "Enemy_Landmine.h"
#include "Enemy_Sandbag.h"
#include "Enemy_Barrel.h"
#include "Enemy_BarrelGroup.h"
#include "Enemy_Car.h"

#define SPAWN_MARGIN 5000


ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;

}
 
ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start() {

	// Reset win condition
	winCondition = false;
	miniBossKilled = false;

	soldierShot = 0;
	soldierKnife = 0;
	soldierDamaged1 = 0;
	soldierDamaged2 = 0;

	tankShot = 0;
	tankDestroyed = 0;

	bridgeDestroyed = 0;
	bridgeDamaged = 0;
	crateDestroyed = 0;
	landmineExplosion = 0;

	flyingBattleshipShot = 0;
	flyingBattleshipMissile = 0;

	// TODO cargar texturas y fx enemigos
	textureTankBoss = App->textures->Load("Assets/Sprites/characters/tank_boss.png");
	textureTank = App->textures->Load("Assets/Sprites/characters/tank_spritesheet.png");
	textureFlyingBattleship = App->textures->Load("Assets/Sprites/characters/jet_boss.png");
	textureInfantrySoldier = App->textures->Load("Assets/Sprites/characters/Soldiers-Infantry.png");
	textureCrate = App->textures->Load("Assets/Sprites/background/level1/crates.png");
	textureLandmines = App->textures->Load("Assets/Sprites/background/level1/landmine.png");
	textureBridge = App->textures->Load("Assets/Sprites/background/level1/stone-bridge.png");
	textureSandbags = App->textures->Load("Assets/Sprites/background/level1/sandbags.png");
	textureBarrel = App->textures->Load("Assets/Sprites/background/level1/barrel.png");
	textureBarrelGroup = App->textures->Load("Assets/Sprites/background/level1/barrelGroup.png");
	textureCar = App->textures->Load("Assets/Sprites/background/level1/car.png");

	// Load sound effects
	soldierShot = App->audio->LoadFx("Assets/fx/infantry_soldier_shot.wav");
	if (soldierShot == -1)
	{
		LOG("Failed to load infantry_soldier_shot.wav sound effect");
	}

	soldierKnife = App->audio->LoadFx("Assets/fx/infantry_soldier_knife.wav");
	if (soldierKnife == -1)
	{
		LOG("Failed to load infantry_soldier_knife.wav sound effect");
	}

	soldierDamaged1 = App->audio->LoadFx("Assets/fx/infantry_soldier_damaged_1.wav");
	if (soldierDamaged1 == -1)
	{
		LOG("Failed to load infantry_soldier_damaged_1.wav sound effect");
	}

	soldierDamaged2 = App->audio->LoadFx("Assets/fx/infantry_soldier_damaged_2.wav");
	if (soldierDamaged2 == -1)
	{
		LOG("Failed to load infantry_soldier_damaged_2.wav sound effect");
	}

	tankShot = App->audio->LoadFx("Assets/fx/tank_shot.wav");
	if (tankShot == -1)
	{
		LOG("Failed to load tank_shot.wav sound effect");
	}

	tankDestroyed = App->audio->LoadFx("Assets/fx/tank_destroyed.wav");
	if (tankDestroyed == -1)
	{
		LOG("Failed to load tank_destroyed.wav sound effect");
	}

	flyingBattleshipShot = App->audio->LoadFx("Assets/fx/flyingbattleship_shot.wav");
	if (flyingBattleshipShot == -1)
	{
		LOG("Failed to load flyingbattleship_shot.wav sound effect");
	}
	
	flyingBattleshipMissile = App->audio->LoadFx("Assets/fx/flyingbattleship_missile.wav");
	if (flyingBattleshipMissile == -1)
	{
		LOG("Failed to load flyingbattleship_shot.wav sound effect");
	}

	bridgeDestroyed = App->audio->LoadFx("Assets/fx/bridge_destroyed.wav");
	if (bridgeDestroyed == -1)
	{
		LOG("Failed to load bridge_destroyed.wav sound effect");
	}

	bridgeDamaged = App->audio->LoadFx("Assets/fx/bridge_damaged.wav");
	if (bridgeDamaged == -1)
	{
		LOG("Failed to load bridge_damaged.wav sound effect");
	}

	crateDestroyed = App->audio->LoadFx("Assets/fx/crate_destroyed.wav");
	if (crateDestroyed == -1)
	{
		LOG("Failed to load crate_destroyed.wav sound effect");
	}

	landmineExplosion = App->audio->LoadFx("Assets/fx/milky_grenade_explosion.wav");
	if (landmineExplosion == -1)
	{
		LOG("Failed to load milky_grenade_explosion.wav sound effect");
	}

	return true;
}


Update_Status ModuleEnemies::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->pendingToDelete)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemies::Update()
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
			enemies[i]->Update();
	}
	HandleEnemiesDespawn();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(Enemy_Type type, int x, int y)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(spawnQueue[i].type == Enemy_Type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			spawnQueue[i].isFalling = false;
			ret = true;
			break;
		}
	}

	return ret;
}

bool ModuleEnemies::AddEnemy(Enemy_Type type, int x, int y, bool isFalling)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(spawnQueue[i].type == Enemy_Type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			spawnQueue[i].isFalling = isFalling;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != Enemy_Type::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = Enemy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn()
{
	// TODO despawn enemies
	
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				enemies[i]->SetToDelete();
			}
		}
	}
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
				case Enemy_Type::INFANTRY_SOLDIER:
					enemies[i] = new Enemy_InfantrySoldier(info.x, info.y, info.isFalling);
					if (info.isFalling)
					{
						enemies[i]->state = Enemy_State::SPAWN;
					}
					else {
						enemies[i]->state = Enemy_State::IDLE;
					}
					enemies[i]->texture = textureInfantrySoldier;
					break;
				case Enemy_Type::FLYING_BATTLESHIP:
					enemies[i] = new Enemy_FlyingBattleship(info.x, info.y);
					enemies[i]->state = Enemy_State::SPAWN;
					enemies[i]->texture = textureFlyingBattleship;
					break;
				case Enemy_Type::BRIDGE:
					enemies[i] = new Enemy_Bridge(info.x, info.y);
					enemies[i]->state = Enemy_State::SPAWN;
					enemies[i]->texture = textureBridge;
					break;
				case Enemy_Type::CRATE:
					enemies[i] = new Enemy_Crate(info.x, info.y);
					enemies[i]->state = Enemy_State::SPAWN;
					enemies[i]->texture = textureCrate;
					break;
				case Enemy_Type::TANK_BOSS:
					enemies[i] = new Enemy_TankBoss(info.x, info.y);
					enemies[i]->state = Enemy_State::SPAWN;
					enemies[i]->texture = textureTankBoss;
					break;
				case Enemy_Type::TANK:
					enemies[i] = new Enemy_Tank(info.x, info.y);
					enemies[i]->state = Enemy_State::SPAWN;
					enemies[i]->texture = textureTank;
					break;
				case Enemy_Type::SANDBAG:
					enemies[i] = new Enemy_Sandbag(info.x, info.y);
					enemies[i]->state = Enemy_State::SPAWN;
					enemies[i]->texture = textureSandbags;
					break;
				case Enemy_Type::BARREL:
					enemies[i] = new Enemy_Barrel(info.x, info.y);
					enemies[i]->state = Enemy_State::SPAWN;
					enemies[i]->texture = textureBarrel;
					break;
				case Enemy_Type::LANDMINE:
					enemies[i] = new Enemy_Landmine(info.x, info.y);
					enemies[i]->state = Enemy_State::SPAWN;
					enemies[i]->texture = textureLandmines;
					break;
				case Enemy_Type::BARRELGROUP:
					enemies[i] = new Enemy_BarrelGroup(info.x, info.y);
					enemies[i]->state = Enemy_State::SPAWN;
					enemies[i]->texture = textureBarrelGroup;
					break;
				case Enemy_Type::CAR:
					enemies[i] = new Enemy_Car(info.x, info.y);
					enemies[i]->state = Enemy_State::SPAWN;
					enemies[i]->texture = textureCar;
					break;
			}
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2); //Notify the enemy of a collision
			break;
		}
	}
}