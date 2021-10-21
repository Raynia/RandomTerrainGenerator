#define _AFXDLL
#include "Viewer.h"

const GLfloat red[4] = { 0.8f, 0.0, 0.0, 1.0 };
const GLfloat blue[4] = { 0.0, 0.2f, 1.0, 1.0 };
const GLfloat white[4] = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat black[4] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat green[4] = { 0.3, 0.8, 0.4, 1.0 };
const GLfloat polished[4] = { 100.0 };
const GLfloat dull[4] = { 0.0 };

GLfloat light_pos[4] = { 0.0, 200.0, 0.0, 1.0 };
GLfloat const_att = 1.0;

Viewer::Viewer()
{

}

Viewer::~Viewer()
{

}

// 프로그램 창 초기화
void Viewer::ShowWindow(const char *Window)
{
	std::string directoryCreateImage = "image/Create_";
	std::string directorySaveImage = "image/Save_";
	std::string directoryLoadImage = "image/Open_";

	SetScreenWidth(1480);
	SetScreenHeight(740);

	trash = true;
	fps = 0;
	ChangePartitionValue();

	//SDL 초기화
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("Could not initalize SDL - %s", SDL_GetError());
		exit(1);
	}

	Uint32 flag = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
	//SDL 윈도우, GL 컨텍스트 초기화

	screen = SDL_CreateWindow(Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flag);

	SDL_VERSION(&wminfo.version);

	//MFC 핸들 생성
	if (!SDL_GetWindowWMInfo(screen, &wminfo))
	{
		printf("Handle Init Fail!");
	}

	//MFC 핸들 초기화
	hwnd = wminfo.info.win.window;
	pwnd = CWnd::FromHandle(hwnd);
	FileManager.SetHANDLE(pwnd);

	SDL_GLContext context;

	context = SDL_GL_CreateContext(screen);

	// SDL OpenGL 설정
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5, 0.5, 0.5, 1.0);

	Texture_Create.LoadTexture(directoryCreateImage, screenWidth);
	Texture_Save.LoadTexture(directorySaveImage, screenWidth);
	Texture_Open.LoadTexture(directoryLoadImage, screenWidth);

	SDL_Event event;
	const Uint8 *keyboardstate = SDL_GetKeyboardState(NULL);

	// SDL 메인 루프
	while (sdlLoopFlag)
	{
		starTick = SDL_GetTicks();
		//SDL 이벤트 루프
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				ViewerKeyboard(event);
				break;

			case SDL_MOUSEBUTTONDOWN:
				ViewerMouse(event);
				break;

			case SDL_MOUSEWHEEL:
				ViewerWheel(event);
				break;

			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					SetScreenWidth(event.window.data1);
					SetScreenHeight(event.window.data2);
					ChangePartitionValue();
					Texture_Create.LoadTexture(directoryCreateImage, screenWidth);
					Texture_Save.LoadTexture(directorySaveImage, screenWidth);
					Texture_Open.LoadTexture(directoryLoadImage, screenWidth);
				}
				break;

			case SDL_QUIT:
				sdlLoopFlag = false;

			defalut:
				break;
			}
		}
		ViewerDisplay();			// 화면 렌더링
		SDL_GL_SwapWindow(screen);

		delay = 1000.0 / 30.0 - (SDL_GetTicks() - starTick);	//1 Frame 생성시 걸리는 시간 측정 하여 초당 30Frame을 맞추기 위해 Delay값 수정
		if (delay > 0)															//초당 30Frame 미만일 경우 Delay없이 바로 다음 Frame 생성
		{
			SDL_Delay(delay);
		}
		fps = 1000.0f / (float)(SDL_GetTicks() - starTick);		// 초당 표시되는 Frame 수 계산

	}
	SDL_DestroyWindow(screen);
	SDL_GL_DeleteContext(context);
	SDL_Quit();
}

// 프로그램 창 너비 설정
void Viewer::SetScreenWidth(int w) 
{ 
	screenWidth = w; 
}

//프로그램 창 높이 설정
void Viewer::SetScreenHeight(int h)
{ 
	screenHeight = h; 
}

// 프로그램 창 너비 받기
int Viewer::GetScreenWidth() 
{ 
	return screenWidth; 
}

//프로그램 창 높이 받기
int Viewer::GetScreenHeight() 
{ 
	return screenHeight; 
}

// UI, Viewer 파티션 크기 조정
void Viewer::ChangePartitionValue()
{
	screenRatio = (double)screenWidth / (double)screenHeight;
	menuWidth = screenWidth;
	infoWidth = 300;
	infoHeight = screenHeight - menuHeight;
	viewerWidth = screenWidth - infoWidth;
	viewerHeight = infoHeight;
}

