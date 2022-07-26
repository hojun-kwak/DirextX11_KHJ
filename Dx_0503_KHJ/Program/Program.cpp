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
	_scene = make_shared<MapleScene>();

	/*_viewBuffer = make_shared<MatrixBuffer>();
	_projectionBuffer = make_shared<MatrixBuffer>();*/

	// ��ǥ�谡 ������� 0,0
	//XMMATRIX projection = XMMatrixOrthographicLH(WIN_WIDTH, WIN_HEIGHT, 0.0f, 1.0f);

	// ��ǥ�� ���� �Ʒ����� 0,0
	/*XMMATRIX projection = XMMatrixOrthographicOffCenterLH(0, WIN_WIDTH, 0, WIN_HEIGHT, 0.0f, 1.0f);
	_projectionBuffer->SetMatrix(projection);*/

	// ���̴����� ������Ʈ�ҿ뵵 �ѹ���
	//_projectionBuffer->Update();

	// world �ѹ� �����̰�
	/*_worldPos = { 100.0f, 0.0f };
	XMMATRIX _worldMatrix = XMMatrixTranslation(_worldPos.x, _worldPos.y, 0);
	_worldBuffer->SetMatrix(_worldMatrix);*/

	// camera �ѹ� �����̱�
	/*_cameraPos = { -300.0f, -100.0f };
	XMMATRIX _cameraMatrix = XMMatrixTranslation(_cameraPos.x, _cameraPos.y, 0);
	_viewBuffer->SetMatrix(_cameraMatrix);*/

	//_viewBuffer->Update();

	//Timer::GetInstance()->SetFPS(60);

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
	// ��ó�� ����
	_scene->PreRender();

	Device::GetInstance()->SetRenderTarget();
	Device::GetInstance()->Clear(184.0f, 248.0f, 251.0f);

	/*if (KEY_PRESS(VK_UP))
	{
		Device::GetInstance()->Clear(150.0f, 2.0f, 251.0f);
	}
	if (KEY_PRESS(VK_DOWN))
	{
		Device::GetInstance()->Clear(184.0f, 248.0f, 251.0f);
	}*/

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ALPHA_STATE->SetState();

	Camera::GetInstance()->SetViewPort();
	Camera::GetInstance()->SetProjectionBuffer();
	/*_viewBuffer->SetVSBuffer(1);
	_projectionBuffer->SetVSBuffer(2);*/

	_scene->Render();
	EffectManager::GetInstance()->Render();

	//ImGui::Text("FPS : %d", Timer::GetInstance()->GetFPS());
	wstring fps = L"FPS : " + to_wstring((int)Timer::GetInstance()->GetFPS());
	RECT rect = { 0,0,100,100 };

	DirectWrite::GetInstance()->GetDeviceContext()->BeginDraw();
	DirectWrite::GetInstance()->RenderText(fps, rect);


	Camera::GetInstance()->PostRender();
	_scene->PostRender();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	DirectWrite::GetInstance()->GetDeviceContext()->EndDraw();
	Device::GetInstance()->Present();
}
