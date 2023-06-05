#include "SceneLevel1.h"

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
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled) {

}

SceneLevel1::~SceneLevel1()
{}

bool SceneLevel1::Start() {

	LOG("Enabling player");
	App->player->Enable();
	LOG("Enabling enemies");
	App->enemies->Enable();
	LOG("Enabling collisions");
	App->collisions->Enable();
	LOG("Enabling pickups");
	App->pickUps->Enable();
	LOG("Enabling UI");
	App->ui->Enable();
	LOG("Enabling particles");
	App->particles->Enable();


	LOG("Loading background assets");

	bool ret = true;

	wave = 0;

	App->render->leaveZone = false;

	// Load textures and fx
	bgTexture = App->textures->Load("Assets/sprites/background/level1/background_mountain_full.png");
	bgSky = App->textures->Load("Assets/Sprites/background/level1/background_sky.png");
	App->audio->PlayMusic("Assets/Music/03_Shock_Troopers_stage1.ogg", 1.0f);

	// Add colliders
	App->collisions->AddCollider({ 0, 1000, 486, SCREEN_HEIGHT }, Collider::Type::STOP_CAM_ZONE);
	App->collisions->AddCollider({ 838, 1000, SCREEN_WIDTH, SCREEN_HEIGHT }, Collider::Type::STOP_CAM_ZONE_2);
	App->collisions->AddCollider({ 1255, 3, 366, 253 }, Collider::Type::STOP_CAM_ZONE_3);
	App->collisions->AddCollider({ 100, 1078, 1170, 6 }, Collider::Type::PLAYER_WALL);
	App->collisions->AddCollider({ 6, 1105, 100, 6 }, Collider::Type::PLAYER_WALL);
	App->collisions->AddCollider({ 500, 1190, 880, 6 }, Collider::Type::PLAYER_WALL);
	App->collisions->AddCollider({ 487, 1198, 10, 1804 }, Collider::Type::CAMERA_LIMIT);
	App->collisions->AddCollider({ 1619, 0, 10, 330 }, Collider::Type::CAMERA_LIMIT);
	App->collisions->AddCollider({ 1251, 0, 10, 824 }, Collider::Type::CAMERA_LIMIT);

	createMargenes();

	// Add enemies
	//Add landmines
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 109, 2319);// start
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 300, 1547);// miniboss
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 211, 1590);// miniboss
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 138, 1626);// miniboss
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 1567, 863);// pre boss
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 1522, 803);// pre boss
	App->enemies->AddEnemy(Enemy_Type::LANDMINE, 1639, 803);// pre boss

	// Soldier
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1323, 351);// pre 3rd miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1510, 351);// pre 3rd miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1526, 909);// pre 2nd miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1436, 981);// post 1st boss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1516, 1111);// post 1st boss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1393, 1014);// post 1st boss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1278, 1092);// post 1st boss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1287, 1117);// post 1st boss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1066, 1117);// post 1st boss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 266, 1280);// pre 1st boss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 119, 1328);// pre 1st boss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 237, 1449);// post 2nd miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 193, 1488);// post 2nd miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 157, 1534);// post 2nd miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 295, 1781);// pre 2nd miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 223, 2015);// post 1st miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 237, 2028);// post 1st miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 307, 2075);// post 1st miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 171, 2075);// post 1st miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 201, 2271);// pre 1st miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 268, 2271);// pre 1st miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 121, 2327);// pre 1st miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 57, 2361);// pre 1st miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 173, 2618);// spawn
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 158, 2726);// spawn
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 173, 2710);// spawn
	

	// Battleship boss
	App->enemies->AddEnemy(Enemy_Type::FLYING_BATTLESHIP, 140, 965);

	// Tank miniboss
	App->enemies->AddEnemy(Enemy_Type::TANK, 1385, 275);// 3rd
	App->enemies->AddEnemy(Enemy_Type::TANK, 1660, 565);// 2nd
	App->enemies->AddEnemy(Enemy_Type::TANK, 385, 2100);// 1st

	// Tank finalboss
	App->enemies->AddEnemy(Enemy_Type::TANK_BOSS, 1355, 10);
	
	//Add objects
	//Add bridge
	App->enemies->AddEnemy(Enemy_Type::BRIDGE, 65, 2624);// start

	//Add crates
	App->enemies->AddEnemy(Enemy_Type::CRATE, 131, 2267);// start
	App->enemies->AddEnemy(Enemy_Type::CRATE, 314, 1783);// half
	App->enemies->AddEnemy(Enemy_Type::CRATE, 314, 1744);// half
	App->enemies->AddEnemy(Enemy_Type::CRATE, 114, 1111);// miniboss
	App->enemies->AddEnemy(Enemy_Type::CRATE, 246, 1111);// miniboss
	App->enemies->AddEnemy(Enemy_Type::CRATE, 537, 1116);// bridge
	App->enemies->AddEnemy(Enemy_Type::CRATE, 1536, 1038);// post bridge
	App->enemies->AddEnemy(Enemy_Type::CRATE, 1325, 221);// boss
	App->enemies->AddEnemy(Enemy_Type::CRATE, 1441, 221);// boss

	//Add sandbags
	App->enemies->AddEnemy(Enemy_Type::SANDBAG, 83, 2269);// start
	App->enemies->AddEnemy(Enemy_Type::SANDBAG, 228, 1231);//miniboss
	App->enemies->AddEnemy(Enemy_Type::SANDBAG, 83, 1283);//miniboss
	App->enemies->AddEnemy(Enemy_Type::SANDBAG, 1472, 300);//boss
	App->enemies->AddEnemy(Enemy_Type::SANDBAG, 1285, 300);//boss

	//Add barrels
	App->enemies->AddEnemy(Enemy_Type::BARREL, 83, 1928);//near tank
	App->enemies->AddEnemy(Enemy_Type::BARREL, 1243, 940);//post bridge
	App->enemies->AddEnemy(Enemy_Type::BARREL, 1257, 972);//post bridge

	App->enemies->AddEnemy(Enemy_Type::BARRELGROUP, 189, 1976);

	//Add car
	App->enemies->AddEnemy(Enemy_Type::CAR, 1288, 975);

	//this enemy need to be the last one to be added
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 237, 2070);// post 1st miniboss

	App->render->camera.x = 66;
	App->render->camera.y = 2800;

	return ret;
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

