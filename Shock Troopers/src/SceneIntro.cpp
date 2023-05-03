#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{
	// intro animation
	int milkyWidht = 173;
	int milkyHeight = 209;
	milkyAnimation.PushBack({ 0, 0, milkyWidht, milkyHeight });
	milkyAnimation.PushBack({ 173, 0, milkyWidht, milkyHeight });
	milkyAnimation.PushBack({ 346, 0, milkyWidht, milkyHeight });
	milkyAnimation.PushBack({ 519, 0, milkyWidht, milkyHeight });
	milkyAnimation.PushBack({ 692, 0, milkyWidht, milkyHeight });
	milkyAnimation.PushBack({ 865, 0, milkyWidht, milkyHeight });
	milkyAnimation.PushBack({ 1038, 0, milkyWidht, milkyHeight });
	milkyAnimation.PushBack({ 1211, 0, milkyWidht, milkyHeight });
	milkyAnimation.speed = 0.06f;

	// smoke animation
	int smokeWidht = 29;
	int smokeHeight = 81;
	smokeAnimation.PushBack({ 0, 210, smokeWidht, smokeHeight });
	smokeAnimation.PushBack({ 29, 210, smokeWidht, smokeHeight });
	smokeAnimation.PushBack({ 58, 210, smokeWidht, smokeHeight });
	smokeAnimation.PushBack({ 87, 210, smokeWidht, smokeHeight });
	smokeAnimation.PushBack({ 116, 210, smokeWidht, smokeHeight });
	smokeAnimation.PushBack({ 145, 210, smokeWidht, smokeHeight });
	smokeAnimation.speed = 0.06f;
}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading intro assets");

	bool ret = true;

	textures = App->textures->Load("assets/sprites/screenIntroSprites.png");
	background = App->textures->Load("assets/sprites/screenIntroBackground.png");
	App->audio->PlayMusic("assets/music/01_Shock_Troopers.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneIntro::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneMenu, 90);
	}

	milkyAnimation.Update();
	smokeAnimation.Update();

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(background, 0, 0, NULL, 1.0f);
	App->render->Blit(textures, (SCREEN_WIDTH/4), 15, &(milkyAnimation.GetCurrentFrame()), 1.0f);
	App->render->Blit(textures, 120, 2, &(smokeAnimation.GetCurrentFrame()), 1.0f);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneIntro::CleanUp()
{
	// TODO Remove All Memory Leaks
	App->sceneIntro->Disable();

	return true;
}