#include "framework.h"
#include "_2D_Tile.h"

_2D_Tile::_2D_Tile()
{
	_quad = make_shared<Quad>(L"Resource/Maple/tile.png");
	_col = make_shared<RectCollider>(_quad->GetHalfSize());
	_col->SetParent(_quad->GetTransform());
}

_2D_Tile::~_2D_Tile()
{
}

void _2D_Tile::Update()
{
	_quad->Update();
	_col->Update();
}

void _2D_Tile::Render()
{
	_quad->Render();
}

void _2D_Tile::DebugRender()
{
	_col->Render();
}

void _2D_Tile::SetPosition(float x, float y)
{
	_quad->GetTransform()->GetPos() = { x,y };
	_tilePos = { x,y };
}
