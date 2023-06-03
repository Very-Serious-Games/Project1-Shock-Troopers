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
#include <iostream>

using namespace std;

ModuleUI::ModuleUI(bool startEnabled) : Module(startEnabled)
{

	//iterate the start stage animation, that has 29 frames per row and 3 rows
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
	
	//iterate the start stage animation, that has 6 frames per row and 14 rows
	for (int row = 0; row < 14; row++) {
		for (int col = 0; col < 6; col++) {
			int frameX = col * SCREEN_WIDTH;
			int frameY = row * SCREEN_HEIGHT;
			endStage.PushBack({ frameX, frameY, SCREEN_WIDTH, SCREEN_HEIGHT });
		}
	}

	endStage.PushBack({ 0, 0, 0, 0 });
	endStage.speed = 1.0f;
	endStage.loop = false;
	//path.PushBack({ 0.0f, 0.0f }, 1000, &endStage);
	
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

	//Obtenemos la posicion de la camara
	x = App->render->camera.x + 2;
	y = App->render->camera.y + 2;

	// Reset the score
	score = 0;

	// Reset animations

	startStage.Reset();
	endStage.Reset();

	LOG("Loading UI textures");

	bool ret = true;

	currentAnim = &hp100;

	timerCounter = 360;

	// Starting sprite
	textureP1 = App->textures->Load("Assets/sprites/ui/Player1_Milky.png");
	textureWeapon = App->textures->Load("Assets/sprites/ui/Weapon_Normal.png");
	textureSstage = App->textures->Load("Assets/sprites/ui/start-anim.png");
	textureEstage = App->textures->Load("Assets/sprites/ui/stage-clear.png");
	textureHp = App->textures->Load("Assets/sprites/ui/hp_bar.png");
	timerTextTexture = App->textures->Load("Assets/Fonts/TIME_text.png");

	// Starting font points
	char lookupTable[] = { "0123456789:;(=)? abcdefghijklmnopqrstuvwxyz@!.-." };
	scoreFont = App->fonts->Load("Assets/fonts/orange_font.png", lookupTable, 3);

	// Starting font timer
	char lookupTableTimer[] = { "0123456789" };
	timerFont = App->fonts->Load("Assets/Fonts/green_font.png", lookupTableTimer);


	return ret;
}

Update_Status ModuleUI::Update()
{
	updateHp();
	startStage.Update();
	endStage.Update();

	currentAnim->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleUI::PostUpdate() {

	//Mostramos por pantalla la UI
	App->render->Blit(textureHp, x + 3, y + 40, &currentAnim->GetCurrentFrame());
	App->render->Blit(textureP1, x, y, NULL);
	App->render->Blit(textureWeapon, x + 10, y + 200, NULL);
	App->render->Blit(timerTextTexture, x + 132, y + 2, NULL);

	//Mostramos por pantalla la anim inicial
	App->render->Blit(textureSstage, x, y, &(startStage.GetCurrentFrame()), 1.0f);

	App->render->Blit(textureSstage, x, y, &(endStage.GetCurrentFrame()), 1.0f);

	//Mostramos por pantalla el score
	sprintf_s(scoreText, 10, "%08d", score);
	App->fonts->BlitText(34, 3, scoreFont, scoreText);

	// Actualizamos timer
	// TODO Timer

	// Mostramos por pantalla el timer
	sprintf_s(timerCounterText, 10, "%3d", timerCounter);
	App->fonts->BlitText(137.5, 15, timerFont, timerCounterText);

	return Update_Status::UPDATE_CONTINUE;
}