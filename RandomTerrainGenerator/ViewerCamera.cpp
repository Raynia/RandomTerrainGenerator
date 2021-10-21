#include "ViewerCamera.h"

enum Position { X, Y, Z };

ViewerCamera::ViewerCamera()
{
	CameraReset();
}

ViewerCamera::ViewerCamera(GLdouble x, GLdouble y, GLdouble z) 
{

}

ViewerCamera::~ViewerCamera()
{
}

//현재 카메라 X좌표 받아오기 
GLdouble ViewerCamera::GetCameraPositionX() 
{ 
	return CameraPosition[X]; 
}

//현재 카메라 Y좌표 받아오기 
GLdouble ViewerCamera::GetCameraPositionY()
{ 
	return CameraPosition[Y]; 
}

//현재 카메라 Z좌표 받아오기 
GLdouble ViewerCamera::GetCameraPositionZ()
{
	return CameraPosition[Z]; 
}

//현재 카메라 시점 X좌표 받아오기
GLdouble ViewerCamera::GetCameraCenterX()
{
	return CameraCenter[X] + CameraPosition[X];
}

//현재 카메라 시점 Y좌표 받아오기
GLdouble ViewerCamera::GetCameraCenterY() 
{ 
	return CameraCenter[Y] + CameraPosition[Y];
}

//현재 카메라 시점 Z좌표 받아오기
GLdouble ViewerCamera::GetCameraCenterZ()
{ 
	return CameraCenter[Z] + CameraPosition[Z]; 
}

//현재 카메라 방향축X 받아오기
GLdouble ViewerCamera::GetCameraUpX()
{
	return CameraUp[X];
}

//현재 카메라 방향축Y 받아오기
GLdouble ViewerCamera::GetCameraUpY() 
{
	return CameraUp[Y]; 
}

//현재 카메라 방향축Z 받아오기
GLdouble ViewerCamera::GetCameraUpZ() 
{
	return CameraUp[Z]; 
}

// FOV값 받아오기
GLdouble ViewerCamera::GetFovy()
{
	return fovy; 
}

// Near값 받아오기
GLdouble ViewerCamera::GetZNear()
{ 
	return zNear; 
}

// Far값 받아오기
GLdouble ViewerCamera::GetZFar() 
{
	return zFar; 
}

//현재 카메라 속도 받아오기
GLdouble ViewerCamera::GetCameraSpeed()
{ 
	return CameraSpeed; 
}

// 카메라 Pitch값 받아오기
GLdouble ViewerCamera::GetCameraPitch() 
{ 
	return CameraPitch; 
}

// 카메라 Yaw값 받아오기
GLdouble ViewerCamera::GetCameraYaw() 
{
	return CameraYaw;
}

// 카메라 Zoom값 받아오기
GLdouble ViewerCamera::GetCameraZoom(short int xyz) //x=1,y=2,z=3
{
	switch (xyz) {
	case 1:
		return CameraCenter[X] * CameraZoom;
		break;
	case 2:
		return CameraCenter[Y] * CameraZoom;
		break;
	case 3:
		return CameraCenter[Z] * CameraZoom;
		break;
	}
}

//현재 카메라 X좌표 설정
void ViewerCamera::SetCameraPositionX(GLdouble value) 
{
	CameraPosition[X] = value; 
}

//현재 카메라 Y좌표 설정
void ViewerCamera::SetCameraPositionY(GLdouble value)
{ 
	CameraPosition[Y] = value; 
}

//현재 카메라 Z좌표 설정
void ViewerCamera::SetCameraPositionZ(GLdouble value) 
{
	CameraPosition[Z] = value;
}

//현재 카메라 시점 X좌표 설정
void ViewerCamera::SetCameraCenterX(GLdouble value) 
{ 
	CameraCenter[X] = value;
}

//현재 카메라 시점 Y좌표 설정
void ViewerCamera::SetCameraCenterY(GLdouble value) 
{ 
	CameraCenter[Y] = value; 
}

//현재 카메라 시점 Z좌표 설정
void ViewerCamera::SetCameraCenterZ(GLdouble value)
{ 
	CameraCenter[Z] = value; 
}

