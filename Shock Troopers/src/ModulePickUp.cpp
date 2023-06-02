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

	// Anim base Medkit
	Medkit.PushBack({ 0, 16 * 2, 32, 16 });
	Medkit.PushBack({ 32, 16 * 2, 32, 16 });
	Medkit.PushBack({ 2 * 32, 16 * 2, 32, 16 });
	Medkit.PushBack({ 3 * 32, 16 * 2, 32, 16 });
	Medkit.PushBack({ 4 * 32, 16 * 2, 32, 16 });
	Medkit.PushBack({ 5 * 32, 16 * 2, 32, 16 });
	Medkit.PushBack({ 6 * 32, 16 * 2, 32, 16 });
	Medkit.PushBack({ 7 * 32, 16 * 2, 32, 16 });
	Medkit.PushBack({ 8 * 32, 16 * 2, 32, 16 });
	Medkit.PushBack({ 9 * 32, 16 * 2, 32, 16 });

	// Anim Picked Medkit
	PickedMedkit.PushBack({ 0, 16 * 3, 32, 16 });
	PickedMedkit.PushBack({ 32, 16 * 3, 32, 16 });
	PickedMedkit.PushBack({ 32 * 2, 16 * 3, 32, 16 });

	// Anim DiamondP
	Diamond.PushBack({ 0, 0, 32, 16 });
	Diamond.PushBack({ 32, 0, 32, 16 });
	Diamond.PushBack({ 3 * 32, 0, 32, 16 });
	Diamond.PushBack({ 4 * 32, 0, 32, 16 });
	Diamond.PushBack({ 5 * 32, 0, 32, 16 });
	Diamond.PushBack({ 6 * 32, 0, 32, 16 });
	Diamond.PushBack({ 7 * 32, 0, 32, 16 });

	// Anim PickedDiamondP
	PickedDiamond.PushBack({ 8 * 32, 0, 32, 16 });
	PickedDiamond.PushBack({ 9 * 32, 0, 32, 16 });
	PickedDiamond.PushBack({ 10 * 32, 0, 32, 16 });

	// Anim NoDamage DiamondP
	NoDamage.PushBack({ 0, 16, 32, 16 });
	NoDamage.PushBack({ 32, 16, 32, 16 });
	NoDamage.PushBack({ 3 * 32, 16, 32, 16 });
	NoDamage.PushBack({ 4 * 32, 16, 32, 16 });
	NoDamage.PushBack({ 5 * 32, 16, 32, 16 });
	NoDamage.PushBack({ 6 * 32, 16, 32, 16 });
	NoDamage.PushBack({ 7 * 32, 16, 32, 16 });

	// Anim Picked NoDamage 
	PickedNoDamage.PushBack({ 8 * 32, 16, 32, 16 });
	PickedNoDamage.PushBack({ 9 * 32, 16, 32, 16 });
	PickedNoDamage.PushBack({ 10 * 32, 16, 32, 16 });

	Medkit.speed = 0.08f;
	PickedMedkit.speed = 0.05;
	PickedMedkit.loop = false;

	Diamond.speed = 0.08f;
	PickedDiamond.speed = 0.05;
	PickedDiamond.loop = false;

	NoDamage.speed = 0.08f;
	PickedNoDamage.speed = 0.05;
	PickedNoDamage.loop = false;
}

ModulePickUp::~ModulePickUp()
{

}



bool ModulePickUp::Start()
{
	texture = App->textures->Load("Assets/sprites/pickups/pickups_spritesheet.png");

	return true;
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

	Medkit.Update();
	Diamond.Update();
	NoDamage.Update();

	PickedMedkit.Update();
	PickedDiamond.Update();
	PickedNoDamage.Update();

	HandlePickUpDespawn();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePickUp::PostUpdate()
{
	for (uint i = 0; i < MAX_PICKUP; ++i)
	{
		if (pickUp[i] != nullptr)
		{ 		
			if (pickUp[i]->isPicked)
			{
				switch (pickUp[i]->type)
				{
				case PickUpType::HP:
					pickUp[i]->currentAnim = &PickedMedkit;
					break;
				case PickUpType::DIAMOND:
					pickUp[i]->currentAnim = &PickedDiamond;
					break;
				case PickUpType::INVENCIBILITY:
					pickUp[i]->currentAnim = &PickedNoDamage;
					break;
				case PickUpType::NO_TYPE:
					pickUp[i]->currentAnim = nullptr;
					break;
				default:
					pickUp[i]->currentAnim = nullptr;
					break;
				}
			}

			pickUp[i]->Draw();
		}
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
	//// Find an empty slot in the pickUp array
	for (uint i = 0; i < MAX_PICKUP; ++i)
	{
		if (pickUp[i] == nullptr)
		{
			switch (info.type)
			{
				case PickUp_Type::HP:
					pickUp[i] = new PickUp(PickUpType::HP, info.x, info.y);

					pickUp[i]->texture = texture;
					pickUp[i]->currentAnim = &Medkit;

					pickUp[i]->DrawColider(PickUpType::HP);
					
					break;

				case PickUp_Type::DIAMOND:
					pickUp[i] = new PickUp(PickUpType::DIAMOND, info.x, info.y);

					pickUp[i]->texture = texture;
					pickUp[i]->currentAnim = &Diamond;

      					pickUp[i]->DrawColider(PickUpType::DIAMOND);

					break;
				case PickUp_Type::INVENCIBILITY:
					pickUp[i] = new PickUp(PickUpType::INVENCIBILITY, info.x, info.y);

					pickUp[i]->texture = texture;
					pickUp[i]->currentAnim = &NoDamage;

					pickUp[i]->DrawColider(PickUpType::INVENCIBILITY);

					break;
			}
			
			break;
		}
	}
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

void ModulePickUp::OnCollision(Collider* c1, Collider* c2) 
{
	for (uint i = 0; i < MAX_PICKUP; ++i)
	{
		if (pickUp[i] != nullptr && pickUp[i]->GetCollider() == c1 && c2->type == Collider::Type::PLAYER)
		{
			// TODO Cuando colisiona con el player se cambia a isPicked true
			pickUp[i]->isPicked = true;

			pickUp[i]->OnCollision(c2);
			
			break;
		}
	}
}