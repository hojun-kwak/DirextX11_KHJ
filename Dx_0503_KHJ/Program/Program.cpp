#include "framework.h"
#include "Program.h"


Program::Program()
{
	//_scene = make_shared<DunGridScene>();
	srand(static_cast<unsigned int>(time(nullptr)));
}

Program::~Program()
{
}

void Program::Update()
{
	EffectManager::GetInstance()->Update();
	Camera::GetInstance()->Update();

	SCENE->Update();
}

void Program::Render()
{
	// 傈贸府 开开
	SCENE->PreRender();

	Device::GetInstance()->SetRenderTarget();
	Device::GetInstance()->Clear(184.0f, 248.0f, 251.0f);

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ALPHA_STATE->SetState();

	Camera::GetInstance()->SetViewPort();
	Camera::GetInstance()->SetProjectionBuffer();

	SCENE->Render();
	if (KEY_DOWN(VK_F1))
	{
		if (_IsLookingDebug == false)
			_IsLookingDebug = true;
		else
			_IsLookingDebug = false;
	}
	if (_IsLookingDebug == true)
	{
		SCENE->DebugRender();
	}
	EffectManager::GetInstance()->Render();

	wstring fps = L"FPS : " + to_wstring((int)Timer::GetInstance()->GetFPS());
	RECT rect = { 0,0,100,100 };

	DirectWrite::GetInstance()->GetDeviceContext()->BeginDraw();
	DirectWrite::GetInstance()->RenderText(fps, rect);


	Camera::GetInstance()->PostRender();
	Camera::GetInstance()->SetUIBuffer();
	SCENE->PostRender();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	DirectWrite::GetInstance()->GetDeviceContext()->EndDraw();
	Device::GetInstance()->Present();
}
