#include "framework.h"
#include "Gun.h"

Gun::Gun()
{
	_texture = make_shared<Texture>(L"Resource/kar_98k.png");
	//_texture->GetTransform()->GetPos().x = 50.0f;
}

Gun::~Gun()
{
}

void Gun::Update()
{
	_texture->Update();
}

void Gun::Render()
{
	_texture->Render();
}
