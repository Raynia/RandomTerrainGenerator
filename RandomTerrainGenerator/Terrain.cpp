#include "Terrain.h"

Terrain::Terrain()
{
}


Terrain::~Terrain()
{
	AreaInTerrain.clear();
}

// (X,Z) ��ǥ�� ������ ������ ����
Area *Terrain::CreateArea(int xInTerrain, int zInTerrain)
{
	Area *Temp = new Area(xInTerrain, zInTerrain);
	Temp->SetBiome(this->GetBiome(xInTerrain, zInTerrain));
	Temp->CreateBlock();
	AreaInTerrain.push_back(Temp);
	hashTable.InsertValue(xInTerrain, zInTerrain, AreaInTerrain.size() - 1);
	return Temp;
}

// ����� ������ ���Ϳ� ����
void Terrain::InsertArea(Area *area) 
{ 
	this->AreaInTerrain.push_back(area); 
	hashTable.InsertValue(area->GetXinTerrain(), area->GetZinTerrain(), AreaInTerrain.size() - 1);
}

// ���� �ʱ�ȭ : 7x7 ������ ����
void Terrain::InitTerrain()
{
	for (int Z = -3; Z <= 3; Z++) {
		for (int X = -3; X <= 3; X++) {
			CreateArea(X, Z);
		}
	}
}

// ���� �ȿ� ���Ե� ������ ���� �޾ƿ���
int Terrain::GetAreaSize() 
{
	return this->AreaInTerrain.size();
}

// ���� ���� (X,Z) ��ǥ�� ������ ������ �ֺ����� ������ ����
void Terrain::UpdateArea(int xInTerrain, int zInTerrain)
{
	for (int sp1 = xInTerrain - 3; sp1 <= xInTerrain + 3; sp1++) 
	{
		for (int sp2 = zInTerrain - 3; sp2 <= zInTerrain + 3; sp2++)
		{
			if (!IsAreaInTerrain(sp1, sp2))		// �ش� ����� ���� ��� ���� ����
			{
				CreateArea(sp1, sp2);
			}
		}
	}
}

// ���� ���� (X,Z) ��ǥ�� ������ ����� �ִ��� Ȯ��
bool Terrain::IsAreaInTerrain(int xInTerrain, int zInTerrain)
{
	Area *temp = NULL;
	bool isThere = false;
	for (std::vector<Area*>::iterator iter = AreaInTerrain.begin(); iter != AreaInTerrain.end(); iter++)
	{
		temp = *iter;
		if (temp->GetXinTerrain() == xInTerrain && temp->GetZinTerrain() == zInTerrain) {
			isThere = true;
			break;
		}
	}
	return isThere;
}

// ���̿�,���� ������ �����ϴ� �õ尪�� ���� �ϰ� ���� ����
void Terrain::SetRandomNumber(unsigned int Seed)
{
	this->TerrainSeed = Seed;
	this->BiomeSeed = UINT_MAX - Seed;
	srand(this->BiomeSeed);
	for (int i = 0; i < 256; i++) {
		permutation[i] = rand() % 255;
		p[256 + i] = p[i] = permutation[i];
	}
	Block InitRandom(this->TerrainSeed);		//���� ����
}

// ���� �õ带 �޾ƿ���
int Terrain::GetRandomNumber()
{ 
	return this->TerrainSeed;
}

// ������ ������ �ð� �ʱ�ȭ
void Terrain::InitCreatedTime() 
{ 
	this->TerrainCreatedTime = time(NULL); 
}

// ������ ������ �ð��� ����
void Terrain::SetCreatedTime(time_t c_time) 
{
	this->TerrainCreatedTime = c_time; 
}

// ������ ������ �ð��� �޾ƿ���
time_t Terrain::GetCreatedTime()
{ 
	return this->TerrainCreatedTime; 
}

// ������ ���� �ȿ� index+1 ��° �����ϴ� ������ �ּ� �޾ƿ���
Area *Terrain::GetAreaAt(int index) 
{
	return this->AreaInTerrain.at(index);
}

// ������ ���� �ȿ� �����ϴ� (X,Z) ��ǥ�� ������ ������ �ּ� �޾ƿ���
Area *Terrain::GetAreaAt(int xInTerrain, int zInTerrain)
{
	int address = hashTable.GetAreaAddress(xInTerrain, zInTerrain);
	if (address != -1)
	{
		return GetAreaAt(address);	// ����� ����� ������ �ּҸ� ��ȯ
	}
	else
	{
		return CreateArea(xInTerrain, zInTerrain);	// ����� ���� �ȿ� ���� ��� ���� ����
	}
}


int Terrain::GetBiome(float X, float Z) 
{
	int result = Noise(X*0.025, Z*0.025, 0) * 10;
	result = result < 0 ? (-result) % 10 : result % 10;
	return result;
}

float Terrain::Noise(float x, float y, float z) {
	int X = (int)floor(x) & 255, Y = (int)floor(y) & 255, Z = (int)floor(z) & 255;
	x -= floor(x);
	y -= floor(y);
	z -= floor(z);

	float u = Fade(x), v = Fade(y), w = Fade(z);

	int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z, B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

	return Lerp(w, Lerp(v, Lerp(u, Grad(p[AA], x, y, z), Grad(p[BA], x - 1, y, z)), Lerp(u, Grad(p[AB], x, y - 1, z), Grad(p[BB], x - 1, y - 1, z)))
		, Lerp(v, Lerp(u, Grad(p[AA + 1], x, y, z - 1), Grad(p[BA + 1], x - 1, y, z - 1)), Lerp(u, Grad(p[AB + 1], x, y - 1, z - 1), Grad(p[BB + 1], x - 1, y - 1, z - 1))));
}

float Terrain::Fade(float t) { return t * t*t*(t*(t * 6 - 15) + 10); }

float Terrain::Lerp(float t, float a, float b) { return a + t * (b - a); }

float Terrain::Grad(int hash, float x, float y, float z) {
	int h = hash & 15;
	float u = h < 8 ? x : y,
		v = h < 4 ? y : h == 12 || h == 14 ? x : z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}