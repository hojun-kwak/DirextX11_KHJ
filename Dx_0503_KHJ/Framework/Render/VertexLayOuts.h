#pragma once

struct VertexPos
{
	VertexPos()
		:pos(0, 0, 0)
	{}

	VertexPos(float x, float y)
		:pos(x, y,0)
	{}


	XMFLOAT3 pos;
};

struct VertexUV
{
	VertexUV()
		:pos(0,0,0)
		,uv(0,0)
	{}

	VertexUV(float x, float y, float u, float v)
		:pos(x,y,0)
		,uv(u,v)
	{}

	XMFLOAT3 pos;
	XMFLOAT2 uv;
};