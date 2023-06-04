#include "SceneMenu.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"

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

	// character selected default
	characterSelected.x = 262;
	characterSelected.y = 239;
	characterSelected.w = 59;
	characterSelected.h = 59;

	// gun selected default
	gunSelected.x = 159;
	gunSelected.y = 264;
	gunSelected.w = 27;
	gunSelected.h = 31;

	// character name default
	characterName.x = 0;
	characterName.y = 667;
	characterName.w = 63;
	characterName.h = 15;

	// available character Miky
	availableCharacterMiky.x = 30;
	availableCharacterMiky.y = 301;
	availableCharacterMiky.w = 29;
	availableCharacterMiky.h = 29;

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
bool SceneMenu::Start() {

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	LOG("Loading menu assets");

	bool ret = true;

	currentCharacter = 0; // reset the selected character to Jackal

	sprites = App->textures->Load("Assets/Sprites/ui/characterSelection.png");

	App->audio->PlayMusic("Assets/Music/02_Shock_Troopers_menu.ogg", 1.0f);

	return ret;
}

Update_Status SceneMenu::Update() {

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	selectionAnimation.Update();
	GamePad& pad = App->input->pads[0];

	// Pressing SPACE or A(gamepad) goes to the level 1 if current character is Milky
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN and currentCharacter == 1 || pad.a == true and currentCharacter == 1)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}

	if (App->input->keys[SDL_SCANCODE_D] == Key_State::KEY_DOWN || pad.right == true) {
		currentCharacter++;
	}

	if (App->input->keys[SDL_SCANCODE_A] == Key_State::KEY_DOWN || pad.left == true) {
		currentCharacter--;
	}

	if (App->player->isGodMode == true) {
		App->player->isGodMode = false;
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
	App->render->Blit(sprites, 186, 47, &availableCharacterMiky, 1.0f);

	// Menu selection logic
	switch (currentCharacter) {
		case 0:
			characterName.x = 0;
			characterName.y = 667;
			characterSelected.x = 262;
			characterSelected.y = 239;
			gunSelected.x = 128;
			gunSelected.y = 264;
			App->render->Blit(sprites, animationPositions[0][0], animationPositions[0][1], &(selectionAnimation.GetCurrentFrame()), 1.0f); // draw the selection animation
			App->render->Blit(sprites, 59, 56, &characterSelected, 1.0f); // draw the character selected
			App->render->Blit(sprites, 122, 54, &gunSelected, 1.0f); // draw the gun selected
			App->render->Blit(sprites, 90, 105, &characterName, 1.0f); // draw the character name
			break;
		case 1:
			characterName.x = 69;
			characterName.y = 667;
			characterSelected.x = 327;
			characterSelected.y = 239;
			gunSelected.x = 159;
			gunSelected.y = 264;
			App->render->Blit(sprites, animationPositions[1][0], animationPositions[1][1], &(selectionAnimation.GetCurrentFrame()), 1.0f); // draw the selection animation
			App->render->Blit(sprites, 59, 56, &characterSelected, 1.0f); // draw the character selected
			App->render->Blit(sprites, 122, 54, &gunSelected, 1.0f); // draw the gun selected
			App->render->Blit(sprites, 90, 105, &characterName, 1.0f); // draw the character name
			break;
		case 2:
			characterName.x = 138;
			characterName.y = 667;
			characterSelected.x = 392;
			characterSelected.y = 239;
			gunSelected.x = 187;
			gunSelected.y = 264;
			App->render->Blit(sprites, animationPositions[2][0], animationPositions[2][1], &(selectionAnimation.GetCurrentFrame()), 1.0f); // draw the selection animation
			App->render->Blit(sprites, 59, 56, &characterSelected, 1.0f); // draw the character selected
			App->render->Blit(sprites, 122, 55, &gunSelected, 1.0f); // draw the gun selected
			App->render->Blit(sprites, 90, 105, &characterName, 1.0f); // draw the character name
			break;
		case 3:
			characterName.x = 207;
			characterName.y = 667;
			characterSelected.x = 457;
			characterSelected.y = 239;
			gunSelected.x = 215;
			gunSelected.y = 264;
			App->render->Blit(sprites, animationPositions[3][0], animationPositions[3][1], &(selectionAnimation.GetCurrentFrame()), 1.0f); // draw the selection animation
			App->render->Blit(sprites, 59, 56, &characterSelected, 1.0f); // draw the character selected
			App->render->Blit(sprites, 122, 55, &gunSelected, 1.0f); // draw the gun selected
			App->render->Blit(sprites, 90, 105, &characterName, 1.0f); // draw the character name
			break;
		case 4:
			characterName.x = 0;
			characterName.y = 688;
			characterSelected.x = 262;
			characterSelected.y = 304;
			gunSelected.x = 128;
			gunSelected.y = 299;
			App->render->Blit(sprites, animationPositions[4][0], animationPositions[4][1], &(selectionAnimation.GetCurrentFrame()), 1.0f); // draw the selection animation
			App->render->Blit(sprites, 59, 56, &characterSelected, 1.0f); // draw the character selected
			App->render->Blit(sprites, 120, 54, &gunSelected, 1.0f); // draw the gun selected
			App->render->Blit(sprites, 90, 105, &characterName, 1.0f); // draw the character name
			break; 
		case 5:
			characterName.x = 69;
			characterName.y = 688;
			characterSelected.x = 327;
			characterSelected.y = 304;
			gunSelected.x = 159;
			gunSelected.y = 299;
			App->render->Blit(sprites, animationPositions[5][0], animationPositions[5][1], &(selectionAnimation.GetCurrentFrame()), 1.0f); // draw the selection animation
			App->render->Blit(sprites, 59, 56, &characterSelected, 1.0f); // draw the character selected
			App->render->Blit(sprites, 120, 54, &gunSelected, 1.0f); // draw the gun selected
			App->render->Blit(sprites, 90, 105, &characterName, 1.0f); // draw the character name
			break;
		case 6:
			characterName.x = 138;
			characterName.y = 688;
			characterSelected.x = 392;
			characterSelected.y = 304;
			gunSelected.x = 189;
			gunSelected.y = 299;
			App->render->Blit(sprites, animationPositions[6][0], animationPositions[6][1], &(selectionAnimation.GetCurrentFrame()), 1.0f); // draw the selection animation
			App->render->Blit(sprites, 59, 56, &characterSelected, 1.0f); // draw the character selected
			App->render->Blit(sprites, 122, 52, &gunSelected, 1.0f); // draw the gun selected
			App->render->Blit(sprites, 90, 105, &characterName, 1.0f); // draw the character name
			break;
		case 7:
			characterName.x = 207;
			characterName.y = 688;
			characterSelected.x = 457;
			characterSelected.y = 304;
			gunSelected.x = 215;
			gunSelected.y = 299;
			App->render->Blit(sprites, animationPositions[7][0], animationPositions[7][1], &(selectionAnimation.GetCurrentFrame()), 1.0f); // draw the selection animation
			App->render->Blit(sprites, 59, 56, &characterSelected, 1.0f); // draw the character selected
			App->render->Blit(sprites, 120, 54, &gunSelected, 1.0f); // draw the gun selected
			App->render->Blit(sprites, 90, 105, &characterName, 1.0f); // draw the character name
			break;
	default:
		// handle the jump between the last and the first characters  
		if (currentCharacter > 7) { 
			currentCharacter = 0;
		} else if (currentCharacter < 0) {
			currentCharacter = 7;
		}
		break;
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneMenu::CleanUp() {
	App->textures->Unload(sprites);
	App->sceneMenu->Disable();
	return true;
}