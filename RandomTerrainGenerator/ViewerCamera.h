#pragma once
#include "AllInOne.h"

class ViewerCamera
{
private:
	GLdouble CameraPosition[3];	//ī�޶� ��ġ
	GLdouble CameraCenter[3];	//ī�޶� ����
	GLdouble CameraUp[3];			//ī�޶� ������
	GLdouble fovy;						//ī�޶� FOV��
	GLdouble zNear;					//ī�޶� Near��
	GLdouble zFar;						//ī�޶� Far��
	GLdouble CameraSpeed;		//ī�޶� ���ǵ�
	GLdouble CameraPitch;			//ī�޶� ���Ʒ� ����
	GLdouble CameraYaw;			//ī�޶� �¿� ����
	GLdouble CameraZoom;			//ī�޶� �ܰ�
	int CameraInAreaX, CameraInAreaZ;	//ī�޶� ��ġ�� (X,Z) ������

public:
	ViewerCamera();
	ViewerCamera(GLdouble x, GLdouble y, GLdouble z);
	~ViewerCamera();

	//���� ī�޶� X��ǥ �޾ƿ��� 
	GLdouble GetCameraPositionX();	
	
	//���� ī�޶� Y��ǥ �޾ƿ��� 
	GLdouble GetCameraPositionY();

	//���� ī�޶� Z��ǥ �޾ƿ��� 
	GLdouble GetCameraPositionZ();

	//���� ī�޶� ���� X��ǥ �޾ƿ���
	GLdouble GetCameraCenterX();

	//���� ī�޶� ���� Y��ǥ �޾ƿ���
	GLdouble GetCameraCenterY();

	//���� ī�޶� ���� Z��ǥ �޾ƿ���
	GLdouble GetCameraCenterZ();

	//���� ī�޶� ������X �޾ƿ���
	GLdouble GetCameraUpX();		

	//���� ī�޶� ������Y �޾ƿ���
	GLdouble GetCameraUpY();

	//���� ī�޶� ������Z �޾ƿ���
	GLdouble GetCameraUpZ();

	// FOV�� �޾ƿ���
	GLdouble GetFovy();

	// Near�� �޾ƿ���
	GLdouble GetZNear();

	// Far�� �޾ƿ���
	GLdouble GetZFar();

	//���� ī�޶� �ӵ� �޾ƿ���
	GLdouble GetCameraSpeed();			

	/*���� ī�޶� ��ġ ����*/
	//���� ī�޶� X��ǥ ����
	void SetCameraPositionX(GLdouble value);	

	//���� ī�޶� Y��ǥ ����
	void SetCameraPositionY(GLdouble value);

	//���� ī�޶� Z��ǥ ����
	void SetCameraPositionZ(GLdouble value);

	/*���� ī�޶� ���� ����*/
	//���� ī�޶� ���� X��ǥ ����
	void SetCameraCenterX(GLdouble value);	

	//���� ī�޶� ���� Y��ǥ ����
	void SetCameraCenterY(GLdouble value);

	//���� ī�޶� ���� Z��ǥ ����
	void SetCameraCenterZ(GLdouble value);

	/*���� ī�޶� ������ ����*/
	//���� ī�޶� ������X ����
	void SetCameraUpX(GLdouble value);			

	//���� ī�޶� ������Y ����
	void SetCameraUpY(GLdouble value);

	//���� ī�޶� ������Z ����
	void SetCameraUpZ(GLdouble value);

	/*���� ī�޶� ��ġ +/- */
	//���� ī�޶� X��ǥ +/-
	void SetCameraPositionPlusX(GLdouble value);

	//���� ī�޶� Y��ǥ +/-
	void SetCameraPositionPlusY(GLdouble value);

	//���� ī�޶� Z��ǥ +/-
	void SetCameraPositionPlusZ(GLdouble value);

	/*���� ī�޶� ���� ����*/
	//���� ī�޶� ���� X��ǥ +/-
	void SetCameraCenterPlusX(GLdouble value);

	//���� ī�޶� ���� Y��ǥ +/-
	void SetCameraCenterPlusY(GLdouble value);

	//���� ī�޶� ���� Z��ǥ +/-
	void SetCameraCenterPlusZ(GLdouble value);

	/*���� ī�޶� ������ ����*/
	//���� ī�޶� ������X +/-
	void SetCameraUpPlusX(GLdouble value);

	//���� ī�޶� ������Y +/-
	void SetCameraUpPlusY(GLdouble value);

	//���� ī�޶� ������Z +/-
	void SetCameraUpPlusZ(GLdouble value);

	// FOV�� +/-
	void PlusFovy(GLdouble value);
	
	// Near�� +/-
	void PlusZNear(GLdouble value);

	// Far�� +/-
	void PlusZFar(GLdouble value);

	// ī�޶� �ӵ� +/-
	void PlusCameraSpeed(GLdouble value);		

	// ī�޶� �ӵ� ����
	void SetCameraSpeed(GLdouble value);		
	
	// ī�޶� ���� ��ġ�� ������ ���� �� X��ǥ �޾ƿ���
	int GetCameraInAreaX();				

	// ī�޶� ���� ��ġ�� ������ ���� �� Y��ǥ �޾ƿ���
	int GetCameraInAreaZ();

	// ī�޶� ���� ��ġ�� ������ ���� X��ǥ ����
	void SetCameraInAreaX(int areaX);

	// ī�޶� ���� ��ġ�� ������ ���� Y��ǥ ����
	void SetCameraInAreaZ(int areaZ);

	// ī�޶� Pitch�� ����
	void SetCameraPitch(GLdouble newPitch);

	// ī�޶� Yaw�� ����
	void SetCameraYaw(GLdouble newYaw);

	// ī�޶� Zoom�� ����
	void SetCameraZoom(GLdouble newZoom);

	// ī�޶� Pitch�� �޾ƿ���
	GLdouble GetCameraPitch();

	// ī�޶� Yaw�� �޾ƿ���
	GLdouble GetCameraYaw();

	// ī�޶� Zoom�� �޾ƿ���
	GLdouble GetCameraZoom(short int xyz); // 1->x, 2->y, 3->z

	// ī�޶� ���� ����
	void CameraReset();			

	// ī�޶� Z�� �ݽð� ���� ȸ��
	void CameraUpRotate(float rad);

	// ī�޶� Z�� �ð� ���� ȸ��
	void CameraDownRotate(float rad);

	// ī�޶� Y�� �ݽð� ���� ȸ��
	void CameraRightRotate(float rad);

	// ī�޶� Y�� �ð� ���� ȸ��
	void CameraLeftRotate(float rad);

	// ī�޶� ����
	void CameraFrontMove(float dis);

	// ī�޶� ����
	void CameraBackMove(float dis);

	//ī�޶� ��� �̵�
	void CameraRightMove(float dis);

	//ī�޶� �·� �̵�
	void CameraLeftMove(float dis);
};