// 에리어 버퍼 업데이트
void Viewer::UpdateBuffer(int AreaX, int AreaZ)
{
	for (int sp1 =  -3; sp1 < BufferSize-3; sp1++)
	{
		for (int sp2 = -3; sp2 < BufferSize-3; sp2++)
		{
			Buffer[sp1+3][sp2+3] = FileManager.Terrain->GetAreaAt(AreaX+sp2, AreaZ+sp1);
		}
	}
}

// SDL 디스플레이 동작
void Viewer::ViewerDisplay() 
{
	glClear(GL_COLOR_BUFFER_BIT);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ViewerViewDisplay();
	ViewerMenuDisplay();
	ViewerInfoDisplay();
}

// SDL 키보드 동작
void Viewer::ViewerKeyboard(SDL_Event event)
{
	GLdouble cameraSpeed = mainCamera.GetCameraSpeed();
	ViewerKeyboardCameraRotate(event);
	ViewerKeyboardEyeSwitch(event,cameraSpeed);
	ViewerKeyboardCenterSwitch(event, cameraSpeed);
	ViewerKeyboardPerpectiveSwitch(event, cameraSpeed);
}

// SDL 마우스 동작
void Viewer::ViewerMouse(SDL_Event event)
{
	switch(event.button.button)
	{
	case SDL_BUTTON_LEFT:
		if (event.button.x >= Texture_Create.GetX1() &&									// 'Create' 버튼을 클릭한 경우
			event.button.x <= Texture_Create.GetX2() &&
			event.button.y >= Texture_Create.GetY1() && 
			event.button.y <= Texture_Create.GetY2())
		{
			FileManager.CreateTerrain();
			UpdateBuffer(mainCamera.GetCameraInAreaX(), mainCamera.GetCameraInAreaZ());
		}
		else if (event.button.x >= Texture_Save.GetX1() &&								//'Save' 버튼을 클릭한 경우
			event.button.x <= Texture_Save.GetX2() &&
			event.button.y >= Texture_Save.GetY1() &&
			event.button.y <= Texture_Save.GetY2())
		{
			if (FileManager.Terrain != NULL)														//지형이 생성된 경우에만 저장 가능
			{
				FileManager.SaveTerrain();
			}
			else
			{
				MessageBoxA(NULL, "Terrain is Empty!", "FileManager", MB_OK);	//지형이 생성되지 않았을때 저장하는 경우 경고창을 발생시킨다.
			}
		}
		else if (event.button.x >= Texture_Open.GetX1() &&								//'Open' 버튼을 클릭한 경우
			event.button.x <= Texture_Open.GetX2() &&
			event.button.y >= Texture_Open.GetY1() && 
			event.button.y <= Texture_Open.GetY2())
		{
			FileManager.OpenTerrain();
			UpdateBuffer(mainCamera.GetCameraInAreaX(), mainCamera.GetCameraInAreaZ());
			trash = true;
		}
		break;

	case SDL_BUTTON_MIDDLE:
		break;

	case SDL_BUTTON_RIGHT:
		break;

	default:
		break;
	}
}

// SDL 마우스 휠 동작 : 지형 확대/축소
void Viewer::ViewerWheel(SDL_Event event)
{
	mainCamera.SetCameraZoom(event.wheel.y * 0.01);
}

