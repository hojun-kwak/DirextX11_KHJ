#include "framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
    _quad = make_shared<Quad>(L"Resource/VRising.png", L"Shaders/TextureVertexShader.hlsl", L"Shaders/LeftRightPixelShader.hlsl");
    _quad->GetTransform()->GetPos() = CENTER;

    _filterBuffer = make_shared<FilterBuffer>(1);
    //_filterBuffer->data.selected = 1; // ¿ÞÂÊ
}

TextureScene::~TextureScene()
{
}

void TextureScene::Update()
{
    _quad->Render();
}

void TextureScene::Render()
{
    _filterBuffer->SetPSBuffer(0);
    _quad->Render();
}

void TextureScene::PostRender()
{
    ImGui::SliderInt("Left Right", &_filterBuffer->data.selected, 0, 1);
}
