#include "framework.h"
#include "Tiles.h"

Tiles::Tiles()
{
	_quad = make_shared<Quad>(MAPLE_TILES);
	_col = make_shared<RectCollider>(_quad->GetHalfSize());
	_col->SetParent(_quad->GetTransform());

	CreateData();

}

Tiles::~Tiles()
{
}

void Tiles::Update()
{
	_quad->Update();
	_col->Update();
}

void Tiles::Render()
{
	_quad->Render();
}

void Tiles::DebugRender()
{
	_col->Render();
}

void Tiles::CreateData()
{
	
}
