#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled) {

	// iterate the animation, that have 23 frames per row and 6 rows
	for (int row = 0; row < 6; row++) {
		for (int col = 0; col < 23; col++) {
			int frameX = col * SCREEN_WIDTH;
			int frameY = row * SCREEN_HEIGHT;
			introAnimation.PushBack({ frameX, frameY, SCREEN_WIDTH, SCREEN_HEIGHT });
		}
	}

	introAnimation.speed = 0.1f;

	path.PushBack({ 0.0f, 0.0f }, 1000, &introAnimation);

}

SceneIntro::~SceneIntro() {

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading intro assets");

	bool ret = true;

	// load sprite sheet
	textures = App->textures->Load("assets/sprites/background/intro/intro.png");
	// load audio resources
	App->audio->PlayMusic("assets/music/01_Shock_Troopers.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneIntro::Update()
{
	GamePad& pad = App->input->pads[0];

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneMenu, 90);
	}

	// update resources
	path.Update();
	introAnimation.Update();

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(textures, 0, 0, &(path.GetCurrentAnimation()->GetCurrentFrame()), 1.0f);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneIntro::CleanUp()
{
	// TODO Remove All Memory Leaks
	App->sceneIntro->Disable();

	return true;
}