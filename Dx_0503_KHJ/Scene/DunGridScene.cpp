#include "framework.h"
#include "DunGridScene.h"

DunGridScene::DunGridScene()
{
	_player = make_shared<Player>();
	_aim = make_shared<Aim>();

	_rectCollider = make_shared<RectCollider>(Vector2{ 100.0f,100.0f });
}

DunGridScene::~DunGridScene()
{
}

void DunGridScene::Update()
{
	_player->Update();
	_aim->Update();

	_rectCollider->Update();
}

void DunGridScene::Render()
{
	_player->Render();
	_aim->Render();

	_rectCollider->Render();

	// Imgui
	ImGui::SliderFloat("ColliderPosX", &_rectCollider->GetLocalPosition()._x, 0, 1280);
	ImGui::SliderFloat("ColliderPosY", &_rectCollider->GetLocalPosition()._y, 0, 720);
}
