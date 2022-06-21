#include "framework.h"
#include "Player.h"

Player::Player()
{
	_texture = make_shared<Texture>(L"Resource/ezreal.png");
	_texture->GetTransform()->GetPos() = { 200.0f, 200.0f };

	_gunTrans = make_shared<Transform>();
	_gunTrans->SetParent(_texture->GetTransform()->GetMatrix());
	_gunTrans->GetPos() = { 50.0f,50.0f };

	_gun = make_shared<Gun>();
	_gun->SetPlayer(_gunTrans);

	//_bullet = make_shared<Bullet>();
	for (int i = 0; i < _objpooling; i++)
	{
		shared_ptr<Bullet> temp = make_shared<Bullet>();
		temp->_isActive = false;
		_bullets.emplace_back(temp);
	}

}

Player::~Player()
{
}

void Player::Update()
{
	Move();
	Aimming();
	Fire();

	if (KEY_PRESS(VK_ADD))
	{
		Reset();
	}

	_texture->Update();

	_gunTrans->UpdateWorldBuffer();

	_gun->Update();
	//_bullet->Update();
	for (auto& bullet : _bullets)
	{
		bullet->Update();
	}
}

void Player::Render()
{
	_texture->Render();

	_gun->Render();
	//_bullet->Render();
	for (auto& bullet : _bullets)
		bullet->Render();
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

void Player::Fire()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		Vector2 v = MOUSE_POS - _gunTrans->GetWorldPos();
		v.Normallize();
		//_bullet->SetDirection(v);
		/*_bullet->SetPosition(_gunTrans->GetWorldPos());
		_bullet->_isActive = true;*/
		for (auto& bullet : _bullets)
		{
			if (bullet->_isActive == false)
			{
				bullet->SetDirection(v);
				bullet->SetPosition(_gunTrans->GetWorldPos());
				bullet->_isActive = true;
				bullet->SetAngle(_gunTrans->GetAnlgle());
				break;
			}
		}
	}
}

void Player::Reset()
{
	for (auto& bullet : _bullets)
	{
		bullet->_isActive = false;
	}
}
