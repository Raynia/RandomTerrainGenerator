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

// ���α׷� â �ʱ�ȭ
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

	//SDL �ʱ�ȭ
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("Could not initalize SDL - %s", SDL_GetError());
		exit(1);
	}

	Uint32 flag = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
	//SDL ������, GL ���ؽ�Ʈ �ʱ�ȭ

	screen = SDL_CreateWindow(Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flag);

	SDL_VERSION(&wminfo.version);

	//MFC �ڵ� ����
	if (!SDL_GetWindowWMInfo(screen, &wminfo))
	{
		printf("Handle Init Fail!");
	}

	//MFC �ڵ� �ʱ�ȭ
	hwnd = wminfo.info.win.window;
	pwnd = CWnd::FromHandle(hwnd);
	FileManager.SetHANDLE(pwnd);

	SDL_GLContext context;

	context = SDL_GL_CreateContext(screen);

	// SDL OpenGL ����
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

	// SDL ���� ����
	while (sdlLoopFlag)
	{
		starTick = SDL_GetTicks();
		//SDL �̺�Ʈ ����
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
		ViewerDisplay();			// ȭ�� ������
		SDL_GL_SwapWindow(screen);

		delay = 1000.0 / 30.0 - (SDL_GetTicks() - starTick);	//1 Frame ������ �ɸ��� �ð� ���� �Ͽ� �ʴ� 30Frame�� ���߱� ���� Delay�� ����
		if (delay > 0)															//�ʴ� 30Frame �̸��� ��� Delay���� �ٷ� ���� Frame ����
		{
			SDL_Delay(delay);
		}
		fps = 1000.0f / (float)(SDL_GetTicks() - starTick);		// �ʴ� ǥ�õǴ� Frame �� ���

	}
	SDL_DestroyWindow(screen);
	SDL_GL_DeleteContext(context);
	SDL_Quit();
}

// ���α׷� â �ʺ� ����
void Viewer::SetScreenWidth(int w) 
{ 
	screenWidth = w; 
}

//���α׷� â ���� ����
void Viewer::SetScreenHeight(int h)
{ 
	screenHeight = h; 
}

// ���α׷� â �ʺ� �ޱ�
int Viewer::GetScreenWidth() 
{ 
	return screenWidth; 
}

//���α׷� â ���� �ޱ�
int Viewer::GetScreenHeight() 
{ 
	return screenHeight; 
}

// UI, Viewer ��Ƽ�� ũ�� ����
void Viewer::ChangePartitionValue()
{
	screenRatio = (double)screenWidth / (double)screenHeight;
	menuWidth = screenWidth;
	infoWidth = 300;
	infoHeight = screenHeight - menuHeight;
	viewerWidth = screenWidth - infoWidth;
	viewerHeight = infoHeight;
}

// ������ ���� ������Ʈ
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

// SDL ���÷��� ����
void Viewer::ViewerDisplay() 
{
	glClear(GL_COLOR_BUFFER_BIT);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ViewerViewDisplay();
	ViewerMenuDisplay();
	ViewerInfoDisplay();
}

// SDL Ű���� ����
void Viewer::ViewerKeyboard(SDL_Event event)
{
	GLdouble cameraSpeed = mainCamera.GetCameraSpeed();
	ViewerKeyboardCameraRotate(event);
	ViewerKeyboardEyeSwitch(event,cameraSpeed);
	ViewerKeyboardCenterSwitch(event, cameraSpeed);
	ViewerKeyboardPerpectiveSwitch(event, cameraSpeed);
}

