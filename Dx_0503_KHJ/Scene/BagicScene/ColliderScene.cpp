#include "framework.h"
#include "ColliderScene.h"

ColliderScene::ColliderScene()
{
	_circleCollider1 = make_shared<CircleCollider>(80);
	_circleCollider2 = make_shared<CircleCollider>(50);
	_rectCollider1 = make_shared<RectCollider>(Vector2(500, 50));
	_rectCollider2 = make_shared<RectCollider>(Vector2(50, 100));

	_circleCollider1->GetLocalPosition() = Vector2(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f);
	_rectCollider1->GetLocalPosition() = Vector2(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f);
	_rectCollider2->GetLocalPosition() = Vector2(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f);
}

ColliderScene::~ColliderScene()
{
}

void ColliderScene::Update()
{
	if (_rectCollider2->IsCollision(_rectCollider1,false))
		_rectCollider2->SetRed();
	else
		_rectCollider2->SetGreen();

	//if (_circleCollider1->IsCollision(MOUSE_POS))
	//	_circleCollider1->SetRed();
	//else
	//	_circleCollider1->SetGreen();

	_circleCollider2->Update();
	_circleCollider1->Update();
	_rectCollider1->Update();
	_rectCollider2->Update();
}

void ColliderScene::Render()
{
	_circleCollider2->Render();
	_circleCollider1->Render();
	_rectCollider1->Render();
	_rectCollider2->Render();

	// ImGui
}

void ColliderScene::PostRender()
{
	ImGui::SliderFloat("Rect1 PosX", &_rectCollider1->GetLocalPosition().x, 0, WIN_WIDTH);
	ImGui::SliderFloat("Rect1 PosY", &_rectCollider1->GetLocalPosition().y, 0, WIN_HEIGHT);

	ImGui::SliderFloat("mouse PosY", &MOUSE_POS.x, 0, WIN_HEIGHT);
	ImGui::SliderFloat("mouse PosY", &MOUSE_POS.y, 0, WIN_HEIGHT);

	ImGui::SliderFloat("Rect1 Angle", &_rectCollider1->GetAngle(), 0, 2 * PI);
}
