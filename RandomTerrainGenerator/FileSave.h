#pragma once
#define _AFXDLL
#include "AllInOne.h"
#include "Terrain.h"
#include "ErrorFunction.h"

class FileSave
{
private:
	std::ofstream File;	// 지형이 저장될 이진 파일 / .ter 파일

public:
	FileSave();
	~FileSave();

	// 지형을 이진 파일로 저장
	void SaveFile(const char *FileTitle, Terrain *nTerrain);
};

