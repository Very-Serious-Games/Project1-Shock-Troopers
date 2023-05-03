#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

public:
	// Position of the player in the map
	iPoint position;

	iPoint direccion;

	iPoint diferencia;

	bool roll = false;

	// The speed in which we move the player (pixels per frame)
	iPoint speed = iPoint(1,1);

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnimUp;			// Idle animation
	Animation idleAnimDown;			// Idle animation
	Animation idleAnimLeft;			// Idle animation
	Animation idleAnimRight;		// Idle animation
	Animation idleAnimUpLeft;		// Idle animation
	Animation idleAnimUpRight;		// Idle animation
	Animation idleAnimDownLeft;		// Idle animation
	Animation idleAnimDownRight;	// Idle animation

	Animation upAnimTorso;			// Movement animation (torso)
	Animation downAnimTorso;		// Movement animation (torso)
	Animation leftAnimTorso;		// Movement animation (torso)
	Animation rightAnimTorso;		// Movement animation (torso)
	Animation upleftAnimTorso;		// Movement animation (torso)
	Animation uprightAnimTorso;		// Movement animation (torso)
	Animation downleftAnimTorso;	// Movement animation (torso)
	Animation downrightAnimTorso;	// Movement animation (torso)
	Animation upAnimLegs;			// Movement animation (legs)
	Animation downAnimLegs;			// Movement animation (legs)
	Animation leftAnimLegs;			// Movement animation (legs)
	Animation rightAnimLegs;		// Movement animation (legs)
	Animation upleftAnimLegs;		// Movement animation (legs)
	Animation uprightAnimLegs;		// Movement animation (legs)
	Animation downleftAnimLegs;		// Movement animation (legs)
	Animation downrightAnimLegs;	// Movement animation (legs)

		// Roll animation (whole body)
	Animation rollAnimUp;			// Roll animation
	Animation rollAnimDown;			// Roll animation
	Animation rollAnimLeft;			// Roll animation	
	Animation rollAnimRight;		// Roll animation
	Animation rollAnimUpLeft;		// Roll animation
	Animation rollAnimUpRight;		// Roll animation
	Animation rollAnimDownLeft;		// Roll animation
	Animation rollAnimDownRight;	// Roll animation

		// Shoot animation (only for the torso)
	Animation shootAnimUp;			// Shoot animation
	Animation shootAnimDown;		// Shoot animation
	Animation shootAnimLeft;		// Shoot animation
	Animation shootAnimRight;		// Shoot animation
	Animation shootAnimUpLeft;		// Shoot animation
	Animation shootAnimUpRight;		// Shoot animation
	Animation shootAnimDownLeft;	// Shoot animation
	Animation shootAnimDownRight;	// Shoot animation

	Animation deathAnim;			// Death animation

	// legacy
	Animation upAnim;
	Animation downAnim;





	// Sound effects indices
	uint laserFx = 0;
	uint explosionFx = 0;

	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// Font score index
	uint score = 000;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };

};

#endif //!__MODULE_PLAYER_H__