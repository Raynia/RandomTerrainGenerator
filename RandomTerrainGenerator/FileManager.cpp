#include "FileManager.h"

FileManager::FileManager()
{
	this->fileName = "terrain_file";
}

FileManager::~FileManager()
{
}

//���� ������ �ʱ�ȭ
void FileManager::Begin()
{
	Terrain = NULL;		// �� ������ ������ �ϴ� ���� �������� NULL ���� �־���
}

// MFC�� �ҷ��� ������ Path�� �޾Ƽ� �ҷ���
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

// MFC�� ������ ������ Path�� �޾Ƽ� ����
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

// ������ ����
void FileManager::CreateTerrain()
{
	CInputDialog seedInput(this->pwnd);		// ������ �õ尪�� ���� ���̾�α׸� �����
	if (seedInput.DoModal() == IDOK)			// Ȯ�� ��ư�� �������
	{
		unsigned int seed = seedInput.GetSeed();
		Block::BlockInit();
		if (Terrain != NULL) delete Terrain;
		Terrain = this->create.CreateTerrain(seed);
		this->fileName = "terrain_file";
	}
}

// ���α׷��� ������ �ڵ��� MFCŬ������ ��������
void FileManager::SetHANDLE(CWnd *pwnd)
{
	this->pwnd = pwnd;
}
