cbuffer Color : register(b0)
{
	float4 color;
}

// �ٲ� ������ ������
struct PixelInput
{
	float4 pos : SV_POSITION;
};

// SV_TARGET : �׸��� = �ĸ� ����
float4 PS(PixelInput input) : SV_TARGET
{
	return color;
}