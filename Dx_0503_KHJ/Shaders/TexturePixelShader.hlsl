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
	// RGBA
	// 그림이 짤림
	//input.uv = input.uv / 2;
	// 
	//float4(1.0f, 0.7f, 0.0f, 1.0f);
	float4 result = map.Sample(samp,input.uv);
	// 색깔 변경
	//result.g = 1.0f;
	return result;
}