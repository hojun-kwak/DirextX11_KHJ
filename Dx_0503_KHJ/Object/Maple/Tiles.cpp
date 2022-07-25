#include "framework.h"
#include "Tiles.h"

Tiles::Tiles()
{
	_sprite = make_shared<Sprite>(MAPLE_TILES,Vector2(5,3));
	_col = make_shared<RectCollider>(_sprite->GetHalfFrameSize());
	_col->SetParent(_sprite->GetTransform());

	CreateData();

}

Tiles::~Tiles()
{
}

void Tiles::Update()
{

}

void Tiles::Render()
{
}

void Tiles::CreateData()
{
}
