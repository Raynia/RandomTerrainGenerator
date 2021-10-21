#pragma once
#define _AFXDLL
#include <fstream>
#include "Terrain.h"
#include "ErrorFunction.h"

class FileLoad
{
private:
	std::ifstream File;	// 지형이 저장되어 있는 파일 / .ter 파일

public:
	FileLoad();
	~FileLoad();

	// 저장된 이진 파일에서 지형을 불러옴
	Terrain *LoadFile(const char *FileTitle, Terrain *nTerrain);
};

