// Dlg.cpp : implementation file
//

#include "StdAfx.h"
#include "Dlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "SaveOptionDlg.h"
#include "DBConncetion.h"
#include "Path.h"
#include "QuxianDialog.h"
#include "Dialog_Licheng.h"

string cstring_to_string(CString input) {
	CT2CA temp(input);
	string output(temp);
	return output;
}

CString string_to_csting(string input) {
	return CString(input.c_str());
}
IMPLEMENT_DYNAMIC(Dlg, CAcUiDialog)
int row, col;
Dlg::Dlg(CWnd* pParent /*=nullptr*/)
	: CAcUiDialog(IDD_DIALOG1, pParent)
{

}

Dlg::~Dlg()
{
}

void Dlg::DoDataExchange(CDataExchange* pDX)
{
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, jd_list);
	DDX_Control(pDX, IDC_EDIT1, input_edit);
	DDX_Control(pDX, IDC_EDIT2, qdlc_edit);
}


BEGIN_MESSAGE_MAP(Dlg, CAcUiDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &Dlg::OnDblclkList1)
//	ON_NOTIFY(NM_KILLFOCUS, IDC_LIST1, &Dlg::OnKillfocusList1)
	ON_BN_CLICKED(IDC_BUTTON1, &Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Dlg::OnBnClickedButton2)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &Dlg::OnRclickList1)
	ON_BN_CLICKED(IDC_BUTTON3, &Dlg::OnBnClickedButton3)
	ON_COMMAND(IDR_MENU, &Dlg::OnIdrMenu)
	ON_BN_CLICKED(IDC_BUTTON4, &Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &Dlg::OnBnClickedButton9)
	
	ON_EN_KILLFOCUS(IDC_EDIT1, &Dlg::OnKillfocusEdit1)
END_MESSAGE_MAP()


// Dlg message handlers


BOOL Dlg::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();
	qxdlog = new QuxianDialog();
	lcdlog = new Dialog_Licheng();
	qdlc_edit.SetWindowTextW(string_to_csting(to_string(qdlc)));
	// TODO:  Add extra initialization here
	long dwStyle = jd_list.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	jd_list.SetExtendedStyle(dwStyle);

	jd_list.InsertColumn(0, L"�����", LVCFMT_LEFT, 50);
	jd_list.InsertColumn(1, L"X����", LVCFMT_LEFT, 100);
	jd_list.InsertColumn(2, L"Y����", LVCFMT_LEFT, 100);
	jd_list.InsertColumn(3, L"�뾶R", LVCFMT_LEFT, 100);
	jd_list.InsertColumn(4, L"����L0", LVCFMT_LEFT, 100);
	for (int i = 0; i < path.jd_num(jd_vector); i++) {//�б���
		vector<string> jd_info = path.get_jd(jd_vector, i);//��ȡ����
		jd_list.InsertItem(i, string_to_csting(to_string(i + 1)));//��������
		jd_list.SetItemText(i, 1, string_to_csting(jd_info[1]));//x
		jd_list.SetItemText(i, 2, string_to_csting(jd_info[2]));//y
		jd_list.SetItemText(i, 3, string_to_csting(jd_info[3]));//r
		jd_list.SetItemText(i, 4, string_to_csting(jd_info[4]));//l0
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void Dlg::OnDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	CRect rc;//�о���
	CString strTemp;
	NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;
	row = pNMListView->iItem;//�к�
	col = pNMListView->iSubItem;//�к�


	if (col != 0)	// ѡ������������޸Ľ����
	{
		jd_list.GetSubItemRect(row, col, LVIR_LABEL, rc); //�õ�˫�����õ�λ��
		input_edit.SetParent(&jd_list);//�����Ӵ���edit�ĸ�����(�̶�)
		input_edit.MoveWindow(rc);//�ı䴰�ڴ�Сλ��
		strTemp = jd_list.GetItemText(row, col);
		input_edit.SetWindowTextW(strTemp);//��ȡ���ݴ��ݸ��ؼ�
		input_edit.ShowWindow(SW_SHOW);//��ʾ����
		input_edit.SetFocus();//����Edit����
		input_edit.ShowCaret();//��ʾ���
		input_edit.SetSel(0, -1);//ȫѡ
	}
	*pResult = 0;
}





