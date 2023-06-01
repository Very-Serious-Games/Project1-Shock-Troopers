#include "ModulePickUp.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"

#include "PickUp.h"


#define SPAWN_MARGIN 50

ModulePickUp::ModulePickUp(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_PICKUP; ++i)
		pickUp[i] = nullptr;
}

ModulePickUp::~ModulePickUp()
{

}

bool ModulePickUp::Start()
{
	SpawnPickUp({ PickUp_Type::HP, 220, 1800 });
	return true;
}


Update_Status ModulePickUp::PreUpdate()
{
	// Remove all pickUp scheduled for deletion
	for (uint i = 0; i < MAX_PICKUP; ++i)
	{
		if (pickUp[i] != nullptr && pickUp[i]->pendingToDelete)
		{
			delete pickUp[i];
			pickUp[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePickUp::Update()
{

	HandlePickUpSpawn();

	for (uint i = 0; i < MAX_PICKUP; ++i)
	{
		if (pickUp[i] != nullptr){
			pickUp[i]->Update();
			
		}
	}

	HandlePickUpDespawn();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePickUp::PostUpdate()
{
	for (uint i = 0; i < MAX_PICKUP; ++i)
	{
		//if (pickUp[i] != nullptr)
			//pickUp[i]->Draw();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModulePickUp::CleanUp()
{
	LOG("Freeing all pickUp");

	for (uint i = 0; i < MAX_PICKUP; ++i)
	{
		if (pickUp[i] != nullptr)
		{
			delete pickUp[i];
			pickUp[i] = nullptr;
		}
	}

	return true;
}

bool ModulePickUp::AddPickUp(PickUp_Type type, int x, int y)
{
	bool ret = true;

	return ret;
}

void ModulePickUp::HandlePickUpSpawn()
{

}

void ModulePickUp::HandlePickUpDespawn()
{
	for (uint i = 0; i < MAX_PICKUP; ++i)
	{
		if (pickUp[i] != nullptr)
		{
		if ((abs(pickUp[i]->position.x - App->player->position.x) > 200 || abs(pickUp[i]->position.y - App->player->position.y) > 200) && pickUp[i]->despawn)
			{
				LOG("DeSpawning pickUp at %d", pickUp[i]->position.x * SCREEN_SIZE);

				pickUp[i]->SetToDelete();
			}
		}
	}
}

void ModulePickUp::SpawnPickUp(const PickUpSpawnpoint& info)
{
	// Find an empty slot in the pickUp array
	for (uint i = 0; i < MAX_PICKUP; ++i)
	{
		if (pickUp[i] == nullptr)
		{
			switch (info.type)
			{
			case PickUp_Type::HP:
				pickUp[i] = new PickUp(info.x, info.y);
				pickUp[i]->collider = App->collisions->AddCollider({ info.x, info.y, 32, 16 }, Collider::Type::HEAL, this);
				break;
			}
			pickUp[i]->texture = texture;
			break;
		}
	}
}

void ModulePickUp::OnCollision(Collider* c1, Collider* c2) 
{
	for (uint i = 0; i < MAX_PICKUP; ++i)
	{
		if (pickUp[i] != nullptr && pickUp[i]->GetCollider() == c1 && c2->type == Collider::Type::PLAYER)
		{
			pickUp[i]->OnCollision(c2);
			break;
		}
	}
}