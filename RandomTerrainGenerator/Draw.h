#pragma once
#include "Terrain.h"
#include "Area.h"
#include "Block.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "SDL2/SDL_syswm.h"
#include <GL/GLU.h>

#define SETCOLOR(fl) {fl}

// ���� �׸���
void DrawTerrain(Terrain *Terrain, int Mode);

// ���� �׸��� WireFrame ���
void DrawWireTerrain(Terrain *Terrain);

// ���� �׸��� Polygon ���
void DrawSolidTerrain(Terrain *Terrain);

// ������ �׸���
void DrawArea(Area *Area, int Mode);

// ������ �׸��� WireFrame ���
void DrawWireArea(Area *Area);

// ������ �׸��� Polygon ���
void DrawSolidArea(Area *Area);

// ��� �׸���
void DrawBlock(Block Block, int Mode);

// ��� �׸��� WireFrame ���
void DrawWireBlock(Block Block);

// ��� �׸��� Polygon ���
void DrawSolidBlock(Block Block);

// ������ ���� �׸��� : 7x7 ������
void DrawBuffer(Area *Buffer[7][7], int Mode);

// ������ ���� �׸��� WireFrame ��� : 7x7 ������
void DrawWireBuffer(Area *Buffer[7][7]);

// ������ ���� �׸��� Polygon ��� : 7x7 ������
void DrawSolidBuffer(Area *Buffer[7][7]);