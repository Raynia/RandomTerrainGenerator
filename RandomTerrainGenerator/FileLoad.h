#pragma once
#define _AFXDLL
#include <fstream>
#include "Terrain.h"
#include "ErrorFunction.h"

class FileLoad
{
private:
	std::ifstream File;	// ������ ����Ǿ� �ִ� ���� / .ter ����

public:
	FileLoad();
	~FileLoad();

	// ����� ���� ���Ͽ��� ������ �ҷ���
	Terrain *LoadFile(const char *FileTitle, Terrain *nTerrain);
};

