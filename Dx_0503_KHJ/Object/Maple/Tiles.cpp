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
	_sprite->Update();
	_col->Update();
}

void Tiles::Render()
{
	_sprite->Render();
}

void Tiles::PostRender()
{
	_col->Render();
}

void Tiles::CreateData()
{
	// 618 404 5*3
	float w = 618.0f / 5.0f;
	float h = 404.0f / 3.0f;

	
}
