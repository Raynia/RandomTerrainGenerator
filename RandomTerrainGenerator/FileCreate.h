#pragma once
#include "Terrain.h"

class FileCreate
{
private:
	Terrain *CreatedTerrain;		// ������ ������ �����ϴ� ���� Ŭ����

public:
	FileCreate();
	~FileCreate();

	// ���� ����
	Terrain *CreateTerrain(int Seed);
};