void SceneLevel1::moveSky() {

	int cameraX = App->render->camera.x;
	int speedX = 1;
	int maxX = 225;

	cameraX += speedX;

	if (cameraX >= maxX) {
		cameraX = maxX;
	}

	App->render->Blit(bgSky, cameraX, 960, NULL);
}

Update_Status SceneLevel1::Update() {

	
	if (App->render->isInZone3 and musicPlayOnce < 1) {
		musicPlayOnce++;
		App->audio->PlayMusic("Assets/Music/04_Shock_Troopers_boss.ogg", 0.5f);
	}
	// Add falling enemies
	if (App->player->position.y <= 2600 and wave == 0){
		App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 202, 2526, true);// post stone bridge
		App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 91, 2526, true);// post stone bridge
		wave++;
	}
	if (App->player->position.y <= 2560 and wave == 1) {
		App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 211, 2491, true);// post stone bridge
		App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 91, 2491, true);// post stone bridge
		wave++;
	}
	if (App->player->position.y <= 2510 and wave == 2) {
		App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 262, 2421, true);// pre 1st miniboss
		wave++;
	}
	if (App->player->position.y <= 2315 and wave == 3) {
		App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 300, 2250, true);// pre 1st miniboss
		App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 266, 2323, true);// pre 1st miniboss
		App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 233, 2382, true);// pre 1st miniboss
		wave++;
	}
	if (App->player->position.y <= 1750 and wave == 4) {
		App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 319, 1580, true);// pre 2nd miniboss
		App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 319, 1681, true);// pre 2nd miniboss
		wave++;
	}
	if (App->player->position.y <= 1510 and wave == 5) {
		App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 266, 1376, true);// pre 1st boss
		wave++;
	}
	if (App->player->position.y <= 1510 and wave == 6) {
		App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1364, 1080, true);// post 1st boss
		App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1320, 1077, true);// post 1st boss
		wave++;
	}
	if (App->player->position.y <= 970 and wave == 7) {
		App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1603, 846, true);// pre 2nd miniboss
		App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1506, 846, true);// pre 2nd miniboss
		wave++;
	}
	if (App->player->position.y <= 840 and wave == 8) {
		App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1641, 719, true);// pre 2nd miniboss
		App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1514, 719, true);// pre 2nd miniboss
		wave++;
	}
	if (App->player->position.y <= 700 and wave == 9) {
		App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1411, 467, true);// pre 3rd miniboss
		App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1490, 538, true);// pre 3rd miniboss
		wave++;
	}
	if (App->player->position.y <= 560 and wave == 10) {
		App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1493, 444, true);// pre 3rd miniboss
		App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1543, 498, true);// pre 3rd miniboss
		wave++;
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status SceneLevel1::PostUpdate()
{
	moveSky();
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
	LOG("Unloading car texture");
	App->textures->Unload(App->enemies->textureCar);
	LOG("Unloading group barrel texture");
	App->textures->Unload(App->enemies->textureBarrelGroup);
	LOG("Disabiling enemies");
	App->enemies->Disable();

	// Scene Level 1
	LOG("Unloading background texture");
	App->textures->Unload(bgTexture);
	LOG("Unloading sky background texture");
	App->textures->Unload(bgSky);
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
	App->textures->Unload(App->ui->textureGameOver);
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