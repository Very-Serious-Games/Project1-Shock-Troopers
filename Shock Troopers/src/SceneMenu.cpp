#include "SceneMenu.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneMenu::SceneMenu(bool startEnabled) : Module(startEnabled)
{
	// Background
	background.x = 261;
	background.y = 0;
	background.w = 320;
	background.h = 224;

	// Character selection
	characterSelector.x = 0;
	characterSelector.y = 131;
	characterSelector.w = 247;
	characterSelector.h = 90;

	// Player Select Text
	playerSelectText.x = 25;
	playerSelectText.y = 0;
	playerSelectText.w = 207;
	playerSelectText.h = 15;
}

SceneMenu::~SceneMenu()
{

}

// Load assets
bool SceneMenu::Start()
{
	LOG("Loading menu assets");

	bool ret = true;

	sprites = App->textures->Load("Assets/Sprites/characterSelection.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneMenu::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneMenu::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(sprites, 0, 0, &background, 1.0f);
	App->render->Blit(sprites, 0, 20, &characterSelector, 1.0f);
	App->render->Blit(sprites, 0, 0, &playerSelectText, 1.0f);

	return Update_Status::UPDATE_CONTINUE;
}