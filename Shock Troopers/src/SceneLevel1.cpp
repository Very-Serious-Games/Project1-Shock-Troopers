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
#include "ModuleFonts.h"
#include "ModuleParticles.h"
 
SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled) {

}

SceneLevel1::~SceneLevel1()
{}

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

bool SceneLevel1::Start() {

	LOG("Enabling modules");
	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();
	App->pickUps->Enable();
	App->ui->Enable();
	App->particles->Enable();

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
	App->collisions->AddCollider({ 500, 1085, 740, 6 }, Collider::Type::PLAYER_WALL);
	App->collisions->AddCollider({ 500, 1190, 880, 6 }, Collider::Type::PLAYER_WALL);


	App->render->camera.x = 66;
	App->render->camera.y = 2800;

	createMargenes();

	// Add enemies

	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 128, 2900);
	App->enemies->AddEnemy(Enemy_Type::FLYING_BATTLESHIP, 183, 20);
	App->enemies->AddEnemy(Enemy_Type::TANK_BOSS, 1355, 70);
	App->enemies->AddEnemy(Enemy_Type::TANK, 385, 2100);
	
	//TODO spawnear todas las minas
	//Add landmines
	
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 109, 2319);// start
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 300, 1547);// miniboss
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 211, 1590);// miniboss
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 138, 1626);// miniboss
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 1567, 863);// pre boss
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 1522, 803);// pre boss
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 1639, 803);// pre boss

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

bool SceneLevel1::CleanUp() {

	// Player
	LOG("Unloading player texture");
	App->textures->Unload(App->player->texture);
	LOG("Disabiling player");
	App->player->Disable();

	// Enemies
	LOG("Unloading barrel texture");
	App->textures->Unload(App->enemies->textureBarrel);
	LOG("Unloading bridge texture");
	App->textures->Unload(App->enemies->textureBridge);
	LOG("Unloading crate texture");
	App->textures->Unload(App->enemies->textureCrate);
	LOG("Unloading flying battleship texture");
	App->textures->Unload(App->enemies->textureFlyingBattleship);
	LOG("Unloading infantry soldier texture");
	App->textures->Unload(App->enemies->textureInfantrySoldier);
	LOG("Unloading landmines texture");
	App->textures->Unload(App->enemies->textureLandmines);
	LOG("Unloading sandbags texture");
	App->textures->Unload(App->enemies->textureSandbags);
	LOG("Unloading tank texture");
	App->textures->Unload(App->enemies->textureTank);
	LOG("Unloading tank boss texture");
	App->textures->Unload(App->enemies->textureTankBoss);

	LOG("Disabiling enemies");
	App->enemies->Disable();
	// Scene Level 1
	LOG("Unloading background texture");
	App->textures->Unload(bgTexture);
	LOG("Disabiling sceneLevel_1");
	App->sceneLevel_1->Disable();

	// PickUps
	LOG("Unloading pickUps texture");
	App->textures->Unload(App->pickUps->texture);
	LOG("Disabiling pickUps");
	App->pickUps->Disable();

	// Collisions
	LOG("Disabiling collisions");
	App->collisions->Disable();

	// UI
	App->textures->Unload(App->ui->textureEstage);
	App->textures->Unload(App->ui->textureHp);
	App->textures->Unload(App->ui->textureP1);
	App->textures->Unload(App->ui->textureSstage);
	App->textures->Unload(App->ui->textureWeapon);
	LOG("Disabiling ui");
	App->ui->Disable();

	// Fonts
	App->fonts->UnLoad(App->ui->scoreFont);

	// Particles
	LOG("Unloading particles texture");
	App->textures->Unload(App->particles->texture);
	LOG("Disabiling particles");
	App->particles->Disable();

	return true;
}