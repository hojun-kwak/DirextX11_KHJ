#pragma once
class Texture
{
public:
	Texture(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv, ScratchImage& image);
	~Texture();

	static shared_ptr<Texture> Add(wstring file);
	static shared_ptr<Texture> Add(wstring file, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv);

	static void Delete();
	void Set(UINT slot);
	class Vector2 GetSize();
private:

	wstring _file;
	ScratchImage _image;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _srv;

	static unordered_map<wstring, shared_ptr<Texture>> _texturesMap;
};

