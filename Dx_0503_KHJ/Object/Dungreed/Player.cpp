#include "framework.h"
#include "Player.h"

Player::Player()
{
	_quad = make_shared<Quad>(L"Resource/ezreal.png");
	_quad->GetTransform()->GetScale() = { 0.5f,0.5f };
	_quad->GetTransform()->GetPos() = { 200.0f, 200.0f };

	_gunTrans = make_shared<Transform>();
	_gunTrans->SetParent(_quad->GetTransform());
	_gunTrans->GetPos() = { 50.0f,50.0f };

	_gun = make_shared<Gun>();
	_gun->SetPlayer(_gunTrans);

	//_bullet = make_shared<Bullet>();

	_bullets.reserve(_objpooling);
	for (int i = 0; i < _objpooling; i++)
	{
		shared_ptr<Bullet> temp = make_shared<Bullet>();
		temp->_isActive = false;
		_bullets.emplace_back(temp);
	}

	_collider = make_shared<RectCollider>(Vector2(100, 100));
	_collider->SetParent(_quad->GetTransform());

}

Player::~Player()
{
}

void Player::Update()
{
	Move();
	Aimming();
	Fire();

	//if (_bullet->GetCollider()->IsCollision(_mons->GetCollider(), false))
	//{
	//	_mons->GetCollider()->SetRed();
	//	/*int a = _mons->_monsterHp;
	//	_mons->_monsterHp--;*/
	//	_mons->_monster_isActive = false;
	//	//_mons->GetRed();
	//	_bullet->_isActive	= false;
	//}
	//else
	//	_mons->GetCollider()->SetGreen();

	if (KEY_PRESS(VK_ADD))
	{
		Reset();
	}

	_quad->Update();

	_gunTrans->UpdateWorldBuffer();

	_gun->Update();
	//_bullet->Update();
	for (auto& bullet : _bullets)
		bullet->Update();

	_collider->Update();
}

void Player::Render()
{
	_quad->Render();

	_gun->Render();
	//_bullet->Render();
	for (auto& bullet : _bullets)
		bullet->Render();

	_collider->Render();
}

void Player::Move()
{
	if (KEY_PRESS('W'))
		_quad->GetTransform()->GetPos().y += 100.0f * DELTA_TIME;
	if(KEY_PRESS('A'))
		_quad->GetTransform()->GetPos().x -= 100.0f * DELTA_TIME;
	if(KEY_PRESS('S'))
		_quad->GetTransform()->GetPos().y -= 100.0f * DELTA_TIME;
	if(KEY_PRESS('D'))
		_quad->GetTransform()->GetPos().x += 100.0f * DELTA_TIME;
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
		/*_bullet->SetDirection(v);
		_bullet->SetPosition(_gunTrans->GetWorldPos());
		_bullet->_isActive = true;*/

		for (auto& bullet : _bullets)
		{
			if (bullet->_isActive == false)
			{
				bullet->SetDirection(v);
				bullet->SetPosition(_gunTrans->GetWorldPos());
				bullet->_isActive = true;
				//bullet->SetAngle(_gunTrans->GetAngle());
				break;
			}
		}
	}

}

void Player::MonsAttack(vector<shared_ptr<class Monster>> monster)
{
	for (auto & bullet : _bullets)
	{
		if (bullet->_isActive == false)
		{
			continue;
		}
		for (auto& mons : _mons)
		{
			if(mons->_monster_isActive == true)
				mons->MonsAttacked(bullet);
		}
	}
}

void Player::Reset()
{
	for (auto& bullet : _bullets)
	{
		bullet->_isActive = false;
	}
	//_bullet->_isActive = false;
}
