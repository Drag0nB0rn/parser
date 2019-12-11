#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>

using namespace std;

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
	catKeyWord	// 7 �ؼ���
};

struct synbl   //���ű�
{
	string name; //����
	synblTval type;//����
	int typePosition;	//��������
	synblCat cat;//����
	int addr;		//��ַ
};

struct typel //���ͱ�
{
	synblTval tval;//����
	int position;	//���꣨0��ʼ��
};



struct arryTval   //����
{
	int low=0;				//�����½�
	int up;					//�����Ͻ�

	//synblTval arrtCtp;	//�������� ָ��

	typel type;		//����
	int position;	//����
	int arryClen;			//���鳤��  �ֳ�
};

struct  rinflTval //�ṹ��
{
	string rinflId;		//�ṹ������
	int rinflOff;			//����
	//synblTval structType; //���� ָ��
	typel type;			//����ָ��
	int position;		//����
};


struct pfinfl  //����
{
	int pfinflLevel;	//��κ�
	int pfinflOff;		//����
	int pfinflFn;		//��������
	int pfinflParam;	//������  ָ��
	//auto pfinflEntry;	//��ڵ�ַ
	int entry;		//��ڵ�ַ
};

struct consl	//����
{
	string value;	//����ֵ
};

struct lenl     //����
{
	int length;
};

struct  vall   //���¼
{
	//
};


class table
{
public:


	table();

	~table();
	
	void init();


private:
	vector<synbl> synblTable;



};

table::~table()
{
}

