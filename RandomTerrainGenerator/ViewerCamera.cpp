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

//���� ī�޶� X��ǥ �޾ƿ��� 
GLdouble ViewerCamera::GetCameraPositionX() 
{ 
	return CameraPosition[X]; 
}

//���� ī�޶� Y��ǥ �޾ƿ��� 
GLdouble ViewerCamera::GetCameraPositionY()
{ 
	return CameraPosition[Y]; 
}

//���� ī�޶� Z��ǥ �޾ƿ��� 
GLdouble ViewerCamera::GetCameraPositionZ()
{
	return CameraPosition[Z]; 
}

//���� ī�޶� ���� X��ǥ �޾ƿ���
GLdouble ViewerCamera::GetCameraCenterX()
{
	return CameraCenter[X] + CameraPosition[X];
}

//���� ī�޶� ���� Y��ǥ �޾ƿ���
GLdouble ViewerCamera::GetCameraCenterY() 
{ 
	return CameraCenter[Y] + CameraPosition[Y];
}

//���� ī�޶� ���� Z��ǥ �޾ƿ���
GLdouble ViewerCamera::GetCameraCenterZ()
{ 
	return CameraCenter[Z] + CameraPosition[Z]; 
}

//���� ī�޶� ������X �޾ƿ���
GLdouble ViewerCamera::GetCameraUpX()
{
	return CameraUp[X];
}

//���� ī�޶� ������Y �޾ƿ���
GLdouble ViewerCamera::GetCameraUpY() 
{
	return CameraUp[Y]; 
}

//���� ī�޶� ������Z �޾ƿ���
GLdouble ViewerCamera::GetCameraUpZ() 
{
	return CameraUp[Z]; 
}

// FOV�� �޾ƿ���
GLdouble ViewerCamera::GetFovy()
{
	return fovy; 
}

// Near�� �޾ƿ���
GLdouble ViewerCamera::GetZNear()
{ 
	return zNear; 
}

// Far�� �޾ƿ���
GLdouble ViewerCamera::GetZFar() 
{
	return zFar; 
}

//���� ī�޶� �ӵ� �޾ƿ���
GLdouble ViewerCamera::GetCameraSpeed()
{ 
	return CameraSpeed; 
}

// ī�޶� Pitch�� �޾ƿ���
GLdouble ViewerCamera::GetCameraPitch() 
{ 
	return CameraPitch; 
}

// ī�޶� Yaw�� �޾ƿ���
GLdouble ViewerCamera::GetCameraYaw() 
{
	return CameraYaw;
}

// ī�޶� Zoom�� �޾ƿ���
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

//���� ī�޶� X��ǥ ����
void ViewerCamera::SetCameraPositionX(GLdouble value) 
{
	CameraPosition[X] = value; 
}

//���� ī�޶� Y��ǥ ����
void ViewerCamera::SetCameraPositionY(GLdouble value)
{ 
	CameraPosition[Y] = value; 
}

//���� ī�޶� Z��ǥ ����
void ViewerCamera::SetCameraPositionZ(GLdouble value) 
{
	CameraPosition[Z] = value;
}

//���� ī�޶� ���� X��ǥ ����
void ViewerCamera::SetCameraCenterX(GLdouble value) 
{ 
	CameraCenter[X] = value;
}

//���� ī�޶� ���� Y��ǥ ����
void ViewerCamera::SetCameraCenterY(GLdouble value) 
{ 
	CameraCenter[Y] = value; 
}

//���� ī�޶� ���� Z��ǥ ����
void ViewerCamera::SetCameraCenterZ(GLdouble value)
{ 
	CameraCenter[Z] = value; 
}

//���� ī�޶� ������X ����
void ViewerCamera::SetCameraUpX(GLdouble value)
{ 
	CameraUp[X] = value;
}

//���� ī�޶� ������Y ����
void ViewerCamera::SetCameraUpY(GLdouble value) 
{ 
	CameraUp[Y] = value;
}

//���� ī�޶� ������Z ����
void ViewerCamera::SetCameraUpZ(GLdouble value) 
{ 
	CameraUp[Z] = value;
}

//���� ī�޶� X��ǥ +/-
void ViewerCamera::SetCameraPositionPlusX(GLdouble value) 
{ 
	CameraPosition[X] += value;
}

//���� ī�޶� Y��ǥ +/-
void ViewerCamera::SetCameraPositionPlusY(GLdouble value)
{ 
	CameraPosition[Y] += value; 
}

//���� ī�޶� Z��ǥ +/-
void ViewerCamera::SetCameraPositionPlusZ(GLdouble value) 
{ 
	CameraPosition[Z] += value; 
}

//���� ī�޶� ���� X��ǥ +/-
void ViewerCamera::SetCameraCenterPlusX(GLdouble value) 
{ 
	CameraCenter[X] += value; 
}

