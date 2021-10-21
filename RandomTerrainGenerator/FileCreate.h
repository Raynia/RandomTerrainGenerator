#pragma once
#include "Terrain.h"

class FileCreate
{
private:
	Terrain *CreatedTerrain;		// 생성한 지형을 저장하는 지형 클래스

public:
	FileCreate();
	~FileCreate();

	// 지형 생성
	Terrain *CreateTerrain(int Seed);
};

