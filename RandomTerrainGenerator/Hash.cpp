#include "Hash.h"



Hash::Hash()
{
}


Hash::~Hash()
{
}

// (X,Z)�� ��ǥ���� ������ �������� ���� �޾ƿ���
int Hash::GetAreaAddress(int XinTerrain, int ZinTerrain)
{
	int HashValue = GetHashValue(XinTerrain, ZinTerrain);
	int result = GetVector(XinTerrain, ZinTerrain, HashValue);
	return result;
}

// �ؽ��� �����Ͽ� �޾ƿ���
int Hash::GetHashValue(int XinTerrain, int ZinTerrain)
{
	int result = XinTerrain ^ ZinTerrain;
	result *= 3506;
	result = (XinTerrain * 1435 + ZinTerrain * 15) ^ result;
	result = result % 1013;
	result = result < 0 ? result * -1 : result;
	return result;
}

// (X,Z)�� ��ǥ�� ������ �������� �������� ��ǥ�� �ؽ� ���̺� ����
void Hash::InsertValue(int XinTerrain, int ZinTerrain,int index)
{
	int HashValue = GetHashValue(XinTerrain, ZinTerrain);	//�ؽ��� �޾ƿ���
	InsertVector(XinTerrain, ZinTerrain, HashValue,index);
}

// ���̺��� (X,Z) ��ǥ�� ������ �������� ���� �޾ƿ���
int Hash::GetVector(int XinTerrain, int ZinTerrain, int HashValue)
{
	int result = -1;	// �ش� ����� ���� ��� -1�� ��ȯ
	std::vector< std::pair<int, std::pair<int, int> > >::iterator iter = table[HashValue].begin();
	for (; iter != table[HashValue].end(); iter++)	// ���̺� ��ȸ
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

// �ؽ� ���̺� �� ����
void Hash::InsertVector(int XinTerrain, int ZinTerrain, int HashValue,int index)
{
	table[HashValue].push_back(std::make_pair(index,std::make_pair(XinTerrain,ZinTerrain)));
}