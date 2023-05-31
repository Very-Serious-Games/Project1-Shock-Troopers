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
#include "ModuleUI.h"
#include "ModulePlayer.h"

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

	// Add colliders
//	App->collisions->AddCollider({ 0, 1909, 493, 16 }, Collider::Type::WALL);
//	App->collisions->AddCollider({ 0, 0, 1, 1909 }, Collider::Type::WALL);
//	App->collisions->AddCollider({ 490, 0, 1, 1909 }, Collider::Type::WALL);

	createMargenes();

	// Add enemies
	//App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 100, 100);
								
	App->enemies->AddEnemy(Enemy_Type::FLYING_BATTLESHIP, 183, 20); // (493 / 2) - (128 / 2) = 183
	
	//TODO spawnear todas las minas
	//Add landmines
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 87, 2330);
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 146, 1631);
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 217, 1597);
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 290, 1563);
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 1564, 848);// no spawnea
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 1513, 808);// no spawnea
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 1635, 808);// no spawnea

	//TODO spawnear todos los objetos
	//Add objects
	App->enemies->AddEnemy(Enemy_Type::BRIDGE, 65, 2624);

	App->enemies->AddEnemy(Enemy_Type::CRATE, 120, 2264);
	App->enemies->AddEnemy(Enemy_Type::CRATE, 330, 1747);
	App->enemies->AddEnemy(Enemy_Type::CRATE, 330, 1790);
	App->enemies->AddEnemy(Enemy_Type::CRATE, 628, 1122);// no spawnea
	App->enemies->AddEnemy(Enemy_Type::CRATE, 1534, 1025);// no spawnea
	App->enemies->AddEnemy(Enemy_Type::CRATE, 1436, 211);// no spawnea
	App->enemies->AddEnemy(Enemy_Type::CRATE, 1338, 211);// no spawnea


	App->render->camera.x = 220;
	App->render->camera.y = 2800;

	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();
	App->pickUps->Enable();
	App->ui->Enable();

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