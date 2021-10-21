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

// 에리어 내의 블록 생성
void Area::CreateBlock()
{
	for (int Z = 0; Z < 2; Z++) {
		for (int X = 0; X < 2; X++) {
			BlockInArea[Z][X].SetBlock(X + (2 * this->xInTerrain), Z + (2 * this->zInTerrain),X,Z, 0.025, 40.0,this->biome);
		}
	}
}

// 에리어의 지형 X좌표 받아오기
int Area::GetXinTerrain() 
{ 
	return this->xInTerrain; 
}

// 에리어의 지형 Z좌표 받아오기
int Area::GetZinTerrain() 
{
	return this->zInTerrain;
}

// 에리어의 바이옴 설정
void Area::SetBiome(int biome)
{
	this->biome = biome; 
}

// 에리어의 바이옴 받아오기
int Area::GetBiome()
{ 
	return this->biome;
}