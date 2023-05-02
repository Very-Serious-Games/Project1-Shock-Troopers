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

	// characters Avatar
	charactersAvatar.x = 0;
	charactersAvatar.y = 233;
	charactersAvatar.w = 121;
	charactersAvatar.h = 60;

	// character selected Milky
	characterSelectedMilky.x = 327;
	characterSelectedMilky.y = 239;
	characterSelectedMilky.w = 59;
	characterSelectedMilky.h = 59;

	// Selection animation
	int selectionWidht = 32, selectioHeight = 32;

	selectionAnimation.PushBack({ 0, 468, selectionWidht, selectioHeight });
	selectionAnimation.PushBack({ 35, 468, selectionWidht, selectioHeight });
	selectionAnimation.PushBack({ 70, 468, selectionWidht, selectioHeight });
	selectionAnimation.PushBack({ 105, 468, selectionWidht, selectioHeight });
	selectionAnimation.PushBack({ 0, 503, selectionWidht, selectioHeight });
	selectionAnimation.PushBack({ 35, 503, selectionWidht, selectioHeight });
	selectionAnimation.PushBack({ 70, 503, selectionWidht, selectioHeight });
	selectionAnimation.PushBack({ 105, 503, selectionWidht, selectioHeight });
	selectionAnimation.speed = 0.06f;

	// store the animation positions
	

	animationPositions[0][0] = 153;
	animationPositions[0][1] = 45;
	animationPositions[1][0] = 185;
	animationPositions[1][1] = 45;
	animationPositions[2][0] = 217;
	animationPositions[2][1] = 45;
	animationPositions[3][0] = 249;
	animationPositions[3][1] = 45;
	animationPositions[4][0] = 153;
	animationPositions[4][1] = 77;
	animationPositions[5][0] = 185;
	animationPositions[5][1] = 77;
	animationPositions[6][0] = 217;
	animationPositions[6][1] = 77;
	animationPositions[7][0] = 249;
	animationPositions[7][1] = 77;


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
	selectionAnimation.Update();

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN) {
		currentCharacter++;
	}

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN) {
		currentCharacter--;
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneMenu::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(sprites, 0, 0, &background, 1.0f);
	App->render->Blit(sprites, 40, 40, &characterSelector, 1.0f);
	App->render->Blit(sprites, 65, 15, &playerSelectText, 1.0f);
	App->render->Blit(sprites, 156, 47, &charactersAvatar, 1.0f);
	App->render->Blit(sprites, 59, 56, &characterSelectedMilky, 1.0f);

	// character 1
	//App->render->Blit(sprites, 153, 45, &(selectionAnimation.GetCurrentFrame()), 1.0f);

	// character 2
	//App->render->Blit(sprites, 185, 45, &(selectionAnimation.GetCurrentFrame()), 1.0f);

	// character 3
	//App->render->Blit(sprites, 217, 45, &(selectionAnimation.GetCurrentFrame()), 1.0f);

	// character 4
	//App->render->Blit(sprites, 249, 45, &(selectionAnimation.GetCurrentFrame()), 1.0f);

	// character 5
	//App->render->Blit(sprites, 153, 77, &(selectionAnimation.GetCurrentFrame()), 1.0f);

	// character 6
	//App->render->Blit(sprites, 185, 77, &(selectionAnimation.GetCurrentFrame()), 1.0f);

	// character 7
	//App->render->Blit(sprites, 217, 77, &(selectionAnimation.GetCurrentFrame()), 1.0f);

	// character 8
	//App->render->Blit(sprites, 249, 77, &(selectionAnimation.GetCurrentFrame()), 1.0f);

	switch (currentCharacter) {
		case 0:
			App->render->Blit(sprites, animationPositions[0][0], animationPositions[0][1], &(selectionAnimation.GetCurrentFrame()), 1.0f);
			break;
		case 1:
			App->render->Blit(sprites, animationPositions[1][0], animationPositions[1][1], &(selectionAnimation.GetCurrentFrame()), 1.0f);
			break;
		case 2:
			App->render->Blit(sprites, animationPositions[2][0], animationPositions[2][1], &(selectionAnimation.GetCurrentFrame()), 1.0f);
			break;
		case 3:
			App->render->Blit(sprites, animationPositions[3][0], animationPositions[3][1], &(selectionAnimation.GetCurrentFrame()), 1.0f);
			break;
		case 4:
			App->render->Blit(sprites, animationPositions[4][0], animationPositions[4][1], &(selectionAnimation.GetCurrentFrame()), 1.0f);
			break;
		case 5:
			App->render->Blit(sprites, animationPositions[5][0], animationPositions[5][1], &(selectionAnimation.GetCurrentFrame()), 1.0f);
			break;
		case 6:
			App->render->Blit(sprites, animationPositions[6][0], animationPositions[6][1], &(selectionAnimation.GetCurrentFrame()), 1.0f);
			break;
		case 7:
			App->render->Blit(sprites, animationPositions[7][0], animationPositions[7][1], &(selectionAnimation.GetCurrentFrame()), 1.0f);
			break;
	default:
		if (currentCharacter > 7) {
			currentCharacter = 0;
		} else if (currentCharacter < 0) {
			currentCharacter = 7;
		}
		break;
	}

	return Update_Status::UPDATE_CONTINUE;
}