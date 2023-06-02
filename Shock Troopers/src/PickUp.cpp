#include "PickUp.h"
#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePickUp.h"

PickUp::PickUp(PickUpType type1, int x, int y) : position(x, y)
{
	spawnPos = position;
	type = type1;
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
	LOG("Drawing Pickup");
	App->render->Blit(texture, position.x, position.y, &currentAnim->GetCurrentFrame());
}

void PickUp::DrawColider()
{
	LOG("Drawing Colider");
       collider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::PICKUP, App->pickUps);
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