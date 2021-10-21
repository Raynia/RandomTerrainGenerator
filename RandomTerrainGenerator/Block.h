#pragma once
#include "AllInOne.h"

class Block
{
	
public:
	float BlockHeight[32][32];	// 블록 높이맵
private:
	int areaX, areaZ;				// 블록이 속한 에리어의 지형 좌표 (X,Z)
	int xInTerrain, zInTerrain;	// 블록의 지형 좌표(X,Z)
	int xInArea, zInArea;			// 블록의 에리어 좌표
	float heightFrequency, heightWeight;	// 블록의 높이 가중치, 높이 주파수


public:
	Block();
	Block(int Seed);
	~Block();

	// 지형 내 X좌표 받아오기
	int GetXinTerrain();

	// 지형 내 Y좌표 받아오기
	int GetZinTerrain();

	// 에리어 내 X좌표 받아오기
	int GetXinArea();

	// 에리어 내 Z좌표 받아오기
	int GetZinArea();

	// 주파수 받아오기
	float GetFrequency();

	// 가중치 받아오기
	float GetWeight();

	// 블록 속성 설정
	void SetBlockHeader(int xInTerrain, int zInTerrain, int xInArea, int zInArea, float fre, float wei, int biome);

	// 블록 속성 설정 후 블록 생성
	void SetBlock(int xInTerrain, int zInTerrain, int xInArea, int zInArea, float fre, float wei, int biome);
private:
	// 블록 높이맵 생성
	void InitBlock(int biome);

	// 높이값 받아오기
	float GetHeight(float x, float z, float fre, float wei);
	float Noise(float x, float y, float z);
	float Fade(float t);
	float Lerp(float t, float a, float b);
	float Grad(int hash, float x, float y, float z);

private:
	static unsigned int blockCount;		// 블록 난수 초기화 여부
	static int p[512], permutation[256];	//블록 난수

public:
	// 블록 클래스 초기화
	static void BlockInit();
private:
	// 블록 난수 초기화
	static void InitRandom(int Seed);


};