//카메라 회전 : 카메라 방향축 기준
void Viewer::ViewerKeyboardCameraRotate(SDL_Event event) 
{
	GLfloat tempPitch;
	GLfloat tempYaw;
	switch (event.key.keysym.scancode)
	{
	case SDL_SCANCODE_UP:				//카메라 방향축 기준 Z축 반시계 회전
		tempPitch = mainCamera.GetCameraPitch() + 1.0;
		if (tempPitch > 180) tempPitch = 1.0;
		mainCamera.SetCameraPitch(tempPitch);
		mainCamera.SetCameraCenterX(1000 *cos(mainCamera.GetCameraPitch()*3.1415 / 90)*sin(mainCamera.GetCameraYaw()*3.1415 / 90));
		mainCamera.SetCameraCenterY(1000 *sin(mainCamera.GetCameraPitch()*3.1415 / 90));
		mainCamera.SetCameraCenterZ(1000 *cos(mainCamera.GetCameraPitch()*3.1415 / 90)*cos(mainCamera.GetCameraYaw()*3.1415 / 90));
		break;

	case SDL_SCANCODE_DOWN:			//카메라 방향축 기준 Z축 시계 회전
		tempPitch = mainCamera.GetCameraPitch() - 1.0;
		if (tempPitch < 1) tempPitch = 180.0;
		mainCamera.SetCameraPitch(tempPitch);
		mainCamera.SetCameraCenterX(1000 *cos(mainCamera.GetCameraPitch()*3.1415 / 90)*sin(mainCamera.GetCameraYaw()*3.1415 / 90));
		mainCamera.SetCameraCenterY(1000 *sin(mainCamera.GetCameraPitch()*3.1415 / 90));
		mainCamera.SetCameraCenterZ(1000 *cos(mainCamera.GetCameraPitch()*3.1415 / 90)*cos(mainCamera.GetCameraYaw()*3.1415 / 90));
		break;

	case SDL_SCANCODE_RIGHT:			//카메라 방향축 기준 Y축 반시계 회전
		tempYaw = mainCamera.GetCameraYaw() - 1.0;
		if (tempYaw < 1) tempYaw = 180.0;
		mainCamera.SetCameraYaw(tempYaw);
		mainCamera.SetCameraCenterX(1000 * cos(mainCamera.GetCameraPitch()*3.1415 / 90)*sin(mainCamera.GetCameraYaw()*3.1415 / 90));
		mainCamera.SetCameraCenterY(1000 * sin(mainCamera.GetCameraPitch()*3.1415 / 90));
		mainCamera.SetCameraCenterZ(1000 * cos(mainCamera.GetCameraPitch()*3.1415 / 90)*cos(mainCamera.GetCameraYaw()*3.1415 / 90));
		break;

	case SDL_SCANCODE_LEFT:				//카메라 방향축 기준 Y축 시계 회전
		tempYaw = mainCamera.GetCameraYaw() + 1.0;
		if (tempYaw > 180) tempYaw = 1.0;
		mainCamera.SetCameraYaw(tempYaw);
		mainCamera.SetCameraCenterX(1000 * cos(mainCamera.GetCameraPitch()*3.1415 / 90)*sin(mainCamera.GetCameraYaw()*3.1415 / 90));
		mainCamera.SetCameraCenterY(1000 * sin(mainCamera.GetCameraPitch()*3.1415 / 90));
		mainCamera.SetCameraCenterZ(1000 * cos(mainCamera.GetCameraPitch()*3.1415 / 90)*cos(mainCamera.GetCameraYaw()*3.1415 / 90));
		break;

	default:
		break;
	}
}

//카메라 이동 : 카메라 좌표 기준
void Viewer::ViewerKeyboardEyeSwitch(SDL_Event event, GLdouble cameraSpeed)
{
	int seed = 100;
	switch (event.key.keysym.scancode)
	{
	case SDL_SCANCODE_D:				// 카메라 우로 이동
		mainCamera.CameraRightMove(3.0);
		break;

	case SDL_SCANCODE_A:				// 카메라 좌로 이동
		mainCamera.CameraLeftMove(3.0);
		break;

	case SDL_SCANCODE_W:				// 카메라 앞으로 이동
		mainCamera.CameraFrontMove(0.01);
		break;

	case SDL_SCANCODE_S:				// 카메라 뒤로 이동
		mainCamera.CameraBackMove(0.01);
		break;

	case SDL_SCANCODE_Q:				// 카메라 높이 '-' 이동
		mainCamera.SetCameraPositionPlusY(-cameraSpeed);
		break;

	case SDL_SCANCODE_E:				// 카메라 높이 '+' 이동
		mainCamera.SetCameraPositionPlusY(cameraSpeed);
		break;

	case SDL_SCANCODE_R:				// 카메라 위치, 각도 리셋
		mainCamera.CameraReset();
		break;

	case SDL_SCANCODE_1:				// 지형 생성 단축키
	case SDL_SCANCODE_KP_1:
		FileManager.CreateTerrain();
		trash = true;
		break;
	case SDL_SCANCODE_2:				// 지형 불러오기 단축키
	case SDL_SCANCODE_KP_2:
		FileManager.OpenTerrain();
		trash = true;
			break;
	case SDL_SCANCODE_3:				// 지형 저장 단축키
	case SDL_SCANCODE_KP_3:
		FileManager.SaveTerrain();
		break;

	default:
		break;
	}
}