void Dlg::OnBnClickedButton1()
{
	SaveOptionDlg import_dlg;
	INT_PTR select = import_dlg.DoModal();

	if (select == IDOK) {
		if (import_dlg.is_file) {
			CFileDialog   dlg(TRUE);//�򿪶Ի���
			if (dlg.DoModal() != IDOK)//����OK����
				return;
			CString file_name_cstring = dlg.GetPathName();//cstringתstring
			CT2CA temp(file_name_cstring);
			string file_name(temp);

			if (path.read_data(jd_vector, file_name)) { // ����ɹ������ļ�

				for (int i = jd_list.GetItemCount(); i < path.jd_num(jd_vector); i++) {//�б���
					vector<string> jd_info = path.get_jd(jd_vector, i);//��ȡ����
					jd_list.InsertItem(i, string_to_csting(to_string(i + 1)));//��������
					jd_list.SetItemText(i, 1, string_to_csting(jd_info[1]));//x
					jd_list.SetItemText(i, 2, string_to_csting(jd_info[2]));//y
					jd_list.SetItemText(i, 3, string_to_csting(jd_info[3]));//r
					jd_list.SetItemText(i, 4, string_to_csting(jd_info[4]));//l0
				}

				MessageBox(L"�ɹ������ļ���", L"��ʾ");
			}
			else {

				MessageBox(L"���ܴ��ļ���" + file_name_cstring, L"��ʾ");
			}
		}
		else {
			DBConncetion db_conn;
			if (db_conn.DoModal() == IDOK) {
				DB db_info;
				db_info.ip = cstring_to_string(db_conn.ip);
				db_info.port = cstring_to_string(db_conn.port);
				db_info.user = cstring_to_string(db_conn.user);
				db_info.passwd = cstring_to_string(db_conn.passwd);
				db_info.db = cstring_to_string(db_conn.db);
				db_info.table = cstring_to_string(db_conn.table);
				int status = path.read_data_from_db(jd_vector, db_info);
				if (status == 0) {
					for (int i = jd_list.GetItemCount(); i < path.jd_num(jd_vector); i++) {//�б���
						vector<string> jd_info = path.get_jd(jd_vector, i);//��ȡ����
						jd_list.InsertItem(i, string_to_csting(to_string(i + 1)));//��������
						jd_list.SetItemText(i, 1, string_to_csting(jd_info[1]));//x
						jd_list.SetItemText(i, 2, string_to_csting(jd_info[2]));//y
						jd_list.SetItemText(i, 3, string_to_csting(jd_info[3]));//r
						jd_list.SetItemText(i, 4, string_to_csting(jd_info[4]));//l0
					}
					MessageBox(L"�ɹ���ȡ���㣡");
				}
				else if (status == 1) {
					MessageBox(L"��ǰ��û�пɵ���Ľ��㣡");
				}
				else if (status == 2) {
					MessageBox(L"���ݿ�����ʧ�ܣ�����������Ϣ��");
				}
				else {
					MessageBox(L"�˱����ڣ�");
				}

			}
			else {
				return;
			}

		}


	}

}


void Dlg::OnBnClickedButton2()
{
	CString str_temp;
	row = jd_list.GetItemCount();//��
	str_temp.Format(_T("%d"), row + 1);//��+1
	JD jd;
	jd_vector.push_back(jd);
	path.set_qx_done(false);//���߼���δ���
	path.set_lc_done(false);//��̼���δ���
	jd_list.InsertItem(row, str_temp);//������
	jd_list.SetItemText(row, 1, string_to_csting("0"));//x Ĭ��0
	jd_list.SetItemText(row, 2, string_to_csting("0"));//y
	jd_list.SetItemText(row, 3, string_to_csting("0"));//r
	jd_list.SetItemText(row, 4, string_to_csting("0"));//l0
	jd_list.SetItemState(row, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);//ÿһ�� ѡ��|��ѡ�� ״̬
	jd_list.EnsureVisible(row, FALSE);//��λ�п���
}


