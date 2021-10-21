#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")
#pragma comment(lib,"glut32.lib")

#include <afx.h>
#include <afxwin.h>
#include "InitializeProgram.h"

int main(int argc, char **argv) {

	if (SDL_Init(SDL_INIT_VIDEO))		// SDL �ʱ�ȭ
	{
		printf("Could not initalize SDL - %s", SDL_GetError());
		exit(1);
	}

	AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0);		// MFC �ʱ�ȭ

	InitProgram();	//���� ���α׷� �ʱ�ȭ
	return 0;
}

