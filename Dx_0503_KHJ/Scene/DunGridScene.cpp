#include "framework.h"
#include "DunGridScene.h"

DunGridScene::DunGridScene()
{
	_Character = make_shared<Texture>(L"Resource/ezreal.png");
	_Character->GetTransform()->GetPos() = { -550.0f, -250.0f };
	_Character->GetTransform()->GetScale() = { 1.0f, 1.0f };
	
	_Gun = make_shared<Texture>(L"Resource/kar_98k.png");
	_Gun->GetTransform()->GetPos() = { _Character->GetTransform()->GetPos().x, _Character->GetTransform()->GetPos().y };
	_Gun->GetTransform()->GetScale() = { 1.0f,1.0f };

	_Skill = make_shared<Texture>(L"Resource/mysticShot.png");
	_Skill->GetTransform()->GetPos() = { _Character->GetTransform()->GetPos().x + 50.0f, _Character->GetTransform()->GetPos().y + 100.0f };
	_Skill->GetTransform()->GetScale() = { 0.3f,0.3f };

	_MousePointer = make_shared<Texture>(L"Resource/mousePointer.png");
	_MousePointer->GetTransform()->GetScale() = { 0.5f,0.5f };
	_MousePointer->GetTransform()->GetPos().x = MOUSE_POS._x;
	_MousePointer->GetTransform()->GetPos().y = MOUSE_POS._y;

	/*_Gun->GetTransform()->GetAnlgle() = _MousePointer->GetTransform()->GetAnlgle();*/

	_samplerState = make_shared<SamplerState>();
	_blendState = make_shared<BlendState>();

}

DunGridScene::~DunGridScene()
{
}

void DunGridScene::Update()
{

	_MousePointer->GetTransform()->GetPos().x = MOUSE_POS._x;
	_MousePointer->GetTransform()->GetPos().y = MOUSE_POS._y;

	// 두 벡터간의 사이각을 구한다?
	//_Gun->GetTransform()->GetAnlgle() - _MousePointer->GetTransform()->GetAnlgle();
	//_Gun->GetTransform()->GetAnlgle() += 0.1f + DELTA_TIME;

	if (KEY_PRESS(VK_LBUTTON))
	{
		
		skillActive = true;
	}

	_Character->Update();
	_Gun->Update();
	_Skill->Update();
	_MousePointer->Update();
}

void DunGridScene::Render()
{
	_blendState->Additive();
	_blendState->SetState();

	_Character->Render();
	_Gun->Render();

	if (skillActive == true)
	{
		_Skill->Render();
	}
	_MousePointer->Render();
}
