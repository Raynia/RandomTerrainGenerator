#include "Block.h"

unsigned int Block::blockCount = 0;
int Block::p[512];
int Block::permutation[256];

Block::Block()
{
}

Block::Block(int Seed) 
{
	if (blockCount++ == 0) {
		InitRandom(Seed);
	}
}

Block::~Block()
{
}

// 지형 내 X좌표 받아오기
int Block::GetXinTerrain() 
{ 
	return this->xInTerrain; 
}

// 지형 내 Y좌표 받아오기
int Block::GetZinTerrain() 
{ 
	return this->zInTerrain; 
}

// 에리어 내 X좌표 받아오기
int Block::GetXinArea()
{ 
	return this->xInArea;
}

// 에리어 내 Z좌표 받아오기
int Block::GetZinArea() 
{
	return this->zInArea;
}

// 주파수 받아오기
float Block::GetFrequency()
{
	return this->heightFrequency;
}

// 가중치 받아오기
float Block::GetWeight() 
{ 
	return this->heightWeight;
}

// 블록 속성 설정
void Block::SetBlockHeader(int xInTerrain, int zInTerrain, int xInArea, int zInArea, float fre, float wei, int biome)
{
	this->xInTerrain = xInTerrain;
	this->zInTerrain = zInTerrain;
	this->xInArea = xInArea;
	this->xInArea = zInArea;
	this->areaX = (xInTerrain < 0) ? (xInTerrain - 1) / 2 : xInTerrain / 2;
	this->areaZ = (zInTerrain < 0) ? (zInTerrain - 1) / 2 : zInTerrain / 2;
	this->heightFrequency = fre;
	this->heightWeight = wei;
}

// 블록 속성 설정 후 블록 생성
void Block::SetBlock(int xInTerrain, int zInTerrain, int xInArea, int zInArea, float fre, float wei, int biome)
{
	this->SetBlockHeader(xInTerrain, zInTerrain, xInArea, zInArea, fre, wei, biome);
	InitBlock(biome);
}


// 블록 클래스 초기화
void Block::BlockInit()
{
	blockCount = 0;
}

// 블록 난수 초기화
void Block::InitRandom(int Seed) {
	srand(Seed);
	for (int i = 0; i < 256; i++) {
		permutation[i] = rand() % 255;
		p[256 + i] = p[i] = permutation[i];
	}
}

// 블록 높이맵 생성
void Block::InitBlock(int biome) {
	for (int Z = 0; Z < 32; Z++) 
	{
		for (int X = 0; X < 32; X++) 
		{
			BlockHeight[Z][X] = +GetHeight(X, Z, 0.05, 1.2)+ GetHeight(X, Z, 0.025, 2.0) + GetHeight(X, Z, 0.008, 60.0) + 53.0;
		}
	}
}

// 높이값 받아오기
float Block::GetHeight(float X, float Z, float Fre, float Wei)
{ 
	return Noise((X + 31 * (float)xInTerrain)*Fre, (Z + 31 * (float)zInTerrain)*Fre, 0)*Wei;
}

float Block::Noise(float x, float y, float z) {
	int X = (int)floor(x) & 255, Y = (int)floor(y) & 255, Z = (int)floor(z) & 255;
	x -= floor(x);
	y -= floor(y);
	z -= floor(z);

	float u = Fade(x), v = Fade(y), w = Fade(z);

	int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z, B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

	return Lerp(w, Lerp(v, Lerp(u, Grad(p[AA], x, y, z), Grad(p[BA], x - 1, y, z)), Lerp(u, Grad(p[AB], x, y - 1, z), Grad(p[BB], x - 1, y - 1, z)))
		, Lerp(v, Lerp(u, Grad(p[AA + 1], x, y, z - 1), Grad(p[BA + 1], x - 1, y, z - 1)), Lerp(u, Grad(p[AB + 1], x, y - 1, z - 1), Grad(p[BB + 1], x - 1, y - 1, z - 1))));
}

float Block::Fade(float t)
{ 
	return t * t*t*(t*(t * 6 - 15) + 10);
}

float Block::Lerp(float t, float a, float b) 
{ 
	return a + t * (b - a); 
}

float Block::Grad(int hash, float x, float y, float z) 
{
	int h = hash & 15;
	float u = h < 8 ? x : y,
		v = h < 4 ? y : h == 12 || h == 14 ? x : z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}