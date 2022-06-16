#pragma once
 class Vector2
{
public:
	Vector2() {}
	Vector2(float x, float y) : _x(x), _y(y) {}
	~Vector2() {}

	Vector2 operator+(const Vector2& value);
	Vector2& operator+=(const Vector2& value);
	Vector2 operator-(const Vector2& value);
	Vector2& operator-=(const Vector2& value);
	Vector2 operator*(const float& value);

	bool operator==(const Vector2 value);
	bool operator!=(const Vector2 value);

	bool operator<(const Vector2& value) const;

	float Length() const;
	float Distance(const Vector2& pos);

	Vector2 NormalVector();
	void Normallize();

	float Dot(const Vector2& value);
	float Shadow(const Vector2& floor);

	float Cross(const Vector2& value);

	void YAxisSymmetry();
	int Manhattan(const Vector2& value) const;

	float _x = 0.0f;
	float _y = 0.0f;
};

