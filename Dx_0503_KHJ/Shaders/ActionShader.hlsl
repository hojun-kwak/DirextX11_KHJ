cbuffer Action : register(b0)
{
	float2 size;
	float2 startPos;
	float2 maxSize;
	float2 padding;
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
	float2 uv;

	uv.x = input.uv.x / (maxSize.x / size.x) + (startPos.x / maxSize.x);
	uv.y = input.uv.y / (maxSize.y / size.y) + (startPos.y / maxSize.y);

	float4 result = map.Sample(samp,uv);

	return result;
}