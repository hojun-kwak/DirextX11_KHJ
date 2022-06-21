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
	if (_isActive == false)
		return;

	_texture->GetTransform()->GetPos() += _direction * 300.0f * DELTA_TIME;

	_texture->Update();
	
	// 3초가 지나면 사라짐
	_runTime += DELTA_TIME;

	if (_runTime > _destroyTime)
	{
		_isActive = false;
		_runTime = 0;
	}
}

void Bullet::Render()
{
	if (_isActive == false)
		return;

	_texture->Render();
}

void Bullet::SetDirection(Vector2 dir)
{
	_direction = dir;
	_texture->GetTransform()->GetAnlgle() = dir.Angle();
}
