#include "FileLoad.h"

FileLoad::FileLoad()
{
}

FileLoad::~FileLoad()
{
}

// ����� ���� ���Ͽ��� ������ �ҷ���
Terrain *FileLoad::LoadFile(const char *FileTitle, Terrain *nTerrain)
{
	nTerrain = new Terrain();		// �ҷ��� ������ ������ ���� Ŭ����
	Block block;
	time_t CreatedTime;			// ������ ������ �ð�
	unsigned int seed;				// ������ �õ�
	int AreaInTerrain, tempInt1, tempInt2;	// ���� ���� ������ �� �� �ӽð�
	this->File.open(FileTitle,std::ios_base::in | std::ios_base::binary);
	if (!File.is_open())				// ������ ���� ������ ���
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

		for (int sp1 = 0; sp1 < AreaInTerrain; sp1++)		// ������ �ҷ�����
		{
			File.read((char*)&tempInt1, sizeof(int));		// �������� ���� X��ǥ
			File.read((char*)&tempInt2, sizeof(int));		// �������� ���� Z��ǥ
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