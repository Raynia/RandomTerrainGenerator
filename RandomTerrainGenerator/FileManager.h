#pragma once
#include "AllInOne.h"
#include "CInputDialog.h"
#include "Terrain.h"
#include "FileLoad.h"
#include "FileSave.h"
#include "FileCreate.h"

class FileManager
{
public:
	Terrain *Terrain;	// ���� Ŭ����
private:
	CWnd *pwnd;	// MFC Ŭ����
	FileSave save;	// ���� ���� Ŭ����
	FileLoad load;	// ���� �ҷ����� Ŭ����
	FileCreate create;	//���� ���� Ŭ����
	std::string fileName;

public:
	FileManager();
	~FileManager();

	//���� ������ �ʱ�ȭ
	void Begin();

	// MFC�� �ҷ��� ������ Path�� �޾Ƽ� �ҷ���
	void CreateTerrain();

	// MFC�� ������ ������ Path�� �޾Ƽ� ����
	void OpenTerrain();

	// ������ ����
	void SaveTerrain();

	// ���α׷��� ������ �ڵ��� MFCŬ������ ��������
	void SetHANDLE(CWnd *pwnd);
};

