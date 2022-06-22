cbuffer Color : register(b0)
{
	float4 color;
}

// 바뀐 서식을 가져옴
struct PixelInput
{
	float4 pos : SV_POSITION;
};

// SV_TARGET : 그릴곳 = 후면 버퍼
float4 PS(PixelInput input) : SV_TARGET
{
	return color;
}