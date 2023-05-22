#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include <string>
#include <cmath>
using namespace std;
#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

// Define the player states
enum class PlayerState {
	Idle,
	Moving,
	Shooting,
	Grenade,
	Roll,
	Win,
	Spawn,
	Death,
	Damage,
	ShootingMoving,
	GrenadeMoving
};

class ModulePlayer : public Module {
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

	void updateHp();

	void setIdleAnimations();
	void setMovingAnimations();
	void setShootingAnimations();
	void setGrenadeAnimations();
	void setRollAnimations();
	void setWinAnimations();
	void setSpawnAnimations();
	void setDeathAnimations();
	void setDamageAnimations();
	void setShootingMovingAnimations();

	bool isMoving();

	bool isShooting();

	bool isGrenade();

	bool isRoll();

	bool isShootingMoving();

	void move();

	void roll();

	void shoot();

	void grenade();

	void shootMoving();

	void getLastDirection();

	void stateMachine();

public:
	// Position of the player in the map
	iPoint position;

	// Player current state
	PlayerState currentState;

	int lastDirection;

	int delay = 10;

	int hp = 100;

	int currentDirection;

	iPoint diferencia;

	bool isRolling = false;

	bool godMode = false;

	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;

	SDL_Texture* textureHp = nullptr;
	SDL_Texture* textureP1 = nullptr;
	SDL_Texture* textureWeapon = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimationTorso = nullptr;
	Animation* currentAnimationLegs = nullptr;

	// A set of animations
	float animSpeed = 0.1f;

	Animation emptyAnimation;

	Animation idleAnimUpTorso;			// Idle animation (torso)
	Animation idleAnimDownTorso;		// Idle animation (torso)
	Animation idleAnimLeftTorso;		// Idle animation (torso)
	Animation idleAnimRightTorso;		// Idle animation (torso)
	Animation idleAnimUpLeftTorso;		// Idle animation (torso)
	Animation idleAnimUpRightTorso;		// Idle animation (torso)
	Animation idleAnimDownLeftTorso;	// Idle animation (torso)
	Animation idleAnimDownRightTorso;	// Idle animation (torso)
	Animation idleAnimUpLegs;			// Idle animation (legs)
	Animation idleAnimDownLegs;			// Idle animation (legs)
	Animation idleAnimLeftLegs;			// Idle animation (legs)
	Animation idleAnimRightLegs;		// Idle animation (legs)
	Animation idleAnimUpLeftLegs;		// Idle animation (legs)
	Animation idleAnimUpRightLegs;		// Idle animation (legs)
	Animation idleAnimDownLeftLegs;		// Idle animation (legs)
	Animation idleAnimDownRightLegs;	// Idle animation (legs)

	Animation upAnimLegs;				// Movement animation (legs)
	Animation downAnimLegs;				// Movement animation (legs)
	Animation leftAnimLegs;				// Movement animation (legs)
	Animation rightAnimLegs;			// Movement animation (legs)
	Animation upLeftAnimLegs;			// Movement animation (legs)
	Animation upRightAnimLegs;			// Movement animation (legs)
	Animation downLeftAnimLegs;			// Movement animation (legs)
	Animation downRightAnimLegs;		// Movement animation (legs)

		// Roll animation (whole body)
	Animation rollAnimUp;				// Roll animation
	Animation rollAnimDown;				// Roll animation
	Animation rollAnimLeft;				// Roll animation	
	Animation rollAnimRight;			// Roll animation
	Animation rollAnimUpLeft;			// Roll animation
	Animation rollAnimUpRight;			// Roll animation
	Animation rollAnimDownLeft;			// Roll animation
	Animation rollAnimDownRight;		// Roll animation

		// Shoot animation (only for the torso)
	Animation shootAnimUp;				// Shoot animation
	Animation shootAnimDown;			// Shoot animation
	Animation shootAnimLeft;			// Shoot animation
	Animation shootAnimRight;			// Shoot animation
	Animation shootAnimUpLeft;			// Shoot animation
	Animation shootAnimUpRight;			// Shoot animation
	Animation shootAnimDownLeft;		// Shoot animation
	Animation shootAnimDownRight;		// Shoot animation

	Animation grenadeAnimUp;			// Grenade animation
	Animation grenadeAnimDown;			// Grenade animation
	Animation grenadeAnimLeft;			// Grenade animation
	Animation grenadeAnimRight;			// Grenade animation
	Animation grenadeAnimUpLeft;		// Grenade animation
	Animation grenadeAnimUpRight;		// Grenade animation
	Animation grenadeAnimDownLeft;		// Grenade animation
	Animation grenadeAnimDownRight;		// Grenade animation

	Animation deathAnim;				// Death animation

	Animation damageAnim;				// Damage animation

	// Sound effects indices
	uint laserFx = 0;
	uint explosionFx = 0;

	// The player's collider
	Collider* collider = nullptr;
	Collider* colliderU = nullptr;
	Collider* colliderD = nullptr;
	Collider* colliderR = nullptr;
	Collider* colliderL = nullptr;

	bool lockR = false;
	bool lockU = false;
	bool lockD = false;
	bool lockL = false;
	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// Font score index
	uint score = 010;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };

};

#endif //!__MODULE_PLAYER_H__