



#ifndef PATH_H
#define PATH_H
#include<vector>
#include<string>
using namespace std;

const string CREATE_RESULT_TABLE = "(����� int,\
��λ�� double,\
ת��� double,\
���߳� double,\
���߳� double,\
ֱ�������� char(30),\
ֱ������� double,\
��Բ������ char(30),\
��Բ����� double,\
���е����� char(30),\
���е���� double,\
Բ�������� char(30),\
Բ������� double,\
��ֱ������ char(30),\
��ֱ����� double);";

const string CREATE_JD_TABLE = "(����� int,\
��������x double,\
��������y double,\
�������߳� double,\
Բ���߰뾶 double);";
struct Angle {
	int degree = 0;
	int minute = 0;
	int second = 0;
};

struct DB {
	string ip;
	string port;
	string user;
	string passwd;
	string db;
	string table;
};



struct  QX // ������Ϣ
{

	double qx_fwj = 0; // ��λ�� �����ȣ�
	double qx_a = 0; // ����ת�� ���Ƕȣ�
	double qx_l0 = 0; // �������߳�
	double qx_L = 0; // ���߳�
	double qx_R = 0; // ���߰뾶
	double qx_m = 0; // �д���
	double qx_p = 0; // ���ƾ�
	double qx_T = 0; // ���߳�
	double qx_E = 0; // ��ʸ��
	double qx_lc = 0; // Բ���߳�
	double qx_b = 0; // �������߽ǣ��Ƕȣ� 
	double qx_q = 0; //������

};

struct ZB {//����
	ZB(double x = 0, double y = 0) { this->x = x; this->y = y; };
	double x = 0;
	double y = 0;
	string show_zb() const;
};

struct LC //�����Ϣ
{

	double zh = 0; //ֱ�������
	ZB zh_zb; //ֱ��������
	double hy = 0; //��Բ�����
	ZB hy_zb;//��Բ������
	double qz = 0; //���е����
	ZB qz_zb;//���е�����
	double yh = 0; //Բ�������
	ZB yh_zb;//Բ��������
	double hz = 0; //��ֱ�����
	ZB hz_zb;//��ֱ������
};

struct JD
{

	JD(double jd_x = 0, double jd_y = 0, double jd_l0 = 0, double jd_r = 0);
	double get_distance(const JD& jd) const;//��������ľ���
	double jd_x = 0;//��������x
	double jd_y = 0;//��������y
	double jd_l0 = 0;//�������߳�
	double jd_r = 0;//Բ���߰뾶

};

class Path {
public:
	Path(); //���캯��
	int jd_num(const vector<JD>& jd_vector) { return jd_vector.size(); }; // �������
	int get_qdlc1() const { return qdlc1; };//��ȡ������+ǰ����
	int get_qdlc2() const { return qdlc2; };//��ȡ������+�󲿷�
	double get_zdlc() const { return zdlc; };//��ȡ�յ����
	bool is_qx_done() const { return qx_done; };//���߼������
	bool is_lc_done() const { return lc_done; };//��̼������
	void set_qx_done(bool b) { this->qx_done = b; };//�������߼����Ƿ����
	void set_lc_done(bool b) { this->lc_done = b; };//������̼����Ƿ����
	void set_qdlc1(int qdlc1) { this->qdlc1 = qdlc1; };//����qdlc1
	void set_qdlc2(int qdlc2) { this->qdlc2 = qdlc2; };//����qdlc2
	void set_zdlc(double zdlc) { this->zdlc = zdlc; }//����zdlc
	void clean_jd(vector<JD>& jd_vector) { jd_vector.clear(); }; //���������Ϣ
	void clean_qx(vector<QX>& qx_vector) { qx_vector.clear(); };//���������Ϣ
	void clean_lc(vector<LC>& lc_vector) { lc_vector.clear(); };//��������Ϣ
	vector <string> get_jd(const vector<JD>& jd_vector, int jd_index);//��ȡ������Ϣ
	vector <string> get_quxian(const vector<QX>& qx_vector, int index);//��ȡ������Ϣ
	vector <string> get_licheng(const vector<LC>& lc_vector, int index);//��ȡ�����Ϣ
	double get_lc2(double rylc); //����������̵ĺ��沿��
	Angle to_angle(double a);
	bool read_data(vector<JD>& jd_vector, string file_nmae); //������
	int read_data_from_db(vector<JD>& jd_vector, DB &db_info);
	bool compute_quxian(const vector<JD>& jd_vector, vector<QX>& qx_vector); //����������Ϣ
	bool compute_licheng(const vector<JD>& jd_vector, const vector<QX>& qx_vector, vector<LC>& lc_vector, int qdlc1, int qdlc2); //�����������
	bool show_licheng(const vector<LC>& lc_vector); //չʾ���
	bool show_jd(const vector<JD>& jd_vector); //չʾ����
	bool show_quxian(const vector<QX>& qx_vector);//չʾ������Ϣ
	bool save_result(vector<JD>& jd_vector, const vector<QX>& qx_vector, const vector<LC>& lc_vector, string file_name); //����������Ϣ
	int save_result_to_db(vector<JD>& jd_vector, const vector<QX>& qx_vector, const vector<LC>& lc_vector, DB &db); // �����������ݿ�
	bool save_jd(const vector<JD>& jd_vector, string file_name); //���潻����Ϣ
	int save_jd_to_db(const vector<JD>& jd_vector, DB& db); //���潻�㵽���ݿ�
	void edit_jd(vector<JD>& jd_vector, int jd_index, int attribute_index, string value);//�༭����
	ZB lc_to_zb(const vector<JD>& jd_vector, const vector<QX>& qx_vector, const vector<LC>& lc_vector, int rylc); //���ת����


private:
	bool qx_done; //���߼������
	bool lc_done; //��̼������
	int qdlc1;//������+��ǰ�沿��
	int qdlc2;//������+�ź��沿��
	double zdlc; //�յ����

};


string get_formal_licheng(int lc);//������̸�ʽDKx+xxx
string fill_zero(int lc); //��λ������
#endif PATH_H