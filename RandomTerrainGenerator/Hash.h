#pragma once
#include "AllInOne.h"
class Hash
{
private:
	// 에리어 순서와 에리어 좌표 해쉬 테이블
	std::array<std::vector<std::pair<int, std::pair<int, int> > >, 1013 > table;

public:
	Hash();
	~Hash();

	// (X,Z)의 좌표값을 가지는 에리어의 순서 받아오기
	int GetAreaAddress(int XinTerrain, int ZinTerrain);

	// (X,Z)의 좌표를 가지는 에리어의 순서값과 좌표를 해쉬 테이블에 삽입
	void InsertValue(int XinTerrain, int ZinTerrain,int index);
private:
	// 해쉬값 생성하여 받아오기
	int GetHashValue(int XinTerrain, int ZinTerrain);

	// 테이블에서 (X,Z) 좌표를 가지는 에리어의 순서 받아오기
	int GetVector(int XinTerrain, int ZinTerrain, int HashValue);

	// 해쉬 테이블에 값 삽입
	void InsertVector(int XinTerrain, int ZinTerrain, int HashValue,int index);
};

