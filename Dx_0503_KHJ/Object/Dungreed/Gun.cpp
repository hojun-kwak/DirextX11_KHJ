#include "framework.h"
#include "Gun.h"

Gun::Gun()
{
	_quad = make_shared<Quad>(L"Resource/kar_98k.png");
	_quad->GetTransform()->GetScale() = { 0.5f,0.5f };
}

Gun::~Gun()
{
}

void Gun::Update()
{
	_quad->Update();
}

void Gun::Render()
{
	_quad->Render();
}
