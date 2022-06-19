#include "framework.h"
#include "Vector2.h"

Vector2 Vector2::operator+(const Vector2& value)
{
	return Vector2(_x + value._x, _y + value._y);
}

Vector2& Vector2::operator+=(const Vector2& value)
{
	this->_x += value._x;
	this->_y += value._y;

	return *this;
}

Vector2 Vector2::operator-(const Vector2& value)
{
	Vector2 result;
	result._x = this->_x - value._x;
	result._y = this->_y - value._y;

	return result;
	//return Vector2(_x - value._x, _y - value._y);
}

Vector2& Vector2::operator-=(const Vector2& value)
{
	this->_x -= value._x;
	this->_y -= value._y;

	return *this;
}

Vector2 Vector2::operator*(const float& value)
{
	return Vector2(_x * value, _y * value);
}

XMFLOAT2 Vector2::operator-(const XMFLOAT2& value)
{
	return XMFLOAT2(_x - value.x, _y - value.y);
}

bool Vector2::operator==(const Vector2 value)
{
	if ((this->_x == value._x) &&
		(this->_y == value._y))
	{
		return true;
	}
	return false;
}

bool Vector2::operator!=(const Vector2 value)
{
	return !(this->operator==(value));
}

bool Vector2::operator<(const Vector2& value) const
{
	if (_y != value._y)
		return _y < value._y;
	return _x < value._x;
}

float Vector2::Length() const
{
	return sqrtf(_x*_x + _y*_y);
}

float Vector2::Distance(const Vector2& pos)
{
	float w = pos._x - _x;
	float h = pos._y - _y;

	return sqrtf(w * w + h * h);
}

Vector2 Vector2::NormalVector()
{
	float length = Length();
	return Vector2(_x/length, _y/length);
}

void Vector2::Normallize()
{
	float length = Length();
	_x /= length;
	_y /= length;
}

float Vector2::Dot(const Vector2& value) const
{
	return _x * value._x + _y * value._y;
}

float Vector2::Shadow(const Vector2& floor)
{
	float f_length = sqrtf(floor._x * floor._x + floor._y * floor._y);
	Vector2 E_floor = Vector2(floor._x / f_length, floor._y / f_length);
	return this->Dot(E_floor);
}

float Vector2::Cross(const Vector2& value)
{
	return _x*value._y - value._x * _y;
}

float Vector2::Angle() const
{
	return atan2(_y, _x);
}

float Vector2::Angle(const Vector2& value) const
{
	// cos?
	// ³»Àû = cos(a) x A x B
	float D = this->Dot(value);
	float cos = D / (this->Length() * value.Length());

	return acos(cos);
}

void Vector2::YAxisSymmetry()
{
	std::swap(_x, _y);
}

int Vector2::Manhattan(const Vector2& value) const
{
	return abs(value._x - _x) + abs(value._y - _y);
}
