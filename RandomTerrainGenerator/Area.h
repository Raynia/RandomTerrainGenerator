#pragma once
#include <afx.h>
#include <afxwin.h>
#include "Block.h"

class Area
{
public:
	// 에리어 내의 블록 2x2
	Block BlockInArea[2][2];
private:
	int xInTerrain, zInTerrain, biome;		// 지형내 X,Z 좌표 및 에리어의 바이옴 값

public:
	Area();
	Area(unsigned int seed);
	Area(int xInTerrain, int zInTerrain);
	~Area();

	// 에리어의 블록 생성
	void CreateBlock();

	// 에리어의 지형 X좌표 받아오기
	int GetXinTerrain();

	// 에리어의 지형 Z좌표 받아오기
	int GetZinTerrain();

	// 에리어의 바이옴 설정
	void SetBiome(int biome);

	// 에리어의 바이옴 받아오기
	int GetBiome();
};

