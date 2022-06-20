#include "framework.h"
#include "Bullet.h"

Bullet::Bullet()
{
	_texture = make_shared<Texture>(L"Resource/mysticShot.png");
	_texture->GetTransform()->GetScale() = { 0.3f, 0.3f };
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (!_isActive)
		return;

	_texture->GetTransform()->GetPos() += _direction * 300.0f * DELTA_TIME;

	_texture->Update();
}

void Bullet::Render()
{
	if (!_isActive)
		return;

	_texture->Render();
}

void Bullet::SetDirection(Vector2 dir)
{
	_direction = dir;
}
