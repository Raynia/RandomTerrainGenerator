#include "Draw.h"

// ���� �׸���
void DrawTerrain(Terrain *Terrain, int Mode)
{
	int AreaCount = Terrain->GetAreaSize();
	for (int i = 0; i < AreaCount; i++)
	{
		DrawWireArea(Terrain->GetAreaAt(i));
	}
}

// ���� �׸��� WireFrame ���
void DrawWireTerrain(Terrain *Terrain) 
{ 
	DrawTerrain(Terrain, GL_LINE_LOOP); 
}

// ���� �׸��� Polygon ���
void DrawSolidTerrain(Terrain *Terrain) 
{ 
	DrawTerrain(Terrain, GL_POLYGON); 
}

// ������ �׸���
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

// ������ �׸��� WireFrame ���
void DrawWireArea(Area *Area) 
{
	DrawArea(Area, GL_LINE_LOOP);
}

// ������ �׸��� Polygon ���
void DrawSolidArea(Area *Area) 
{ 
	DrawArea(Area, GL_POLYGON); 
}

// ��� �׸���
void DrawBlock(Block Block, int Mode) {
	GLfloat size[2];
	int ax = Block.GetXinTerrain() * 31, aZ = Block.GetZinTerrain() * 31;
	GLfloat tempColor = 0.0;
	glGetFloatv(GL_POINT_SIZE_RANGE, size);
	glPointSize(size[0] * 30);
	if (Mode == GL_POLYGON)		// Polygon ����� ��� ������ ����
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}

	if (Mode == GL_POLYGON)		//Polygon ����� ��� ����� ����
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
		glColor3f(0.0, 0.0, 0.0);		//WireFrame ����� ��� �������� ����
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
	else	//WireFrame�� ��� �������� �׷���
	{
		
		// X�� ������
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex3f(ax + 31, 0, aZ + 31);
		glVertex3f(ax, 0, aZ + 31);
		glVertex3f(ax + 31, 0, aZ);
		glVertex3f(ax, 0, aZ);
		glEnd();

		// Z�� ������
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINES);
		glVertex3f(ax, 0, aZ);
		glVertex3f(ax, 0, aZ + 31);
		glVertex3f(ax + 31, 0, aZ);
		glVertex3f(ax + 31, 0, aZ + 31);
		glEnd();
	}
}

// ��� �׸��� WireFrame ���
void DrawWireBlock(Block Block)
{
	DrawBlock(Block, GL_LINE_LOOP);
}

// ��� �׸��� Polygon ���
void DrawSolidBlock(Block Block)
{
	DrawBlock(Block, GL_POLYGON);
}

// ������ ���� �׸��� : 7x7 ������
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

// ������ ���� �׸��� WireFrame ��� : 7x7 ������
void DrawWireBuffer(Area *Buffer[7][7]) 
{
	DrawBuffer(Buffer, GL_LINE_LOOP); 
}

// ������ ���� �׸��� Polygon ��� : 7x7 ������
void DrawSolidBuffer(Area *Buffer[7][7])
{ 
	DrawBuffer(Buffer, GL_POLYGON);
}


