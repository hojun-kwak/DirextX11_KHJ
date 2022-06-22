#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(const Vector2 halfSize)
:_halfSize(halfSize)
{
	CreateData();
}

RectCollider::~RectCollider()
{
}

void RectCollider::CreateData()
{
	VertexPos vertex;
	_verices.reserve(5);
	vertex.pos = XMFLOAT3(-_halfSize._x, _halfSize._y, 0); // 좌측상단
	_verices.push_back(vertex); // 복사하기떄문에 emplace_back 은 쓰면 안됨
	vertex.pos = XMFLOAT3(_halfSize._x, _halfSize._y, 0); // 우측상단
	_verices.push_back(vertex);
	vertex.pos = XMFLOAT3(_halfSize._x, -_halfSize._y, 0); // 우측하단
	_verices.push_back(vertex);
	vertex.pos = XMFLOAT3(-_halfSize._x, -_halfSize._y, 0); // 좌측하단
	_verices.push_back(vertex);
	vertex.pos = XMFLOAT3(-_halfSize._x, _halfSize._y, 0); // 좌측상단
	_verices.push_back(vertex);

	_vertexShader = make_shared<VertexShader>(L"Shaders/ColliderShader/ColliderVertexShader.hlsl");
	_pixelShader = make_shared<PixelShader>(L"Shaders/ColliderShader/ColliderPixelShader.hlsl");

	_vertexBuffer = make_shared<VertexBuffer>(_verices.data(), sizeof(VertexPos), _verices.size());
	_colorBuffer = make_shared<ColorBuffer>();
	_colorBuffer->SetColor(GREEN);

	_transform = make_shared<Transform>();
	_parent = nullptr;

}

void RectCollider::Update()
{
	if (_isActive == false)
		return;

	if (_isCollision == true)
		_colorBuffer->SetColor(RED);
	else
		_colorBuffer->SetColor(GREEN);

	_center = GetPosition();

	_transform->UpdateWorldBuffer();
	_colorBuffer->Update();
}

void RectCollider::Render()
{
	if (_isActive == false)
		return;

	_transform->SetWorldBuffer(0);
	_colorBuffer->SetPSBuffer(0);

	_vertexBuffer->IASet(0);
	DEVICE_CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	_vertexShader->Set();
	_pixelShader->PsSet();

	DEVICE_CONTEXT->Draw(_verices.size(), 0);
}

bool RectCollider::IsCollision(shared_ptr<RectCollider> rect)
{
	if (rect->Left() < this->Right() && rect->Right() > this->Left() &&
		rect->Bottom() < this->Top() && rect->Top() > this->Bottom())
		return _isCollision = true;

	return _isCollision = false;
}

bool RectCollider::IsCollision(Vector2 pos)
{
	if (pos._x < Left() || pos._x > Right())
		return _isCollision = false;

	if (pos._y > Top() || pos._y < Bottom())
		return _isCollision = false;

	return _isCollision = true;
}
