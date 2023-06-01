#ifndef __MODULE_UI_H__
#define __MODULE_UI_H__

#include <string>
#include <cmath>

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "Path.h"

using namespace std;

struct SDL_Texture;

class ModuleUI : public Module
{
public:
	// Constructor
	ModuleUI(bool startEnabled);

	// Destructor
	~ModuleUI();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	void updateHp();

	// Font score index
	uint score = 010;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };

	void updateScore(int points);
	
	////start and end stage anims
	//void startstage();
	//void endstage();

	Animation startStage;
	Animation endStage;
	Path path;
public:

	SDL_Texture* textureHp = nullptr;
	SDL_Texture* textureP1 = nullptr;
	SDL_Texture* textureWeapon = nullptr;
	SDL_Texture* textureSstage = nullptr;
	SDL_Texture* textureEstage = nullptr;
};

#endif //!__MODULE_UI_H__