//���� ī�޶� ���� Y��ǥ +/-
void ViewerCamera::SetCameraCenterPlusY(GLdouble value) 
{ 
	CameraCenter[Y] += value;
}

//���� ī�޶� ���� Z��ǥ +/-
void ViewerCamera::SetCameraCenterPlusZ(GLdouble value) 
{ 
	CameraCenter[Z] += value;
}

//���� ī�޶� ������X +/-
void ViewerCamera::SetCameraUpPlusX(GLdouble value) 
{ 
	CameraUp[X] += value;
}

//���� ī�޶� ������Y +/-
void ViewerCamera::SetCameraUpPlusY(GLdouble value)
{
	CameraUp[Y] += value;
}

//���� ī�޶� ������Z +/-
void ViewerCamera::SetCameraUpPlusZ(GLdouble value) 
{ 
	CameraUp[Z] += value; 
}

// FOV�� +/-
void ViewerCamera::PlusFovy(GLdouble value) 
{ 
	fovy += value; 
}

// Near�� +/-
void ViewerCamera::PlusZNear(GLdouble value)
{
	zNear += value;
}

// Far�� +/-
void ViewerCamera::PlusZFar(GLdouble value)
{ 
	zFar += value; 
}

// ī�޶� �ӵ� +/-
void ViewerCamera::PlusCameraSpeed(GLdouble value)
{ 
	CameraSpeed += value; 
}

// ī�޶� �ӵ� ����
void ViewerCamera::SetCameraSpeed(GLdouble value) 
{ 
	CameraSpeed = value; 
}

// ī�޶� ���� ��ġ�� ������ ���� �� X��ǥ �޾ƿ���
int ViewerCamera::GetCameraInAreaX()
{
	return CameraInAreaX;
}

// ī�޶� ���� ��ġ�� ������ ���� �� Y��ǥ �޾ƿ���
int ViewerCamera::GetCameraInAreaZ()
{
	return CameraInAreaZ;
}

// ī�޶� ���� ��ġ�� ������ ���� X��ǥ ����
void ViewerCamera::SetCameraInAreaX(int AreaX)
{
	CameraInAreaX = AreaX; 
}

// ī�޶� ���� ��ġ�� ������ ���� Y��ǥ ����
void ViewerCamera::SetCameraInAreaZ(int AreaZ)
{
	CameraInAreaZ = AreaZ; 
}

// ī�޶� Pitch�� ����
void ViewerCamera::SetCameraPitch(GLdouble newPitch)
{ 
	CameraPitch = newPitch; 
}

// ī�޶� Yaw�� ����
void ViewerCamera::SetCameraYaw(GLdouble newYaw) 
{ 
	CameraYaw = newYaw; 
}

// ī�޶� Zoom�� ����
void ViewerCamera::SetCameraZoom(GLdouble newZoom)
{
	if (CameraZoom >= 0.8) // ���� �Ѱ�ġ
	{ 
		if (newZoom < 0) 
		{
			CameraZoom += newZoom;
		}
	}
	else if (CameraZoom <= -2.0) // �ܾƿ� �Ѱ�ġ
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



// ī�޶� ���� ����
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

// ī�޶� Z�� �ݽð� ���� ȸ��
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

// ī�޶� Z�� �ð� ���� ȸ��
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

// ī�޶� Y�� �ݽð� ���� ȸ��
void ViewerCamera::CameraRightRotate(float rad)
{
	CameraYaw += rad;
}

// ī�޶� Y�� �ð� ���� ȸ��
void ViewerCamera::CameraLeftRotate(float rad)
{
	CameraYaw -= rad;
}

// ī�޶� ����
void ViewerCamera::CameraFrontMove(float dis)
{
	CameraPosition[X] += CameraCenter[X] * dis;
	CameraPosition[Y] += CameraCenter[Y] * dis;
	CameraPosition[Z] += CameraCenter[Z] * dis;
}

// ī�޶� ����
void ViewerCamera::CameraBackMove(float dis)
{
	CameraPosition[X] -= CameraCenter[X] * dis;
	CameraPosition[Y] -= CameraCenter[Y] * dis;
	CameraPosition[Z] -= CameraCenter[Z] * dis;
}

//ī�޶� ��� �̵�
void ViewerCamera::CameraRightMove(float dis)
{
	CameraPosition[X] -= dis * cos(CameraPitch * 3.1415 / 90) * sin((CameraYaw + 45) * 3.1415 / 90);
	CameraPosition[Z] -= dis * cos(CameraPitch * 3.1415 / 90) * cos((CameraYaw + 45) * 3.1415 / 90);
}

//ī�޶� �·� �̵�
void ViewerCamera::CameraLeftMove(float dis)
{
	CameraPosition[X] += dis * cos(CameraPitch * 3.1415 / 90) * sin((CameraYaw + 45) * 3.1415 / 90);
	CameraPosition[Z] += dis * cos(CameraPitch * 3.1415 / 90) * cos((CameraYaw + 45) * 3.1415 / 90);
}