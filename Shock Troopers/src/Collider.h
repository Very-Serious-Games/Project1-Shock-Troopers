#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"

#define MAX_LISTENERS 500

class Module;

struct Collider
{
	enum Type
	{
		NONE = -1,
		WALL,
		PLAYER_WALL,
		LASER,
		PLAYER,
		ENEMY,
		PLAYER_SHOT,
		ENEMY_SHOT,
		PICKUP_HP,
		PICKUP_DIAMOND,
		PICKUP_NODAMAGE,
		OBJECT,
		DETECTION_ZONE,
		STOP_CAM_ZONE,
		STOP_CAM_ZONE_2,
		STOP_CAM_TRIGGER,
		KNIFE,
		MISSILE,
		MUZZLE,
		LANDMINE,
		BRIDGE,
		EXPLOSION,

		MAX
	};

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);

	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;

	void AddListener(Module* listener);

	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listeners[MAX_LISTENERS] = { nullptr };
};


#endif // !__COLLIDER_H__

