#include "PickUp.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

PickUp::PickUp(int x, int y) : position(x, y)
{
	spawnPos = position;
}

PickUp::~PickUp()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* PickUp::GetCollider() const
{
	return collider;
}

void PickUp::Update()
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void PickUp::Draw()
{
	App->render->Blit(texture, position.x, position.y, NULL);
}

void PickUp::OnCollision(Collider* collider)
{
	SetToDelete();
}

void PickUp::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}