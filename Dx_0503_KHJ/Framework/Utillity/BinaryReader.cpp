#include "framework.h"
#include "BinaryReader.h"

BinaryReader::BinaryReader(wstring filePath)
	:_size(0)
{
	_file = CreateFile(filePath.c_str(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
}

BinaryReader::~BinaryReader()
{
	CloseHandle(_file);
}

int BinaryReader::Int()
{
	int temp;

	// assert -> false 반환시 강제 종료

	if (ReadFile(_file, &temp, sizeof(int), OUT & _size, nullptr))
		return temp;

	return 0;

}

UINT BinaryReader::Uint()
{
	UINT temp;

	if (ReadFile(_file, &temp, sizeof(UINT), OUT & _size, nullptr))
		return temp;

	return 0;
}

float BinaryReader::Float()
{
	float temp;

	if (ReadFile(_file, &temp, sizeof(float), OUT & _size, nullptr))
		return temp;

	return 0;
}

string BinaryReader::String()
{
	UINT size = Uint();
	char* temp = new char[size + 1];
	if (ReadFile(_file, &temp, sizeof(char), OUT & _size, nullptr))
		return temp;

	return "";
}

// 포인터로 생성하고 포인터로 접근
void BinaryReader::Byte(void** data, UINT dataSize)
{
	(ReadFile(_file, *data, dataSize, OUT & _size, nullptr));
}
