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
};

// ¹Ù²ï ¼­½ÄÀ» °¡Á®¿È
struct VertexOutput
{
	float4 pos : SV_POSITION;
};

// vertexShader
// sv = System Value
VertexOutput VS(VertexInput input)
{

	matrix wvp = mul(world, view);
	wvp = mul(wvp, projection);

	VertexOutput output;
	output.pos = mul(input.pos, wvp);

	return output;
}