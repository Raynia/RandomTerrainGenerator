#pragma once
#include "AllInOne.h"
#include "Area.h"
#include "Block.h"
#include "Hash.h"

class Terrain
{
private:
	time_t TerrainCreatedTime;					// 지형이 생성된 시간
	std::vector<Area*> AreaInTerrain;		// 에리어들이 생성된 순으로 저장된 벡터
	Hash hashTable;								// 에리어가 저장된 벡터의 인덱스와 (X,Z) 좌표의 에리어의 해시 테이블
	unsigned int TerrainSeed, BiomeSeed;	// 지형 시드와 바이옴 시드
	int p[512], permutation[256];				// 바이옴 난수
	Block InitBlock;									// Block 초기화용 Block

public:
	Terrain();
	~Terrain();

	// (X,Z) 좌표를 가지는 에리어 생성
	Area *CreateArea(int xInTerrain, int zInTerrain);

	// 에리어를 에리어 벡터에 삽입
	void InsertArea(Area *area);

	// 지형 초기화 : 7x7 에리어 생성
	void InitTerrain();

	// 지형 안에 포함된 에리어 개수 받아오기
	int GetAreaSize();

	// 지형 내에 (X,Z) 좌표를 가지는 에리어 주변으로 에리어 생성
	void UpdateArea(int xInTerrain, int zInTerrain);

	// 지형 내에 (X,Z) 좌표를 가지는 에리어가 있는지 확인
	bool IsAreaInTerrain(int xInTerrain, int zInTerrain);

	// 바이옴,지형 난수를 생성하는 시드값을 설정 하고 난수 생성
	void SetRandomNumber(unsigned int Seed);

	// 지형 시드를 받아오기
	int GetRandomNumber();

	// 지형이 생성된 시간 초기화
	void InitCreatedTime();

	// 지형이 생성된 시간을 설정
	void SetCreatedTime(time_t c_time);

	// 지형이 생성된 시간을 받아오기
	time_t GetCreatedTime();

	// 에리어 벡터 안에 index+1 번째 존재하는 에리어 주소 받아오기
	Area *GetAreaAt(int index);

	// 에리어 벡터 안에 존재하는 (X,Z) 좌표를 가지는 에리어 주소 받아오기
	Area *GetAreaAt(int xInTerrain, int zInTerrain);
private:
	int GetBiome(float X, float Z);
	float Noise(float x, float y, float z);
	float Fade(float t);
	float Lerp(float t, float a, float b);
	float Grad(int hash, float x, float y, float z);
};