//현재 카메라 방향축X 설정
void ViewerCamera::SetCameraUpX(GLdouble value)
{ 
	CameraUp[X] = value;
}

//현재 카메라 방향축Y 설정
void ViewerCamera::SetCameraUpY(GLdouble value) 
{ 
	CameraUp[Y] = value;
}

//현재 카메라 방향축Z 설정
void ViewerCamera::SetCameraUpZ(GLdouble value) 
{ 
	CameraUp[Z] = value;
}

//현재 카메라 X좌표 +/-
void ViewerCamera::SetCameraPositionPlusX(GLdouble value) 
{ 
	CameraPosition[X] += value;
}

//현재 카메라 Y좌표 +/-
void ViewerCamera::SetCameraPositionPlusY(GLdouble value)
{ 
	CameraPosition[Y] += value; 
}

//현재 카메라 Z좌표 +/-
void ViewerCamera::SetCameraPositionPlusZ(GLdouble value) 
{ 
	CameraPosition[Z] += value; 
}

//현재 카메라 시점 X좌표 +/-
void ViewerCamera::SetCameraCenterPlusX(GLdouble value) 
{ 
	CameraCenter[X] += value; 
}

//현재 카메라 시점 Y좌표 +/-
void ViewerCamera::SetCameraCenterPlusY(GLdouble value) 
{ 
	CameraCenter[Y] += value;
}

//현재 카메라 시점 Z좌표 +/-
void ViewerCamera::SetCameraCenterPlusZ(GLdouble value) 
{ 
	CameraCenter[Z] += value;
}

//현재 카메라 방향축X +/-
void ViewerCamera::SetCameraUpPlusX(GLdouble value) 
{ 
	CameraUp[X] += value;
}

//현재 카메라 방향축Y +/-
void ViewerCamera::SetCameraUpPlusY(GLdouble value)
{
	CameraUp[Y] += value;
}

//현재 카메라 방향축Z +/-
void ViewerCamera::SetCameraUpPlusZ(GLdouble value) 
{ 
	CameraUp[Z] += value; 
}

// FOV값 +/-
void ViewerCamera::PlusFovy(GLdouble value) 
{ 
	fovy += value; 
}

// Near값 +/-
void ViewerCamera::PlusZNear(GLdouble value)
{
	zNear += value;
}

// Far값 +/-
void ViewerCamera::PlusZFar(GLdouble value)
{ 
	zFar += value; 
}

// 카메라 속도 +/-
void ViewerCamera::PlusCameraSpeed(GLdouble value)
{ 
	CameraSpeed += value; 
}

// 카메라 속도 설정
void ViewerCamera::SetCameraSpeed(GLdouble value) 
{ 
	CameraSpeed = value; 
}

// 카메라가 현재 위치한 에리어 지형 내 X좌표 받아오기
int ViewerCamera::GetCameraInAreaX()
{
	return CameraInAreaX;
}

// 카메라가 현재 위치한 에리어 지형 내 Y좌표 받아오기
int ViewerCamera::GetCameraInAreaZ()
{
	return CameraInAreaZ;
}

// 카메라가 현재 위치한 에리어 지형 X좌표 설정
void ViewerCamera::SetCameraInAreaX(int AreaX)
{
	CameraInAreaX = AreaX; 
}

// 카메라가 현재 위치한 에리어 지형 Y좌표 설정
void ViewerCamera::SetCameraInAreaZ(int AreaZ)
{
	CameraInAreaZ = AreaZ; 
}

// 카메라 Pitch값 수정
void ViewerCamera::SetCameraPitch(GLdouble newPitch)
{ 
	CameraPitch = newPitch; 
}

// 카메라 Yaw값 수정
void ViewerCamera::SetCameraYaw(GLdouble newYaw) 
{ 
	CameraYaw = newYaw; 
}

// 카메라 Zoom값 수정
void ViewerCamera::SetCameraZoom(GLdouble newZoom)
{
	if (CameraZoom >= 0.8) // 줌인 한계치
	{ 
		if (newZoom < 0) 
		{
			CameraZoom += newZoom;
		}
	}
	else if (CameraZoom <= -2.0) // 줌아웃 한계치
	{ 
		if (newZoom > 0) 
		{
			CameraZoom += newZoom;
		}
	}
	else
	{
		CameraZoom += newZoom;
	}
}



