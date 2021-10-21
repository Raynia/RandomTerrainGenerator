#pragma once
#include <afx.h>
#include <afxwin.h>
#include "Block.h"

class Area
{
public:
	// ������ ���� ��� 2x2
	Block BlockInArea[2][2];
private:
	int xInTerrain, zInTerrain, biome;		// ������ X,Z ��ǥ �� �������� ���̿� ��

public:
	Area();
	Area(unsigned int seed);
	Area(int xInTerrain, int zInTerrain);
	~Area();

	// �������� ��� ����
	void CreateBlock();

	// �������� ���� X��ǥ �޾ƿ���
	int GetXinTerrain();

	// �������� ���� Z��ǥ �޾ƿ���
	int GetZinTerrain();

	// �������� ���̿� ����
	void SetBiome(int biome);

	// �������� ���̿� �޾ƿ���
	int GetBiome();
};

