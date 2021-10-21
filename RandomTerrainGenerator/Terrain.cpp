#include "Terrain.h"

Terrain::Terrain()
{
}


Terrain::~Terrain()
{
	AreaInTerrain.clear();
}

// (X,Z) 좌표를 가지는 에리어 생성
Area *Terrain::CreateArea(int xInTerrain, int zInTerrain)
{
	Area *Temp = new Area(xInTerrain, zInTerrain);
	Temp->SetBiome(this->GetBiome(xInTerrain, zInTerrain));
	Temp->CreateBlock();
	AreaInTerrain.push_back(Temp);
	hashTable.InsertValue(xInTerrain, zInTerrain, AreaInTerrain.size() - 1);
	return Temp;
}

// 에리어를 에리어 벡터에 삽입
void Terrain::InsertArea(Area *area) 
{ 
	this->AreaInTerrain.push_back(area); 
	hashTable.InsertValue(area->GetXinTerrain(), area->GetZinTerrain(), AreaInTerrain.size() - 1);
}

// 지형 초기화 : 7x7 에리어 생성
void Terrain::InitTerrain()
{
	for (int Z = -3; Z <= 3; Z++) {
		for (int X = -3; X <= 3; X++) {
			CreateArea(X, Z);
		}
	}
}

// 지형 안에 포함된 에리어 개수 받아오기
int Terrain::GetAreaSize() 
{
	return this->AreaInTerrain.size();
}

// 지형 내에 (X,Z) 좌표를 가지는 에리어 주변으로 에리어 생성
void Terrain::UpdateArea(int xInTerrain, int zInTerrain)
{
	for (int sp1 = xInTerrain - 3; sp1 <= xInTerrain + 3; sp1++) 
	{
		for (int sp2 = zInTerrain - 3; sp2 <= zInTerrain + 3; sp2++)
		{
			if (!IsAreaInTerrain(sp1, sp2))		// 해당 에리어가 없는 경우 새로 생성
			{
				CreateArea(sp1, sp2);
			}
		}
	}
}

// 지형 내에 (X,Z) 좌표를 가지는 에리어가 있는지 확인
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

// 바이옴,지형 난수를 생성하는 시드값을 설정 하고 난수 생성
void Terrain::SetRandomNumber(unsigned int Seed)
{
	this->TerrainSeed = Seed;
	this->BiomeSeed = UINT_MAX - Seed;
	srand(this->BiomeSeed);
	for (int i = 0; i < 256; i++) {
		permutation[i] = rand() % 255;
		p[256 + i] = p[i] = permutation[i];
	}
	Block InitRandom(this->TerrainSeed);		//난수 생성
}

// 지형 시드를 받아오기
int Terrain::GetRandomNumber()
{ 
	return this->TerrainSeed;
}

// 지형이 생성된 시간 초기화
void Terrain::InitCreatedTime() 
{ 
	this->TerrainCreatedTime = time(NULL); 
}

// 지형이 생성된 시간을 설정
void Terrain::SetCreatedTime(time_t c_time) 
{
	this->TerrainCreatedTime = c_time; 
}

// 지형이 생성된 시간을 받아오기
time_t Terrain::GetCreatedTime()
{ 
	return this->TerrainCreatedTime; 
}

// 에리어 벡터 안에 index+1 번째 존재하는 에리어 주소 받아오기
Area *Terrain::GetAreaAt(int index) 
{
	return this->AreaInTerrain.at(index);
}

// 에리어 벡터 안에 존재하는 (X,Z) 좌표를 가지는 에리어 주소 받아오기
Area *Terrain::GetAreaAt(int xInTerrain, int zInTerrain)
{
	int address = hashTable.GetAreaAddress(xInTerrain, zInTerrain);
	if (address != -1)
	{
		return GetAreaAt(address);	// 에리어가 저장된 벡터의 주소를 반환
	}
	else
	{
		return CreateArea(xInTerrain, zInTerrain);	// 에리어가 벡터 안에 없는 경우 새로 생성
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