void Dlg::OnRclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR; //list-view ��Ϣ�Ľṹ��
	if (pNMListView->iItem != -1)//������������ �����к�
	{
		row = pNMListView->iItem;//�к�
		DWORD dwPos = GetMessagePos(); //�������λ�� DWORD����16λΪx, ��16λy
		CPoint Point(LOWORD(dwPos), HIWORD(dwPos));
		CMenu Menu;
		Menu.LoadMenu(IDR_MENU1);  //��Ҫ���Ĳ˵�ID 
		CMenu* Popup = Menu.GetSubMenu(0); //�˵�����
		ASSERT(Popup != NULL);
		Popup->TrackPopupMenu(TPM_CENTERALIGN | TPM_RIGHTBUTTON, Point.x, Point.y, this); //���ò˵�ˮƽ���û�����ѡ��˵���ѡ�����Ұ���
		Popup->Detach();
	}

	*pResult = 0;
}


void Dlg::OnBnClickedButton3()
{
	CString qdlc_cstring;
	GetDlgItem(IDC_EDIT2)->GetWindowText(qdlc_cstring);//�ѱ༭��1�����ֵ����qdlc
	qdlc = strtol(cstring_to_string(qdlc_cstring).c_str(), NULL, 10);
	string qdlc_string = cstring_to_string(qdlc_cstring);
	long qdlc_int = strtol(qdlc_string.c_str(), NULL, 10);//stringתcstring//NULL�����طǷ��ַ���//baseΪ10���Ϸ��ַ�Ϊ012...9��
	int qdlc_1 = qdlc_int / 1000;//���+��ǰ�沿��
	int qdlc_2 = qdlc_int % 1000;//���+�ź��沿��
	path.set_qdlc1(qdlc_1);//����qdlc_1Ϊqdlc1
	path.set_qdlc2(qdlc_2);//����qdlc_2Ϊqdlc2
	path.clean_lc(lc_vector);//��������Ϣ
	path.set_lc_done(false);//��������������Ϊδ���״̬
	lcdlog->DestroyWindow();//��̶Ի�������
	string info = get_formal_licheng(qdlc_1 * 1000 + qdlc_2);//��ʼ���
	MessageBox(L"����������Ϊ: " + string_to_csting(info), L"������");
}


void Dlg::OnIdrMenu()
{
	for (int i = row; i < jd_vector.size(); i++) {
		jd_list.DeleteItem(row);//ɾ���б���
	}
	jd_vector.erase(jd_vector.begin() + row);//ɾ������
	for (int i = row; i < jd_vector.size(); i++) {
		vector<string> jd_info = path.get_jd(jd_vector, i);//��ȡ����
		jd_list.InsertItem(i, string_to_csting(to_string(i + 1)));//���
		jd_list.SetItemText(i, 1, string_to_csting(jd_info[1]));//x
		jd_list.SetItemText(i, 2, string_to_csting(jd_info[2]));//y
		jd_list.SetItemText(i, 3, string_to_csting(jd_info[3]));//r
		jd_list.SetItemText(i, 4, string_to_csting(jd_info[4]));//l0
	}
	path.set_qx_done(false);//���߼�������Ϊδ���״̬
	path.set_lc_done(false);//��������������Ϊδ���״̬
}


