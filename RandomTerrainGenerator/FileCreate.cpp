#include "FileCreate.h"



FileCreate::FileCreate()
{
}


FileCreate::~FileCreate()
{
}

// ���� ����
Terrain *FileCreate::CreateTerrain(int Seed)
{
	CreatedTerrain = new Terrain();
	CreatedTerrain->SetRandomNumber(Seed);
	CreatedTerrain->InitCreatedTime();
	CreatedTerrain->InitTerrain();

	return CreatedTerrain;
}