#include "framework.h"
#include "MiniMap.h"

MiniMap::MiniMap(Vector2 size)
	:_size(size)
{
	_rtv = make_shared<RenderTarget>(_size.x, _size.y);
	_targetTexture = make_shared<Quad>(L"RTV", _size * 2.0f);
	shared_ptr<Texture> texture = Texture::Add(L"test", _rtv->GetSRV());
	_targetTexture->SetTexture(texture);
	_targetTexture->GetTransform()->GetPos() = { WIN_WIDTH - size.x * 0.5f - 50.0f , WIN_HEIGHT - size.y * 0.5f - 50.0f };
	// vertex쉐이터에서 한번은 해야하기때문에, 미니맵은 움직이지 않아도 되기때문에
	_targetTexture->Update();

	_miniPlayer = make_shared<Quad>(L"Resource/cs.png");
	_miniPlayer->GetTransform()->GetScale() *= 0.1f;
	_miniPlayer->GetTransform()->GetPos() = _targetTexture->GetTransform()->GetPos();
}

MiniMap::~MiniMap()
{
}

void MiniMap::Update()
{
	float backgroundX = _rightTop.x - _leftBottom.x;
	float backgroundY = _rightTop.y - _leftBottom.y;

	Vector2 ratio;
	ratio.x = _playerPos->x / backgroundX;
	ratio.y = _playerPos->y / backgroundY;

	_miniPlayer->GetTransform()->GetPos().x = ratio.x * _size.x + _targetTexture->LeftBottom().x;
	_miniPlayer->GetTransform()->GetPos().y = ratio.y * _size.y + _targetTexture->LeftBottom().y;

	_miniPlayer->Update();
}

void MiniMap::SetRTV()
{
	_rtv->Set();
}

void MiniMap::PostRender()
{
	_miniPlayer->Render();
}
