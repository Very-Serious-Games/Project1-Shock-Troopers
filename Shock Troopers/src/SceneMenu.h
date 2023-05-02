#ifndef __SCENE_MENU_H__
#define __SCENE_MENU_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneMenu : public Module
{
public:
	//Constructor
	SceneMenu(bool startEnabled);

	//Destructor
	~SceneMenu();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* sprites = nullptr;
	SDL_Rect background;
	SDL_Rect playerSelectText;
	SDL_Rect characterSelector;
	SDL_Rect charactersAvatar;

	int currentCharacter = 0;		// 0 = Jackal, 1 = Milky, 2 = Loki, 3 = Southern Cross, 4 = Marie Bee, 5 = Rio, 6 = Maru, 7 = Big Mama
	SDL_Rect characterSelected;

	Animation selectionAnimation;
	int animationPositions[8][2];	// 8 characters, 2 positions

	SDL_Rect gunSelected;

	SDL_Rect availableCharacterMiky;
};

#endif