//카메라 이동 : 전역 좌표 기준
void Viewer::ViewerKeyboardCenterSwitch(SDL_Event event, GLdouble cameraSpeed)
{
	switch (event.key.keysym.scancode)
	{
	case SDL_SCANCODE_I:				// 카메라 X축 '+' 이동
		mainCamera.SetCameraPositionPlusX(cameraSpeed);
		break;

	case SDL_SCANCODE_K:				// 카메라 X축 '-' 이동
		mainCamera.SetCameraPositionPlusX(-cameraSpeed);
		break;

	case SDL_SCANCODE_J:				// 카메라 Z축 '+' 이동
		mainCamera.SetCameraPositionPlusZ(-cameraSpeed);
		break;

	case SDL_SCANCODE_L:				// 카메라 Z축 '-' 이동
		mainCamera.SetCameraPositionPlusZ(cameraSpeed);
		break;

	default:
		break;
	}
}

//카메라 설정값 수정(Z,X : FOV(-/+), C,V : Near(-/+), B,N : Far(-/+), H : WireFrame 모드(On/Off))
void Viewer::ViewerKeyboardPerpectiveSwitch(SDL_Event event, GLdouble cameraSpeed)
{
	switch (event.key.keysym.scancode)
	{
	case SDL_SCANCODE_Z:				//카메라 FOV 값 -
		mainCamera.PlusFovy(-cameraSpeed);
		break;

	case SDL_SCANCODE_X:				//카메라 FOV 값 +
		mainCamera.PlusFovy(cameraSpeed);
		break;

	case SDL_SCANCODE_C:				//카메라 Near 값 -
		mainCamera.PlusZNear(-cameraSpeed);
		break;

	case SDL_SCANCODE_V:				//카메라 Near 값 +
		mainCamera.PlusZNear(cameraSpeed);
		break;

	case SDL_SCANCODE_B:				//카메라 Far 값 -
		mainCamera.PlusZFar(-cameraSpeed);
		break;

	case SDL_SCANCODE_N:				//카메라 Far 값 +
		mainCamera.PlusZFar(cameraSpeed);
		break;
	case SDL_SCANCODE_H:				//WireFrame 모드(On/Off)
		wireMode = !wireMode;
		break;
	case SDL_SCANCODE_KP_PLUS:						//카메라 스피드 Up
		mainCamera.SetCameraSpeed(mainCamera.GetCameraSpeed() + 1);
		if (mainCamera.GetCameraSpeed() > 10)
		{
			mainCamera.SetCameraSpeed(10);
		}
		break;
	case SDL_SCANCODE_KP_MINUS:						// 카메라 스피드 Down
		mainCamera.SetCameraSpeed(mainCamera.GetCameraSpeed() - 1);
		if (mainCamera.GetCameraSpeed() < 1)
		{
			mainCamera.SetCameraSpeed(1);
		}
		break;
	default:
		break;
	}
}

//현재 카메라가 위치하고 있는 에리어를 체크하고 에리어 버퍼를 업데이트
void Viewer::ViewerCheckCameraBlock(GLdouble CameraX, GLdouble CameraZ)
{
	int areaX = mainCamera.GetCameraInAreaX(), areaZ = mainCamera.GetCameraInAreaZ();
	if (areaX != floor(CameraX / 62) ||					//카메라가 현재 위치하고 있는 에리어 위치가 저장된 위치와 다른경우
		areaZ != floor(CameraZ / 62))
	{
		areaX = floor(CameraX / 62);
		areaZ = floor(CameraZ / 62);
		mainCamera.SetCameraInAreaX(areaX);		//카메라가 현재 위치하고 있는 에리어 저장
		mainCamera.SetCameraInAreaZ(areaZ);
		if (!trash)
		{
			UpdateBuffer(areaX, areaZ);					//에리어 버퍼를 수정한다.
		}
	}
}