void Dlg::OnBnClickedButton4()
{
	if (!qxdlog->GetSafeHwnd()) {//��ȫ��ȡ����
		qxdlog->Create(IDD_DIALOG5);//����������Ϣ�Ի���
	}

	if (path.jd_num(jd_vector) >= 3) { //�����������������
		if (!path.is_qx_done()) { // �����û�м�������
			qxdlog->quxian_list.DeleteAllItems();//��������б�
			path.compute_quxian(jd_vector, qx_vector);//����������Ϣ
			for (int i = 0; i < path.jd_num(jd_vector); i++) {//��
				vector<string> qx_info = path.get_quxian(qx_vector, i);
				qxdlog->quxian_list.InsertItem(i, string_to_csting(to_string(i)));
				for (int j = 0; j < 12; j++) {//��
					qxdlog->quxian_list.SetItemText(i, j + 1, string_to_csting(qx_info[j + 1]));
				}
			}
		}
		else {
			if (qxdlog->quxian_list.GetItemCount() != path.jd_num(jd_vector)) {
				for (int i = 0; i < path.jd_num(jd_vector); i++) {//��
					vector<string> qx_info = path.get_quxian(qx_vector, i);
					qxdlog->quxian_list.InsertItem(i, string_to_csting(to_string(i)));
					for (int j = 0; j < 12; j++) {//��
						qxdlog->quxian_list.SetItemText(i, j + 1, string_to_csting(qx_info[j + 1]));
					}
				}
			}
			qxdlog->ShowWindow(SW_SHOWNORMAL);//չʾ
		}
	}
	else
	{
		MessageBox(L"�뵼������3������!", L"��ʾ");
	}
}


void Dlg::OnBnClickedButton5()
{
	if (!path.is_qx_done()) {//δ������߼���
		MessageBox(L"���ȼ���������Ϣ", L"��ʾ");
		return;
	}
	if (!lcdlog->GetSafeHwnd()) {
		lcdlog->Create(IDD_DIALOG4);//�����������Ի���
	}

	if (!path.is_lc_done()) {//δ�������������
		lcdlog->list_licheng.DeleteAllItems();//���������Ϣ���
		path.compute_licheng(jd_vector, qx_vector, lc_vector, path.get_qdlc1(), path.get_qdlc2());//�����������
		for (int i = 0; i < path.jd_num(jd_vector); i++) {//��
			vector<string> lc_info = path.get_licheng(lc_vector, i);
			lcdlog->list_licheng.InsertItem(i, string_to_csting(to_string(i)));
			for (int j = 0; j < 10; j++) {//��
				lcdlog->list_licheng.SetItemText(i, j + 1, string_to_csting(lc_info[j + 1]));
			}
		}
		lcdlog->list_licheng.InsertItem(path.jd_num(jd_vector), L"������");
		lcdlog->list_licheng.SetItemText(path.jd_num(jd_vector), 1, string_to_csting(get_formal_licheng(path.get_qdlc1() * 1000 + path.get_qdlc2())));
		lcdlog->list_licheng.InsertItem(path.jd_num(jd_vector) + 1, L"�յ����");
		lcdlog->list_licheng.SetItemText(path.jd_num(jd_vector) + 1, 1, string_to_csting(get_formal_licheng(path.get_zdlc())));
	}
	else {
	
		if (lcdlog->list_licheng.GetItemCount() != path.jd_num(jd_vector)) {
			for (int i = 0; i < path.jd_num(jd_vector); i++) {//��
				vector<string> lc_info = path.get_licheng(lc_vector, i);
				lcdlog->list_licheng.InsertItem(i, string_to_csting(to_string(i)));
				for (int j = 0; j < 10; j++) {//��
					lcdlog->list_licheng.SetItemText(i, j + 1, string_to_csting(lc_info[j + 1]));
				}
			}
			lcdlog->list_licheng.InsertItem(path.jd_num(jd_vector), L"������");
			lcdlog->list_licheng.SetItemText(path.jd_num(jd_vector), 1, string_to_csting(get_formal_licheng(path.get_qdlc1() * 1000 + path.get_qdlc2())));
			lcdlog->list_licheng.InsertItem(path.jd_num(jd_vector) + 1, L"�յ����");
			lcdlog->list_licheng.SetItemText(path.jd_num(jd_vector) + 1, 1, string_to_csting(get_formal_licheng(path.get_zdlc())));
		}
	}

	lcdlog->ShowWindow(SW_SHOWNORMAL);
}


