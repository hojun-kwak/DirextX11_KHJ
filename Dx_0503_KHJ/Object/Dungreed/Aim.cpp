#include "framework.h"
#include "Aim.h"

Aim::Aim()
{
	_quad = make_shared<Quad>(L"Resource/mousePointer.png");
	_quad->GetTransform()->GetScale() = { 0.1f,0.1f };
}

Aim::~Aim()
{
}

void Aim::Update()
{
	_quad->Update();
	_quad->GetTransform()->GetPos() = MOUSE_POS;
}

void Aim::Render()
{
	_quad->Render();
}
