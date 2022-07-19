#pragma once

struct FontBrushDesc
{
	XMFLOAT4 _color;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> _brush;

	bool operator==(const FontBrushDesc& value)
	{
		return _color.x == value._color.x && _color.y == value._color.y
			&& _color.z == value._color.z && _color.w == value._color.w;
	}
};

struct FontTextDesc
{
	wstring _font;
	float _fontSize;

	DWRITE_FONT_WEIGHT	 _weight;
	DWRITE_FONT_STYLE	 _style;
	DWRITE_FONT_STRETCH	 _stretch;

	Microsoft::WRL::ComPtr<IDWriteTextFormat> _format;

	bool operator==(const FontTextDesc& value)
	{
		bool b = true;

		b &= (_font == value._font);
		b &= (_fontSize == value._fontSize);
		b &= (_weight == value._weight);
		b &= (_style == value._style);
		b &= (_stretch == value._stretch);

		return b;
	}
};

using namespace Microsoft::WRL;

class DirectWrite
{
public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new DirectWrite();
	}
	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}
	static DirectWrite* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
	}

	void RenderText(wstring text, RECT rect, float fontSize = 20.0f,
		wstring font = L"»ﬁ∏’µ’±Ÿ«ÏµÂ∂Û¿Œ ∫∏≈Î",
		XMFLOAT4 color = XMFLOAT4(1, 1, 1, 1),
		DWRITE_FONT_WEIGHT weight = DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE stlye = DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH stretch = DWRITE_FONT_STRETCH_NORMAL);

	ComPtr<ID2D1DeviceContext> GetDeviceContext() { return _deviceContext; }

private:
	DirectWrite();
	~DirectWrite();

	ComPtr<ID2D1Factory1>		 _factory;
	ComPtr<IDWriteFactory>		 _writeFactory;

	Microsoft::WRL::ComPtr<ID2D1Device>			 _device;
	ComPtr<ID2D1DeviceContext>	 _deviceContext;

	ComPtr<ID2D1Bitmap1>		 _targetBitMap;

	vector<FontBrushDesc>		 _fontBrushes;
	vector<FontTextDesc>		 _fontTexts;

	static DirectWrite* _instance;
};

