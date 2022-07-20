#include "framework.h"
#include "MapleScene.h"

MapleScene::MapleScene()
{
}

MapleScene::~MapleScene()
{
}

void MapleScene::Update()
{
}

void MapleScene::Render()
{
}

void MapleScene::PostRender()
{
	if (KEY_PRESS(VK_F12))
	{
		ImGui::Text("CameraInfo");
		//ImGui::Text("CameraX : %.1f, CameraY : %.1f", _transform->GetPos().x * (-1.0f), _transform->GetPos().y * (-1.0f));
		//ImGui::Text("CameraX : %.1f, CameraY : %.1f", Camera::GetInstance()->GetTransform()->GetPos().x * (-1.0f), Camera::GetInstance()->GetTransform()->GetPos().y * (-1.0f));
	}
}
