#include "framework.h"
#include "BinaryWriter.h"

BinaryWriter::BinaryWriter(wstring filePath)
	:_size(0)
{
	_file = CreateFile(filePath.c_str(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
}

BinaryWriter::~BinaryWriter()
{
	CloseHandle(_file);
}

void BinaryWriter::Int(int data)
{
	WriteFile(_file, &data, sizeof(int), &_size, nullptr);
}

void BinaryWriter::Uint(UINT data)
{
	WriteFile(_file, &data, sizeof(UINT), &_size, nullptr);
}

void BinaryWriter::Float(float data)
{
	WriteFile(_file, &data, sizeof(float), &_size, nullptr);
}

void BinaryWriter::String(string data)
{
	UINT(data.size());

	const char* str = data.c_str();

	WriteFile(_file, str, data.size(), &_size, nullptr);
}

void BinaryWriter::Byte(void* data, UINT dataSize)
{
	WriteFile(_file, data, dataSize, &_size, nullptr);
}
