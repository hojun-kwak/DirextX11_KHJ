#include "framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
    _texture = make_shared<Texture>(L"Resource/VRising.png");
}

TextureScene::~TextureScene()
{
}

void TextureScene::Update()
{
    _texture->Render();
}

void TextureScene::Render()
{
    _texture->Render();
}
