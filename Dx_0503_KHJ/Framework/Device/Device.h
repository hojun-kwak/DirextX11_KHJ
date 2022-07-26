#pragma once
class Device
{
private:
	Device(HWND hWnd);
	~Device();
public:
	static void Create(HWND hWnd)
	{
		if (_instance == nullptr)
			_instance = new  Device(hWnd);
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;

		_instance = nullptr;
	}

	static Device* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;

		return nullptr;
	}

	void CreateDeviceAndSwapChain();
	void CreateBackBuffer();

	Microsoft::WRL::ComPtr<ID3D11Device> GetDevice()
	{
		return _device;
	}

	Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetDeviceContext()
	{
		return _deviceContext;
	}

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRenderTargetView()
	{
		return _RenderTargetView;
	}
	Microsoft::WRL::ComPtr<IDXGISwapChain> GetSwapChain() { return _swapChain; }

	void SetRenderTarget();

	void Clear(float R, float G, float B);
	void Present();

private:
	static Device* _instance;

	// 윈도우 핸들
	HWND _hWnd;

	// 외주 맡기고 실질적인 공사 대표 뽑기
	Microsoft::WRL::ComPtr<ID3D11Device> _device; // 컴퓨터의 하드웨어 기능 정검, 리소스 할당
	// 세트장을 실질적으로 꾸미고 보여주는...연출가
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> _deviceContext; // 렌더링 대상 결정
	// -> 리소스를 그래픽 파이프라인에 바인딩, GPU가 수행할 렌더링 명령 지시

	Microsoft::WRL::ComPtr<IDXGISwapChain> _swapChain;
	// 백버퍼
	// Dx의 인터페이스로써 1개 이상의 표면을 포함할 수 있다.
	// 각각의 표면(버퍼, 텍스쳐)을 출력하기 전에 데이터를 보관한다.

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _RenderTargetView;
	// 후면버퍼메모리를 가리키는 포인터
};