#pragma once
class BinaryWriter
{
public:
	BinaryWriter(wstring filePath);
	~BinaryWriter();

	void Int(int data);
	void Uint(UINT data);
	void Float(float data);
	void String(string data);

	void Byte(void* data, UINT dataSize);

private:
	HANDLE _file;
	DWORD _size;
};

