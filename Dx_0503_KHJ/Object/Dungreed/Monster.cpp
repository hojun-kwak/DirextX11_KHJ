#include "framework.h"
#include "Monster.h"

Monster::Monster()
{
	_texture = make_shared<Texture>(L"Resource/cs.png");
	_texture->GetTransform()->GetPos() = { 300.0f, 600.0f };
	_texture->GetTransform()->GetScale() = { 0.5f,0.5f };

	_collider = make_shared<RectCollider>(Vector2(60.0f, 60.0f));
	_collider->SetParent(_texture->GetTransform());
}

Monster::~Monster()
{
}

void Monster::Update()
{
	if (!_monster_isActive)
		return;

	_texture->Update();
	_collider->Update();
}

void Monster::Render()
{
	if (!_monster_isActive)
		return;

	_texture->Render();
	_collider->Render();

	/*if (_monsterHp <= 0)
	{
		ImGui::Text("Monster HP : %d", 0);
	}
	else
	{
		ImGui::Text("Monster HP : %d", (UINT)_monsterHp);
	}*/
	ImGui::Text("Monster HP : %d", (UINT)_monsterHp);

}

void Monster::MonsAttacked(shared_ptr<class Bullet> bullet)
{
	if (_collider->IsCollision(bullet->GetCollider(), false) && _monster_isActive && bullet->_isActive)
	{
		/*if (_monsterHp == 0)
		{
			_monster_isActive = false;
		}*/
		bullet->_isActive = false;
		_monster_isActive = false;
		_monsterHp--;
		_collider->SetRed();
		
	}
	else
		_collider->SetGreen();
}
