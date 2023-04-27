#include "SceneMenu.h"

#include "src/Application.h"
#include "src/ModuleTextures.h"
#include "src/ModuleRender.h"
#include "src/ModuleAudio.h"
#include "src/ModuleInput.h"
#include "src/ModuleFadeToBlack.h"

SceneMenu::SceneMenu(bool startEnabled) : Module(startEnabled)
{

}

SceneMenu::~SceneMenu()
{

}

// Load assets
bool SceneMenu::Start()
{
	LOG("Loading menu assets");

	bool ret = true;

	sprites = App->textures->Load("Assets/Sprites/background.png");

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
	App->render->Blit(sprites, 0, 0, NULL, 1.0f);

	return Update_Status::UPDATE_CONTINUE;
}