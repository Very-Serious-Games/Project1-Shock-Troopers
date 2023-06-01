#include "SceneLevel1.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModulePickUp.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleUI.h"
 
SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{}

SceneLevel1::~SceneLevel1()
{}

bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	// Load textures and fx
	bgTexture = App->textures->Load("Assets/Sprites/background/level1/background_mountain_full.png");
	App->audio->PlayMusic("Assets/Music/mountain1.ogg", 1.0f);
	App->ui->Enable();

	// Add colliders
	App->collisions->AddCollider({ 0, 1000, 486, SCREEN_HEIGHT }, Collider::Type::STOP_CAM_ZONE);
	App->collisions->AddCollider({ 838, 1000, SCREEN_WIDTH, SCREEN_HEIGHT }, Collider::Type::STOP_CAM_ZONE_2);
	App->collisions->AddCollider({ 1255, 3, 366, 253 }, Collider::Type::STOP_CAM_ZONE);


	createMargenes();

	// Add enemies
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 128, 2900);
								
	App->enemies->AddEnemy(Enemy_Type::FLYING_BATTLESHIP, 183, 20); // (493 / 2) - (128 / 2) = 183

	App->enemies->AddEnemy(Enemy_Type::TANK_BOSS, 1355, 70);

	App->enemies->AddEnemy(Enemy_Type::TANK, 128, 2300);
	
	//Add objects
	//App->enemies->AddEnemy(Enemy_Type::BRIDGE, 125, 1822);
	App->enemies->AddEnemy(Enemy_Type::CRATE, 133, 1182);
	App->enemies->AddEnemy(Enemy_Type::CRATE, 333, 713);
	App->enemies->AddEnemy(Enemy_Type::CRATE, 333, 668);
	
	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();
	App->pickUps->Enable();

	return ret;
}

Update_Status SceneLevel1::Update()
{
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status SceneLevel1::PostUpdate()
{
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();
	App->sceneLevel_1->Disable();
	App->pickUps->Disable();
	App->collisions->Disable();
	App->ui->Disable();

	// TODO remove all memory leaks

	return true;
}

void SceneLevel1::createMargenes() {
	ifstream file("Assets/Sprites/colisionesMapa.csv");
	string line;

	while (getline(file, line)) {
		int values[4];
		int pos = 0;
		string value;

		for (int i = 0; i < line.size(); i++) {
			if (line[i] == ';') {
				values[pos] = stoi(value);
				pos++;
				value = "";
			}
			else {
				value += line[i];
			}
		}

		values[pos] = stoi(value);
		App->collisions->AddCollider({ values[0], values[1], values[2], values[3] }, Collider::Type::WALL);

		cout << endl;
	}

	file.close();
}