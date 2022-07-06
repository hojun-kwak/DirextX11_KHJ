#include "framework.h"
#include "FilterScene.h"

FilterScene::FilterScene()
{
	_quad = make_shared<Quad>(L"Resource/tomboy.png"
		, L"Shaders/TextureVertexShader.hlsl", L"Shaders/FillterShader/FilterShader.hlsl");
	_quad->GetTransform()->GetPos() = { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f };
	_quad->GetTransform()->GetScale() *= 2.0f;

	_filterBuffer = make_shared<FilterBuffer>();
	_filterBuffer->data.value1 = 5;
}

FilterScene::~FilterScene()
{
}

void FilterScene::Update()
{
	_quad->Update();
}

void FilterScene::Render()
{
	_quad->Render();
	_filterBuffer->SetPSBuffer(0);
}

void FilterScene::PostRender()
{
	ImGui::SliderInt("Mosaic", &(_filterBuffer->data.value1), 0, 100);
}
