#include "framework.h"
#include "Rope.h"

Rope::Rope()
{
	_quad = make_shared<Quad>(L"Resource/Maple/Rope.png");
	_col = make_shared<RectCollider>(_quad->GetHalfSize());
	_col->SetParent(_quad->GetTransform());
	Vector2 ropeColSize = { _quad->GetHalfSize().x, _quad->GetHalfSize().y + 20.0f };
	_ropeCol = make_shared<RectCollider>(ropeColSize);
	_ropeCol->SetParent(_quad->GetTransform());
}

Rope::~Rope()
{
}

void Rope::Update()
{
	_quad->Update();
	_col->Update();
	_ropeCol->Update();
}

void Rope::Render()
{
	_quad->Render();
}

void Rope::DebugRender()
{
	_col->Render();
	_ropeCol->Render();
}

void Rope::SetPosition(Vector2 pos)
{
	_quad->GetTransform()->GetPos() = pos;
	_ropePos = pos;
}
