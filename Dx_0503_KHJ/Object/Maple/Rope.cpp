#include "framework.h"
#include "Rope.h"

Rope::Rope()
{
	_quad = make_shared<Quad>(L"Resource/Maple/Rope.png");
	_col = make_shared<RectCollider>(_quad->GetHalfSize());
	_col->SetParent(_quad->GetTransform());
}

Rope::~Rope()
{
}

void Rope::Update()
{
	_quad->Update();
	_col->Update();
}

void Rope::Render()
{
	_quad->Render();
}

void Rope::DebugRender()
{
	_col->Render();
}

void Rope::SetPosition(Vector2 pos)
{
	_quad->GetTransform()->GetPos() = pos;
	_ropePos = pos;
}
