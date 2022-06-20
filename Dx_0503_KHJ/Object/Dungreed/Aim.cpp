#include "framework.h"
#include "Aim.h"

Aim::Aim()
{
	_texture = make_shared<Texture>(L"Resource/mousePointer.png");
	_texture->GetTransform()->GetScale() = { 0.5f,0.5f };
}

Aim::~Aim()
{
}

void Aim::Update()
{
	_texture->Update();
	_texture->GetTransform()->GetPos() = MOUSE_POS;
}

void Aim::Render()
{
	_texture->Render();
}
