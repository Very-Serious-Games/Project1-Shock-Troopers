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
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 109, 2319);// start
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 300, 1547);// miniboss
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 211, 1590);// miniboss
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 138, 1626);// miniboss
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 1567, 863);// pre boss
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 1522, 803);// pre boss
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 1639, 803);// pre boss

	//TODO spawnear todos los objetos
	//Add objects
	App->enemies->AddEnemy(Enemy_Type::BRIDGE, 65, 2624);// start

	App->enemies->AddEnemy(Enemy_Type::CRATE, 131, 2267);// start
	App->enemies->AddEnemy(Enemy_Type::CRATE, 314, 1783);// half
	App->enemies->AddEnemy(Enemy_Type::CRATE, 314, 1744);// half
	App->enemies->AddEnemy(Enemy_Type::CRATE, 114, 1111);// miniboss
	App->enemies->AddEnemy(Enemy_Type::CRATE, 246, 1111);// miniboss
	App->enemies->AddEnemy(Enemy_Type::CRATE, 628, 1116);// bridge
	App->enemies->AddEnemy(Enemy_Type::CRATE, 1536, 1038);// post bridge
	App->enemies->AddEnemy(Enemy_Type::CRATE, 1325, 191);// boss
	App->enemies->AddEnemy(Enemy_Type::CRATE, 1441, 191);// boss

	App->enemies->AddEnemy(Enemy_Type::SANDBAG, 83, 2254);// start
	App->enemies->AddEnemy(Enemy_Type::SANDBAG, 228, 1231);//miniboss
	App->enemies->AddEnemy(Enemy_Type::SANDBAG, 83, 1283);//miniboss
	App->enemies->AddEnemy(Enemy_Type::SANDBAG, 1472, 289);//boss
	App->enemies->AddEnemy(Enemy_Type::SANDBAG, 1285, 289);//boss

	App->enemies->AddEnemy(Enemy_Type::BARREL, 83, 1928);//near tank
	App->enemies->AddEnemy(Enemy_Type::BARREL, 1257, 972);//post bridge
	App->enemies->AddEnemy(Enemy_Type::BARREL, 1243, 940);//post bridge

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