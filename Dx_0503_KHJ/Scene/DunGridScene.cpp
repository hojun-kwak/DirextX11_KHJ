#include "framework.h"
#include "DunGridScene.h"

DunGridScene::DunGridScene()
{
	/*_Character = make_shared<Texture>(L"Resource/ezreal.png");
	_Character->GetTransform()->GetPos() = { -550.0f, -250.0f };
	_Character->GetTransform()->GetScale() = { 1.0f, 1.0f };*/

	//_Gun = make_shared<Texture>(L"Resource/kar_98k.png");
	//_Gun->GetTransform()->GetPos() = { _Character->GetTransform()->GetPos().x, _Character->GetTransform()->GetPos().y };
	//_Gun->GetTransform()->GetScale() = { 1.0f,1.0f };

	//_Skill = make_shared<Texture>(L"Resource/mysticShot.png");
	//_Skill->GetTransform()->GetPos() = { _Character->GetTransform()->GetPos().x + 50.0f, _Character->GetTransform()->GetPos().y + 100.0f };
	//_Skill->GetTransform()->GetScale() = { 0.3f,0.3f };

	_MousePointer = make_shared<Texture>(L"Resource/mousePointer.png");
	_MousePointer->GetTransform()->GetScale() = { 0.5f,0.5f };
	/*_Gun->GetTransform()->GetAnlgle() = _MousePointer->GetTransform()->GetAnlgle();*/

	_player = make_shared<Player>();
	//_gun = make_shared<Gun>();
	_skill = make_shared<Bullet>();
}

DunGridScene::~DunGridScene()
{
}

void DunGridScene::Update()
{

	_MousePointer->GetTransform()->GetPos() = MOUSE_POS;

	// 두 벡터간의 사이각을 구한다?
	//_Gun->GetTransform()->GetAnlgle() - _MousePointer->GetTransform()->GetAnlgle();
	//_Gun->GetTransform()->GetAnlgle() += 0.1f + DELTA_TIME;

	/*float cosX = (_MousePointer->GetTransform()->GetPos().x - _Gun->GetTransform()->GetPos().x);
	float cosY = (_MousePointer->GetTransform()->GetPos().y - _Gun->GetTransform()->GetPos().y);*/

	// vector에 추가했는데 왜 안될까??
	//float cos = (_MousePointer->GetTransform()->GetPos() - _Gun->GetTransform()->GetPos());

	//float angle1 = Vector2(cosX, cosY).Angle();
	//float angle1 = Vector2(_MousePointer->GetTransform()->GetPos()).Angle();
	//_Gun->GetTransform()->GetAnlgle() = angle1 - PI * 0.05f;

	if (KEY_PRESS(VK_LBUTTON))
	{
		//_Skill->GetTransform()->GetPos() = _Gun->GetTransform()->GetPos();
		skillActive = true;
		//_Skill->GetTransform()->GetPos() = _MousePointer->GetTransform()->GetPos() - _Gun->GetTransform()->GetPos();
		// 
		//_earth->GetTranform()->_pos = _earth->GetTransform()->_pos + (staffToMousePos)*DELTATIME;
	}
	//if (skillActive)
	//{
	//	Vector2 shootPos = { 0.0f,0.0f };
	//	shootPos.Normallize();
	//	//shootPos = _MousePointer->GetTransform()->GetPos() - _Gun->GetTransform()->GetPos();
	//	shootPos._x = _MousePointer->GetTransform()->GetPos().x - _Gun->GetTransform()->GetPos().x;
	//	shootPos._y = _MousePointer->GetTransform()->GetPos().y - _Gun->GetTransform()->GetPos().y;
	//	_Skill->GetTransform()->GetPos().x = _Skill->GetTransform()->GetPos().x + shootPos._x * DELTA_TIME;
	//	_Skill->GetTransform()->GetPos().y = _Skill->GetTransform()->GetPos().y + shootPos._y * DELTA_TIME;
	//}
	if (KEY_PRESS(VK_RBUTTON))
	{
		//_Skill->GetTransform()->GetPos() = { _Character->GetTransform()->GetPos().x + 50.0f, _Character->GetTransform()->GetPos().y + 100.0f };
		skillActive = false;
	}

	//_Character->Update();
	_player->Update();
	//_gun->Update();
	_skill->Update();
	_MousePointer->Update();
}

void DunGridScene::Render()
{
	//_Character->Render();
	_player->Render();
	//_gun->Render();
	_skill->Render();

	/*if (skillActive == true)
	{
		_skill->Render();
	}*/
	_MousePointer->Render();
}
