#include "framework.h"
#include "_2D_Rope.h"

_2D_Rope::_2D_Rope()
{
	_quad = make_shared<Quad>(L"Resource/Maple/Rope.png");
	_col = make_shared<RectCollider>(_quad->GetHalfSize());
	_col->SetParent(_quad->GetTransform());

	_quad->GetTransform()->GetScale() *= 0.3f;
}

_2D_Rope::~_2D_Rope()
{
}

void _2D_Rope::Update()
{
	if (_isActive == false)
		return;

	_quad->Update();
	_col->Update();
}

void _2D_Rope::Render()
{
	if (_isActive == false)
		return;

	_quad->Render();
}

void _2D_Rope::DebugRender()
{
	if (_isActive == false)
		return;

	_col->Render();
}

void _2D_Rope::SetPosition(Vector2 pos)
{
	_quad->GetTransform()->GetPos() = pos;
	_ropePos = pos;
}
