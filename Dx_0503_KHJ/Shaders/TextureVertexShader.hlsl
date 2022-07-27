cbuffer World : register(b0)
{
	matrix world;
}

cbuffer View : register(b1)
{
	matrix view;
}

cbuffer Projection : register(b2)
{
	matrix projection;
}

struct VertexInput
{
	float4 pos : POSITION;
	float2 uv : UV;
};

struct VertexOutput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

// VertexShader
// SV : System Value
VertexOutput VS(VertexInput input)
{
	matrix wvp = mul(world, view);
	wvp = mul(wvp, projection);

	VertexOutput output;
	output.pos = mul(input.pos, wvp);

	// 이부분만 고쳐주면 좌우반전 가능
	//input.uv.x = 1 - input.uv.x;
	output.uv = input.uv;

	return output;
}