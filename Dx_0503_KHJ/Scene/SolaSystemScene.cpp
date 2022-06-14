#include "framework.h"
#include "SolaSystemScene.h"

SolaSystemScene::SolaSystemScene()
{
	_texture1 = make_shared<Texture>(L"Resource/sun.png");

	_texture2 = make_shared<Texture>(L"Resource/earth.png");
	_texture2->SetParent(_texture1->GetMatrix());
	_texture2->GetPos().x = 400;
	_texture2->GetScale() = { 0.8f ,0.8f };

	_texture3 = make_shared<Texture>(L"Resource/moon.png");
	_texture3->SetParent(_texture2->GetMatrix());
	/*_texture3->SetParent(_texture2->GetMatrix() * temp);
	_texture3->SetParent(_texture2->)*/
	_texture3->GetPos().x = 200;
	_texture3->GetScale() = { 0.5f ,0.5f };
}

SolaSystemScene::~SolaSystemScene()
{
}

void SolaSystemScene::Update()
{
	// DeltaTime : 1 Tick당 걸리는 시간
	//_texture1->GetPos().x -= 0.01f;
	_texture1->GetAnlgle() += 0.0001f;
	_texture2->GetAnlgle() += 0.0005f;
	_texture3->GetAnlgle() += 0.001f;

	if (GetAsyncKeyState(VK_LEFT))
	{
		_texture1->GetPos().x -= 0.1f;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		_texture1->GetPos().x += 0.1f;
	}
	if (GetAsyncKeyState(VK_UP))
	{
		_texture1->GetPos().y += 0.1f;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		_texture1->GetPos().y -= 0.1f;
	}

	// 내부에 worldBuffer를 가지고 있기때문에 지속적으로 업데이트 해줘야함
	_texture1->Update();
	_texture2->Update();
	_texture3->Update();
}

void SolaSystemScene::Render()
{
	//AdditiveBlendState->SetState();

	//AlphaBlendState->SetState();
	_texture1->Render();
	_texture2->Render();
	_texture3->Render();
}
