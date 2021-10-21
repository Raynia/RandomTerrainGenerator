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
	FileManager FileManager;	// 파일 매니저
private:
	SDL_Window *screen;			// SDL Window
	SDL_SysWMinfo wminfo;		// SDL Window의 System 종속 정보
	HWND hwnd;						// Window 핸들
	CWnd *pwnd;					// MFC 클래스
	Area *Buffer[BufferSize][BufferSize];		// 에리어 버퍼
	ViewerCamera mainCamera;					// 카메라
	ViewerTexture Texture_Create, Texture_Save, Texture_Open;	//생성버튼, 저장버튼, 불러오기버튼

	int screenWidth, screenHeight; // 화면 너비와 높이
	const int menuHeight = 40; // 상단 메뉴 바의 높이
	int menuWidth; // 상단 메뉴 바의 너비
	int infoWidth, infoHeight; // 우측 UI 파티션의 너비와 높이
	int viewerWidth, viewerHeight; //좌측 Viewer 파티션의 너비와 높이
	double screenRatio; // 화면 비율
	bool sdlLoopFlag = true;	//SDL 루프
	bool wireMode = false;  //WireFrame 모드
	int delay;						//딜레이
	int fps;							//초당 프레임 수
	UINT32 starTick;			
	bool trash;

public:
	Viewer();
	~Viewer();

	//UI, Viewer 파티션 크기 조정
	void ChangePartitionValue(); 

	// 프로그램 창 초기화
	void ShowWindow(const char *Window);

	// 프로그램 창 너비 설정
	void SetScreenWidth(int w);

	//프로그램 창 높이 설정
	void SetScreenHeight(int h);

	// 프로그램 창 너비 받기
	int GetScreenWidth();

	//프로그램 창 높이 받기
	int GetScreenHeight();
private:
	// 에리어 버퍼 업데이트
	void UpdateBuffer(int AreaX,int AreaZ);

	// SDL 디스플레이 동작
	void ViewerDisplay();

	// SDL 키보드 동작
	void ViewerKeyboard(SDL_Event event);

	// SDL 마우스 동작
	void ViewerMouse(SDL_Event event);

	// SDL 마우스 휠 동작 : 지형 확대/축소
	void ViewerWheel(SDL_Event event);

	//카메라 회전 : 카메라 방향축 기준
	void ViewerKeyboardCameraRotate(SDL_Event event);

	//카메라 이동 : 카메라 좌표 기준
	void ViewerKeyboardEyeSwitch(SDL_Event event, GLdouble cameraSpeed);

	//카메라 이동 : 전역 좌표 기준
	void ViewerKeyboardCenterSwitch(SDL_Event event, GLdouble cameraSpeed);

	//카메라 설정값 수정(Z,X : FOV(-/+), C,V : Near(-/+), B,N : Far(-/+), H : WireFrame 모드(On/Off))
	void ViewerKeyboardPerpectiveSwitch(SDL_Event event, GLdouble cameraSpeed);

	//현재 카메라가 위치하고 있는 에리어를 체크하고 에리어 버퍼를 업데이트
	void ViewerCheckCameraBlock(GLdouble CameraX, GLdouble CameraZ);

	//메인 View 디스플레이
	void ViewerViewDisplay();

	//상단 메뉴 디스플레이
	void ViewerMenuDisplay();

	//우측 정보창 렌더링
	void ViewerInfoDisplay();

	//정보창에 메세지를 폰트로 디스플레이
	void ViewerTextRender(GLfloat x, GLfloat y, const char *text);
};