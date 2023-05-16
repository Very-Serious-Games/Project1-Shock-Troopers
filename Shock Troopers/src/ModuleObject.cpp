#include "ModuleObject.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

#include "Object.h"


#define SPAWN_MARGIN 50

ModuleObject::ModuleObject(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_OBJECT; ++i)
		object[i] = nullptr;
}

ModuleObject::~ModuleObject()
{

}

bool ModuleObject::Start()
{
	texture = App->textures->Load("Assets/Sprites/crate.png");
	objectDestroyedFx = App->audio->LoadFx("Assets/Fx/explosion.wav");

	return true;
}

Update_Status ModuleObject::PreUpdate()
{
	for (uint i = 0; i < MAX_OBJECT; ++i)
	{
		if (object[i] != nullptr && object[i]->pendingToDelete)
		{
			delete object[i];
			object[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleObject::Update()
{
	HandleObjectSpawn();

	for (uint i = 0; i < MAX_OBJECT; ++i)
	{
		if (object[i] != nullptr)
			object[i]->Update();
	}

	HandleObjectDespawn();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleObject::PostUpdate()
{
	for (uint i = 0; i < MAX_OBJECT; ++i)
	{
		if (object[i] != nullptr)
			object[i]->Draw();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleObject::CleanUp()
{
	LOG("Freeing all objects");

	for (uint i = 0; i < MAX_OBJECT; ++i)
	{
		if (object[i] != nullptr)
		{
			delete object[i];
			object[i] = nullptr;
		}
	}

	return true;
}

void ModuleObject::OnCollision(Collider* c1, Collider* c2){
	for (uint i = 0; i < MAX_OBJECT; ++i)
	{
		if (object[i] != nullptr && object[i]->GetCollider() == c1)
		{
			object[i]->OnCollision(c2);
			break;
		}
	}
}

bool ModuleObject::AddObject(Object_Type type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_OBJECT; ++i)
	{
		if (spawnQueue[i].type == Object_Type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleObject::HandleObjectSpawn() {
	for (uint i = 0; i < MAX_OBJECT; ++i)
	{
		if (spawnQueue[i].type != Object_Type::NO_TYPE)
		{
			if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnObject(spawnQueue[i]);
				spawnQueue[i].type = Object_Type::NO_TYPE;
			}
		}
	}
}

void ModuleObject::HandleObjectDespawn() {
	for (uint i = 0; i < MAX_OBJECT; ++i)
	{
		if (object[i] != nullptr)
		{
			if (object[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", object[i]->position.x * SCREEN_SIZE);

				object[i]->SetToDelete();
			}
		}
	}
}

void ModuleObject::SpawnObject(const ObjectSpawnpoint& info) {

}