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

	// Font and text Score
	uint score = 000;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };


	// Font and text Timer
	int timerFont = -1;
	int timerCounter;
	char timerCounterText[10] = { "\0" };

	void updateScore(int points);

	Animation startStage;
	Animation endStage;
	Path path;
public:

	int scoreFont = -1;
	SDL_Texture* textureHp = nullptr;
	SDL_Texture* textureP1 = nullptr;
	SDL_Texture* textureWeapon = nullptr;
	SDL_Texture* timerTextTexture = nullptr;

	Animation* currentAnim = nullptr;

	Animation hp100;
	Animation hp90;
	Animation hp80;
	Animation hp70;
	Animation hp60;
	Animation hp50;
	Animation hp40;
	Animation hp30;
	Animation hp20;
	Animation hp10;
	Animation hp0;
};

#endif //!__MODULE_UI_H__
