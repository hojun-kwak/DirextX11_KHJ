#include "framework.h"
#include "ColliderScene.h"

ColliderScene::ColliderScene()
{
	_rectCollider1 = make_shared<RectCollider>(Vector2{ 100.0f,100.0f });
	_rectCollider2 = make_shared<RectCollider>(Vector2{ 50.0f,50.0f });

	_rectCollider2->GetPosition() = Vector2(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f);
}

ColliderScene::~ColliderScene()
{
}

void ColliderScene::Update()
{
	_rectCollider1->IsCollision(_rectCollider2);
	_rectCollider2->IsCollision(MOUSE_POS);

	_rectCollider1->Update();
	_rectCollider2->Update();
}

void ColliderScene::Render()
{
	_rectCollider1->Render();
	_rectCollider2->Render();

	// ImGui
}

void ColliderScene::PostRender()
{
	ImGui::SliderFloat("Rect1 PosX", &_rectCollider1->GetPosition()._x, 0, WIN_WIDTH);
	ImGui::SliderFloat("Rect1 PosY", &_rectCollider1->GetPosition()._y, 0, WIN_HEIGHT);

	ImGui::SliderFloat("mouse PosY", &MOUSE_POS._x, 0, WIN_HEIGHT);
	ImGui::SliderFloat("mouse PosY", &MOUSE_POS._y, 0, WIN_HEIGHT);
}
