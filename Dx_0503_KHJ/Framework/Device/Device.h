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

	// ������ �ڵ�
	HWND _hWnd;

	// ���� �ñ�� �������� ���� ��ǥ �̱�
	Microsoft::WRL::ComPtr<ID3D11Device> _device; // ��ǻ���� �ϵ���� ��� ����, ���ҽ� �Ҵ�
	// ��Ʈ���� ���������� �ٹ̰� �����ִ�...���Ⱑ
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> _deviceContext; // ������ ��� ����
	// -> ���ҽ��� �׷��� ���������ο� ���ε�, GPU�� ������ ������ ��� ����

	Microsoft::WRL::ComPtr<IDXGISwapChain> _swapChain;
	// �����
	// Dx�� �������̽��ν� 1�� �̻��� ǥ���� ������ �� �ִ�.
	// ������ ǥ��(����, �ؽ���)�� ����ϱ� ���� �����͸� �����Ѵ�.

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _RenderTargetView;
	// �ĸ���۸޸𸮸� ����Ű�� ������
};