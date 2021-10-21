#pragma once
#include "AllInOne.h"
class Hash
{
private:
	// ������ ������ ������ ��ǥ �ؽ� ���̺�
	std::array<std::vector<std::pair<int, std::pair<int, int> > >, 1013 > table;

public:
	Hash();
	~Hash();

	// (X,Z)�� ��ǥ���� ������ �������� ���� �޾ƿ���
	int GetAreaAddress(int XinTerrain, int ZinTerrain);

	// (X,Z)�� ��ǥ�� ������ �������� �������� ��ǥ�� �ؽ� ���̺� ����
	void InsertValue(int XinTerrain, int ZinTerrain,int index);
private:
	// �ؽ��� �����Ͽ� �޾ƿ���
	int GetHashValue(int XinTerrain, int ZinTerrain);

	// ���̺��� (X,Z) ��ǥ�� ������ �������� ���� �޾ƿ���
	int GetVector(int XinTerrain, int ZinTerrain, int HashValue);

	// �ؽ� ���̺� �� ����
	void InsertVector(int XinTerrain, int ZinTerrain, int HashValue,int index);
};

