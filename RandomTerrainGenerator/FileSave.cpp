#include "FileSave.h"

FileSave::FileSave()
{
}

FileSave::~FileSave()
{
}

// 지형을 이진 파일로 저장
void FileSave::SaveFile(const char *FileTitle, Terrain *nTerrain) {
	Area *area = NULL;
	int tempInt = 0;
	time_t createdTime;		// 지형이 생성된 시간
	unsigned int seed;			// 지형 시드값
	int areaInTerrain;			// 지형이 가지고 있는 에리어의 수
	if (nTerrain != NULL)
	{
		createdTime = nTerrain->GetCreatedTime();
		seed = nTerrain->GetRandomNumber();
		areaInTerrain = nTerrain->GetAreaSize();
		this->File.open(FileTitle, std::ios_base::out | std::ios_base::binary);
		if (!File.is_open())
		{
			ShowError(0x000001, FileTitle);
		}
		else {
			File.write((char*)&createdTime, sizeof(time_t));  
			File.write((char*)&seed, sizeof(unsigned int));	
			File.write((char*)&areaInTerrain, sizeof(int));
			for (int sp1 = 0; sp1 < areaInTerrain; sp1++)		// 에리어 정보 저장
			{
				area = nTerrain->GetAreaAt(sp1);
				tempInt = area->GetXinTerrain();					// 에리어의 지형 X좌표
				File.write((char*)&tempInt, sizeof(int));
				tempInt = area->GetZinTerrain();					// 에리어의 지형 Z좌표
				File.write((char*)&tempInt, sizeof(int));
				tempInt = area->GetBiome();						// 에리어 바이옴 값
				File.write((char*)&tempInt, sizeof(int));
				for (int sp2 = 0; sp2 < 2; sp2++)					// 각 블록을 저장
				{
					for (int sp3 = 0; sp3 < 2; sp3++)
					{
						File.write((char*)&area->BlockInArea[sp2][sp3], sizeof(Block));		//지형높이맵
					}
				}
			}
		}
	}
	else
	{
		ShowError(0x000004, FileTitle);
	}
	File.close();
}