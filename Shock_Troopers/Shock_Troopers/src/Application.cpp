#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleScene.h"
#include "ModuleParticles.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"

Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen
	modules[0] = window = new ModuleWindow();
	modules[1] = input = new ModuleInput();
	modules[2] = textures = new ModuleTextures();
	modules[3] = audio = new ModuleAudio();

	modules[4] = scene = new ModuleScene();
	modules[5] = player = new ModulePlayer();

	modules[6] = particles = new ModuleParticles();
	modules[7] = collisions = new ModuleCollisions();

	modules[8] = render = new ModuleRender();
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		//Important: when deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	//By now we will consider that all modules are always active
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Start();

	return ret;
}

update_status Application::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->PreUpdate();

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->Update();

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->PostUpdate();

	return ret;
}
 
bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->CleanUp();

	return ret;
}
