// QuxianDialog.cpp : implementation file
//

#include "StdAfx.h"
#include "QuxianDialog.h"
#include "afxdialogex.h"
#include "resource.h"

// QuxianDialog dialog

IMPLEMENT_DYNAMIC(QuxianDialog, CAcUiDialog)

QuxianDialog::QuxianDialog(CWnd* pParent /*=nullptr*/)
	: CAcUiDialog(IDD_DIALOG5, pParent)
{

}

QuxianDialog::~QuxianDialog()
{
}

void QuxianDialog::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_QUXIAN, quxian_list);
}


BEGIN_MESSAGE_MAP(QuxianDialog, CAcUiDialog)
END_MESSAGE_MAP()


// QuxianDialog message handlers


BOOL QuxianDialog::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	long dwStyle = quxian_list.GetExtendedStyle();//��չ����
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ������
	dwStyle |= LVS_EX_GRIDLINES;//���Ʊ��
	quxian_list.SetExtendedStyle(dwStyle);//������չ��ʽ

	quxian_list.InsertColumn(0, L"�����", LVCFMT_LEFT, 50);
	quxian_list.InsertColumn(1, L"��λ�ǣ����ȣ�", LVCFMT_LEFT, 100);
	quxian_list.InsertColumn(2, L"����ת�ǣ��Ƕȣ�", LVCFMT_LEFT, 110);
	quxian_list.InsertColumn(3, L"�������߳�", LVCFMT_LEFT, 80);
	quxian_list.InsertColumn(4, L"���߳�", LVCFMT_LEFT, 50);
	quxian_list.InsertColumn(5, L"���߰뾶", LVCFMT_LEFT, 70);
	quxian_list.InsertColumn(6, L"�д���", LVCFMT_LEFT, 50);
	quxian_list.InsertColumn(7, L"���ƾ�", LVCFMT_LEFT, 50);
	quxian_list.InsertColumn(8, L"���߳�", LVCFMT_LEFT, 50);
	quxian_list.InsertColumn(9, L"��ʸ��", LVCFMT_LEFT, 50);
	quxian_list.InsertColumn(10, L"Բ���߳�", LVCFMT_LEFT, 70);
	quxian_list.InsertColumn(11, L"�������߽�", LVCFMT_LEFT, 80);
	quxian_list.InsertColumn(12, L"������", LVCFMT_LEFT, 50);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
