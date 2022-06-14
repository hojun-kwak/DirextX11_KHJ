#include "framework.h"
#include "Program.h"

#include "../Scene/TextureScene.h"
#include "../Scene/TextureWVPScene.h"
#include "../Scene/SolaSystemScene.h"

Program::Program()
{
	_scene = make_shared<SolaSystemScene>();

	_viewBuffer = make_shared<MatrixBuffer>();
	_projectionBuffer = make_shared<MatrixBuffer>();

	XMMATRIX projection = XMMatrixOrthographicLH(WIN_WIDTH, WIN_HEIGHT, 0.0f, 1.0f);
	_projectionBuffer->SetMatrix(projection);
	// ���̴����� ������Ʈ�ҿ뵵 �ѹ���
	_projectionBuffer->Update();

	// world �ѹ� �����̰�
	/*_worldPos = { 100.0f, 0.0f };
	XMMATRIX _worldMatrix = XMMatrixTranslation(_worldPos.x, _worldPos.y, 0);
	_worldBuffer->SetMatrix(_worldMatrix);*/

	// camera �ѹ� �����̱�
	/*_cameraPos = { -300.0f, -100.0f };
	XMMATRIX _cameraMatrix = XMMatrixTranslation(_cameraPos.x, _cameraPos.y, 0);
	_viewBuffer->SetMatrix(_cameraMatrix);*/

	_viewBuffer->Update();

}

Program::~Program()
{
}

void Program::Update()
{
	_projectionBuffer->Update();
	_viewBuffer->Update();

	_scene->Update();
}

void Program::Render()
{
	Device::GetInstance()->Clear(184.0f, 248.0f, 251.0f);

	_viewBuffer->SetVSBuffer(1);
	_projectionBuffer->SetVSBuffer(2);

	_scene->Render();

	Device::GetInstance()->Present();
}
