#pragma once
#include "AllInOne.h"

class ViewerCamera
{
private:
	GLdouble CameraPosition[3];	//카메라 위치
	GLdouble CameraCenter[3];	//카메라 시점
	GLdouble CameraUp[3];			//카메라 방향축
	GLdouble fovy;						//카메라 FOV값
	GLdouble zNear;					//카메라 Near값
	GLdouble zFar;						//카메라 Far값
	GLdouble CameraSpeed;		//카메라 스피드
	GLdouble CameraPitch;			//카메라 위아래 각도
	GLdouble CameraYaw;			//카메라 좌우 각도
	GLdouble CameraZoom;			//카메라 줌값
	int CameraInAreaX, CameraInAreaZ;	//카메라가 위치한 (X,Z) 에리어

public:
	ViewerCamera();
	ViewerCamera(GLdouble x, GLdouble y, GLdouble z);
	~ViewerCamera();

	//현재 카메라 X좌표 받아오기 
	GLdouble GetCameraPositionX();	
	
	//현재 카메라 Y좌표 받아오기 
	GLdouble GetCameraPositionY();

	//현재 카메라 Z좌표 받아오기 
	GLdouble GetCameraPositionZ();

	//현재 카메라 시점 X좌표 받아오기
	GLdouble GetCameraCenterX();

	//현재 카메라 시점 Y좌표 받아오기
	GLdouble GetCameraCenterY();

	//현재 카메라 시점 Z좌표 받아오기
	GLdouble GetCameraCenterZ();

	//현재 카메라 방향축X 받아오기
	GLdouble GetCameraUpX();		

	//현재 카메라 방향축Y 받아오기
	GLdouble GetCameraUpY();

	//현재 카메라 방향축Z 받아오기
	GLdouble GetCameraUpZ();

	// FOV값 받아오기
	GLdouble GetFovy();

	// Near값 받아오기
	GLdouble GetZNear();

	// Far값 받아오기
	GLdouble GetZFar();

	//현재 카메라 속도 받아오기
	GLdouble GetCameraSpeed();			

	/*현재 카메라 위치 설정*/
	//현재 카메라 X좌표 설정
	void SetCameraPositionX(GLdouble value);	

	//현재 카메라 Y좌표 설정
	void SetCameraPositionY(GLdouble value);

	//현재 카메라 Z좌표 설정
	void SetCameraPositionZ(GLdouble value);

	/*현재 카메라 시점 설정*/
	//현재 카메라 시점 X좌표 설정
	void SetCameraCenterX(GLdouble value);	

	//현재 카메라 시점 Y좌표 설정
	void SetCameraCenterY(GLdouble value);

	//현재 카메라 시점 Z좌표 설정
	void SetCameraCenterZ(GLdouble value);

	/*현재 카메라 방향축 설정*/
	//현재 카메라 방향축X 설정
	void SetCameraUpX(GLdouble value);			

	//현재 카메라 방향축Y 설정
	void SetCameraUpY(GLdouble value);

	//현재 카메라 방향축Z 설정
	void SetCameraUpZ(GLdouble value);

	/*현재 카메라 위치 +/- */
	//현재 카메라 X좌표 +/-
	void SetCameraPositionPlusX(GLdouble value);

	//현재 카메라 Y좌표 +/-
	void SetCameraPositionPlusY(GLdouble value);

	//현재 카메라 Z좌표 +/-
	void SetCameraPositionPlusZ(GLdouble value);

	/*현재 카메라 시점 설정*/
	//현재 카메라 시점 X좌표 +/-
	void SetCameraCenterPlusX(GLdouble value);

	//현재 카메라 시점 Y좌표 +/-
	void SetCameraCenterPlusY(GLdouble value);

	//현재 카메라 시점 Z좌표 +/-
	void SetCameraCenterPlusZ(GLdouble value);

	/*현재 카메라 방향축 설정*/
	//현재 카메라 방향축X +/-
	void SetCameraUpPlusX(GLdouble value);

	//현재 카메라 방향축Y +/-
	void SetCameraUpPlusY(GLdouble value);

	//현재 카메라 방향축Z +/-
	void SetCameraUpPlusZ(GLdouble value);

	// FOV값 +/-
	void PlusFovy(GLdouble value);
	
	// Near값 +/-
	void PlusZNear(GLdouble value);

	// Far값 +/-
	void PlusZFar(GLdouble value);

	// 카메라 속도 +/-
	void PlusCameraSpeed(GLdouble value);		

	// 카메라 속도 설정
	void SetCameraSpeed(GLdouble value);		
	
	// 카메라가 현재 위치한 에리어 지형 내 X좌표 받아오기
	int GetCameraInAreaX();				

	// 카메라가 현재 위치한 에리어 지형 내 Y좌표 받아오기
	int GetCameraInAreaZ();

	// 카메라가 현재 위치한 에리어 지형 X좌표 설정
	void SetCameraInAreaX(int areaX);

	// 카메라가 현재 위치한 에리어 지형 Y좌표 설정
	void SetCameraInAreaZ(int areaZ);

	// 카메라 Pitch값 수정
	void SetCameraPitch(GLdouble newPitch);

	// 카메라 Yaw값 수정
	void SetCameraYaw(GLdouble newYaw);

	// 카메라 Zoom값 수정
	void SetCameraZoom(GLdouble newZoom);

	// 카메라 Pitch값 받아오기
	GLdouble GetCameraPitch();

	// 카메라 Yaw값 받아오기
	GLdouble GetCameraYaw();

	// 카메라 Zoom값 받아오기
	GLdouble GetCameraZoom(short int xyz); // 1->x, 2->y, 3->z

	// 카메라 설정 리셋
	void CameraReset();			

	// 카메라 Z축 반시계 방향 회전
	void CameraUpRotate(float rad);

	// 카메라 Z축 시계 방향 회전
	void CameraDownRotate(float rad);

	// 카메라 Y축 반시계 방향 회전
	void CameraRightRotate(float rad);

	// 카메라 Y축 시계 방향 회전
	void CameraLeftRotate(float rad);

	// 카메라 전진
	void CameraFrontMove(float dis);

	// 카메라 후진
	void CameraBackMove(float dis);

	//카메라 우로 이동
	void CameraRightMove(float dis);

	//카메라 좌로 이동
	void CameraLeftMove(float dis);
};

