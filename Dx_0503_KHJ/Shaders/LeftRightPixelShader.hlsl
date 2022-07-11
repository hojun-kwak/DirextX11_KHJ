cbuffer IsRight : register(b0)
{
	int isRight;
	int value1;
	int value2;
	int value3;
}

Texture2D map : register(t0); // srv(쉐이더 리소스 뷰)
SamplerState samp : register(s0); // sampler

// 바뀐 서식을 가져옴
struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

// SV_TARGET : 그릴곳 = 후면 버퍼
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