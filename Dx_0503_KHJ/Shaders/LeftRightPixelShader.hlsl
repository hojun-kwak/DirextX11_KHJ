cbuffer IsRight : register(b0)
{
	int isRight;
	int value1;
	int value2;
	int value3;
}

Texture2D map : register(t0); // srv
SamplerState samp : register(s0); // sampler

struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

// SV_TARGET : 그릴 곳... 우리한테는 후면버퍼
float4 PS(PixelInput input) : SV_TARGET
{
	float4 result;

	if (isRight == 0)
	{
		result = map.Sample(samp, input.uv);
		return result;
	}

	input.uv.x = 1 - input.uv.x;

	result = map.Sample(samp, input.uv);

	return result;
}