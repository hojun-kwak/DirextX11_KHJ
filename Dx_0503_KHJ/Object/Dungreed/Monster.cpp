#include "framework.h"
#include "Monster.h"

Monster::Monster()
{
	_texture = make_shared<Texture>(L"Resource/cs.png");
	_texture->GetTransform()->GetPos() = { 800.0f, 700.0f };
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

	ImGui::Text("Monster HP : %d", _monsterHp);

}
