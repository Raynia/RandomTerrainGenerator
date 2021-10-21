#include "Draw.h"

// 지형 그리기
void DrawTerrain(Terrain *Terrain, int Mode)
{
	int AreaCount = Terrain->GetAreaSize();
	for (int i = 0; i < AreaCount; i++)
	{
		DrawWireArea(Terrain->GetAreaAt(i));
	}
}

// 지형 그리기 WireFrame 모드
void DrawWireTerrain(Terrain *Terrain) 
{ 
	DrawTerrain(Terrain, GL_LINE_LOOP); 
}

// 지형 그리기 Polygon 모드
void DrawSolidTerrain(Terrain *Terrain) 
{ 
	DrawTerrain(Terrain, GL_POLYGON); 
}

// 에리어 그리기
void DrawArea(Area *Area, int Mode) 
{
	for (int Z = 0; Z < 2; Z++)
	{
		for (int X = 0; X < 2; X++)
		{
			DrawBlock(Area->BlockInArea[Z][X], Mode);
		}
	}
}

// 에리어 그리기 WireFrame 모드
void DrawWireArea(Area *Area) 
{
	DrawArea(Area, GL_LINE_LOOP);
}

// 에리어 그리기 Polygon 모드
void DrawSolidArea(Area *Area) 
{ 
	DrawArea(Area, GL_POLYGON); 
}

// 블록 그리기
void DrawBlock(Block Block, int Mode) {
	GLfloat size[2];
	int ax = Block.GetXinTerrain() * 31, aZ = Block.GetZinTerrain() * 31;
	GLfloat tempColor = 0.0;
	glGetFloatv(GL_POINT_SIZE_RANGE, size);
	glPointSize(size[0] * 30);
	if (Mode == GL_POLYGON)		// Polygon 모드인 경우 조명을 켜줌
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}

	if (Mode == GL_POLYGON)		//Polygon 모드인 경우 녹색을 지정
	{
		glColor3f(0.25, 0.5, 0.25);
		for (int Z = 0; Z < 31; Z++) {
			for (int X = 0; X < 31; X++) {

				glBegin(Mode);
				glVertex3f(float(ax + X), Block.BlockHeight[Z + 1][X], aZ + Z + 1);
				glVertex3f(ax + X, Block.BlockHeight[Z][X], aZ + Z);
				glVertex3f(ax + X + 1, Block.BlockHeight[Z + 1][X + 1], aZ + Z + 1);
				glEnd();

				glBegin(Mode);
				glVertex3f(ax + X, Block.BlockHeight[Z][X], aZ + Z);
				glVertex3f(ax + X + 1, Block.BlockHeight[Z][X + 1], aZ + Z);
				glVertex3f(ax + X + 1, Block.BlockHeight[Z + 1][X + 1], aZ + Z + 1);
				glEnd();
			}
		}
	}
	else
	{
		glColor3f(0.0, 0.0, 0.0);		//WireFrame 모드인 경우 검은색을 지정
		for (int Z = 0; Z < 31; Z++) {
			for (int X = 0; X < 31; X++) {

				glBegin(Mode);
				glVertex3f(float(ax + X), Block.BlockHeight[Z + 1][X]+0.1, aZ + Z + 1);
				glVertex3f(ax + X, Block.BlockHeight[Z][X] + 0.1, aZ + Z);
				glVertex3f(ax + X + 1, Block.BlockHeight[Z + 1][X + 1] + 0.1, aZ + Z + 1);
				glEnd();

				glBegin(Mode);
				glVertex3f(ax + X, Block.BlockHeight[Z][X] + 0.1, aZ + Z);
				glVertex3f(ax + X + 1, Block.BlockHeight[Z][X + 1] + 0.1, aZ + Z);
				glVertex3f(ax + X + 1, Block.BlockHeight[Z + 1][X + 1] + 0.1, aZ + Z + 1);
				glEnd();
			}
		}
	}
	

	if (Mode == GL_POLYGON) 
	{
		glDisable(GL_LIGHTING);
	}
	else	//WireFrame인 경우 보조선을 그려줌
	{
		
		// X축 보조선
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex3f(ax + 31, 0, aZ + 31);
		glVertex3f(ax, 0, aZ + 31);
		glVertex3f(ax + 31, 0, aZ);
		glVertex3f(ax, 0, aZ);
		glEnd();

		// Z축 보조선
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINES);
		glVertex3f(ax, 0, aZ);
		glVertex3f(ax, 0, aZ + 31);
		glVertex3f(ax + 31, 0, aZ);
		glVertex3f(ax + 31, 0, aZ + 31);
		glEnd();
	}
}

// 블록 그리기 WireFrame 모드
void DrawWireBlock(Block Block)
{
	DrawBlock(Block, GL_LINE_LOOP);
}

// 블록 그리기 Polygon 모드
void DrawSolidBlock(Block Block)
{
	DrawBlock(Block, GL_POLYGON);
}

// 에리어 버퍼 그리기 : 7x7 에리어
void DrawBuffer(Area *Buffer[7][7], int Mode)
{
	for (int sp1 = 0; sp1 < 7; sp1++)
	{
		for (int sp2 = 0; sp2 < 7; sp2++)
		{
			DrawArea(Buffer[sp1][sp2], Mode);
		}
	}
}

// 에리어 버퍼 그리기 WireFrame 모드 : 7x7 에리어
void DrawWireBuffer(Area *Buffer[7][7]) 
{
	DrawBuffer(Buffer, GL_LINE_LOOP); 
}

// 에리어 버퍼 그리기 Polygon 모드 : 7x7 에리어
void DrawSolidBuffer(Area *Buffer[7][7])
{ 
	DrawBuffer(Buffer, GL_POLYGON);
}


