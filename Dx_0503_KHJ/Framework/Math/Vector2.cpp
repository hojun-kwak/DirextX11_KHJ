#include "framework.h"
#include "Vector2.h"

Vector2 Vector2::operator+(const Vector2& value) const
{
	return Vector2(x + value.x, y + value.y);
}

Vector2& Vector2::operator+=(const Vector2& value)
{
	this->x += value.x;
	this->y += value.y;

	return *this;
}

Vector2 Vector2::operator-(const Vector2& value) const
{
	Vector2 result;
	result.x = this->x - value.x;
	result.y = this->y - value.y;

	return result;
	//return Vector2(_x - value._x, _y - value._y);
}

Vector2& Vector2::operator-=(const Vector2& value)
{
	this->x -= value.x;
	this->y -= value.y;

	return *this;
}

Vector2 Vector2::operator*(const float& value) const
{
	return Vector2(x * value, y * value);
}

Vector2& Vector2::operator*=(const float& value)
{
	this->x *= value;
	this->y *= value;

	return *this;
}

bool Vector2::operator==(const Vector2 value) const
{
	if ((this->x == value.x) &&
		(this->y == value.y))
	{
		return true;
	}
	return false;
}

bool Vector2::operator!=(const Vector2 value) const
{
	return !(this->operator==(value));
}

bool Vector2::operator<(const Vector2& value) const
{
	if (y != value.y)
		return y < value.y;
	return x < value.x;
}

float Vector2::Length() const
{
	return sqrtf(x*x + y*y);
}

float Vector2::Distance(const Vector2& pos) const
{
	float w = pos.x - x;
	float h = pos.y - y;

	return sqrtf(w * w + h * h);
}

Vector2 Vector2::NormalVector()
{
	float length = Length();
	return Vector2(x/length, y/length);
}

void Vector2::Normallize()
{
	float length = Length();
	x /= length;
	y /= length;
}

float Vector2::Dot(const Vector2& value)
{
	return x * value.x + y * value.y;
}

float Vector2::Shadow(const Vector2& floor)
{
	float f_length = sqrtf(floor.x * floor.x + floor.y * floor.y);
	Vector2 E_floor = Vector2(floor.x / f_length, floor.y / f_length);
	return this->Dot(E_floor);
}

float Vector2::Cross(const Vector2& value)
{
	return x*value.y - value.x * y;
}

float Vector2::Angle()
{
	return atan2(y, x);
}

void Vector2::YAxisSymmetry()
{
	std::swap(x, y);
}

int Vector2::Manhattan(const Vector2& value) const
{
	return abs(value.x - x) + abs(value.y - y);
}
