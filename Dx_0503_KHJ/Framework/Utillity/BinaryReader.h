#pragma once
class BinaryReader
{
public:
	BinaryReader(wstring filePath);
	~BinaryReader();

	int Int();
	UINT Uint();
	float Float();
	string String();
	void Byte(void** data, UINT dataSize);


private:
	HANDLE _file;
	DWORD _size;
};

