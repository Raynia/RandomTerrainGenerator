#pragma once
#define _AFXDLL
#include "AllInOne.h"
#include "Terrain.h"
#include "ErrorFunction.h"

class FileSave
{
private:
	std::ofstream File;	// ������ ����� ���� ���� / .ter ����

public:
	FileSave();
	~FileSave();

	// ������ ���� ���Ϸ� ����
	void SaveFile(const char *FileTitle, Terrain *nTerrain);
};

