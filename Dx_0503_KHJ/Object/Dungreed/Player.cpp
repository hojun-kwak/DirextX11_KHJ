#include "framework.h"
#include "Player.h"

Player::Player()
{
	_texture = make_shared<Texture>(L"Resource/ezreal.png");
	_texture->GetTransform()->GetPos() = { 200.0f, 200.0f };

	_gunTrans = make_shared<Transform>();
	_gunTrans->SetParent(_texture->GetTransform()->GetMatrix());
	_gunTrans->GetPos() = { 50.0f,50.0f };
	_gunTrans->GetScale() = { 0.8f,0.8f };

	_gun = make_shared<Gun>();
	_gun->SetPlayer(_gunTrans);

}

Player::~Player()
{
}

void Player::Update()
{
	Move();
	Aimming();

	_texture->Update();

	_gunTrans->UpdateWorldBuffer();

	_gun->Update();
}

void Player::Render()
{
	_texture->Render();

	_gun->Render();
}

void Player::Move()
{
	if (KEY_PRESS('W'))
		_texture->GetTransform()->GetPos()._y += 100.0f * DELTA_TIME;
	if(KEY_PRESS('A'))
		_texture->GetTransform()->GetPos()._x -= 100.0f * DELTA_TIME;
	if(KEY_PRESS('S'))
		_texture->GetTransform()->GetPos()._y -= 100.0f * DELTA_TIME;
	if(KEY_PRESS('D'))
		_texture->GetTransform()->GetPos()._x += 100.0f * DELTA_TIME;
}

void Player::Aimming()
{
	Vector2 v = MOUSE_POS - _gunTrans->GetWorldPos();
	float angle = v.Angle();
	_gunTrans->GetAnlgle() = angle;
}
