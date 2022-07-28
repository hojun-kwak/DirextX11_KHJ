#include "framework.h"
#include "Program.h"

#include "../Scene/TextureScene.h"
#include "../Scene/TextureWVPScene.h"
#include "../Scene/SolaSystemScene.h"
#include "../Scene/DunGridScene.h"
#include "../Scene/ColliderScene.h"
#include "../Scene/ZeldaScene.h"
#include "../Scene/FilterScene.h"
#include "../Scene/EffectScene.h"
#include "../Scene/CameraScene.h"
#include "../Scene/2D_PortFolio/MapleScene.h"
#include "../Scene/XmlLoadScene.h"

Program::Program()
{
	_scene = make_shared<ColliderScene>();
}

Program::~Program()
{
}

void Program::Update()
{
	EffectManager::GetInstance()->Update();
	Camera::GetInstance()->Update();
	_scene->Update();
}

void Program::Render()
{
	// 傈贸府 开开
	_scene->PreRender();

	Device::GetInstance()->SetRenderTarget();
	Device::GetInstance()->Clear(184.0f, 248.0f, 251.0f);

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ALPHA_STATE->SetState();

	Camera::GetInstance()->SetViewPort();
	Camera::GetInstance()->SetProjectionBuffer();

	_scene->Render();
	if (KEY_DOWN(VK_F1))
	{
		if (_OnOff == false)
			_OnOff = true;
		else
			_OnOff = false;
	}
	if (_OnOff == true)
	{
		_scene->DebugRender();

	}
	EffectManager::GetInstance()->Render();

	wstring fps = L"FPS : " + to_wstring((int)Timer::GetInstance()->GetFPS());
	RECT rect = { 0,0,100,100 };

	DirectWrite::GetInstance()->GetDeviceContext()->BeginDraw();
	DirectWrite::GetInstance()->RenderText(fps, rect);


	Camera::GetInstance()->PostRender();
	Camera::GetInstance()->SetUIBuffer();
	_scene->PostRender();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	DirectWrite::GetInstance()->GetDeviceContext()->EndDraw();
	Device::GetInstance()->Present();
}
