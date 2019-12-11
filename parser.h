#pragma once
#include"table.h"
#include<map>
#include<stack>
#include<string>
#include<vector>
#include<iostream>
typedef struct production         //����ʽ
{
	//map<char, string> pro;
	/*production(char t1, string t2)
	{
		pro[t1] = t2;
	}*/
	char left;
	string right;
};
typedef struct check
{
	bool flag;
	//map<char, string> production;
	production p;
};

class parserTable
{
public:

	void getToken();		//��ȡtoken
	void creatParserList();	//����������
	bool isTer(string c);
	bool isNotTer(char c);
	check checkList(string cur);	//�����true or false�����ʽ
	stack<char> getSynStack();
	stack<char> getSemStack();
private:
	vector<string> terTable;
	vector<char> notTerTable;
	vector<production> pro; //����ʽ
	stack<char> synStack;	//����ջ
	stack<char> semStack;	//����ջ
	map<string,production>parserList; //������(��ǰ��������ʽ)
};