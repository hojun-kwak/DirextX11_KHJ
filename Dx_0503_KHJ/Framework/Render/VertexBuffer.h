#pragma once
class VertexBuffer
{
public:
	VertexBuffer(void* data, UINT stride, UINT count, UINT offset = 0);
	~VertexBuffer();


	void IASet(int slot);

private:
	void CreateVertexBuffer(void* data);

	vector<VertexUV> _vertices;
	Microsoft::WRL::ComPtr<ID3D11Buffer> _vertexBuffer;

	UINT _count;
	UINT _stride;
	UINT _offset;
};

