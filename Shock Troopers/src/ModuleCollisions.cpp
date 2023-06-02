#include "ModuleCollisions.h"

#include <iostream>
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_Scancode.h"
using namespace std;

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::LASER] = true;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::HEAL] = false;
	matrix[Collider::Type::WALL][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::WALL][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::WALL][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::WALL][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::WALL][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::WALL][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::WALL][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::WALL][Collider::Type::MUZZLE] = false;

	matrix[Collider::Type::PLAYER_WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::LASER] = true;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::HEAL] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::MISSILE] = false;

	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::LASER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::HEAL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::OBJECT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::MISSILE] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::MUZZLE] = false;

	matrix[Collider::Type::ENEMY][Collider::Type::WALL] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::LASER] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::HEAL] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::MUZZLE] = false;

	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::LASER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::HEAL] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::OBJECT] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::MISSILE] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::MUZZLE] = false;

	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::LASER] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::HEAL] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::MUZZLE] = false;

	matrix[Collider::Type::LASER][Collider::Type::WALL] = true;
	matrix[Collider::Type::LASER][Collider::Type::PLAYER_WALL] = true;
	matrix[Collider::Type::LASER][Collider::Type::LASER] = false;
	matrix[Collider::Type::LASER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::LASER][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::LASER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::LASER][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::LASER][Collider::Type::HEAL] = false;
	matrix[Collider::Type::LASER][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::LASER][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::LASER][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::LASER][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::LASER][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::LASER][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::LASER][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::LASER][Collider::Type::MUZZLE] = false;

	matrix[Collider::Type::HEAL][Collider::Type::WALL] = false;
	matrix[Collider::Type::HEAL][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::HEAL][Collider::Type::LASER] = false;
	matrix[Collider::Type::HEAL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::HEAL][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::HEAL][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::HEAL][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::HEAL][Collider::Type::HEAL] = false;
	matrix[Collider::Type::HEAL][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::HEAL][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::HEAL][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::HEAL][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::HEAL][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::HEAL][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::HEAL][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::HEAL][Collider::Type::MUZZLE] = false;

	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::WALL] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::LASER] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::HEAL] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::STOP_CAM_ZONE] = true;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::STOP_CAM_ZONE_2] = true;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::MISSILE] = false;

	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::WALL] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::LASER] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::HEAL] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::STOP_CAM_TRIGGER] = true;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::MISSILE] = false;

	matrix[Collider::Type::MISSILE][Collider::Type::WALL] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::LASER] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::MISSILE][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::MISSILE][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::HEAL] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::MUZZLE] = false;

	// muzzle
	matrix[Collider::Type::MUZZLE][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::WALL] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::LASER] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::HEAL] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::MUZZLE] = false;


	matrix[Collider::Type::LANDMINE][Collider::Type::PLAYER_SHOT] = false;
}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

Update_Status ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if(colliders[i] == nullptr)
			continue;

		c1 = colliders[i];


		// avoid checking collisions already checkedn
		for(uint k = i+1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if(colliders[k] == nullptr)
				continue;


			c2 = colliders[k];
			if(matrix[c1->type][c2->type] && c1->Intersects(c2->rect)) {
				for (uint i = 0; i < MAX_LISTENERS; ++i) {
					if (c1->listeners[i] != nullptr) {
						c1->listeners[i]->OnCollision(c1, c2);
					}
				}
				
				for (uint i = 0; i < MAX_LISTENERS; ++i) {
					if (c2->listeners[i] != nullptr) {
						c2->listeners[i]->OnCollision(c2, c1);
					}
				}
			}
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::Update()
{
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	return Update_Status::UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		switch(colliders[i]->type)
		{
			case Collider::Type::NONE: // white
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::WALL: // blue
				App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
				break;
			case Collider::Type::PLAYER_WALL: // blue
				App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
				break;
			case Collider::Type::PLAYER: // green
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
				break;
			case Collider::Type::ENEMY: // red
				App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
				break;
			case Collider::Type::PLAYER_SHOT: // yellow
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
				break;
			case Collider::Type::ENEMY_SHOT: // cian
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
				break;
			case Collider::Type::HEAL: // magenta
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
				break;
			case Collider::Type::DETECTION_ZONE: // orange
				App->render->DrawQuad(colliders[i]->rect, 255, 165, 0, alpha);
				break;
			case Collider::Type::LASER: // orange
				App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
				break;
			case Collider::Type::OBJECT: // pink
				App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha);
				break;
			case Collider::Type::STOP_CAM_ZONE_2: // orange
				App->render->DrawQuad(colliders[i]->rect, 255, 100, 100, alpha);
				break;
			case Collider::Type::STOP_CAM_ZONE: // orange
				App->render->DrawQuad(colliders[i]->rect, 255, 100, 100, alpha);
				break;
			case Collider::Type::STOP_CAM_TRIGGER: // orange
				App->render->DrawQuad(colliders[i]->rect, 100, 100, 100, alpha);
				break;
			case Collider::Type::KNIFE: // brown
				App->render->DrawQuad(colliders[i]->rect, 165, 42, 42, alpha);
				break;
			case Collider::Type::MUZZLE: // white
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			default:
				break;
		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}

void ModuleCollisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}