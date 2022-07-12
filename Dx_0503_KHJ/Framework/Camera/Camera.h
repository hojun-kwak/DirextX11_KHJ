#pragma once
// vertexShader view�� �ѱ�
class Camera
{
public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new Camera();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static Camera* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
	}

	void Update();
	void PostRender();

	// ȭ�� ��鸲
	void ShakeStart(float magintude, float duration, float reduceDamping = 1.0f);
	void SetViewPort(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT);

	void SetProjectionBuffer(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT); // â��� ����

	void SetTarget(shared_ptr<Transform> target) { _target = target; }
	void SetLeftBottom(Vector2 value) { _leftBottom = value; }
	void SetRightTop(Vector2 value) { _rightTop = value; }

private:
	Camera();
	~Camera();
	
	void FreeMode();
	void FollowMode();
	void Shake();

private:
	shared_ptr<Transform> _transform;
	static Camera* _instance; // �̱���

	float _speed = 200.0f;
	float _zoomSpeed = 1.0f;

	shared_ptr<Transform> _target = nullptr;
	Vector2 _offset = CENTER;

	Vector2 _leftBottom;
	Vector2 _rightTop;

	float _duration = 0.0f;
	float _reduceDamping = 1.0f;
	float _magnitude = 0.0f; // �Ը�

	Vector2 _originPos;

	shared_ptr<MatrixBuffer> _projectionBuffer; // program���� ���� => ���⼭ ������ �ٽ���
};