// 카메라 설정 리셋
void ViewerCamera::CameraReset()
{
	CameraPosition[X] = -30.0;
	CameraPosition[Y] = 100.0;
	CameraPosition[Z] = 0.0;

	CameraCenter[X] = 30.0;
	CameraCenter[Y] = -127.0;
	CameraCenter[Z] = 0.0;

	CameraUp[X] = 0.0;
	CameraUp[Y] = 1.0;
	CameraUp[Z] = 0.0;

	fovy = 50;
	zNear = 5.0;
	zFar = 600.0;

	CameraPitch = 142;
	CameraYaw = 45;
	CameraZoom = 0.0;

	CameraSpeed = 5;
}

// 카메라 Z축 반시계 방향 회전
void ViewerCamera::CameraUpRotate(float rad)
{
	CameraPitch += rad;
	if (CameraPitch >= 89.0)
	{
		CameraPitch = 89.0;
	}

	CameraCenter[X] -= CameraPosition[X];
	CameraCenter[Y] -= CameraPosition[Y];
	CameraCenter[Z] -= CameraCenter[Z];

	CameraCenter[X] = std::cos(CameraPitch)*CameraCenter[X] - std::sin(CameraPitch)*CameraCenter[Y];
	CameraCenter[Y] = std::sin(CameraPitch)*CameraCenter[X] + std::cos(CameraPitch)*CameraCenter[Y];

	CameraCenter[X] += CameraPosition[X];
	CameraCenter[Y] += CameraPosition[Y];
	CameraCenter[Z] += CameraCenter[Z];
}

// 카메라 Z축 시계 방향 회전
void ViewerCamera::CameraDownRotate(float rad)
{
	CameraPitch -= rad;
	if (CameraPitch <= -89.0)
	{
		CameraPitch = -89.0;
	}

	CameraCenter[X] -= CameraPosition[X];
	CameraCenter[Y] -= CameraPosition[Y];
	CameraCenter[Z] -= CameraCenter[Z];

	CameraCenter[X] = std::cos(CameraPitch)*CameraCenter[X] - std::sin(CameraPitch)*CameraCenter[Y];
	CameraCenter[Y] = std::sin(CameraPitch)*CameraCenter[X] + std::cos(CameraPitch)*CameraCenter[Y];

	CameraCenter[X] += CameraPosition[X];
	CameraCenter[Y] += CameraPosition[Y];
	CameraCenter[Z] += CameraCenter[Z];
}

// 카메라 Y축 반시계 방향 회전
void ViewerCamera::CameraRightRotate(float rad)
{
	CameraYaw += rad;
}

// 카메라 Y축 시계 방향 회전
void ViewerCamera::CameraLeftRotate(float rad)
{
	CameraYaw -= rad;
}

// 카메라 전진
void ViewerCamera::CameraFrontMove(float dis)
{
	CameraPosition[X] += CameraCenter[X] * dis;
	CameraPosition[Y] += CameraCenter[Y] * dis;
	CameraPosition[Z] += CameraCenter[Z] * dis;
}

// 카메라 후진
void ViewerCamera::CameraBackMove(float dis)
{
	CameraPosition[X] -= CameraCenter[X] * dis;
	CameraPosition[Y] -= CameraCenter[Y] * dis;
	CameraPosition[Z] -= CameraCenter[Z] * dis;
}

//카메라 우로 이동
void ViewerCamera::CameraRightMove(float dis)
{
	CameraPosition[X] -= dis * cos(CameraPitch * 3.1415 / 90) * sin((CameraYaw + 45) * 3.1415 / 90);
	CameraPosition[Z] -= dis * cos(CameraPitch * 3.1415 / 90) * cos((CameraYaw + 45) * 3.1415 / 90);
}

//카메라 좌로 이동
void ViewerCamera::CameraLeftMove(float dis)
{
	CameraPosition[X] += dis * cos(CameraPitch * 3.1415 / 90) * sin((CameraYaw + 45) * 3.1415 / 90);
	CameraPosition[Z] += dis * cos(CameraPitch * 3.1415 / 90) * cos((CameraYaw + 45) * 3.1415 / 90);
}