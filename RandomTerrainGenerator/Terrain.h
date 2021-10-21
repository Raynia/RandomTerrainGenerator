#pragma once
#include "AllInOne.h"
#include "Area.h"
#include "Block.h"
#include "Hash.h"

class Terrain
{
private:
	time_t TerrainCreatedTime;					// ������ ������ �ð�
	std::vector<Area*> AreaInTerrain;		// ��������� ������ ������ ����� ����
	Hash hashTable;								// ����� ����� ������ �ε����� (X,Z) ��ǥ�� �������� �ؽ� ���̺�
	unsigned int TerrainSeed, BiomeSeed;	// ���� �õ�� ���̿� �õ�
	int p[512], permutation[256];				// ���̿� ����
	Block InitBlock;									// Block �ʱ�ȭ�� Block

public:
	Terrain();
	~Terrain();

	// (X,Z) ��ǥ�� ������ ������ ����
	Area *CreateArea(int xInTerrain, int zInTerrain);

	// ����� ������ ���Ϳ� ����
	void InsertArea(Area *area);

	// ���� �ʱ�ȭ : 7x7 ������ ����
	void InitTerrain();

	// ���� �ȿ� ���Ե� ������ ���� �޾ƿ���
	int GetAreaSize();

	// ���� ���� (X,Z) ��ǥ�� ������ ������ �ֺ����� ������ ����
	void UpdateArea(int xInTerrain, int zInTerrain);

	// ���� ���� (X,Z) ��ǥ�� ������ ����� �ִ��� Ȯ��
	bool IsAreaInTerrain(int xInTerrain, int zInTerrain);

	// ���̿�,���� ������ �����ϴ� �õ尪�� ���� �ϰ� ���� ����
	void SetRandomNumber(unsigned int Seed);

	// ���� �õ带 �޾ƿ���
	int GetRandomNumber();

	// ������ ������ �ð� �ʱ�ȭ
	void InitCreatedTime();

	// ������ ������ �ð��� ����
	void SetCreatedTime(time_t c_time);

	// ������ ������ �ð��� �޾ƿ���
	time_t GetCreatedTime();

	// ������ ���� �ȿ� index+1 ��° �����ϴ� ������ �ּ� �޾ƿ���
	Area *GetAreaAt(int index);

	// ������ ���� �ȿ� �����ϴ� (X,Z) ��ǥ�� ������ ������ �ּ� �޾ƿ���
	Area *GetAreaAt(int xInTerrain, int zInTerrain);
private:
	int GetBiome(float X, float Z);
	float Noise(float x, float y, float z);
	float Fade(float t);
	float Lerp(float t, float a, float b);
	float Grad(int hash, float x, float y, float z);
};

