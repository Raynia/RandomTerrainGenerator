#pragma once
#include "AllInOne.h"
#define TEXTURE_LENGTH 2
#define SAVE 0
#define LOAD 1

class ViewerTexture
{
private:
	/*�ؽ��ĸ� ������ �� ����Ǵ� ����*/
	GLint textureID;	//�ؽ��� ID
	int width; //�ؽ��� �ʺ�
	int height; //�ؽ��� ����

	/*�ؽ��ĸ� ���÷����� �� ����Ǵ� ����*/
	int x1; // ���� ��ǥ
	int x2; // ���� ��ǥ
	int y1; // �ϴ� ��ǥ
	int y2; // ��� ��ǥ

public:
	ViewerTexture();
	~ViewerTexture();

	// �ؽ��� �ҷ�����
	void LoadTexture(std::string directory, int screen_width);	
	
	// �ؽ��� �׸���
	void DrawTexture(int x, int y);	

	// �ؽ��� ID ����
	void SetTextureID(GLint textureID);
	
	// �ؽ��� �ʺ� ����
	void SetWidth(int width);
	
	// �ؽ��� ���� ����
	void SetHeight(int height);

	// �ؽ��� X ������ ����
	void SetX1(int x1);

	// �ؽ��� X ������ ����
	void SetX2(int x2);

	// �ؽ��� Y ������ ����
	void SetY1(int y1);
	
	// �ؽ��� Y ������ ����
	void SetY2(int y2);

	// �ؽ��� ID �޾ƿ���
	GLint GetTextureID();

	// �ؽ��� �ʺ� �޾ƿ���
	int GetWidth();

	//�ؽ��� ���� �޾ƿ���
	int GetHeight();

	// �ؽ��� X ������ �޾ƿ���
	int GetX1();

	// �ؽ��� X ������ �޾ƿ���
	int GetX2();

	// �ؽ��� Y ������ �޾ƿ���
	int GetY1();

	// �ؽ��� Y ������ �޾ƿ���
	int GetY2();
};