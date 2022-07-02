#include "framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
    _quad = make_shared<Quad>(L"Resource/VRising.png");
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
    _quad->Render();
}
