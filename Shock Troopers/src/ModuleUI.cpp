#include <stdio.h>
#include "ModuleUI.h"
#include "ModulePlayer.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePickUp.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleEnemies.h"
#include <iostream>

using namespace std;

ModuleUI::ModuleUI(bool startEnabled) : Module(startEnabled)
{
	// iterate the start stage animation, that has 29 frames per row and 3 rows
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 11; col++) {
			int frameX = col * SCREEN_WIDTH;
			int frameY = row * SCREEN_HEIGHT;
			startStage.PushBack({ frameX, frameY, SCREEN_WIDTH, SCREEN_HEIGHT });
		}
	}

	startStage.PushBack({ 0, 0, 0, 0 });
	startStage.speed = 0.8f;
	startStage.loop = false;

	//stage clear anim below
	
	// iterate the start stage animation, that has 6 frames per row and 14 rows
	for (int row = 0; row < 14; row++) {
		for (int col = 0; col < 6; col++) {
			int frameX = col * SCREEN_WIDTH;
			int frameY = row * SCREEN_HEIGHT;
			endStage.PushBack({ frameX, frameY, SCREEN_WIDTH, SCREEN_HEIGHT });
		}
	}

	endStage.PushBack({ 0, 0, 0, 0 });
	endStage.speed = 0.5f;
	endStage.loop = false;
	
	// Loading HP Bar animation
	hp100.PushBack({ 2, 2, 7, 131 });
	hp90.PushBack({ 14, 2, 7, 131 });
	hp80.PushBack({ 26, 2, 7, 131 });
	hp70.PushBack({ 38, 2, 7, 131 });
	hp60.PushBack({ 50, 2, 7, 131 });
	hp50.PushBack({ 62, 2, 7, 131 });
	hp40.PushBack({ 74, 2, 7, 131 });
	hp30.PushBack({ 86, 2, 7, 131 });
	hp20.PushBack({ 98, 2, 7, 131 });
	hp10.PushBack({ 110, 2, 7, 131 });
	hp0.PushBack({ 122, 2, 7, 131 });

	// Loading GO Anims
	goUP.PushBack({ 0, 0, 47, 40 });
	goUP.PushBack({ 47, 0, 47, 40 });
	goUP.PushBack({ 0, 0, 47, 40 });
	goUP.PushBack({ 47, 0, 47, 40 });
	goUP.PushBack({ 0, 0, 47, 40 });
	goUP.PushBack({ 47, 0, 47, 40 });
	goUP.PushBack({ 0, 0, 47, 40 });
	goUP.PushBack({ 47, 0, 47, 40 });
	goUP.PushBack({ 0, 0, 47, 40 });
	goUP.PushBack({ 47, 0, 47, 40 });
	goUP.PushBack({ 0, 0, 47, 40 });
	goUP.PushBack({ 47, 0, 47, 40 });
	goUP.PushBack({ 0, 0, 47, 40 });
	goUP.PushBack({ 47, 0, 47, 40 });
	goUP.PushBack({ 0, 0, 47, 40 });
	goUP.PushBack({ 47, 0, 47, 40 });
	goUP.PushBack({ 0, 0, 47, 40 });
	goUP.PushBack({ 47, 0, 47, 40 });


	goRIGTH.PushBack({ 0, 0, 47, 40 });
	goRIGTH.PushBack({ 0, 47, 47, 40 });
	goRIGTH.PushBack({ 0, 0, 47, 40 });
	goRIGTH.PushBack({ 0, 47, 47, 40 });
	goRIGTH.PushBack({ 0, 0, 47, 40 });
	goRIGTH.PushBack({ 0, 47, 47, 40 });
	goRIGTH.PushBack({ 0, 0, 47, 40 });
	goRIGTH.PushBack({ 0, 47, 47, 40 });
	goRIGTH.PushBack({ 0, 0, 47, 40 });
	goRIGTH.PushBack({ 0, 47, 47, 40 });
	goRIGTH.PushBack({ 0, 0, 47, 40 });
	goRIGTH.PushBack({ 0, 47, 47, 40 });
	goRIGTH.PushBack({ 0, 0, 47, 40 });
	goRIGTH.PushBack({ 0, 47, 47, 40 });
	goRIGTH.PushBack({ 0, 0, 47, 40 });
	goRIGTH.PushBack({ 0, 47, 47, 40 });
	goRIGTH.PushBack({ 0, 0, 47, 40 });
	goRIGTH.PushBack({ 0, 47, 47, 40 });

	goUP.speed = 0.03f;
	goRIGTH.speed = 0.03f;
	goUP.loop = false;
	goRIGTH.loop = false;

	// iterate the start stage animation, that has 48 frames per row and 8 rows
	for (int i = 0; i < 20; i++) {
		gameOver.PushBack({ 0,0,0,0 });
	}
	for (int row = 0; row < 48; row++) {
		for (int col = 0; col < 8; col++) {
			int frameX = col * SCREEN_WIDTH;
			int frameY = row * SCREEN_HEIGHT;
			gameOver.PushBack({ frameX, frameY, SCREEN_WIDTH, SCREEN_HEIGHT });
		}
	}

	gameOver.loop = false;
	gameOver.speed = 1.0f;

}

ModuleUI::~ModuleUI()
{
}