//메인 View 디스플레이
void Viewer::ViewerViewDisplay()		
{
	GLdouble CameraX, CameraY, CameraZ;
	glPushMatrix();
	glViewport(0, 0, viewerWidth, viewerHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(mainCamera.GetFovy(), (GLsizei)screenWidth / (GLsizei)screenHeight, mainCamera.GetZNear(), mainCamera.GetZFar());
	CameraX = mainCamera.GetCameraPositionX();
	CameraY = mainCamera.GetCameraPositionY();
	CameraZ = mainCamera.GetCameraPositionZ();

	light_pos[0] = CameraX+200;							// 조명의 좌표가 카메라를 따라가도록 함
	light_pos[2] = CameraZ+300;

	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);		// 조명 설정
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, const_att);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);	//지형 설정
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_SHININESS, polished);

	gluLookAt(mainCamera.GetCameraPositionX() + mainCamera.GetCameraZoom(1), mainCamera.GetCameraPositionY() + mainCamera.GetCameraZoom(2), mainCamera.GetCameraPositionZ() + mainCamera.GetCameraZoom(3), mainCamera.GetCameraCenterX(), mainCamera.GetCameraCenterY(), mainCamera.GetCameraCenterZ(), mainCamera.GetCameraUpX(), mainCamera.GetCameraUpY(), mainCamera.GetCameraUpZ());

	ViewerCheckCameraBlock(mainCamera.GetCameraPositionX(), mainCamera.GetCameraPositionZ());
	
	glMatrixMode(GL_MODELVIEW);

	if (FileManager.Terrain != NULL)						// 지형이 생성되지 않을 경우 지형을 디스플레이 하지 않는다.
	{
		if (trash)
		{
			UpdateBuffer(mainCamera.GetCameraInAreaX(), mainCamera.GetCameraInAreaZ());		// 에리어 버퍼를 (0,0) 기준으로 업데이트 해준다.
			trash = false;
		}
		if (!wireMode)
		{
			DrawSolidBuffer(Buffer);								// 지형을 폴리곤으로 표시해준다.
		}
		DrawWireBuffer(Buffer);								// 지형의 WireFrame을 표시해준다.
	}
	
	glPopMatrix();
}

//상단 메뉴 디스플레이
void Viewer::ViewerMenuDisplay()		
{
	glPushMatrix();
	glViewport(0, viewerHeight, menuWidth, menuHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, menuWidth, 0, menuHeight, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(0.17, 0.17, 0.17);
	glBegin(GL_POLYGON);									//메뉴의 색상 표현
	glVertex3f(0, 0, -0.1);
	glVertex3f(menuWidth, 0, -0.1);
	glVertex3f(menuWidth, menuHeight, -0.1);
	glVertex3f(0, menuHeight, -0.1);
	glEnd();

	glColor4f(1.0, 0.5, 0.0, 1.0);
	Texture_Create.DrawTexture(0, 0);
	Texture_Save.DrawTexture(Texture_Create.GetWidth(), 0);
	Texture_Open.DrawTexture(Texture_Create.GetWidth() + Texture_Save.GetWidth(), 0);
	glPopMatrix();
}

//우측 정보창 렌더링
void Viewer::ViewerInfoDisplay()		
{
	glPushMatrix();
	glViewport(viewerWidth, 0, infoWidth, infoHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, infoWidth, 0, infoHeight, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(0.14, 0.14, 0.14);
	glBegin(GL_POLYGON);									// 정보창의 색상 표현
	glVertex3f(0, 0, -0.1);
	glVertex3f(infoWidth, 0, -0.1);
	glVertex3f(infoWidth, infoHeight, -0.1);
	glVertex3f(0, infoHeight, -0.1);
	glEnd();

	//정보창에 표시할 메세지
	std::string infoMessage[15] =
	{
		"     Eye X    : " + std::to_string(mainCamera.GetCameraPositionX()),
		"     Eye Y    : " + std::to_string(mainCamera.GetCameraPositionY()),
		"     Eye Z    : " + std::to_string(mainCamera.GetCameraPositionZ()),
		"   Center X   : " + std::to_string(mainCamera.GetCameraCenterX()),
		"   Center Y   : " + std::to_string(mainCamera.GetCameraCenterY()),
		"   Center Z   : " + std::to_string(mainCamera.GetCameraCenterZ()),
		"Orientation X : " + std::to_string(mainCamera.GetCameraUpX()),
		"Orientation Y : " + std::to_string(mainCamera.GetCameraUpY()),
		"Orientation Z : " + std::to_string(mainCamera.GetCameraUpZ()),
		"      FOV     : " + std::to_string(mainCamera.GetFovy()),
		"     zNear    : " + std::to_string(mainCamera.GetZNear()),
		"     zFar     : " + std::to_string(mainCamera.GetZFar()),
		" CameraSpeed  : " + std::to_string(mainCamera.GetCameraSpeed()),
		"  Camera In   : (" + std::to_string(mainCamera.GetCameraInAreaX()) + "," + std::to_string(mainCamera.GetCameraInAreaZ()) + ")",
		"      FPS     : " + std::to_string(fps)
	};

	for (int i = 0; i < 15; i++)	//정보창 메세지 표시
	{
		ViewerTextRender(10, 40+(i * 30), infoMessage[i].c_str());
	}

	glPopMatrix();
}

//정보창에 메세지를 폰트로 디스플레이
void Viewer::ViewerTextRender(GLfloat x, GLfloat y, const char *text)
{
	int len;
	glRasterPos2f(x, y);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glRasterPos2i(x, y);
	for (int i = 0, len = strlen(text); i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	}
}
