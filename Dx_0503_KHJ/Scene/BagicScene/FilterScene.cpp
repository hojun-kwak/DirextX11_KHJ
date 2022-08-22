#include "framework.h"
#include "FilterScene.h"

FilterScene::FilterScene()
{
	_quad = make_shared<Quad>(L"Resource/LostArk.png"
		, L"Shaders/TextureVertexShader.hlsl", L"Shaders/FillterShader/FilterShader.hlsl");
	_quad->GetTransform()->GetPos() = { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f };
	_quad->GetTransform()->GetScale() *= 0.5f;

	_filterBuffer = make_shared<FilterBuffer>();
	_filterBuffer->data.value1 = 60;

	_imgSizeBuffer = make_shared<IMGSizeBuffer>();
	_imgSizeBuffer->data.imgSize = _quad->GetHalfSize() * 2.0f;

	_sun = make_shared<Quad>(L"Resource/sun.png"
		, L"Shaders/TextureVertexShader.hlsl", L"Shaders/FillterShader/FilterShader.hlsl");
	_sun->GetTransform()->GetPos() = { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f };
	_sun->GetTransform()->GetScale() *= 0.2f;

	_sunfilterBuffer = make_shared<FilterBuffer>();
	_sunfilterBuffer->data.selected = 6;

	_effect = make_shared<Effect>(L"Resource/Effects/skill_core_4x4.png", Vector2{ 4,4 }, 0.1f);
	_effect->Play(Vector2(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f));
}

FilterScene::~FilterScene()
{
}

void FilterScene::Update()
{
	_quad->Update();
	_sun->Update();
	_effect->Update();
}

void FilterScene::Render()
{
	_filterBuffer->SetPSBuffer(0);
	_imgSizeBuffer->SetPSBuffer(1);
	_quad->Render();

	_sunfilterBuffer->SetPSBuffer(0);
	_sun->Render();

	_effect->Render();
}

void FilterScene::PostRender()
{
	ImGui::SliderInt("Select", &(_filterBuffer->data.selected), 0, 5);
	ImGui::SliderInt("Mosaic", &(_filterBuffer->data.value1), 0, 100);
	ImGui::SliderInt("Blur", &(_filterBuffer->data.value2), 0, 10);
	ImGui::SliderInt("RadialBlur", &(_filterBuffer->data.value3), 0, 1200);
}
