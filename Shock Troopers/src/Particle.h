#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Animation.h"
#include "p2Point.h"

struct Collider;

struct Particle
{
public:
	// Constructor
	Particle();

	// Copy constructor
	Particle(const Particle& p);

	// Destructor
	~Particle();

	// Called in ModuleParticles' Update
	// Handles the logic of the particle
	// Returns false when the particle reaches its lifetime
	bool Update();

	// Sets flag for deletion and for the collider aswell
	void SetToDelete();

	void setDirection(int direction);

	int parabole(int x, int direction_x);

public:
	// Defines the position in the screen
	iPoint position;


	bool granada = false;
	int inicio = 0;

	int direccion;

	// Defines the speed at which the particle will move (pixels per second)
	iPoint speed;

	// A set of rectangle sprites
	Animation anim;

	Animation* currentAnimation;

	Animation bullet_U;
	Animation bullet_D;
	Animation bullet_L;
	Animation bullet_R;
	Animation bullet_U_R;
	Animation bullet_U_L;
	Animation bullet_D_R;
	Animation bullet_D_L;

	// Defines wether the particle is alive or not
	// Particles will be set to not alive until "spawnTime" is reached
	bool isAlive = false;

	// Defines the amout of frames this particle has been active
	// Negative values mean the particle is waiting to be activated
	int frameCount = 0;

	// Defines the total amount of frames during which the particle will be active
	uint lifetime = 0;

	// The particle's collider
	Collider* collider = nullptr;

	// A flag for the particle removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;
};

#endif //__PARTICLE_H__