#pragma once
#include "AllInOne.h"
#define TEXTURE_LENGTH 2
#define SAVE 0
#define LOAD 1

class ViewerTexture
{
private:
	/*텍스쳐를 생성할 때 저장되는 변수*/
	GLint textureID;	//텍스쳐 ID
	int width; //텍스쳐 너비
	int height; //텍스쳐 높이

	/*텍스쳐를 디스플레이할 때 저장되는 변수*/
	int x1; // 좌측 좌표
	int x2; // 우측 좌표
	int y1; // 하단 좌표
	int y2; // 상단 좌표

public:
	ViewerTexture();
	~ViewerTexture();

	// 텍스쳐 불러오기
	void LoadTexture(std::string directory, int screen_width);	
	
	// 텍스쳐 그리기
	void DrawTexture(int x, int y);	

	// 텍스쳐 ID 설정
	void SetTextureID(GLint textureID);
	
	// 텍스쳐 너비 설정
	void SetWidth(int width);
	
	// 텍스쳐 높이 설정
	void SetHeight(int height);

	// 텍스쳐 X 시작점 설정
	void SetX1(int x1);

	// 텍스쳐 X 종료점 설정
	void SetX2(int x2);

	// 텍스쳐 Y 시작점 설정
	void SetY1(int y1);
	
	// 텍스쳐 Y 종료점 설정
	void SetY2(int y2);

	// 텍스쳐 ID 받아오기
	GLint GetTextureID();

	// 텍스쳐 너비 받아오기
	int GetWidth();

	//텍스쳐 높이 받아오기
	int GetHeight();

	// 텍스쳐 X 시작점 받아오기
	int GetX1();

	// 텍스쳐 X 종료점 받아오기
	int GetX2();

	// 텍스쳐 Y 시작점 받아오기
	int GetY1();

	// 텍스쳐 Y 종료점 받아오기
	int GetY2();
};