void Dlg::OnBnClickedButton6()
{
	SaveOptionDlg save_option_dlg;
	INT_PTR slection = save_option_dlg.DoModal();
	if (slection == IDOK) {
		if (save_option_dlg.is_file) { // ���ѡ��ʹ���ļ�ϵͳ
			BOOL IsOpen = false;     //�Ƿ��(����Ϊ����)    
			CString DefaultType = CString("*.csv");   //Ĭ���ļ�����    
			CString DefaultfileName = CString("Result.csv");         //Ĭ���ļ���    
			CString TypesFilter = CString("Save as(*.csv)|*.csv||");   //�ļ����ǵ�����    
			CFileDialog openFileDlg(IsOpen, DefaultType, DefaultfileName, OFN_HIDEREADONLY | OFN_READONLY, TypesFilter, NULL);
			if (openFileDlg.DoModal() == IDOK) {//��okִ�д���

				string file_name = cstring_to_string(openFileDlg.GetPathName()); //��ȡ�ļ�����
				string file_path(file_name);
				if (path.save_result(jd_vector, qx_vector, lc_vector, file_path)) {
					MessageBox(L"�ɹ������������", L"��ʾ");
				}
				else {
					MessageBox(L"����������̣�", L"��ʾ");
				}
			}
		}
		else { //���ʹ�����ݿ�ϵͳ
			DBConncetion db_conn;
			if (db_conn.DoModal() == IDOK) {
				DB db_info;
				db_info.ip = cstring_to_string(db_conn.ip);
				db_info.port = cstring_to_string(db_conn.port);
				db_info.user = cstring_to_string(db_conn.user);
				db_info.passwd = cstring_to_string(db_conn.passwd);
				db_info.db = cstring_to_string(db_conn.db);
				db_info.table = cstring_to_string(db_conn.table);
				int status = path.save_result_to_db(jd_vector, qx_vector, lc_vector, db_info);
				if (status == 0) {
					MessageBox(L"�ɹ����뽻�������ݿ⣡");
				}
				else if (status == 1) {
					MessageBox(L"���ȼ������ߺ������Ϣ��");
				}
				else {
					MessageBox(L"�������ݿ�ʧ�ܣ�����������Ϣ��");
				}
			}
			else {
				return;
			}
		}

	}


	else { //���򷵻�
		return;
	}

}




void Dlg::OnBnClickedButton7()
{
	SaveOptionDlg save_dlg;
	INT_PTR select = save_dlg.DoModal();

	if (select == IDOK) {

		if (save_dlg.is_file) {

			string file_name;  //��ȡ���ļ�����
			BOOL IsOpen = false;     //�Ƿ��(����Ϊ����)    
			CString DefaultType = CString("*.csv");   //Ĭ���ļ�����    
			CString DefaultfileName = CString("JD.csv");         //Ĭ���ļ���    
			CString TypesFilter = CString("Save as(*.csv)|*.csv||");   //�ļ����ǵ�����    
			CFileDialog openFileDlg(IsOpen, DefaultType, DefaultfileName, OFN_HIDEREADONLY | OFN_READONLY, TypesFilter, NULL);
			if (openFileDlg.DoModal() == IDOK) {//��okִ�д���
				file_name = cstring_to_string(openFileDlg.GetPathName());

				if (path.save_jd(jd_vector, file_name)) {
					MessageBox(L"�ɹ����潻�㣡", L"��ʾ");
				}
				else {
					MessageBox(L"����������̣�", L"��ʾ");
				}
			}

		}

		else {
			DBConncetion db_conn;
			if (db_conn.DoModal() == IDOK) {
				DB db_info;
				db_info.ip = cstring_to_string(db_conn.ip);
				db_info.port = cstring_to_string(db_conn.port);
				db_info.user = cstring_to_string(db_conn.user);
				db_info.passwd = cstring_to_string(db_conn.passwd);
				db_info.db = cstring_to_string(db_conn.db);
				db_info.table = cstring_to_string(db_conn.table);
				int status = path.save_jd_to_db(jd_vector, db_info);
				if (status == 0) {
					MessageBox(L"�ɹ����뽻�������ݿ⣡");
				}
				else if (status == 1) {
					MessageBox(L"û�пɵ���Ľ��㣡");
				}
				else {
					MessageBox(L"����ʧ�ܣ�����������Ϣ��");
				}
			}
			else {
				return;
			}
		}
	}
	else {//����ok����
		return;
	}

}


