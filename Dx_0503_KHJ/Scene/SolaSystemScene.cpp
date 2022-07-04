#include "framework.h"
#include "SolaSystemScene.h"

SolaSystemScene::SolaSystemScene()
{
	_sun = make_shared<Quad>(L"Resource/sun.png");

	_earth = make_shared<Quad>(L"Resource/earth.png");
	_earth->GetTransform()->SetParent(_sun->GetTransform());
	_earth->GetTransform()->GetPos().x = 400;
	_earth->GetTransform()->GetScale() = { 0.8f ,0.8f };

	_moon = make_shared<Quad>(L"Resource/moon.png");
	_moon->GetTransform()->SetParent(_earth->GetTransform());
	/*_moon->SetParent(_earth->GetMatrix() * temp);
	_moon->SetParent(_earth->)*/
	_moon->GetTransform()->GetPos().x = 200;
	_moon->GetTransform()->GetScale() = { 0.5f ,0.5f };

	_samplerState = make_shared<SamplerState>();
	_blendState = make_shared<BlendState>();
}

SolaSystemScene::~SolaSystemScene()
{
}

void SolaSystemScene::Update()
{
	// DeltaTime : 1 Tick�� �ɸ��� �ð�
	//_sun->GetPos().x -= 0.01f;
	_sun->GetTransform()->GetPos().x = MOUSE_POS.x;
	_sun->GetTransform()->GetPos().y = MOUSE_POS.y;

	if (KEY_PRESS(VK_SPACE))
	{
		_sun->GetTransform()->GetAngle() += 1.0f * DELTA_TIME;
		_earth->GetTransform()->GetAngle() += 5.0f * DELTA_TIME;
		_moon->GetTransform()->GetAngle() += 3.0f * DELTA_TIME;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		_sun->GetTransform()->GetPos().x -= 1.0f + DELTA_TIME;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		_sun->GetTransform()->GetPos().x += 1.0f + DELTA_TIME;
	}
	if (GetAsyncKeyState(VK_UP))
	{
		_sun->GetTransform()->GetPos().y += 1.0f + DELTA_TIME;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		_sun->GetTransform()->GetPos().y -= 1.0f + DELTA_TIME;
	}

	if (GetAsyncKeyState(VK_ADD))
	{
		_sun->GetTransform()->GetScale().x += 0.1f + DELTA_TIME;
		_sun->GetTransform()->GetScale().y += 0.1f + DELTA_TIME;
	}
	if (GetAsyncKeyState(VK_SUBTRACT))
	{
		_sun->GetTransform()->GetScale().x -= 0.1f + DELTA_TIME;
		_sun->GetTransform()->GetScale().y -= 0.1f + DELTA_TIME;
	}

	// ���ο� worldBuffer�� ������ �ֱ⶧���� ���������� ������Ʈ �������
	_sun->Update();
	_earth->Update();
	_moon->Update();
}

void SolaSystemScene::Render()
{
	_blendState->Additive();
	_blendState->SetState();

	_sun->Render();
	_earth->Render();
	_moon->Render();
}
