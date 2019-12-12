#pragma once
#include"table.h"
#include<map>
#include<stack>
#include<string>
#include<vector>
#include<iostream>
typedef struct production         //����ʽ
{
	string left;
	string right;
};
typedef struct check
{
	bool flag;
	//map<char, string> production;
	int proIndex; //����ʽ���
};

class parserTable
{
public:

	void getToken();		//��ȡtoken
	production getProduction(int index);   //��ȡ����ʽ
	void creatProduction(); //д�����ʽ
	void travelProduction(); //����
	void creatParserList();	//����������
	bool isTer(string c);
	bool isNotTer(char c);
	check checkList(string cur,string top);	//�����true or false�����ʽ���
	stack<string> getSynStack();
	stack<string> getSemStack();
private:
	vector<string> terTable;
	vector<char> notTerTable;
	vector<production> pro; //����ʽ
	stack<string> synStack;	//����ջ
	stack<string> semStack;	//����ջ
	map<int,string>parserList; //������(����ʽ��ţ���ǰ��)
};