// SDL ���콺 ����
void Viewer::ViewerMouse(SDL_Event event)
{
	switch(event.button.button)
	{
	case SDL_BUTTON_LEFT:
		if (event.button.x >= Texture_Create.GetX1() &&									// 'Create' ��ư�� Ŭ���� ���
			event.button.x <= Texture_Create.GetX2() &&
			event.button.y >= Texture_Create.GetY1() && 
			event.button.y <= Texture_Create.GetY2())
		{
			FileManager.CreateTerrain();
			UpdateBuffer(mainCamera.GetCameraInAreaX(), mainCamera.GetCameraInAreaZ());
		}
		else if (event.button.x >= Texture_Save.GetX1() &&								//'Save' ��ư�� Ŭ���� ���
			event.button.x <= Texture_Save.GetX2() &&
			event.button.y >= Texture_Save.GetY1() &&
			event.button.y <= Texture_Save.GetY2())
		{
			if (FileManager.Terrain != NULL)														//������ ������ ��쿡�� ���� ����
			{
				FileManager.SaveTerrain();
			}
			else
			{
				MessageBoxA(NULL, "Terrain is Empty!", "FileManager", MB_OK);	//������ �������� �ʾ����� �����ϴ� ��� ���â�� �߻���Ų��.
			}
		}
		else if (event.button.x >= Texture_Open.GetX1() &&								//'Open' ��ư�� Ŭ���� ���
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

// SDL ���콺 �� ���� : ���� Ȯ��/���
void Viewer::ViewerWheel(SDL_Event event)
{
	mainCamera.SetCameraZoom(event.wheel.y * 0.01);
}

//ī�޶� ȸ�� : ī�޶� ������ ����
void Viewer::ViewerKeyboardCameraRotate(SDL_Event event) 
{
	GLfloat tempPitch;
	GLfloat tempYaw;
	switch (event.key.keysym.scancode)
	{
	case SDL_SCANCODE_UP:				//ī�޶� ������ ���� Z�� �ݽð� ȸ��
		tempPitch = mainCamera.GetCameraPitch() + 1.0;
		if (tempPitch > 180) tempPitch = 1.0;
		mainCamera.SetCameraPitch(tempPitch);
		mainCamera.SetCameraCenterX(1000 *cos(mainCamera.GetCameraPitch()*3.1415 / 90)*sin(mainCamera.GetCameraYaw()*3.1415 / 90));
		mainCamera.SetCameraCenterY(1000 *sin(mainCamera.GetCameraPitch()*3.1415 / 90));
		mainCamera.SetCameraCenterZ(1000 *cos(mainCamera.GetCameraPitch()*3.1415 / 90)*cos(mainCamera.GetCameraYaw()*3.1415 / 90));
		break;

	case SDL_SCANCODE_DOWN:			//ī�޶� ������ ���� Z�� �ð� ȸ��
		tempPitch = mainCamera.GetCameraPitch() - 1.0;
		if (tempPitch < 1) tempPitch = 180.0;
		mainCamera.SetCameraPitch(tempPitch);
		mainCamera.SetCameraCenterX(1000 *cos(mainCamera.GetCameraPitch()*3.1415 / 90)*sin(mainCamera.GetCameraYaw()*3.1415 / 90));
		mainCamera.SetCameraCenterY(1000 *sin(mainCamera.GetCameraPitch()*3.1415 / 90));
		mainCamera.SetCameraCenterZ(1000 *cos(mainCamera.GetCameraPitch()*3.1415 / 90)*cos(mainCamera.GetCameraYaw()*3.1415 / 90));
		break;

	case SDL_SCANCODE_RIGHT:			//ī�޶� ������ ���� Y�� �ݽð� ȸ��
		tempYaw = mainCamera.GetCameraYaw() - 1.0;
		if (tempYaw < 1) tempYaw = 180.0;
		mainCamera.SetCameraYaw(tempYaw);
		mainCamera.SetCameraCenterX(1000 * cos(mainCamera.GetCameraPitch()*3.1415 / 90)*sin(mainCamera.GetCameraYaw()*3.1415 / 90));
		mainCamera.SetCameraCenterY(1000 * sin(mainCamera.GetCameraPitch()*3.1415 / 90));
		mainCamera.SetCameraCenterZ(1000 * cos(mainCamera.GetCameraPitch()*3.1415 / 90)*cos(mainCamera.GetCameraYaw()*3.1415 / 90));
		break;

	case SDL_SCANCODE_LEFT:				//ī�޶� ������ ���� Y�� �ð� ȸ��
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

//ī�޶� �̵� : ī�޶� ��ǥ ����
void Viewer::ViewerKeyboardEyeSwitch(SDL_Event event, GLdouble cameraSpeed)
{
	int seed = 100;
	switch (event.key.keysym.scancode)
	{
	case SDL_SCANCODE_D:				// ī�޶� ��� �̵�
		mainCamera.CameraRightMove(3.0);
		break;

	case SDL_SCANCODE_A:				// ī�޶� �·� �̵�
		mainCamera.CameraLeftMove(3.0);
		break;

	case SDL_SCANCODE_W:				// ī�޶� ������ �̵�
		mainCamera.CameraFrontMove(0.01);
		break;

	case SDL_SCANCODE_S:				// ī�޶� �ڷ� �̵�
		mainCamera.CameraBackMove(0.01);
		break;

	case SDL_SCANCODE_Q:				// ī�޶� ���� '-' �̵�
		mainCamera.SetCameraPositionPlusY(-cameraSpeed);
		break;

	case SDL_SCANCODE_E:				// ī�޶� ���� '+' �̵�
		mainCamera.SetCameraPositionPlusY(cameraSpeed);
		break;

	case SDL_SCANCODE_R:				// ī�޶� ��ġ, ���� ����
		mainCamera.CameraReset();
		break;

	case SDL_SCANCODE_1:				// ���� ���� ����Ű
	case SDL_SCANCODE_KP_1:
		FileManager.CreateTerrain();
		trash = true;
		break;
	case SDL_SCANCODE_2:				// ���� �ҷ����� ����Ű
	case SDL_SCANCODE_KP_2:
		FileManager.OpenTerrain();
		trash = true;
			break;
	case SDL_SCANCODE_3:				// ���� ���� ����Ű
	case SDL_SCANCODE_KP_3:
		FileManager.SaveTerrain();
		break;

	default:
		break;
	}
}

//ī�޶� �̵� : ���� ��ǥ ����
void Viewer::ViewerKeyboardCenterSwitch(SDL_Event event, GLdouble cameraSpeed)
{
	switch (event.key.keysym.scancode)
	{
	case SDL_SCANCODE_I:				// ī�޶� X�� '+' �̵�
		mainCamera.SetCameraPositionPlusX(cameraSpeed);
		break;

	case SDL_SCANCODE_K:				// ī�޶� X�� '-' �̵�
		mainCamera.SetCameraPositionPlusX(-cameraSpeed);
		break;

	case SDL_SCANCODE_J:				// ī�޶� Z�� '+' �̵�
		mainCamera.SetCameraPositionPlusZ(-cameraSpeed);
		break;

	case SDL_SCANCODE_L:				// ī�޶� Z�� '-' �̵�
		mainCamera.SetCameraPositionPlusZ(cameraSpeed);
		break;

	default:
		break;
	}
}

//ī�޶� ������ ����(Z,X : FOV(-/+), C,V : Near(-/+), B,N : Far(-/+), H : WireFrame ���(On/Off))
void Viewer::ViewerKeyboardPerpectiveSwitch(SDL_Event event, GLdouble cameraSpeed)
{
	switch (event.key.keysym.scancode)
	{
	case SDL_SCANCODE_Z:				//ī�޶� FOV �� -
		mainCamera.PlusFovy(-cameraSpeed);
		break;

	case SDL_SCANCODE_X:				//ī�޶� FOV �� +
		mainCamera.PlusFovy(cameraSpeed);
		break;

	case SDL_SCANCODE_C:				//ī�޶� Near �� -
		mainCamera.PlusZNear(-cameraSpeed);
		break;

	case SDL_SCANCODE_V:				//ī�޶� Near �� +
		mainCamera.PlusZNear(cameraSpeed);
		break;

	case SDL_SCANCODE_B:				//ī�޶� Far �� -
		mainCamera.PlusZFar(-cameraSpeed);
		break;

	case SDL_SCANCODE_N:				//ī�޶� Far �� +
		mainCamera.PlusZFar(cameraSpeed);
		break;
	case SDL_SCANCODE_H:				//WireFrame ���(On/Off)
		wireMode = !wireMode;
		break;
	case SDL_SCANCODE_KP_PLUS:						//ī�޶� ���ǵ� Up
		mainCamera.SetCameraSpeed(mainCamera.GetCameraSpeed() + 1);
		if (mainCamera.GetCameraSpeed() > 10)
		{
			mainCamera.SetCameraSpeed(10);
		}
		break;
	case SDL_SCANCODE_KP_MINUS:						// ī�޶� ���ǵ� Down
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

//���� ī�޶� ��ġ�ϰ� �ִ� ����� üũ�ϰ� ������ ���۸� ������Ʈ
void Viewer::ViewerCheckCameraBlock(GLdouble CameraX, GLdouble CameraZ)
{
	int areaX = mainCamera.GetCameraInAreaX(), areaZ = mainCamera.GetCameraInAreaZ();
	if (areaX != floor(CameraX / 62) ||					//ī�޶� ���� ��ġ�ϰ� �ִ� ������ ��ġ�� ����� ��ġ�� �ٸ����
		areaZ != floor(CameraZ / 62))
	{
		areaX = floor(CameraX / 62);
		areaZ = floor(CameraZ / 62);
		mainCamera.SetCameraInAreaX(areaX);		//ī�޶� ���� ��ġ�ϰ� �ִ� ������ ����
		mainCamera.SetCameraInAreaZ(areaZ);
		if (!trash)
		{
			UpdateBuffer(areaX, areaZ);					//������ ���۸� �����Ѵ�.
		}
	}
}

//���� View ���÷���
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

	light_pos[0] = CameraX+200;							// ������ ��ǥ�� ī�޶� ���󰡵��� ��
	light_pos[2] = CameraZ+300;

	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);		// ���� ����
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, const_att);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);	//���� ����
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_SHININESS, polished);

	gluLookAt(mainCamera.GetCameraPositionX() + mainCamera.GetCameraZoom(1), mainCamera.GetCameraPositionY() + mainCamera.GetCameraZoom(2), mainCamera.GetCameraPositionZ() + mainCamera.GetCameraZoom(3), mainCamera.GetCameraCenterX(), mainCamera.GetCameraCenterY(), mainCamera.GetCameraCenterZ(), mainCamera.GetCameraUpX(), mainCamera.GetCameraUpY(), mainCamera.GetCameraUpZ());

	ViewerCheckCameraBlock(mainCamera.GetCameraPositionX(), mainCamera.GetCameraPositionZ());
	
	glMatrixMode(GL_MODELVIEW);

	if (FileManager.Terrain != NULL)						// ������ �������� ���� ��� ������ ���÷��� ���� �ʴ´�.
	{
		if (trash)
		{
			UpdateBuffer(mainCamera.GetCameraInAreaX(), mainCamera.GetCameraInAreaZ());		// ������ ���۸� (0,0) �������� ������Ʈ ���ش�.
			trash = false;
		}
		if (!wireMode)
		{
			DrawSolidBuffer(Buffer);								// ������ ���������� ǥ�����ش�.
		}
		DrawWireBuffer(Buffer);								// ������ WireFrame�� ǥ�����ش�.
	}
	
	glPopMatrix();
}

//��� �޴� ���÷���
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
	glBegin(GL_POLYGON);									//�޴��� ���� ǥ��
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

//���� ����â ������
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
	glBegin(GL_POLYGON);									// ����â�� ���� ǥ��
	glVertex3f(0, 0, -0.1);
	glVertex3f(infoWidth, 0, -0.1);
	glVertex3f(infoWidth, infoHeight, -0.1);
	glVertex3f(0, infoHeight, -0.1);
	glEnd();

	//����â�� ǥ���� �޼���
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

	for (int i = 0; i < 15; i++)	//����â �޼��� ǥ��
	{
		ViewerTextRender(10, 40+(i * 30), infoMessage[i].c_str());
	}

	glPopMatrix();
}

//����â�� �޼����� ��Ʈ�� ���÷���
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
