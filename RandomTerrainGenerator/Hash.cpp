#include "Hash.h"



Hash::Hash()
{
}


Hash::~Hash()
{
}

// (X,Z)의 좌표값을 가지는 에리어의 순서 받아오기
int Hash::GetAreaAddress(int XinTerrain, int ZinTerrain)
{
	int HashValue = GetHashValue(XinTerrain, ZinTerrain);
	int result = GetVector(XinTerrain, ZinTerrain, HashValue);
	return result;
}

// 해쉬값 생성하여 받아오기
int Hash::GetHashValue(int XinTerrain, int ZinTerrain)
{
	int result = XinTerrain ^ ZinTerrain;
	result *= 3506;
	result = (XinTerrain * 1435 + ZinTerrain * 15) ^ result;
	result = result % 1013;
	result = result < 0 ? result * -1 : result;
	return result;
}

// (X,Z)의 좌표를 가지는 에리어의 순서값과 좌표를 해쉬 테이블에 삽입
void Hash::InsertValue(int XinTerrain, int ZinTerrain,int index)
{
	int HashValue = GetHashValue(XinTerrain, ZinTerrain);	//해쉬값 받아오기
	InsertVector(XinTerrain, ZinTerrain, HashValue,index);
}

// 테이블에서 (X,Z) 좌표를 가지는 에리어의 순서 받아오기
int Hash::GetVector(int XinTerrain, int ZinTerrain, int HashValue)
{
	int result = -1;	// 해당 에리어가 없는 경우 -1을 반환
	std::vector< std::pair<int, std::pair<int, int> > >::iterator iter = table[HashValue].begin();
	for (; iter != table[HashValue].end(); iter++)	// 테이블 순회
	{
		if ((*iter).second.first == XinTerrain &&		
			(*iter).second.second == ZinTerrain)	
		{
			result = (*iter).first;
			break;
		}
	}
	return result;
}

// 해쉬 테이블에 값 삽입
void Hash::InsertVector(int XinTerrain, int ZinTerrain, int HashValue,int index)
{
	table[HashValue].push_back(std::make_pair(index,std::make_pair(XinTerrain,ZinTerrain)));
}