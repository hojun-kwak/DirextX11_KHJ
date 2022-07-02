#include "framework.h"
#include "Bullet.h"

Bullet::Bullet()
{
	_quad = make_shared<Quad>(L"Resource/mysticShot.png");
	_quad->GetTransform()->GetScale() = { 0.3f, 0.3f };

	_collider = make_shared<CircleCollider>(30);
	_collider->SetParent(_quad->GetTransform());
	//_collider->GetLocalPosition()._x += 20;

}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (_isActive == false)
		return;

	_quad->GetTransform()->GetPos() += _direction * 300.0f * DELTA_TIME;

	_quad->Update();
	
	// 3초가 지나면 사라짐
	_runTime += DELTA_TIME;

	if (_runTime > _destroyTime)
	{
		_isActive = false;
		_runTime = 0;
	}

	_collider->Update();
}

void Bullet::Render()
{
	if (_isActive == false)
		return;

	_quad->Render();
	_collider->Render();
}

void Bullet::SetDirection(Vector2 dir)
{
	_direction = dir;
	_quad->GetTransform()->GetAngle() = dir.Angle();
}
