#include "FileSave.h"

FileSave::FileSave()
{
}

FileSave::~FileSave()
{
}

// ������ ���� ���Ϸ� ����
void FileSave::SaveFile(const char *FileTitle, Terrain *nTerrain) {
	Area *area = NULL;
	int tempInt = 0;
	time_t createdTime;		// ������ ������ �ð�
	unsigned int seed;			// ���� �õ尪
	int areaInTerrain;			// ������ ������ �ִ� �������� ��
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
			for (int sp1 = 0; sp1 < areaInTerrain; sp1++)		// ������ ���� ����
			{
				area = nTerrain->GetAreaAt(sp1);
				tempInt = area->GetXinTerrain();					// �������� ���� X��ǥ
				File.write((char*)&tempInt, sizeof(int));
				tempInt = area->GetZinTerrain();					// �������� ���� Z��ǥ
				File.write((char*)&tempInt, sizeof(int));
				tempInt = area->GetBiome();						// ������ ���̿� ��
				File.write((char*)&tempInt, sizeof(int));
				for (int sp2 = 0; sp2 < 2; sp2++)					// �� ����� ����
				{
					for (int sp3 = 0; sp3 < 2; sp3++)
					{
						File.write((char*)&area->BlockInArea[sp2][sp3], sizeof(Block));		//�������̸�
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