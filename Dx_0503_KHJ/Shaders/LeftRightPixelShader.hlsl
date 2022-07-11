cbuffer IsRight : register(b0)
{
	int isRight;
	int value1;
	int value2;
	int value3;
}

Texture2D map : register(t0); // srv(���̴� ���ҽ� ��)
SamplerState samp : register(s0); // sampler

// �ٲ� ������ ������
struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

// SV_TARGET : �׸��� = �ĸ� ����
float4 PS(PixelInput input) : SV_TARGET
{
	float4 result;

	if (isRight == 0)
		result = map.Sample(samp, input.uv);
	else
	{
		input.uv.x = 1 - input.uv.x;
		input.uv.y = 1 - input.uv.y;

		result = map.Sample(samp, input.uv);
	}

	return result;
};