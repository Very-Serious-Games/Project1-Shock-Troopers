#include "ModuleCollisions.h"

#include <iostream>
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_Scancode.h"

using namespace std;

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i) {
		colliders[i] = nullptr;
	}
}
// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

bool ModuleCollisions::Start()
{
	bool ret = true;

	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::LASER] = true;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::WALL][Collider::Type::PICKUP_HP] = false;
	matrix[Collider::Type::WALL][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::WALL][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::WALL][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::WALL][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::WALL][Collider::Type::STOP_CAM_ZONE_3] = false;
	matrix[Collider::Type::WALL][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::WALL][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::WALL][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::WALL][Collider::Type::MUZZLE] = false;
	matrix[Collider::Type::WALL][Collider::Type::BRIDGE] = false;
	matrix[Collider::Type::WALL][Collider::Type::LANDMINE] = false;
	matrix[Collider::Type::WALL][Collider::Type::PICKUP_DIAMOND] = false;
	matrix[Collider::Type::WALL][Collider::Type::PICKUP_NODAMAGE] = false;
	matrix[Collider::Type::WALL][Collider::Type::CAMERA_LIMIT] = true;
	matrix[Collider::Type::WALL][Collider::Type::TRIGGER_LEAVE_ZONE_2] = false;
	matrix[Collider::Type::WALL][Collider::Type::STOP_ENEMY] = false;

	matrix[Collider::Type::DETECTION_ZONE][Collider::Type::WALL] = false;
	matrix[Collider::Type::DETECTION_ZONE][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::DETECTION_ZONE][Collider::Type::LASER] = false;
	matrix[Collider::Type::DETECTION_ZONE][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::DETECTION_ZONE][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::DETECTION_ZONE][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::DETECTION_ZONE][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::DETECTION_ZONE][Collider::Type::PICKUP_HP] = false;
	matrix[Collider::Type::DETECTION_ZONE][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::DETECTION_ZONE][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::DETECTION_ZONE][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::DETECTION_ZONE][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::DETECTION_ZONE][Collider::Type::STOP_CAM_ZONE_3] = false;
	matrix[Collider::Type::DETECTION_ZONE][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::DETECTION_ZONE][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::DETECTION_ZONE][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::DETECTION_ZONE][Collider::Type::MUZZLE] = false;
	matrix[Collider::Type::DETECTION_ZONE][Collider::Type::BRIDGE] = false;
	matrix[Collider::Type::DETECTION_ZONE][Collider::Type::LANDMINE] = false;
	matrix[Collider::Type::DETECTION_ZONE][Collider::Type::PICKUP_DIAMOND] = false;
	matrix[Collider::Type::DETECTION_ZONE][Collider::Type::PICKUP_NODAMAGE] = false;
	matrix[Collider::Type::DETECTION_ZONE][Collider::Type::CAMERA_LIMIT] = false;
	matrix[Collider::Type::DETECTION_ZONE][Collider::Type::TRIGGER_LEAVE_ZONE_2] = false;
	matrix[Collider::Type::DETECTION_ZONE][Collider::Type::STOP_ENEMY] = false;

	matrix[Collider::Type::PLAYER_WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::LASER] = true;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::PICKUP_HP] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::STOP_CAM_ZONE_3] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::MUZZLE] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::BRIDGE] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::LANDMINE] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::PICKUP_DIAMOND] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::PICKUP_NODAMAGE] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::CAMERA_LIMIT] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::TRIGGER_LEAVE_ZONE_2] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::STOP_ENEMY] = false;
	matrix[Collider::Type::PLAYER_WALL][Collider::Type::STOP_ENEMY] = false;

	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::LASER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PICKUP_HP] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::OBJECT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::STOP_CAM_ZONE_3] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::MISSILE] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::MUZZLE] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::BRIDGE] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::LANDMINE] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PICKUP_DIAMOND] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PICKUP_NODAMAGE] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::CAMERA_LIMIT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::TRIGGER_LEAVE_ZONE_2] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::STOP_ENEMY] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::STOP_ENEMY] = false;

	matrix[Collider::Type::ENEMY][Collider::Type::WALL] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::LASER] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PICKUP_HP] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::STOP_CAM_ZONE_3] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::MUZZLE] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::BRIDGE] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::LANDMINE] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PICKUP_DIAMOND] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PICKUP_NODAMAGE] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::CAMERA_LIMIT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::TRIGGER_LEAVE_ZONE_2] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::STOP_ENEMY] = true;

	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::LASER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PICKUP_HP] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::OBJECT] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::STOP_CAM_ZONE_3] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::MISSILE] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::MUZZLE] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::BRIDGE] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::LANDMINE] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PICKUP_DIAMOND] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PICKUP_NODAMAGE] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::CAMERA_LIMIT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::TRIGGER_LEAVE_ZONE_2] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::STOP_ENEMY] = false;

	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WALL] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::LASER] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PICKUP_HP] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::STOP_CAM_ZONE_3] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::MUZZLE] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::BRIDGE] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::LANDMINE] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PICKUP_DIAMOND] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PICKUP_NODAMAGE] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::CAMERA_LIMIT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::TRIGGER_LEAVE_ZONE_2] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::STOP_ENEMY] = false;

	matrix[Collider::Type::LASER][Collider::Type::WALL] = true;
	matrix[Collider::Type::LASER][Collider::Type::PLAYER_WALL] = true;
	matrix[Collider::Type::LASER][Collider::Type::LASER] = false;
	matrix[Collider::Type::LASER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::LASER][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::LASER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::LASER][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::LASER][Collider::Type::PICKUP_HP] = false;
	matrix[Collider::Type::LASER][Collider::Type::OBJECT] = true;
	matrix[Collider::Type::LASER][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::LASER][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::LASER][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::LASER][Collider::Type::STOP_CAM_ZONE_3] = false;
	matrix[Collider::Type::LASER][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::LASER][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::LASER][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::LASER][Collider::Type::MUZZLE] = false;
	matrix[Collider::Type::LASER][Collider::Type::BRIDGE] = false;
	matrix[Collider::Type::LASER][Collider::Type::LANDMINE] = false;
	matrix[Collider::Type::LASER][Collider::Type::PICKUP_DIAMOND] = false;
	matrix[Collider::Type::LASER][Collider::Type::PICKUP_NODAMAGE] = false;
	matrix[Collider::Type::LASER][Collider::Type::CAMERA_LIMIT] = false;
	matrix[Collider::Type::LASER][Collider::Type::TRIGGER_LEAVE_ZONE_2] = false;
	matrix[Collider::Type::LASER][Collider::Type::STOP_ENEMY] = false;

	matrix[Collider::Type::OBJECT][Collider::Type::WALL] = false;
	matrix[Collider::Type::OBJECT][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::OBJECT][Collider::Type::LASER] = true;
	matrix[Collider::Type::OBJECT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::OBJECT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::OBJECT][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::OBJECT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::OBJECT][Collider::Type::PICKUP_HP] = false;
	matrix[Collider::Type::OBJECT][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::OBJECT][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::OBJECT][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::OBJECT][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::OBJECT][Collider::Type::STOP_CAM_ZONE_3] = false;
	matrix[Collider::Type::OBJECT][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::OBJECT][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::OBJECT][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::OBJECT][Collider::Type::MUZZLE] = false;
	matrix[Collider::Type::OBJECT][Collider::Type::BRIDGE] = false;
	matrix[Collider::Type::OBJECT][Collider::Type::LANDMINE] = false;
	matrix[Collider::Type::OBJECT][Collider::Type::PICKUP_DIAMOND] = false;
	matrix[Collider::Type::OBJECT][Collider::Type::PICKUP_NODAMAGE] = false;
	matrix[Collider::Type::OBJECT][Collider::Type::CAMERA_LIMIT] = false;
	matrix[Collider::Type::OBJECT][Collider::Type::TRIGGER_LEAVE_ZONE_2] = false;
	matrix[Collider::Type::OBJECT][Collider::Type::STOP_ENEMY] = false;

	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::WALL] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::LASER] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::PICKUP_HP] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::STOP_CAM_ZONE] = true;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::STOP_CAM_ZONE_2] = true;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::STOP_CAM_ZONE_3] = true;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::MUZZLE] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::BRIDGE] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::LANDMINE] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::PICKUP_DIAMOND] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::PICKUP_NODAMAGE] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::CAMERA_LIMIT] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::TRIGGER_LEAVE_ZONE_2] = false;
	matrix[Collider::Type::STOP_CAM_TRIGGER][Collider::Type::STOP_ENEMY] = false;

	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::WALL] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::LASER] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::PICKUP_HP] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::STOP_CAM_ZONE_3] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::STOP_CAM_TRIGGER] = true;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::MUZZLE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::BRIDGE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::LANDMINE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::PICKUP_DIAMOND] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::PICKUP_NODAMAGE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::CAMERA_LIMIT] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::TRIGGER_LEAVE_ZONE_2] = false;
	matrix[Collider::Type::STOP_CAM_ZONE][Collider::Type::STOP_ENEMY] = false;

	matrix[Collider::Type::STOP_CAM_ZONE_2][Collider::Type::WALL] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_2][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_2][Collider::Type::LASER] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_2][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_2][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_2][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_2][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_2][Collider::Type::PICKUP_HP] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_2][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_2][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_2][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_2][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_2][Collider::Type::STOP_CAM_ZONE_3] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_2][Collider::Type::STOP_CAM_TRIGGER] = true;
	matrix[Collider::Type::STOP_CAM_ZONE_2][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_2][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_2][Collider::Type::MUZZLE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_2][Collider::Type::BRIDGE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_2][Collider::Type::LANDMINE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_2][Collider::Type::PICKUP_DIAMOND] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_2][Collider::Type::PICKUP_NODAMAGE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_2][Collider::Type::CAMERA_LIMIT] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_2][Collider::Type::TRIGGER_LEAVE_ZONE_2] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_2][Collider::Type::STOP_ENEMY] = false;

	matrix[Collider::Type::STOP_CAM_ZONE_3][Collider::Type::WALL] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_3][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_3][Collider::Type::LASER] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_3][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_3][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_3][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_3][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_3][Collider::Type::PICKUP_HP] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_3][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_3][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_3][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_3][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_3][Collider::Type::STOP_CAM_ZONE_3] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_3][Collider::Type::STOP_CAM_TRIGGER] = true;
	matrix[Collider::Type::STOP_CAM_ZONE_3][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_3][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_3][Collider::Type::MUZZLE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_3][Collider::Type::BRIDGE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_3][Collider::Type::LANDMINE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_3][Collider::Type::PICKUP_DIAMOND] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_3][Collider::Type::PICKUP_NODAMAGE] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_3][Collider::Type::CAMERA_LIMIT] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_3][Collider::Type::TRIGGER_LEAVE_ZONE_2] = false;
	matrix[Collider::Type::STOP_CAM_ZONE_3][Collider::Type::STOP_ENEMY] = false;

	matrix[Collider::Type::MISSILE][Collider::Type::WALL] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::LASER] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::MISSILE][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::MISSILE][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::PICKUP_HP] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::STOP_CAM_ZONE_3] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::MUZZLE] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::BRIDGE] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::LANDMINE] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::PICKUP_DIAMOND] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::PICKUP_NODAMAGE] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::CAMERA_LIMIT] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::TRIGGER_LEAVE_ZONE_2] = false;
	matrix[Collider::Type::MISSILE][Collider::Type::STOP_ENEMY] = false;

	matrix[Collider::Type::MUZZLE][Collider::Type::WALL] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::LASER] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::PICKUP_HP] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::STOP_CAM_ZONE_3] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::MUZZLE] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::BRIDGE] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::LANDMINE] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::PICKUP_DIAMOND] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::PICKUP_NODAMAGE] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::CAMERA_LIMIT] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::TRIGGER_LEAVE_ZONE_2] = false;
	matrix[Collider::Type::MUZZLE][Collider::Type::STOP_ENEMY] = false;

	matrix[Collider::Type::LANDMINE][Collider::Type::WALL] = false;
	matrix[Collider::Type::LANDMINE][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::LANDMINE][Collider::Type::LASER] = false;
	matrix[Collider::Type::LANDMINE][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::LANDMINE][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::LANDMINE][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::LANDMINE][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::LANDMINE][Collider::Type::PICKUP_HP] = false;
	matrix[Collider::Type::LANDMINE][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::LANDMINE][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::LANDMINE][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::LANDMINE][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::LANDMINE][Collider::Type::STOP_CAM_ZONE_3] = false;
	matrix[Collider::Type::LANDMINE][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::LANDMINE][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::LANDMINE][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::LANDMINE][Collider::Type::MUZZLE] = false;
	matrix[Collider::Type::LANDMINE][Collider::Type::LANDMINE] = false;
	matrix[Collider::Type::LANDMINE][Collider::Type::BRIDGE] = false;
	matrix[Collider::Type::LANDMINE][Collider::Type::PICKUP_DIAMOND] = false;
	matrix[Collider::Type::LANDMINE][Collider::Type::PICKUP_NODAMAGE] = false;
	matrix[Collider::Type::LANDMINE][Collider::Type::CAMERA_LIMIT] = false;
	matrix[Collider::Type::LANDMINE][Collider::Type::TRIGGER_LEAVE_ZONE_2] = false;
	matrix[Collider::Type::LANDMINE][Collider::Type::STOP_ENEMY] = false;

	matrix[Collider::Type::BRIDGE][Collider::Type::WALL] = false;
	matrix[Collider::Type::BRIDGE][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::BRIDGE][Collider::Type::LASER] = false;
	matrix[Collider::Type::BRIDGE][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::BRIDGE][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::BRIDGE][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::BRIDGE][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::BRIDGE][Collider::Type::PICKUP_HP] = false;
	matrix[Collider::Type::BRIDGE][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::BRIDGE][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::BRIDGE][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::BRIDGE][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::BRIDGE][Collider::Type::STOP_CAM_ZONE_3] = false;
	matrix[Collider::Type::BRIDGE][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::BRIDGE][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::BRIDGE][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::BRIDGE][Collider::Type::MUZZLE] = false;
	matrix[Collider::Type::BRIDGE][Collider::Type::LANDMINE] = false;
	matrix[Collider::Type::BRIDGE][Collider::Type::BRIDGE] = false;
	matrix[Collider::Type::BRIDGE][Collider::Type::PICKUP_DIAMOND] = false;
	matrix[Collider::Type::BRIDGE][Collider::Type::PICKUP_NODAMAGE] = false;
	matrix[Collider::Type::BRIDGE][Collider::Type::CAMERA_LIMIT] = false;
	matrix[Collider::Type::BRIDGE][Collider::Type::TRIGGER_LEAVE_ZONE_2] = false;
	matrix[Collider::Type::BRIDGE][Collider::Type::STOP_ENEMY] = false;

	matrix[Collider::Type::PICKUP_HP][Collider::Type::WALL] = false;
	matrix[Collider::Type::PICKUP_HP][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::PICKUP_HP][Collider::Type::LASER] = false;
	matrix[Collider::Type::PICKUP_HP][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::PICKUP_HP][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::PICKUP_HP][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PICKUP_HP][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::PICKUP_HP][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::PICKUP_HP][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::PICKUP_HP][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::PICKUP_HP][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::PICKUP_HP][Collider::Type::STOP_CAM_ZONE_3] = false;
	matrix[Collider::Type::PICKUP_HP][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::PICKUP_HP][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::PICKUP_HP][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::PICKUP_HP][Collider::Type::MUZZLE] = false;
	matrix[Collider::Type::PICKUP_HP][Collider::Type::LANDMINE] = false;
	matrix[Collider::Type::PICKUP_HP][Collider::Type::BRIDGE] = false;
	matrix[Collider::Type::PICKUP_HP][Collider::Type::PICKUP_DIAMOND] = false;
	matrix[Collider::Type::PICKUP_HP][Collider::Type::PICKUP_HP] = false;
	matrix[Collider::Type::PICKUP_HP][Collider::Type::PICKUP_NODAMAGE] = false;
	matrix[Collider::Type::PICKUP_HP][Collider::Type::CAMERA_LIMIT] = false;
	matrix[Collider::Type::PICKUP_HP][Collider::Type::TRIGGER_LEAVE_ZONE_2] = false;
	matrix[Collider::Type::PICKUP_HP][Collider::Type::STOP_ENEMY] = false;

	matrix[Collider::Type::PICKUP_NODAMAGE][Collider::Type::WALL] = false;
	matrix[Collider::Type::PICKUP_NODAMAGE][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::PICKUP_NODAMAGE][Collider::Type::LASER] = false;
	matrix[Collider::Type::PICKUP_NODAMAGE][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::PICKUP_NODAMAGE][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::PICKUP_NODAMAGE][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PICKUP_NODAMAGE][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::PICKUP_NODAMAGE][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::PICKUP_NODAMAGE][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::PICKUP_NODAMAGE][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::PICKUP_NODAMAGE][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::PICKUP_NODAMAGE][Collider::Type::STOP_CAM_ZONE_3] = false;
	matrix[Collider::Type::PICKUP_NODAMAGE][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::PICKUP_NODAMAGE][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::PICKUP_NODAMAGE][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::PICKUP_NODAMAGE][Collider::Type::MUZZLE] = false;
	matrix[Collider::Type::PICKUP_NODAMAGE][Collider::Type::LANDMINE] = false;
	matrix[Collider::Type::PICKUP_NODAMAGE][Collider::Type::BRIDGE] = false;
	matrix[Collider::Type::PICKUP_NODAMAGE][Collider::Type::PICKUP_HP] = false;
	matrix[Collider::Type::PICKUP_NODAMAGE][Collider::Type::PICKUP_DIAMOND] = false;
	matrix[Collider::Type::PICKUP_NODAMAGE][Collider::Type::PICKUP_NODAMAGE] = false;
	matrix[Collider::Type::PICKUP_NODAMAGE][Collider::Type::CAMERA_LIMIT] = false;
	matrix[Collider::Type::PICKUP_NODAMAGE][Collider::Type::TRIGGER_LEAVE_ZONE_2] = false;
	matrix[Collider::Type::PICKUP_NODAMAGE][Collider::Type::STOP_ENEMY] = false;

	matrix[Collider::Type::PICKUP_DIAMOND][Collider::Type::WALL] = false;
	matrix[Collider::Type::PICKUP_DIAMOND][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::PICKUP_DIAMOND][Collider::Type::LASER] = false;
	matrix[Collider::Type::PICKUP_DIAMOND][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::PICKUP_DIAMOND][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::PICKUP_DIAMOND][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PICKUP_DIAMOND][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::PICKUP_DIAMOND][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::PICKUP_DIAMOND][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::PICKUP_DIAMOND][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::PICKUP_DIAMOND][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::PICKUP_DIAMOND][Collider::Type::STOP_CAM_ZONE_3] = false;
	matrix[Collider::Type::PICKUP_DIAMOND][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::PICKUP_DIAMOND][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::PICKUP_DIAMOND][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::PICKUP_DIAMOND][Collider::Type::MUZZLE] = false;
	matrix[Collider::Type::PICKUP_DIAMOND][Collider::Type::LANDMINE] = false;
	matrix[Collider::Type::PICKUP_DIAMOND][Collider::Type::BRIDGE] = false;
	matrix[Collider::Type::PICKUP_DIAMOND][Collider::Type::PICKUP_DIAMOND] = false;
	matrix[Collider::Type::PICKUP_DIAMOND][Collider::Type::PICKUP_HP] = false;
	matrix[Collider::Type::PICKUP_DIAMOND][Collider::Type::PICKUP_NODAMAGE] = false;
	matrix[Collider::Type::PICKUP_DIAMOND][Collider::Type::CAMERA_LIMIT] = false;
	matrix[Collider::Type::PICKUP_DIAMOND][Collider::Type::TRIGGER_LEAVE_ZONE_2] = false;
	matrix[Collider::Type::PICKUP_DIAMOND][Collider::Type::STOP_ENEMY] = false;

	matrix[Collider::Type::CAMERA_LIMIT][Collider::Type::WALL] = true;
	matrix[Collider::Type::CAMERA_LIMIT][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::CAMERA_LIMIT][Collider::Type::LASER] = false;
	matrix[Collider::Type::CAMERA_LIMIT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::CAMERA_LIMIT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::CAMERA_LIMIT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::CAMERA_LIMIT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::CAMERA_LIMIT][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::CAMERA_LIMIT][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::CAMERA_LIMIT][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::CAMERA_LIMIT][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::CAMERA_LIMIT][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::CAMERA_LIMIT][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::CAMERA_LIMIT][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::CAMERA_LIMIT][Collider::Type::MUZZLE] = false;
	matrix[Collider::Type::CAMERA_LIMIT][Collider::Type::LANDMINE] = false;
	matrix[Collider::Type::CAMERA_LIMIT][Collider::Type::BRIDGE] = false;
	matrix[Collider::Type::CAMERA_LIMIT][Collider::Type::PICKUP_DIAMOND] = false;
	matrix[Collider::Type::CAMERA_LIMIT][Collider::Type::PICKUP_HP] = false;
	matrix[Collider::Type::CAMERA_LIMIT][Collider::Type::PICKUP_NODAMAGE] = false;
	matrix[Collider::Type::CAMERA_LIMIT][Collider::Type::CAMERA_LIMIT] = false;
	matrix[Collider::Type::CAMERA_LIMIT][Collider::Type::TRIGGER_LEAVE_ZONE_2] = false;
	matrix[Collider::Type::CAMERA_LIMIT][Collider::Type::STOP_ENEMY] = false;

	matrix[Collider::Type::TRIGGER_LEAVE_ZONE_2][Collider::Type::WALL] = false;
	matrix[Collider::Type::TRIGGER_LEAVE_ZONE_2][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::TRIGGER_LEAVE_ZONE_2][Collider::Type::LASER] = false;
	matrix[Collider::Type::TRIGGER_LEAVE_ZONE_2][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::TRIGGER_LEAVE_ZONE_2][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::TRIGGER_LEAVE_ZONE_2][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::TRIGGER_LEAVE_ZONE_2][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::TRIGGER_LEAVE_ZONE_2][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::TRIGGER_LEAVE_ZONE_2][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::TRIGGER_LEAVE_ZONE_2][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::TRIGGER_LEAVE_ZONE_2][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::TRIGGER_LEAVE_ZONE_2][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::TRIGGER_LEAVE_ZONE_2][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::TRIGGER_LEAVE_ZONE_2][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::TRIGGER_LEAVE_ZONE_2][Collider::Type::MUZZLE] = false;
	matrix[Collider::Type::TRIGGER_LEAVE_ZONE_2][Collider::Type::LANDMINE] = false;
	matrix[Collider::Type::TRIGGER_LEAVE_ZONE_2][Collider::Type::BRIDGE] = false;
	matrix[Collider::Type::TRIGGER_LEAVE_ZONE_2][Collider::Type::PICKUP_DIAMOND] = false;
	matrix[Collider::Type::TRIGGER_LEAVE_ZONE_2][Collider::Type::PICKUP_HP] = false;
	matrix[Collider::Type::TRIGGER_LEAVE_ZONE_2][Collider::Type::PICKUP_NODAMAGE] = false;
	matrix[Collider::Type::TRIGGER_LEAVE_ZONE_2][Collider::Type::TRIGGER_LEAVE_ZONE_2] = false;
	matrix[Collider::Type::TRIGGER_LEAVE_ZONE_2][Collider::Type::STOP_ENEMY] = false;

	matrix[Collider::Type::STOP_ENEMY][Collider::Type::WALL] = false;
	matrix[Collider::Type::STOP_ENEMY][Collider::Type::PLAYER_WALL] = false;
	matrix[Collider::Type::STOP_ENEMY][Collider::Type::LASER] = false;
	matrix[Collider::Type::STOP_ENEMY][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::STOP_ENEMY][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::STOP_ENEMY][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::STOP_ENEMY][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::STOP_ENEMY][Collider::Type::OBJECT] = false;
	matrix[Collider::Type::STOP_ENEMY][Collider::Type::DETECTION_ZONE] = false;
	matrix[Collider::Type::STOP_ENEMY][Collider::Type::STOP_CAM_ZONE] = false;
	matrix[Collider::Type::STOP_ENEMY][Collider::Type::STOP_CAM_ZONE_2] = false;
	matrix[Collider::Type::STOP_ENEMY][Collider::Type::STOP_CAM_TRIGGER] = false;
	matrix[Collider::Type::STOP_ENEMY][Collider::Type::KNIFE] = false;
	matrix[Collider::Type::STOP_ENEMY][Collider::Type::MISSILE] = false;
	matrix[Collider::Type::STOP_ENEMY][Collider::Type::MUZZLE] = false;
	matrix[Collider::Type::STOP_ENEMY][Collider::Type::LANDMINE] = false;
	matrix[Collider::Type::STOP_ENEMY][Collider::Type::BRIDGE] = false;
	matrix[Collider::Type::STOP_ENEMY][Collider::Type::PICKUP_DIAMOND] = false;
	matrix[Collider::Type::STOP_ENEMY][Collider::Type::PICKUP_HP] = false;
	matrix[Collider::Type::STOP_ENEMY][Collider::Type::PICKUP_NODAMAGE] = false;
	matrix[Collider::Type::STOP_ENEMY][Collider::Type::TRIGGER_LEAVE_ZONE_2] = false;
	matrix[Collider::Type::STOP_ENEMY][Collider::Type::STOP_ENEMY] = false;
		
	
	return ret;
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
			case Collider::Type::TRIGGER_LEAVE_ZONE_2: // green
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
			case Collider::Type::PICKUP_HP: // magenta
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
				break;
			case Collider::Type::PICKUP_DIAMOND: // magenta
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
				break;
			case Collider::Type::PICKUP_NODAMAGE: // magenta
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
			case Collider::Type::STOP_CAM_ZONE_3: // orange
				App->render->DrawQuad(colliders[i]->rect, 255, 100, 100, alpha);
				break;
			case Collider::Type::STOP_CAM_ZONE_2: // orange
				App->render->DrawQuad(colliders[i]->rect, 255, 100, 100, alpha);
				break;
			case Collider::Type::STOP_CAM_ZONE: // orange
				App->render->DrawQuad(colliders[i]->rect, 255, 100, 100, alpha);
				break;
			case Collider::Type::STOP_CAM_TRIGGER: // gray
				App->render->DrawQuad(colliders[i]->rect, 100, 100, 100, alpha);
				break;
			case Collider::Type::STOP_ENEMY: // gray
				App->render->DrawQuad(colliders[i]->rect, 100, 100, 100, alpha);
				break;
			case Collider::Type::KNIFE: // brown
				App->render->DrawQuad(colliders[i]->rect, 165, 42, 42, alpha);
				break;
			case Collider::Type::MUZZLE: // white
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::BRIDGE: // pink
				App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha);
				break;
			case Collider::Type::LANDMINE: // red
				App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
				break;
			case Collider::Type::CAMERA_LIMIT: // red
				App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
				break;
			case Collider::Type::MISSILE: // cian
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
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