#pragma once

#include "AllInOne.h"
#include "FileManager.h"
#include "Terrain.h"
#include "Block.h"
#include "Draw.h"
#include "ViewerCamera.h"
#include "ViewerTexture.h"

const double Pi = 3.141592;
const int BufferSize = 7;

class Viewer
{
public:
	FileManager FileManager;	// ���� �Ŵ���
private:
	SDL_Window *screen;			// SDL Window
	SDL_SysWMinfo wminfo;		// SDL Window�� System ���� ����
	HWND hwnd;						// Window �ڵ�
	CWnd *pwnd;					// MFC Ŭ����
	Area *Buffer[BufferSize][BufferSize];		// ������ ����
	ViewerCamera mainCamera;					// ī�޶�
	ViewerTexture Texture_Create, Texture_Save, Texture_Open;	//������ư, �����ư, �ҷ������ư

	int screenWidth, screenHeight; // ȭ�� �ʺ�� ����
	const int menuHeight = 40; // ��� �޴� ���� ����
	int menuWidth; // ��� �޴� ���� �ʺ�
	int infoWidth, infoHeight; // ���� UI ��Ƽ���� �ʺ�� ����
	int viewerWidth, viewerHeight; //���� Viewer ��Ƽ���� �ʺ�� ����
	double screenRatio; // ȭ�� ����
	bool sdlLoopFlag = true;	//SDL ����
	bool wireMode = false;  //WireFrame ���
	int delay;						//������
	int fps;							//�ʴ� ������ ��
	UINT32 starTick;			
	bool trash;

public:
	Viewer();
	~Viewer();

	//UI, Viewer ��Ƽ�� ũ�� ����
	void ChangePartitionValue(); 

	// ���α׷� â �ʱ�ȭ
	void ShowWindow(const char *Window);

	// ���α׷� â �ʺ� ����
	void SetScreenWidth(int w);

	//���α׷� â ���� ����
	void SetScreenHeight(int h);

	// ���α׷� â �ʺ� �ޱ�
	int GetScreenWidth();

	//���α׷� â ���� �ޱ�
	int GetScreenHeight();
private:
	// ������ ���� ������Ʈ
	void UpdateBuffer(int AreaX,int AreaZ);

	// SDL ���÷��� ����
	void ViewerDisplay();

	// SDL Ű���� ����
	void ViewerKeyboard(SDL_Event event);

	// SDL ���콺 ����
	void ViewerMouse(SDL_Event event);

	// SDL ���콺 �� ���� : ���� Ȯ��/���
	void ViewerWheel(SDL_Event event);

	//ī�޶� ȸ�� : ī�޶� ������ ����
	void ViewerKeyboardCameraRotate(SDL_Event event);

	//ī�޶� �̵� : ī�޶� ��ǥ ����
	void ViewerKeyboardEyeSwitch(SDL_Event event, GLdouble cameraSpeed);

	//ī�޶� �̵� : ���� ��ǥ ����
	void ViewerKeyboardCenterSwitch(SDL_Event event, GLdouble cameraSpeed);

	//ī�޶� ������ ����(Z,X : FOV(-/+), C,V : Near(-/+), B,N : Far(-/+), H : WireFrame ���(On/Off))
	void ViewerKeyboardPerpectiveSwitch(SDL_Event event, GLdouble cameraSpeed);

	//���� ī�޶� ��ġ�ϰ� �ִ� ����� üũ�ϰ� ������ ���۸� ������Ʈ
	void ViewerCheckCameraBlock(GLdouble CameraX, GLdouble CameraZ);

	//���� View ���÷���
	void ViewerViewDisplay();

	//��� �޴� ���÷���
	void ViewerMenuDisplay();

	//���� ����â ������
	void ViewerInfoDisplay();

	//����â�� �޼����� ��Ʈ�� ���÷���
	void ViewerTextRender(GLfloat x, GLfloat y, const char *text);
};