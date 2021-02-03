// Dialog_Licheng.cpp : implementation file
//

#include "StdAfx.h"
#include "Dialog_Licheng.h"
#include "afxdialogex.h"
#include "resource.h"

// Dialog_Licheng dialog

IMPLEMENT_DYNAMIC(Dialog_Licheng, CAcUiDialog)

Dialog_Licheng::Dialog_Licheng(CWnd* pParent /*=nullptr*/)
	: CAcUiDialog(IDD_DIALOG4, pParent)
{

}

Dialog_Licheng::~Dialog_Licheng()
{
}

void Dialog_Licheng::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LICHENG, list_licheng);
}


BEGIN_MESSAGE_MAP(Dialog_Licheng, CAcUiDialog)
END_MESSAGE_MAP()


// Dialog_Licheng message handlers


BOOL Dialog_Licheng::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	long dwStyle = list_licheng.GetExtendedStyle();//��չ����
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ������
	dwStyle |= LVS_EX_GRIDLINES;//���Ʊ��
	list_licheng.SetExtendedStyle(dwStyle);//������չ��ʽ

	list_licheng.InsertColumn(0, L"�����", LVCFMT_LEFT, 80);
	list_licheng.InsertColumn(1, L"ֱ�������", LVCFMT_LEFT, 100);
	list_licheng.InsertColumn(2, L"ֱ��������", LVCFMT_LEFT, 150);
	list_licheng.InsertColumn(3, L"��Բ�����", LVCFMT_LEFT, 100);
	list_licheng.InsertColumn(4, L"��Բ������", LVCFMT_LEFT, 150);
	list_licheng.InsertColumn(5, L"���е����", LVCFMT_LEFT, 100);
	list_licheng.InsertColumn(6, L"���е�����", LVCFMT_LEFT, 150);
	list_licheng.InsertColumn(7, L"Բ�������", LVCFMT_LEFT, 100);
	list_licheng.InsertColumn(8, L"Բ��������", LVCFMT_LEFT, 150);
	list_licheng.InsertColumn(9, L"��ֱ�����", LVCFMT_LEFT, 100);
	list_licheng.InsertColumn(10, L"��ֱ������", LVCFMT_LEFT, 150);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
