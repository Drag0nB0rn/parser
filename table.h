#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<stack>
using namespace std;

/*
enum tokenType {	//token����
	tokenKeyWord,	//�ؼ���
	tokenIde,			//��ʶ��
	tokenDeli,			//���
	tokenConst,		//����
};

struct  token
{
	
	
	

	tokenType type;	//����
	int position;		//����
};
*/

enum synblTval { //����
	tvalInt,		// 0 ����
	tvalFloat,	// 1 ������
	tvalChar,	// 2 �ַ���
	tvalBool,	// 3 bool
	tvalArry,	// 4 ������
	tvalStruct, // 5 �ṹ��
	tvalString,	// 6 �ַ���
};

enum synblCat { //��������
	catFun,			// 0 ����
	catConst,		// 1 ����
	catType,		// 2 ����
	catDomain,	// 3 ����
	catV,				// 4 ����
	catVn,			// 5 �����β�
	catVf,			// 6 ��ֵ�β�
};

enum delimiter {//���

};

enum Keyword {	//

};

struct synbl{  //���ű�

	string name; //����
	synblTval type;//����
	int typePosition;	//�������꣬����ûɶ�ã�
	synblCat cat;//����
	int catPos;//�������� 
	int addr;		//��ַ
	int length;		//�ñ�ʶ����ռ�洢��Ԫ
	bool active;	//��Ծ���
	stack<bool> activeStack;//��Ԫʽ�еı�ʶ����Ծ��Ϣ
};

struct tapel //���ͱ�
{
	synblTval tval;//����
	int position;	//���꣨0��ʼ��
};

struct ainfl   //����
{
	int low=0;				//�����½�
	int up;					//�����Ͻ�

	tapel type;		//����
	int position;	//����
	int arryClen;			//���鳤��  �ֳ�
};

struct  rinfl //�ṹ��
{
	string rinflId;		//�ṹ������
	int rinflOff;			//����
	//synblTval structType; //���� ָ��
	tapel type;			//����
	int position;		//����
};


struct pfinfl  //����
{
	int pfinflLevel;	//��κ�
	int pfinflOff;		//����
	int pfinflFn;		//��������
	int pfinflParam;	//������  ָ��
	int entry;		//��ڵ�ַ
};

struct consl	//����
{
	string value;	//����ֵ
};

struct lenl     //���ȱ� 
{
	int length;
};

struct  vall   //���¼
{
	//
};

class table//���ű����������ʱ����ʶ���ĸ���Ϣ����ʱ�
{
public:


	table();

	string getFunName(int pos);

	int getAddr(int pos);//��ñ�ʶ����ַ

	synblCat getCat(int pos);//��ñ�ʶ������  �Ǻ����� ������ ������

	synblTval getTval(int pos);//��ñ�ʶ������   int��float��char��������

	int size(); //����synblTable�����ܱ�Ĵ�С������ʶ������

	bool isactive(int pos);//���ص�ǰ��ʶ����Ծ��־

	int getValue(int pos);//����pos��ʶ����ֵ������posΪ��������Ч����Ϊ����ֵ������0

	bool isTmp(int pos);//�Ƿ�Ϊ��ʱ����

	bool isConst(int pos);//�Ƿ�Ϊ����

	int getConst(int pos);//���س�����ֵ

	void setActive(int pos,bool active);//����ʶ��active��Ϊtrue

	int insertConst(int curConst);//���볣��
	//~table();
	
	void clear();//��ʼ������

	
private:

	vector<synbl> synblTable;	//���ű��ܱ�
	vector<tapel> tapelTable;	//���ͱ�
	vector<ainfl> ainflTable;		//�����
	vector<rinfl> rinflTable;		//�ṹ��
	vector<pfinfl> pfinflTable;	//������
	vector<consl> conslTable;	//������
	vector<lenl> lenlTable;		//���ȱ�
	vector<vall> vallTable;		//���¼��

};




/*
�ݶ���

����if���

1	( if , t1 ,  ,addr)	//���t1Ϊ�٣�����ת��Ŀ���ַaddr ������Ϊ4,��else���ָ���ַ
2	( =, 2  ,  ,a	)
3	( else ,   ,  ,  addr   )//�˴�����t1λtrue������£�Ӧ�������ϲ���������������else��Ĳ��� addr ΪĿ���ַ
4	( =, 3  ,  ,  a)
4	(  ,	,	,	)//�˴�������if else��䣻



*/

//��ʱ��д�������ģ���ֻ��һ�ű���������Ӷຯ�����ܡ�

struct fourelement
{
	string fix;//����� +-*/ > < = if��else fun call endcall
	int pos1=-1, pos2=-1, pos3=-1;//����Ŀ��������ĵ�ַ,ȫ����ʼ��Ϊ-1��-1�����
	bool active1, active2, active3;//�����������Ļ�Ծ��Ϣ
};



/*
//ǰ��
void lex();		//�ʷ��������𲽽�����������ÿ�õ�һ��token�͵����﷨�������������ɹ������������token�����򱨴�

bool sym();	//�﷨��������һ��token����֮��ִ���﷨����������ǰ���գ�����ջ��Ϊ���嶯��ʱ������������������ɹ����򷵻�true�����򷵻�false��

bool syant();	//������������﷨�����������嶯����ִ�����嶯����������ű����ո�����Ԫʽ��

//���
void better(); //����������������Ż���Ԫʽ,

void compiler();	//����Ԫʽ����ɻ�࣬�������Ĵ����Ż���
*/
