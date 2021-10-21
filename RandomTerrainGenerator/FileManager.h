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
	Terrain *Terrain;	// 지형 클래스
private:
	CWnd *pwnd;	// MFC 클래스
	FileSave save;	// 파일 저장 클래스
	FileLoad load;	// 파일 불러오기 클래스
	FileCreate create;	//파일 생성 클래스
	std::string fileName;

public:
	FileManager();
	~FileManager();

	//지형 파일을 초기화
	void Begin();

	// MFC로 불러올 파일의 Path를 받아서 불러옴
	void CreateTerrain();

	// MFC로 저장할 파일의 Path를 받아서 저장
	void OpenTerrain();

	// 지형을 생성
	void SaveTerrain();

	// 프로그램의 윈도우 핸들을 MFC클래스와 연결해줌
	void SetHANDLE(CWnd *pwnd);
};