void Dlg::OnBnClickedButton8()
{
	CString rylc_cstring;
	GetDlgItem(IDC_EDIT3)->GetWindowText(rylc_cstring);//�ѱ༭��2�����ֵ����rylc
	CT2CA temp(rylc_cstring);//cstringתstring
	string rylc_string(temp);
	int rylc = stoi(rylc_string);//stringתint
	ZB zb = path.lc_to_zb(jd_vector, qx_vector, lc_vector, rylc);//path�м������ת����
	if (zb.x == -1) {//����-1
		MessageBox(L"���ȼ��������Ϣ��", L"��ʾ");
	}
	else if (zb.x == -2) {//����-2
		MessageBox(L"�������̲���������յ�����䣡", L"��ʾ");
	}
	else {
		string result = "�������:" + get_formal_licheng(rylc) + " ������Ϊ: \n" + zb.show_zb();
		CString text = CString(result.c_str());//stringתcstring
		GetDlgItem(IDC_STATIC)->SetWindowText(text);//result���͵�static2
		GetDlgItem(IDC_STATIC)->ShowWindow(SW_SHOW);//��static2��λ����ԭ�ߴ���ʾ
		MessageBox(text, L"���ת����");
	}
}


void Dlg::OnBnClickedButton9()
{
	if (jd_vector.size() >= 3) {
		CString qdlc_cstring;
		GetDlgItem(IDC_EDIT2)->GetWindowText(qdlc_cstring);//�ѱ༭��1�����ֵ����qdlc
		qdlc = strtol(cstring_to_string(qdlc_cstring).c_str(), NULL, 10);
		string qdlc_string = cstring_to_string(qdlc_cstring);
		long qdlc_int = strtol(qdlc_string.c_str(), NULL, 10);//stringתcstring//NULL�����طǷ��ַ���//baseΪ10���Ϸ��ַ�Ϊ012...9��
		int qdlc_1 = qdlc_int / 1000;//���+��ǰ�沿��
		int qdlc_2 = qdlc_int % 1000;//���+�ź��沿��
		path.set_qdlc1(qdlc_1);//����qdlc_1Ϊqdlc1
		path.set_qdlc2(qdlc_2);//����qdlc_2Ϊqdlc2
		path.clean_lc(lc_vector);//��������Ϣ
		path.set_lc_done(false);//��������������Ϊδ���״̬
		lcdlog->DestroyWindow();//��̶Ի�������
		string info = get_formal_licheng(qdlc_1 * 1000 + qdlc_2);//��ʼ���
		path.compute_quxian(jd_vector, qx_vector);
		path.compute_licheng(jd_vector, qx_vector, lc_vector, path.get_qdlc1(), path.get_qdlc2());
		CAcUiDialog::OnOK();
	}
	else {
		MessageBox(L"���������3������", L"��ʾ");
	}
	
}



void Dlg::OnKillfocusEdit1()
{
	CString str;
	input_edit.GetWindowTextW(str);//��ȡ����
	if (str.IsEmpty()) {
		input_edit.SetWindowTextW(L"0");
		path.edit_jd(jd_vector, row, col, 0);//�༭���½�����Ϣ
		path.clean_qx(qx_vector);//���������Ϣ
		path.clean_lc(lc_vector);//����������
		path.set_lc_done(false);
		path.set_qx_done(false);
		return ;
	}
	jd_list.SetItemText(row, col, str);//�������ݸ��б���x��x��
	input_edit.ShowWindow(SW_HIDE);//���ش���
	if (!str.IsEmpty()) {
		path.edit_jd(jd_vector, row, col, cstring_to_string(str));//�༭���½�����Ϣ
		path.clean_qx(qx_vector);//���������Ϣ
		path.clean_lc(lc_vector);//����������
		path.set_lc_done(false);
		path.set_qx_done(false);
	}
}
