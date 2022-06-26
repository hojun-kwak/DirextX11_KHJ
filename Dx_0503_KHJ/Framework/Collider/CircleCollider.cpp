#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(const float radius)
	:_radius(radius)
{
	CreateData();
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::CreateData()
{
	for (int i = 0; i < 360; i++)
	{
		float angle = i * PI / 180;

		float cosSeta = cos(angle) * _radius;
		float sinSeta = sin(angle) * _radius;
		_verices.emplace_back(cosSeta, sinSeta);
	}
	

	_vertexShader = make_shared<VertexShader>(L"Shaders/ColliderShader/ColliderVertexShader.hlsl");
	_pixelShader = make_shared<PixelShader>(L"Shaders/ColliderShader/ColliderPixelShader.hlsl");

	_vertexBuffer = make_shared<VertexBuffer>(_verices.data(), sizeof(VertexPos), _verices.size());
	_colorBuffer = make_shared<ColorBuffer>();
	_colorBuffer->SetColor(GREEN);

	_transform = make_shared<Transform>();
	_parent = nullptr;
}

void CircleCollider::Update()
{
	_center = GetLocalPosition();
	_transform->UpdateWorldBuffer();
	_colorBuffer->Update();
}

void CircleCollider::Render()
{
	_transform->SetWorldBuffer(0);
	_colorBuffer->SetPSBuffer(0);

	_vertexBuffer->IASet(0);
	DEVICE_CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	_vertexShader->Set();
	_pixelShader->PsSet();

	DEVICE_CONTEXT->Draw(_verices.size(), 0);
}
