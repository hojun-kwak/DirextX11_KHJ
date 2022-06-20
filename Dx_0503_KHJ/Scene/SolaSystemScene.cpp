#include "framework.h"
#include "SolaSystemScene.h"

SolaSystemScene::SolaSystemScene()
{
	_sun = make_shared<Texture>(L"Resource/sun.png");

	_earth = make_shared<Texture>(L"Resource/earth.png");
	_earth->GetTransform()->SetParent(_sun->GetTransform()->GetMatrix());
	_earth->GetTransform()->GetPos()._x = 400;
	_earth->GetTransform()->GetScale() = { 0.8f ,0.8f };

	_moon = make_shared<Texture>(L"Resource/moon.png");
	_moon->GetTransform()->SetParent(_earth->GetTransform()->GetMatrix());
	/*_moon->SetParent(_earth->GetMatrix() * temp);
	_moon->SetParent(_earth->)*/
	_moon->GetTransform()->GetPos()._x = 200;
	_moon->GetTransform()->GetScale() = { 0.5f ,0.5f };

	_samplerState = make_shared<SamplerState>();
	_blendState = make_shared<BlendState>();
}

SolaSystemScene::~SolaSystemScene()
{
}

void SolaSystemScene::Update()
{
	// DeltaTime : 1 Tick당 걸리는 시간
	//_sun->GetPos().x -= 0.01f;
	_sun->GetTransform()->GetPos()._x = MOUSE_POS._x;
	_sun->GetTransform()->GetPos()._y = MOUSE_POS._y;

	if (KEY_PRESS(VK_SPACE))
	{
		_sun->GetTransform()->GetAnlgle() += 1.0f * DELTA_TIME;
		_earth->GetTransform()->GetAnlgle() += 5.0f * DELTA_TIME;
		_moon->GetTransform()->GetAnlgle() += 3.0f * DELTA_TIME;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		_sun->GetTransform()->GetPos()._x -= 1.0f + DELTA_TIME;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		_sun->GetTransform()->GetPos()._x += 1.0f + DELTA_TIME;
	}
	if (GetAsyncKeyState(VK_UP))
	{
		_sun->GetTransform()->GetPos()._y += 1.0f + DELTA_TIME;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		_sun->GetTransform()->GetPos()._y -= 1.0f + DELTA_TIME;
	}

	if (GetAsyncKeyState(VK_ADD))
	{
		_sun->GetTransform()->GetScale()._x += 0.1f + DELTA_TIME;
		_sun->GetTransform()->GetScale()._y += 0.1f + DELTA_TIME;
	}
	if (GetAsyncKeyState(VK_SUBTRACT))
	{
		_sun->GetTransform()->GetScale()._x -= 0.1f + DELTA_TIME;
		_sun->GetTransform()->GetScale()._y -= 0.1f + DELTA_TIME;
	}

	// 내부에 worldBuffer를 가지고 있기때문에 지속적으로 업데이트 해줘야함
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
