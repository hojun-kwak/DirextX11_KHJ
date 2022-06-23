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
	vertex.pos = XMFLOAT3(-_halfSize._x, _halfSize._y, 0); // �������
	_verices.push_back(vertex); // �����ϱ⋚���� emplace_back �� ���� �ȵ�
	vertex.pos = XMFLOAT3(_halfSize._x, _halfSize._y, 0); // �������
	_verices.push_back(vertex);
	vertex.pos = XMFLOAT3(_halfSize._x, -_halfSize._y, 0); // �����ϴ�
	_verices.push_back(vertex);
	vertex.pos = XMFLOAT3(-_halfSize._x, -_halfSize._y, 0); // �����ϴ�
	_verices.push_back(vertex);
	vertex.pos = XMFLOAT3(-_halfSize._x, _halfSize._y, 0); // �������
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
	if (_isCollision == true)
		_colorBuffer->SetColor(RED);
	else
		_colorBuffer->SetColor(GREEN);

	_center = GetLocalPosition();

	_transform->UpdateWorldBuffer();
	_colorBuffer->Update();
}

void RectCollider::Render()
{
	_transform->SetWorldBuffer(0);
	_colorBuffer->SetPSBuffer(0);

	_vertexBuffer->IASet(0);
	DEVICE_CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	_vertexShader->Set();
	_pixelShader->PsSet();

	DEVICE_CONTEXT->Draw(_verices.size(), 0);
}

bool RectCollider::IsCollision(shared_ptr<RectCollider> rect, bool obb)
{
	if (obb)
		return OBB(rect);
	else
		return AABB(rect);
}

bool RectCollider::IsCollision(const Vector2& pos)
{
	if (pos._x < Left() || pos._x > Right())
		return _isCollision = false;

	if (pos._y > Top() || pos._y < Bottom())
		return _isCollision = false;

	return _isCollision = true;
}

RectCollider::ObbDesc RectCollider::GetObb()
{
	// OBB �浹
	ObbDesc obbDesc;

	obbDesc._position = GetWorldPosition();

	obbDesc._lenght[0] = _halfSize._x * _transform->GetScale()._x;
	obbDesc._lenght[1] = _halfSize._y * _transform->GetScale()._y;

	XMFLOAT4X4 world;
	XMStoreFloat4x4(&world, _transform->GetMatrix());
	obbDesc._direction[0] = { world._11,world._12 };
	obbDesc._direction[1] = { world._21,world._22 };

	obbDesc._direction[0].Normallize();
	obbDesc._direction[1].Normallize();


	return obbDesc;
}

bool RectCollider::AABB(shared_ptr<RectCollider> rect)
{
	if (rect->Left() < this->Right() && rect->Right() > this->Left() &&
		rect->Bottom() < this->Top() && rect->Top() > this->Bottom())
		return _isCollision = true;

	return _isCollision = false;
}

bool RectCollider::OBB(shared_ptr<RectCollider> rect)
{
	ObbDesc obbA = GetObb();
	ObbDesc obbB = rect->GetObb();

	// A�� ���� ������ ���� ����, ���� ����
	Vector2 nea1 = obbA._direction[0]; // �� ����
	Vector2 ea1 = nea1 * obbA._lenght[0]; // �ٲﺤ��
	Vector2 nea2 = obbA._direction[1]; // �� ����
	Vector2 ea2 = nea2 * obbA._lenght[1]; // �ٲﺤ��

	// B�� ���� ������ ���� ����, ���� ����
	Vector2 neb1 = obbB._direction[0]; // �� ����
	Vector2 eb1 = neb1 * obbB._lenght[0]; // �ٲﺤ��
	Vector2 neb2 = obbB._direction[1]; // �� ����
	Vector2 eb2 = neb2 * obbB._lenght[1]; // �ٲﺤ��

	// A�� ������ B�� ���� ������ ����
	Vector2 distance = obbA._position - obbB._position;

	// A X��
	float lengthA = ea1.Length();
	float lengthB = SepareateAxis(nea1, eb1, eb2); // ���簢���� �������� �����ϰ� ����
	float length = abs(distance.Dot(nea1)); // ���� ������ �Ÿ�(����ȭ)
	if (length > lengthA + lengthB)
		return _isCollision = false;

	// A Y��
	lengthA = ea2.Length();
	lengthB = SepareateAxis(nea2, eb1, eb2); // ���簢���� �������� �����ϰ� ����
	length = abs(distance.Dot(nea2)); // ���� ������ �Ÿ�(����ȭ)
	if (length > lengthA + lengthB)
		return _isCollision = false;

	// B X��
	lengthA = SepareateAxis(nea1, eb1, eb2);
	lengthB = ea1.Length(); // ���簢���� �������� �����ϰ� ����
	length = abs(distance.Dot(nea1)); // ���� ������ �Ÿ�(����ȭ)
	if (length > lengthA + lengthB)
		return _isCollision = false;

	// B Y��
	lengthA = SepareateAxis(nea2, eb1, eb2); 
	lengthB = ea1.Length();// ���簢���� �������� �����ϰ� ����
	length = abs(distance.Dot(nea2)); // ���� ������ �Ÿ�(����ȭ)
	if (length > lengthA + lengthB)
		return _isCollision = false;

	return _isCollision = true;
}

float RectCollider::SepareateAxis(Vector2 separate, Vector2 e1, Vector2 e2)
{

	float r1 = abs(separate.Dot(e1));
	float r2 = abs(separate.Dot(e2));

	return r1 + r2;
}
