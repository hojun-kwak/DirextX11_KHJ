Texture2D map : register(t0); // srv(���̴� ���ҽ� ��)
SamplerState samp : register(s0); // sampler

// layout���� �״�� ������
struct VertexInput
{
	float4 pos : POSITION;
	float2 uv : UV;
};

// �ٲ� ������ ������
struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

// vertexShader
// sv = System Value
PixelInput VS(VertexInput input)
{
	PixelInput output;
	output.pos = input.pos;
	output.uv = input.uv;

	return output;
}

// SV_TARGET : �׸��� = �ĸ� ����
float4 PS(PixelInput input) : SV_TARGET
{
	// RGBA
	// �׸��� ©��
	//input.uv = input.uv / 2;
	// 
	//float4(1.0f, 0.7f, 0.0f, 1.0f);
	float4 result = map.Sample(samp,input.uv);
	// ���� ����
	//result.g = 1.0f;
	return result;
}