void ModuleUI::updateHp() {
	switch (App->player->hp) {
	case 100:
		currentAnim = &hp100;
		break;
	case 90:
		currentAnim = &hp90;
		break;
	case 80:
		currentAnim = &hp80;
		break;
	case 70:
		currentAnim = &hp70;
		break;
	case 60:
		currentAnim = &hp60;
		break;
	case 50:
		currentAnim = &hp50;
		break;
	case 40:
		currentAnim = &hp40;
		break;
	case 30:
		currentAnim = &hp30;
		break;
	case 20:
		currentAnim = &hp20;
		break;
	case 10:
		currentAnim = &hp10;
		break;
	case 0:
		currentAnim = &hp0;
		break;
	default:
		currentAnim = &hp0;
		break;
	}
}

void ModuleUI::updateScore(int points)
{
	LOG("Updating Score");
	score += points;
}

bool ModuleUI::Start() {

	goRIGTH.Reset();
	goUP.Reset();

	gameOverSound = 0;
	// Load sound effects
	gameOverSound = App->audio->LoadFx("Assets/fx/ui_game_over.wav");
	if (gameOverSound == -1) {
		LOG("Failed to load ui_game_over.wav sound effect");
	}

	playOnce = false;
	
	// Reset the score
	score = 0;

	// Reset timer
	delayTimer = 200;
	timerCounter = 233;
	

	// Reset animations
	startStage.Reset();
	endStage.Reset();
	gameOver.Reset();

	LOG("Loading UI textures");

	bool ret = true;

	currentAnim = &hp100;

	// Starting sprites
	textureP1 = App->textures->Load("Assets/sprites/ui/Player1_Milky.png");
	textureWeapon = App->textures->Load("Assets/sprites/ui/Weapon_Normal.png");
	textureSstage = App->textures->Load("Assets/sprites/ui/start-anim.png");
	textureEstage = App->textures->Load("Assets/sprites/ui/stage-clear.png");
	textureHp = App->textures->Load("Assets/sprites/ui/hp_bar.png");
	timerTextTexture = App->textures->Load("Assets/Fonts/TIME_text.png");
	textureGameOver = App->textures->Load("Assets/sprites/ui/game_over.png");
	textureDebugLegend = App->textures->Load("Assets/sprites/ui/debug_info.png");
	textureGoUP = App->textures->Load("Assets/sprites/ui/goUp.png");
	textureGoRIGTH = App->textures->Load("Assets/sprites/ui/goRight.png");

	// Starting font points
	char lookupTable[] = { "0123456789:;(=)? abcdefghijklmnopqrstuvwxyz@!.-." };
	scoreFont = App->fonts->Load("Assets/fonts/orange_font.png", lookupTable, 3);

	// Starting font timer
	char lookupTableTimer[] = { "0123456789" };
	timerFont = App->fonts->Load("Assets/Fonts/green_font.png", lookupTableTimer);


	return ret;
}

Update_Status ModuleUI::Update() {

	updateHp();

	startStage.Update();


	if (App->enemies->winCondition) {
		endStage.Update();
	}

	if (App->player->deathAnim.HasFinished()) {
		gameOver.Update();
		if (!playOnce) {
			App->audio->PlayFx(gameOverSound);
			playOnce = true;
		}
	}

	if (App->enemies->miniBossKilled)
	{
		goRIGTH.Update();
	}

	if (startStage.HasFinished())
	{
		goUP.Update();
	}

	currentAnim->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleUI::PostUpdate() {

	int x, y;

	// Get camera position
	x = App->render->camera.x + 2;
	y = App->render->camera.y + 2;

	// Showing UI
	App->render->Blit(textureHp, x + 3, y + 40, &currentAnim->GetCurrentFrame());
	App->render->Blit(textureP1, x, y, NULL);
	App->render->Blit(textureWeapon, x + 10, y + 200, NULL);
	App->render->Blit(timerTextTexture, x + 132, y + 2, NULL);

	// Showing end stage animation screen
	App->render->Blit(textureSstage, x, y, &(startStage.GetCurrentFrame()), 1.0f);

	// Showing end stage animation screen
	if (App->enemies->winCondition) {
  		App->render->Blit(textureEstage, x, y, &(endStage.GetCurrentFrame()), 1.0f);
	}

	// Showing Game over screen 
	if (App->player->deathAnim.HasFinished()) {
		App->render->Blit(textureGameOver, x-2, y-2, &(gameOver.GetCurrentFrame()), 1.0f);
	}

	if (startStage.HasFinished() && !App->render->isInZone && !App->render->isInZone2 && !App->render->isInZone3)
	{
		App->render->Blit(textureGoUP, x + 120, y + 30, &(goUP.GetCurrentFrame()));
	}

	if (App->enemies->miniBossKilled)
	{
		App->render->Blit(textureGoRIGTH, x + 240, y + 100, &(goRIGTH.GetCurrentFrame()));
	}
	
	

	// Showing score
	sprintf_s(scoreText, 10, "%08d", score);
	App->fonts->BlitText(34, 3, scoreFont, scoreText);

	// Update timer
	if (timerCounter > 0) {
		delayTimer--;
		if (delayTimer == 0) {
			timerCounter--;
			delayTimer = 100;
		}
	}

	// Showing timer 
	sprintf_s(timerCounterText, 10, "%3d", timerCounter);
	App->fonts->BlitText(137.5, 15, timerFont, timerCounterText);

	// Showing debug legend when godmode is on
	if (App->player->isGodMode) {
		App->render->Blit(textureDebugLegend, x + 132, y, NULL);
	}

	return Update_Status::UPDATE_CONTINUE;
}