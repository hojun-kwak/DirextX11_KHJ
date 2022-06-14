#include "framework.h"
#include "TextureWVPScene.h"

TextureWVPScene::TextureWVPScene()
{
	_texture = make_shared<Texture>(L"Resource/VRising.png");

	_worldBuffer = make_shared<MatrixBuffer>();
	_viewBuffer = make_shared<MatrixBuffer>();
	_projectionBuffer = make_shared<MatrixBuffer>();

	XMMATRIX projection = XMMatrixOrthographicLH(WIN_WIDTH, WIN_HEIGHT, 0.0f, 1.0f);
	_projectionBuffer->SetMatrix(projection);
	// 쉐이더에서 업데이트할용도 한번만
	_projectionBuffer->Update();

	// world 한번 움직이게
	_worldPos = { 100.0f, 0.0f };
	XMMATRIX _worldMatrix = XMMatrixTranslation(_worldPos.x, _worldPos.y, 0);
	_worldBuffer->SetMatrix(_worldMatrix);

	// camera 한번 움직이기
	/*_cameraPos = { -300.0f, -100.0f };
	XMMATRIX _cameraMatrix = XMMatrixTranslation(_cameraPos.x, _cameraPos.y, 0);
	_viewBuffer->SetMatrix(_cameraMatrix);*/

}

TextureWVPScene::~TextureWVPScene()
{
}

void TextureWVPScene::Update()
{
	// camera 한번 움직이기
	/*_cameraPos = { -300.0f, -100.0f };
	XMMATRIX _cameraMatrix = XMMatrixTranslation(_cameraPos.x, _cameraPos.y, 0);
	_viewBuffer->SetMatrix(_cameraMatrix);*/

	// 삥삥돌리기
	/*_angle += 0.0001f;
	XMMATRIX cameraMatrix = XMMatrixRotationZ(_angle);
	_viewBuffer->SetMatrix(cameraMatrix);*/

	// pos
	if (GetAsyncKeyState(VK_LEFT))
	{
		_texture->GetPos().x -= 0.1f;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		_texture->GetPos().x += 0.1f;
	}
	if (GetAsyncKeyState(VK_UP))
	{
		_texture->GetPos().y += 0.1f;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		_texture->GetPos().y -= 0.1f;
	}

	// scale
	if (GetAsyncKeyState(VK_NUMPAD8)) // x
	{
		_texture->GetScale().x -= 0.001f;
	}
	if (GetAsyncKeyState(VK_NUMPAD2)) // x
	{
		_texture->GetScale().x += 0.001f;
	}
	if (GetAsyncKeyState(VK_NUMPAD4)) // y
	{
		_texture->GetScale().y -= 0.001f;
	}
	if (GetAsyncKeyState(VK_NUMPAD6)) // y
	{
		_texture->GetScale().y += 0.001f;
	}

	// rocation
	if (GetAsyncKeyState(0x5A)) // z
	{
		_texture->GetAnlgle() += 0.001f;
	}
	if (GetAsyncKeyState(0x58)) // x
	{
		_texture->GetAnlgle() -= 0.001f;
	}




	_worldBuffer->Update();
	_viewBuffer->Update();


	_texture->Update();
}

void TextureWVPScene::Render()
{
	_worldBuffer->SetVSBuffer(0);
	_viewBuffer->SetVSBuffer(1);
	_projectionBuffer->SetVSBuffer(2);


	_texture->Render();
}
