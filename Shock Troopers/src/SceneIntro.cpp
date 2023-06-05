#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled) {

	// Very Srerious Games Intro
	// iterate the animation, that have 10 frames per row and 30 rows
	for (int row = 0; row < 30; row++) {
		for (int col = 0; col < 10; col++) {
			int frameX = col * SCREEN_WIDTH;
			int frameY = row * SCREEN_HEIGHT;
			vsgIntroAnimation.PushBack({ frameX, frameY, SCREEN_WIDTH, SCREEN_HEIGHT });
		}
	}

	for (int i = 0; i < 40; i++) {
		vsgIntroAnimation.PushBack({ 0, 0, 0, 0 });		
	}

	// Shock Troopers Intro
	// iterate the animation, that have 23 frames per row and 5 rows
	for (int row = 0; row < 5; row++) {
		for (int col = 0; col < 23; col++) {
			int frameX = col * SCREEN_WIDTH;
			int frameY = row * SCREEN_HEIGHT;
			stAnimation.PushBack({ frameX, frameY, SCREEN_WIDTH, SCREEN_HEIGHT });
		}
	}

	vsgIntroAnimation.speed = 0.43f;
	stAnimation.speed = 0.2f;
	vsgIntroAnimation.loop = false;
	stAnimation.loop = true;

	currentAnimation = &vsgIntroAnimation;

}

SceneIntro::~SceneIntro() {

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading intro assets");

	musicPlayOnce = 0;

	bool ret = true;

	// load sprite sheet
	vsgIntroTexture = App->textures->Load("assets/sprites/background/intro/very_serious_games_intro.png");
	stIntro = App->textures->Load("assets/sprites/background/intro/shock_troopers_intro.png");
	
	currentTexture = vsgIntroTexture;

	App->audio->PlayMusic("assets/music/00_Very_Serious_Games_intro.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

Update_Status SceneIntro::Update()
{
	GamePad& pad = App->input->pads[0];

	if (vsgIntroAnimation.HasFinished()) {
		currentTexture = stIntro;
		currentAnimation = &stAnimation;
		// load audio resources
		if (musicPlayOnce < 1) {
			musicPlayOnce++;
			App->audio->PlayMusic("assets/music/01_Shock_Troopers_intro.ogg", 1.0f);
		}
		
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN || pad.a == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneMenu, 45);
	}

	// update resources
	vsgIntroAnimation.Update();
	stAnimation.Update();

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(currentTexture, 0, 0, &currentAnimation->GetCurrentFrame(), 1.0f);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneIntro::CleanUp()
{
	App->textures->Unload(vsgIntroTexture);
	App->textures->Unload(stIntro);
	App->sceneIntro->Disable();

	return true;
}