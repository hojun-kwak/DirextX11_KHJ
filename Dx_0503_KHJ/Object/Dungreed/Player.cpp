#include "framework.h"
#include "Player.h"

Player::Player()
{
	_texture = make_shared<Texture>(L"Resource/ezreal.png");
	_texture->GetTransform()->GetPos() = { 200.0f, 200.0f };

	_gunTrans = make_shared<Transform>();
	_gunTrans->SetParent(_texture->GetTransform());
	_gunTrans->GetPos() = { 50.0f,50.0f };

	_gun = make_shared<Gun>();
	_gun->SetPlayer(_gunTrans);

	_bullet = make_shared<Bullet>();

	/*_bullets.reserve(_objpooling);
	for (int i = 0; i < _objpooling; i++)
	{
		shared_ptr<Bullet> temp = make_shared<Bullet>();
		temp->_isActive = false;
		_bullets.emplace_back(temp);
	}*/

	_collider = make_shared<RectCollider>(Vector2(100, 100));
	_collider->SetParent(_texture->GetTransform());

	_mons = make_shared<class Monster>();

}

Player::~Player()
{
}

void Player::Update()
{
	Move();
	Aimming();
	Fire();
	Attack();

	bool check = _bullet->GetCollider()->IsCollision(_mons->GetCollider());

	if (_bullet->GetCollider()->IsCollision(_mons->GetCollider(), false))
	{
		_mons->GetCollider()->SetRed();
		int a = _mons->_monsterHp;
		_mons->_monsterHp--;

		//_mons->GetRed();
		//_bullet->_isActive	= false;
	}
	else
		_mons->GetCollider()->SetGreen();

	


	if (KEY_PRESS(VK_ADD))
	{
		Reset();
	}

	_texture->Update();

	_gunTrans->UpdateWorldBuffer();

	_gun->Update();
	_bullet->Update();
	/*for (auto& bullet : _bullets)
	{
		bullet->Update();
	}*/
	_collider->Update();
	_mons->Update();
}

void Player::Render()
{
	_texture->Render();

	_gun->Render();
	_bullet->Render();
	/*for (auto& bullet : _bullets)
		bullet->Render();*/

	_collider->Render();
	_mons->Render();
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
	_gunTrans->GetAngle() = angle;

}

void Player::Fire()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		Vector2 v = MOUSE_POS - _gunTrans->GetWorldPos();
		v.Normallize();
		_bullet->SetDirection(v);
		_bullet->SetPosition(_gunTrans->GetWorldPos());
		_bullet->_isActive = true;

		//for (auto& bullet : _bullets)
		//{
		//	if (bullet->_isActive == false)
		//	{
		//		bullet->SetDirection(v);
		//		bullet->SetPosition(_gunTrans->GetWorldPos());
		//		bullet->_isActive = true;
		//		//bullet->SetAngle(_gunTrans->GetAngle());
		//		break;
		//	}
		//}
	}

}

void Player::Attack()
{
	/*for (auto& bullet : _bullets)
	{
		bullet
	}*/
	//bool check = _bullet->GetCollider()->IsCollision(_mons->GetCollider(), false);

	
}

void Player::Reset()
{
	/*for (auto& bullet : _bullets)
	{
		bullet->_isActive = false;
	}*/
	_bullet->_isActive = false;
}
