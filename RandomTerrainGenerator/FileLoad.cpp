#include "FileLoad.h"

FileLoad::FileLoad()
{
}

FileLoad::~FileLoad()
{
}

// 저장된 이진 파일에서 지형을 불러옴
Terrain *FileLoad::LoadFile(const char *FileTitle, Terrain *nTerrain)
{
	nTerrain = new Terrain();		// 불러온 지형을 저장할 지형 클래스
	Block block;
	time_t CreatedTime;			// 지형이 생성된 시간
	unsigned int seed;				// 지형의 시드
	int AreaInTerrain, tempInt1, tempInt2;	// 지형 내의 에리어 수 와 임시값
	this->File.open(FileTitle,std::ios_base::in | std::ios_base::binary);
	if (!File.is_open())				// 파일을 열지 못했을 경우
	{
		ShowError(0x000001, FileTitle);
		nTerrain = NULL;
	}
	else
	{
		File.read((char *)&CreatedTime, sizeof(time_t));
		nTerrain->SetCreatedTime(CreatedTime);
		File.read((char *)&seed, sizeof(unsigned int));
		nTerrain->SetRandomNumber(seed);
		File.read((char*)&AreaInTerrain, sizeof(int));

		for (int sp1 = 0; sp1 < AreaInTerrain; sp1++)		// 에리어 불러오기
		{
			File.read((char*)&tempInt1, sizeof(int));		// 에리어의 지형 X좌표
			File.read((char*)&tempInt2, sizeof(int));		// 에리어의 지형 Z좌표
			Area *tempArea = new Area(tempInt1,tempInt2);
			File.read((char*)&tempInt1, sizeof(int));
			tempArea->SetBiome(tempInt1);
			for (int sp2 = 0; sp2 < 2; sp2++) 
			{
				for (int sp3 = 0; sp3 < 2; sp3++)
				{
					File.read((char*)&tempArea->BlockInArea[sp2][sp3], sizeof(Block));
				}
			}
			nTerrain->InsertArea(tempArea);
		}
	}
	File.close();
	return nTerrain;
}