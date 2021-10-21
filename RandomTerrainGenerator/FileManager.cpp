#include "FileManager.h"

FileManager::FileManager()
{
	this->fileName = "terrain_file";
}

FileManager::~FileManager()
{
}

//지형 파일을 초기화
void FileManager::Begin()
{
	Terrain = NULL;		// 빈 지형을 렌더링 하는 것을 막기위해 NULL 값을 넣어줌
}

// MFC로 불러올 파일의 Path를 받아서 불러옴
void FileManager::OpenTerrain()
{
	Begin();
	Block::BlockInit();
	std::string file = this->fileName + ".ter";
	CFileDialog fileDlg(TRUE, "*.ter", file.c_str() ,OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,"ter File(*.ter)|*.ter|",this->pwnd );
	if (fileDlg.DoModal() == IDOK)
	{
		CString path = fileDlg.GetPathName();
		Terrain = load.LoadFile(path, this->Terrain);
		this->fileName = fileDlg.GetFileTitle();
	}
}

// MFC로 저장할 파일의 Path를 받아서 저장
void FileManager::SaveTerrain()
{
	std::string file = this->fileName + ".ter";
	CFileDialog fileDlg(FALSE, "*.ter", file.c_str(), OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, "ter File(*.ter)|*.ter|", this->pwnd);
	if (fileDlg.DoModal() == IDOK)
	{
		CString path = fileDlg.GetPathName();
		save.SaveFile(path, this->Terrain);
		this->fileName = fileDlg.GetFileTitle();
	}
}

// 지형을 생성
void FileManager::CreateTerrain()
{
	CInputDialog seedInput(this->pwnd);		// 지형의 시드값을 받을 다이얼로그를 띄어줌
	if (seedInput.DoModal() == IDOK)			// 확인 버튼을 누른경우
	{
		unsigned int seed = seedInput.GetSeed();
		Block::BlockInit();
		if (Terrain != NULL) delete Terrain;
		Terrain = this->create.CreateTerrain(seed);
		this->fileName = "terrain_file";
	}
}

// 프로그램의 윈도우 핸들을 MFC클래스와 연결해줌
void FileManager::SetHANDLE(CWnd *pwnd)
{
	this->pwnd = pwnd;
}
