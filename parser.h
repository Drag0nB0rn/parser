#pragma once
#include"table.h"
#include<map>
#include<stack>
#include<string>
#include<vector>
#include<iostream>
struct production         //����ʽ
{
	map<char, string> pro;
};
struct check
{
	bool flag;
	production pro;
};
class gammer
{
public:
	gammer();

	~gammer();
private:
	vector<string> ter;		//�ս��
	vector<char> notTer;	//���ս��
	map<char, string> pro;	//����ʽ
};

class parserTable
{
public:
	parserTable();
	void getsynl();
	void creatParserTable();
	void getParserTable();
	check checkList(string cur, string top);	//�����true or false�����ʽ
	stack<char> getSynStack();
	stack<char> getSemStack();
	~parserTable();
private:
	stack<char> synStack;	//����ջ
	stack<char> semStack;	//����ջ
	map<production, string> parserList;	//������(����ʽ���ս��)

};

class LL1Parser
{
public:
	LL1Parser();

	~LL1Parser();

private:
	
	
};

LL1Parser::LL1Parser()
{

}

LL1Parser::~LL1Parser()
{

}

