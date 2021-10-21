#include "Area.h"

Area::Area()
{

}

Area::Area(unsigned int seed)
{

}

Area::Area(int xInTerrain, int zInTerrain)
{
	this->xInTerrain = xInTerrain;
	this->zInTerrain = zInTerrain;
}

Area::~Area()
{
}

// ������ ���� ��� ����
void Area::CreateBlock()
{
	for (int Z = 0; Z < 2; Z++) {
		for (int X = 0; X < 2; X++) {
			BlockInArea[Z][X].SetBlock(X + (2 * this->xInTerrain), Z + (2 * this->zInTerrain),X,Z, 0.025, 40.0,this->biome);
		}
	}
}

// �������� ���� X��ǥ �޾ƿ���
int Area::GetXinTerrain() 
{ 
	return this->xInTerrain; 
}

// �������� ���� Z��ǥ �޾ƿ���
int Area::GetZinTerrain() 
{
	return this->zInTerrain;
}

// �������� ���̿� ����
void Area::SetBiome(int biome)
{
	this->biome = biome; 
}

// �������� ���̿� �޾ƿ���
int Area::GetBiome()
{ 
	return this->biome;
}