#pragma once
#include "Terrain.h"
#include "Area.h"
#include "Block.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include "SDL2/SDL_syswm.h"
#include <GL/GLU.h>

#define SETCOLOR(fl) {fl}

// 지형 그리기
void DrawTerrain(Terrain *Terrain, int Mode);

// 지형 그리기 WireFrame 모드
void DrawWireTerrain(Terrain *Terrain);

// 지형 그리기 Polygon 모드
void DrawSolidTerrain(Terrain *Terrain);

// 에리어 그리기
void DrawArea(Area *Area, int Mode);

// 에리어 그리기 WireFrame 모드
void DrawWireArea(Area *Area);

// 에리어 그리기 Polygon 모드
void DrawSolidArea(Area *Area);

// 블록 그리기
void DrawBlock(Block Block, int Mode);

// 블록 그리기 WireFrame 모드
void DrawWireBlock(Block Block);

// 블록 그리기 Polygon 모드
void DrawSolidBlock(Block Block);

// 에리어 버퍼 그리기 : 7x7 에리어
void DrawBuffer(Area *Buffer[7][7], int Mode);

// 에리어 버퍼 그리기 WireFrame 모드 : 7x7 에리어
void DrawWireBuffer(Area *Buffer[7][7]);

// 에리어 버퍼 그리기 Polygon 모드 : 7x7 에리어
void DrawSolidBuffer(Area *Buffer[7][7]);