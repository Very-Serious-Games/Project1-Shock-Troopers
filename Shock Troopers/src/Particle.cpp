#include "Particle.h"

#include "Collider.h"

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();

}

Particle::Particle(const Particle& p) : anim(p.anim), position(p.position), speed(p.speed),
frameCount(p.frameCount), lifetime(p.lifetime)
{
	// Laser particle
	bullet_U.PushBack({ 1, 1, 7, 13 });
	bullet_U.PushBack({ 9, 1, 7, 13 });


	bullet_D.PushBack({ 1, 15, 7, 13 });
	bullet_D.PushBack({ 9, 15, 7, 13 });


	bullet_R.PushBack({ 1, 30, 13, 7 });
	bullet_R.PushBack({ 15, 30, 13, 7 });


	bullet_L.PushBack({ 1, 38, 13, 7 });
	bullet_L.PushBack({ 15, 38, 13, 7 });


	bullet_U_R.PushBack({ 1, 46, 13, 13 });
	bullet_U_R.PushBack({ 15, 46, 13, 13 });


	bullet_U_L.PushBack({ 1, 60, 13, 13 });
	bullet_U_L.PushBack({ 15, 60, 13, 13 });


	bullet_D_R.PushBack({ 1, 74, 13, 13 });
	bullet_D_R.PushBack({ 15, 74, 13, 13 });


	bullet_D_L.PushBack({ 1, 89, 13, 13 });
	bullet_D_L.PushBack({ 15, 89, 13, 13 });
}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

bool Particle::Update()
{
	bool ret = true;
	frameCount++;

	// The particle is set to 'alive' when the delay has been reached
	if (!isAlive && frameCount >= 0)
		isAlive = true;

	if (isAlive)
	{
		anim.Update();

		// If the particle has a specific lifetime, check when it has to be destroyed
		if (lifetime > 0)
		{
			if (frameCount >= lifetime)
				ret = false;
		}
		// Otherwise the particle is destroyed when the animation is finished
		else if (anim.HasFinished())
			ret = false;

		// Update the position in the screen
		if (granada) {
			position.x += speed.x * 2;
			int test = parabole(inicio, speed.x);
			//TODO añadir direccion
			position.y += test;
		}
		else {
			position.x += speed.x;
			position.y += speed.y;
		}


 		if (collider != nullptr)
			collider->SetPos(position.x, position.y);
	}

	return ret;
}

int Particle::parabole(int x, int direction_x) {
	const float a = 1.0f / 32.0f;
	const int b = 3;
	const int c = 1;
	int y = -a * (x - c) * (x - c) + b;
	if (direction_x == 1) {
		y = -y;
	}
	inicio++;
	return y;
}

void Particle::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

void Particle::setDirection(int direction) {
	switch (direction)
	{
	case 1: //UR
		direccion = 1;
		speed.x = 5;
		speed.y = -5;
		currentAnimation = &bullet_U_R;
		break;
	case 2: //UL
		direccion = 2;
		speed.x = -5;
		speed.y = -5;
		currentAnimation = &bullet_U_L;
		break;
	case 3: //DR
		direccion = 3;
		speed.x = 5;
		speed.y = 5;
		currentAnimation = &bullet_D_R;
		break;
	case 4: //DL
		direccion = 4;
		speed.x = -5;
		speed.y = 5;
		currentAnimation = &bullet_D_L;
		break;
	case 5: //R
		direccion = 5;
		speed.x = 5;
		speed.y = 0;
		currentAnimation = &bullet_R;
		break;
	case 6: //L
		direccion = 6;
		speed.x = -5;
		speed.y = 0;
		currentAnimation = &bullet_L;
		break;
	case 7: //D
		direccion = 7;
		speed.x = 0;
		speed.y = 5;
		currentAnimation = &bullet_D;
		break;
	case 8: //U
		direccion = 8;
		speed.x = 0;
		speed.y = -5;
		currentAnimation = &bullet_U;
		break;
	default:
		direccion = 5;
		speed.x = 5;
		speed.y = 0;
		currentAnimation = &bullet_R;

		break;
	}
}