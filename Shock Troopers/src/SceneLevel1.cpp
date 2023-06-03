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
	App->collisions->AddCollider({ 500, 1085, 740, 6 }, Collider::Type::PLAYER_WALL);
	App->collisions->AddCollider({ 500, 1190, 880, 6 }, Collider::Type::PLAYER_WALL);


	App->render->camera.x = 66;
	App->render->camera.y = 2800;

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
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1493, 444);// pre 3rd miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1543, 498);// pre 3rd miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1411, 467);// pre 3rd miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1490, 538);// pre 3rd miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1641, 719);// pre 2nd miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1514, 719);// pre 2nd miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1603, 846);// pre 2nd miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1506, 846);// pre 2nd miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1526, 909);// pre 2nd miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1436, 981);// post 1st boss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1516, 1111);// post 1st boss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1393, 1014);// post 1st boss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1364, 1080);// post 1st boss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1320, 1077);// post 1st boss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1278, 1092);// post 1st boss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1287, 1117);// post 1st boss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 1066, 1117);// post 1st boss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 266, 1280);// pre 1st boss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 119, 1328);// pre 1st boss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 266, 1376);// pre 1st boss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 237, 1449);// post 2nd miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 193, 1488);// post 2nd miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 157, 1534);// post 2nd miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 319, 1580);// pre 2nd miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 319, 1681);// pre 2nd miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 295, 1781);// pre 2nd miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 223, 2015);// post 1st miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 237, 2028);// post 1st miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 307, 2075);// post 1st miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 171, 2075);// post 1st miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 300, 2250);// pre 1st miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 266, 2323);// pre 1st miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 233, 2382);// pre 1st miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 333, 2232);// pre 1st miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 201, 2271);// pre 1st miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 268, 2271);// pre 1st miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 121, 2327);// pre 1st miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 57, 2361);// pre 1st miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 262, 2421);// pre 1st miniboss
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 211, 2491);// post stone bridge
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 91, 2491);// post stone bridge
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 202, 2526);// post stone bridge
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 91, 2526);// post stone bridge
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 173, 2618);// spawn
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 158, 2726);// spawn
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 173, 2710);// spawn
	

	// Battleship boss
	App->enemies->AddEnemy(Enemy_Type::FLYING_BATTLESHIP, 183, 20);

	// Tank miniboss
	App->enemies->AddEnemy(Enemy_Type::TANK, 1385, 275);// 3rd
	App->enemies->AddEnemy(Enemy_Type::TANK, 1660, 565);// 2nd
	App->enemies->AddEnemy(Enemy_Type::TANK, 385, 2100);// 1st

	// Tank finalboss
	App->enemies->AddEnemy(Enemy_Type::TANK_BOSS, 1355, 70);
	
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
	App->enemies->AddEnemy(Enemy_Type::BARREL, 1257, 972);//post bridge
	App->enemies->AddEnemy(Enemy_Type::BARREL, 1243, 940);//post bridge

	App->enemies->AddEnemy(Enemy_Type::BARRELGROUP, 189, 1976);

	//Add car
	App->enemies->AddEnemy(Enemy_Type::CAR, 1288, 975);

	//this enemy need to be the last one to be added
	App->enemies->AddEnemy(Enemy_Type::INFANTRY_SOLDIER, 237, 2070);// post 1st miniboss

	App->render->camera.x = 220;
	App->render->camera.y = 2800;

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