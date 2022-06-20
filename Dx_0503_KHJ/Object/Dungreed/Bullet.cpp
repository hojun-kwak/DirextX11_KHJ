#include "framework.h"
#include "Bullet.h"

Bullet::Bullet()
{
	_texture = make_shared<Texture>(L"Resource/mysticShot.png");
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (!_isActive)
		return;

	_texture->Update();
}

void Bullet::Render()
{
	if (!_isActive)
		return;

	_texture->Render();
}
