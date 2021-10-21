#pragma once
#include "AllInOne.h"

class Block
{
	
public:
	float BlockHeight[32][32];	// ��� ���̸�
private:
	int areaX, areaZ;				// ����� ���� �������� ���� ��ǥ (X,Z)
	int xInTerrain, zInTerrain;	// ����� ���� ��ǥ(X,Z)
	int xInArea, zInArea;			// ����� ������ ��ǥ
	float heightFrequency, heightWeight;	// ����� ���� ����ġ, ���� ���ļ�


public:
	Block();
	Block(int Seed);
	~Block();

	// ���� �� X��ǥ �޾ƿ���
	int GetXinTerrain();

	// ���� �� Y��ǥ �޾ƿ���
	int GetZinTerrain();

	// ������ �� X��ǥ �޾ƿ���
	int GetXinArea();

	// ������ �� Z��ǥ �޾ƿ���
	int GetZinArea();

	// ���ļ� �޾ƿ���
	float GetFrequency();

	// ����ġ �޾ƿ���
	float GetWeight();

	// ��� �Ӽ� ����
	void SetBlockHeader(int xInTerrain, int zInTerrain, int xInArea, int zInArea, float fre, float wei, int biome);

	// ��� �Ӽ� ���� �� ��� ����
	void SetBlock(int xInTerrain, int zInTerrain, int xInArea, int zInArea, float fre, float wei, int biome);
private:
	// ��� ���̸� ����
	void InitBlock(int biome);

	// ���̰� �޾ƿ���
	float GetHeight(float x, float z, float fre, float wei);
	float Noise(float x, float y, float z);
	float Fade(float t);
	float Lerp(float t, float a, float b);
	float Grad(int hash, float x, float y, float z);

private:
	static unsigned int blockCount;		// ��� ���� �ʱ�ȭ ����
	static int p[512], permutation[256];	//��� ����

public:
	// ��� Ŭ���� �ʱ�ȭ
	static void BlockInit();
private:
	// ��� ���� �ʱ�ȭ
	static void InitRandom(int Seed);


};