#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>

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
	//catKeyWord	// 7 �ؼ���
};

enum delimiter {//���

};

enum Keyword {	//

};

struct synbl{  //���ű�

	string name; //����
	synblTval type;//����
	int typePosition;	//��������   
	synblCat cat;//����
	int addr;		//��ַ
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

struct lenl     //����
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



	~table();
	
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


