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
	path.PushBack({ 0.0f, 0.0f }, 1000, &startStage);

	//stage clear anim below
	
	////iterate the start stage animation, that has 6 frames per row and 14 rows
	/*for (int row = 0; row < 14; row++) {
		for (int col = 0; col < 6; col++) {
			int frameX = col * SCREEN_WIDTH;
			int frameY = row * SCREEN_HEIGHT;
			endStage.PushBack({ frameX, frameY, SCREEN_WIDTH, SCREEN_HEIGHT });
		}
	}

	endStage.PushBack({ 0, 0, 0, 0 });
	endStage.speed = 1.0f;
	endStage.loop = false;
	path.PushBack({ 0.0f, 0.0f }, 1000, &endStage);*/
	
}

ModuleUI::~ModuleUI()
{
}

void ModuleUI::updateHp() {
	LOG("Updating HP Scorebar");
	switch (App->player->hp) {
	case 100:
		textureHp = App->textures->Load("Assets/Sprites/ui/HpBar_100.png");
		break;
	case 90:
		textureHp = App->textures->Load("Assets/Sprites/ui/HpBar_90.png");
		break;
	case 80:
		textureHp = App->textures->Load("Assets/Sprites/ui/HpBar_80.png");
		break;
	case 70:
		textureHp = App->textures->Load("Assets/Sprites/ui/HpBar_70.png");
		break;
	case 60:
		textureHp = App->textures->Load("Assets/Sprites/ui/HpBar_60.png");
		break;
	case 50:
		textureHp = App->textures->Load("Assets/Sprites/ui/HpBar_50.png");
		break;
	case 40:
		textureHp = App->textures->Load("Assets/Sprites/ui/HpBar_40.png");
		break;
	case 30:
		textureHp = App->textures->Load("Assets/Sprites/ui/HpBar_30.png");
		break;
	case 20:
		textureHp = App->textures->Load("Assets/Sprites/ui/HpBar_20.png");
		break;
	case 10:
		textureHp = App->textures->Load("Assets/Sprites/ui/HpBar_10.png");
		break;
	case 0:
		textureHp = App->textures->Load("Assets/Sprites/ui/HpBar_00.png");
		break;
	default:
		textureHp = App->textures->Load("Assets/Sprites/ui/HpBar_00.png");
		break;
	}
}

void ModuleUI::updateScore(int points)
{
	LOG("Updating Score");
	score += points;
}

bool ModuleUI::Start()
{
	LOG("Loading UI textures");

	bool ret = true;

	// Starting sprite
	textureP1 = App->textures->Load("Assets/sprites/ui/Player1_Milky.png");
	textureWeapon = App->textures->Load("Assets/sprites/ui/Weapon_Normal.png");
	textureSstage = App->textures->Load("Assets/sprites/ui/start-anim.png");
	textureEstage = App->textures->Load("Assets/sprites/ui/stage-clear.png");

	// Starting fonts
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = App->fonts->Load("Assets/fonts/rtype_font3.png", lookupTable, 2);


	return ret;
}

Update_Status ModuleUI::Update()
{
	updateHp();
	startStage.Update();
	/*endStage.Update();*/
	path.Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleUI::PostUpdate()
{
	int x, y;

	//Obtenemos la posicion de la camara
	x = App->render->camera.x + 2;
	y = App->render->camera.y + 2;

	//Mostramos por pantalla la UI
	App->render->Blit(textureHp, x + 3, y + 40, NULL);
	App->render->Blit(textureP1, x, y, NULL);
	App->render->Blit(textureWeapon, x + 10, y + 200, NULL);

	//Mostramos por pantalla la anim inicial
	App->render->Blit(textureSstage, x, y, &(path.GetCurrentAnimation()->GetCurrentFrame()), 1.0f);
	/*App->render->Blit(textureEstage, x, y, &(path.GetCurrentAnimation()->GetCurrentFrame()), 1.0f);*/

	//Mostramos por pantalla el score
	App->fonts->BlitText(20, 3, scoreFont, scoreText);
	sprintf_s(scoreText, 10, "%7d", score);

	return Update_Status::UPDATE_CONTINUE;
}