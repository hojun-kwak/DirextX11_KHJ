#pragma once
class Texture
{
public:
	static shared_ptr<Texture> Add(wstring file);
	static void Delete();
	void Set(UINT slot);
	const class Vector2 GetSize();

private:
	Texture(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv, ScratchImage image);
	~Texture();

	wstring _file;
	ScratchImage _image;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _srv;

	static unordered_map<wstring, shared_ptr<Texture>> _texturesMap;
};

