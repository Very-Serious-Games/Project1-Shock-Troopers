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