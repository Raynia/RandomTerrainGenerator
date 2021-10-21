﻿// CInputDialog.cpp: 구현 파일
//

#include "stdafx.h"
#include "CInputDialog.h"
#include "afxdialogex.h"

// CInputDialog 대화 상자

IMPLEMENT_DYNAMIC(CInputDialog, CDialogEx)

CInputDialog::CInputDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	//GotoDlgCtrl(GetDlgItem(IDC_EDIT1));
}

unsigned int  CInputDialog::GetSeed()
{
	return seed;
}

CInputDialog::~CInputDialog()
{
}

void CInputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInputDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInputDialog::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &CInputDialog::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CInputDialog 메시지 처리기


void CInputDialog::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
	this->seed = this->GetDlgItemInt(IDC_EDIT1);
}


void CInputDialog::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
