//#include "stdafx.h"
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<iterator>
#include<stack>
#include<map>
#include<queue>
using namespace std;

#define iscam tokenpos >= token.size()
enum tokenenum//��������
{
	token_key, token_sym, token_str_cnt, token_cnt, token_ind, token_char_cnt
};
struct token_type {
	tokenenum t_type;
	int t_pos;
};

enum LL//�ķ�����
{
	LL_E,   LL_E1,   LL_T,   LL_T1,   LL_F,
	LL_W0,   LL_W1,   LL_I,   LL_L,   LL_R,   LL_J,   LL_N,
	LL_GEW0,LL_GEW1,LL_PUSH
};  

struct tab
{
	LL fir;
	LL end;
	bool operator<(tab const& a) const
	{
		return fir == a.fir ? end < a.end : fir < a.fir;
	}
};

struct  siyuan//��Ԫʽ
{
	token_type fi, se, thr, fou;
};

map<tab,int> LLtable;
int indextmp=0;
vector<LL>transGrammer[9];
queue<token_type>anaqueue;
stack<LL> anastack;
stack<token_type> sem;//semջ
vector<siyuan> qt;//��Ԫʽ����
vector<token_type> ac_w0;//w����ջ
vector<token_type> ac_w1;//w1����ջ
vector<token_type> ac_push;//��������ջ

//�ؼ��ֱ�  0
int key_length = 13;
string key[13] = { "main","int","float","double",
"return","if","else","while","do","include","for" ,"define" };


//��� 1
int sym_length = 41;
string sym[41] = { ",",";","//","(",")","{","}" ,"#","\"","\\","!","@","$", "<",">","=","<=",">=","==","+","-","*","/",
"+=","-=","*=","/=","++","--" ,"[","]","->",">>","<<",".",
"^","|","&","&&","%","%=" };

//�ַ���	2
vector<string> str_cnt;

//������  3
vector<double> cnt;

//��ʶ��  4
vector<string> ind;

//�ַ� 5
vector<string> char_cnt;


//�ַ�����
vector<string> word;

//token����
vector<token_type> token;


//�ж��Ƿ�Ϊ�ո񣬻��У��Ʊ��
bool isbn(char &ch) {
	if (ch == ' ' | ch == '\n' | ch == '\t') return true;
	return false;
}

//�ж��Ƿ�Ϊ����
bool isnum(char &ch) {
	if (ch >= 48 && ch <= 57) return true;
	return false;
}

//�ж��Ƿ�Ϊ��ĸ
bool ischar(char &ch) {
	if ((ch >= 65 && ch <= 90) | (ch >= 97 && ch <= 122) | ch == '_') return true;
	return false;
}


//�Զ���
void automatan(string &str)
{
	int pos = 0;
	while (pos < str.length()) {
		//ofile << pos<< endl;
		char ch = str[pos];
		if (isbn(ch)) {//�ո�
			pos++;
			continue;
		}
		else if (ch == '\"')//�ַ�������
							//((str.size() - pos >= 3) && (ch == '"'&&ischar(str[pos + 1])))
		{
			string cnt_char;
			cnt_char += ch;
			ch = str[++pos];
			while (ch != '\"') {
				cnt_char += ch;
				ch = str[++pos];
			}
			cnt_char += '\"';
			word.push_back(cnt_char);
		}
		else if (ch == '\'') {//�ַ�����
							  //((str.size() - pos >= 3) && (ch == '\''&&ischar(str[pos + 1])))
			string cnt_char;
			cnt_char += '\'';
			ch = str[++pos];
			cnt_char += ch;
			cnt_char += '\'';
			pos++;
			//cnt_char += '\'';
			word.push_back(cnt_char);
		}
		else if (isnum(ch) ) {//����
			string num;
			/*
			if (ch == '-') {
				num += ch;
				ch = str[++pos];
			}*/
			num += ch;
			pos++;
			ch = str[pos];
			while (isnum(ch) && pos<str.length()) {
				num += ch;
				ch = str[++pos];
			}
			if (ch == '.') {
				num += ch;
				ch = str[++pos];
				while (isnum(ch) && pos<str.length()) {
					num += ch;
					ch = str[++pos];
				}
			}
			if (ch == 'E' | ch == 'e') {
				num += ch;
				ch = str[++pos];
				if ((ch == '+') | (ch == '-')) num += ch;
				ch = str[++pos];
				while (pos < str.length() && isnum(ch)) {
					num += ch;
					ch = str[++pos];
				}
			}
			pos--;
			word.push_back(num);
		}
		else if (ischar(ch) | ch == '_') {// ��ʶ��
			string _char;
			while (pos < str.length() && (ischar(ch) | ch == '_' | isdigit(ch))) {
				_char += ch;
				ch = str[++pos];
			}
			pos--;
			word.push_back(_char);
		}
		else if (ch == '+') {//  + += ++
			if (pos < (str.length() - 1)) {
				pos++;
				if (str[pos] == '=') {
					word.push_back("+=");
				}
				else if (str[pos] == '+') {
					word.push_back("++");
				}
				else pos--, word.push_back("+");
			}
			else word.push_back("+");
		}
		else if (ch == '-') {// -  -= --
			if (pos < (str.length() - 1)) {
				pos++;
				if (str[pos] == '=') {
					word.push_back("-=");
				}
				else if (str[pos] == '-') {
					word.push_back("--");
				}
				else pos--, word.push_back("-");
			}
			else word.push_back("-");
		}
		else if (ch == '<') {//   < <= <<
			if (pos < (str.length() - 1)) {
				pos++;
				if (str[pos] == '=') {
					word.push_back("<=");
				}
				else if (str[pos] == '<') {
					word.push_back("<<");
				}
				else pos--, word.push_back("<");
			}
			else word.push_back("<");
		}
		else if (ch == '>') {// > >= >>
			if (pos < (str.length() - 1)) {
				pos++;
				if (str[pos] == '=') {
					word.push_back("<=");
				}
				else if (str[pos] == '>') {
					word.push_back(">>");
				}
				else word.push_back(">"), pos--;
			}
			else word.push_back(">");
		}
		else if (ch == '*') {//   *  *=
			if (pos < (str.length() - 1)) {
				pos++;
				if (str[pos] == '=') {
					word.push_back("*=");
				}
				else word.push_back("*"), pos--;
			}
			else word.push_back("*");
		}
		else if (ch == '/') {//  /  /=
			if (pos < (str.length() - 1)) {
				pos++;
				if (str[pos] == '=') {
					word.push_back("/=");
				}
				else if (str[pos] == '/') {
					word.push_back("//");
				}
				else if (str[pos] == '*') {
					word.push_back("/*");
				}
				else word.push_back("/"), pos--;
			}
			else word.push_back("/");
		}
		else if (ch == '&') {//& &&
			if (pos < ((str.length() - 1))) {
				pos++;
				if (str[pos] == '&')
					word.push_back("&&");
				else word.push_back("&"), pos--;
			}
			else word.push_back("&");
		}
		else if (ch == '%') {// %  %=
			if (pos < ((str.length() - 1))) {
				pos++;
				if (str[pos] == '=')
					word.push_back("%=");
				else word.push_back("%"), pos--;
			}
			else word.push_back("%");
		}
		else {
			string tmp;
			tmp += ch;
			word.push_back(tmp);
		}
		pos++;
	}
}


//�����ɵ��ַ��������ɶ�Ӧ��token����
void setToken()
{
	int pos = 0;
	while (pos < word.size()) {
		bool accept = false;
		string tmp_word = word[pos];
		token_type tmp_type;
		if (tmp_word[0] == '_' | ischar(tmp_word[0])) {//��ʶ��

			for (int i = 0; i < key_length; i++) {
				if (key[i] == tmp_word) {
					tmp_type.t_pos = i;
					tmp_type.t_type = token_key;
					token.push_back(tmp_type);
					accept = true;
					break;
				}
			}
			if (!accept) {
				for (int i = 0; i < ind.size(); i++) {
					if (ind[i] == tmp_word) {
						tmp_type.t_pos = i;
						tmp_type.t_type = token_ind;
						token.push_back(tmp_type);
						accept = true;
						break;
					}
				}
				if (!accept) {
					ind.push_back(tmp_word);
					tmp_type.t_pos = ind.size() - 1;
					tmp_type.t_type = token_ind;
					token.push_back(tmp_type);
					accept = true;
				}
			}
		}
		else if (tmp_word[0] == '\''&&tmp_word.size() >= 3) {//�ַ�����
			tmp_type.t_type = token_char_cnt;
			if (char_cnt.size() > 0)
			{
				for (int i = 0; i < char_cnt.size(); i++)
				{
					if (char_cnt[i] == tmp_word)
					{
						tmp_type.t_pos = i;
						accept = true;
					}
				}
			}
			if (!accept) {
				char_cnt.push_back(tmp_word);
				tmp_type.t_pos = char_cnt.size() - 1;
			}
			token.push_back(tmp_type);
		}
		else if (tmp_word[0] == '"') {//�ַ�������
			tmp_type.t_type = token_str_cnt;
			if (str_cnt.size() > 0) {
				for (int i = 0; i < char_cnt.size(); i++)
				{
					if (str_cnt[i] == tmp_word) {
						tmp_type.t_pos = i;
						accept = true;
					}
				}
			}
			if (!accept) {
				str_cnt.push_back(tmp_word);
				tmp_type.t_pos = str_cnt.size() - 1;
			}
			token.push_back(tmp_type);
		}
		else if (isnum(tmp_word[0]) | (tmp_word[0] == '-'&&isnum(tmp_word[1]))) {//����
			double tmp;
			tmp = stod(tmp_word.c_str(), 0);
			for (int i = 0; i < cnt.size(); i++) {
				if (cnt[i] == tmp) {
					tmp_type.t_pos = i;
					tmp_type.t_type = token_cnt;
					token.push_back(tmp_type);
					accept = true;
					break;
				}
			}
			if (!accept) {
				cnt.push_back(tmp);
				tmp_type.t_pos = cnt.size() - 1;
				tmp_type.t_type = token_cnt;
				token.push_back(tmp_type);
				accept = true;
			}
		}
		else {
			if (!accept) {
				for (int i = 0; i < sym_length; i++) {
					if (sym[i] == tmp_word) {
						tmp_type.t_pos = i;
						tmp_type.t_type = token_sym;
						token.push_back(tmp_type);
						accept = true;
						break;
					}
				}
			}
		}
		pos++;
	}
}



void savetoken()
{
	ofstream ofile("result.txt");
	if (!ofile.is_open()) {
		ofile << "Error opening file" << endl;
		return ;
	}


	//����ؼ��ֱ�0
	ofile << "�ؼ��ֱ�0";
	for (int i = 0; i < key_length; i++) {
		if (i % 6 == 0) ofile << endl;
		ofile << key[i] << "\t";
	}



	//��������1
	ofile << endl << "�����1";
	for (int i = 0; i < sym_length; i++) {
		if (i % 6 == 0) ofile << endl;
		ofile << sym[i] << "\t";
	}


	//����ַ�����2
	ofile << endl << "�ַ�����2";
	for (int i = 0; i < str_cnt.size(); i++)
	{
		if (i % 6 == 0) ofile << endl;
		ofile << str_cnt[i] << "\t";
	}

	//���������3
	ofile << endl << "������3";
	for (int i = 0; i < cnt.size(); i++) {
		if (i % 6 == 0) ofile << endl;
		ofile << cnt[i] << "\t";
	}


	//�����ʶ����
	ofile << endl << "��ʶ����4";
	for (int i = 0; i < ind.size(); i++) {
		if (i % 6 == 0) ofile << endl;
		ofile << ind[i] << "\t";
	}

	//����ַ���
	ofile << endl << "�ַ���5";
	for (int i = 0; i < char_cnt.size(); i++) {
		if (i % 6 == 0) ofile << endl;
		ofile << char_cnt[i] << "\t";
	}
	//���token����
	ofile << endl << "token";
	for (int i = 0; i < token.size(); i++) {
		if (i % 6 == 0) ofile << endl;
		ofile << "(" << token[i].t_type << "," << token[i].t_pos << ")" << "\t";
	}
	ofile.close();
	//ofile << "success!" << endl;
}

int tokenpos;

bool isw0()
{
	bool flag;
	if (iscam) return false;
	token_type t = token[tokenpos];
	if (t.t_type == token_sym&&t.t_pos == 19) flag=true;
	else if (t.t_type == token_sym&&t.t_pos == 20) flag=true;
	else flag=false;

	if(flag) tokenpos++;
	return flag;
}

bool isw1()
{
	bool flag;
	if (iscam) return false;
	token_type t = token[tokenpos];
	if (t.t_type == token_sym&&t.t_pos == 21) flag=true;
	else if (t.t_type == token_sym&&t.t_pos == 22) flag=true;
	else flag=false;

	if(flag) tokenpos++;
	return flag;
}

bool isl()
{
	//cout << "isl" << endl;
	bool flag;
	if (iscam) return false;
	token_type t = token[tokenpos];
	if (t.t_type == token_cnt | t.t_type == token_ind) flag = true;
	else flag = false;
	if(flag) tokenpos++;
	return flag;
}

bool iskl()
{
	
	bool flag;
	if (iscam) return false;
	token_type t = token[tokenpos];
	if (t.t_type == token_sym&&t.t_pos == 3) flag = true;
	else flag = false;
	if(flag) tokenpos++;
	return flag;
}

bool iskr()
{
	bool flag;
	if (iscam) return false;
	token_type t = token[tokenpos];
	if (t.t_type == token_sym&&t.t_pos == 4) flag = true;
	else flag = false;
	if(flag) tokenpos++;
	return flag;

}

bool isj() 
{
	bool flag;
	if (iscam) return false;
	token_type t = token[tokenpos];
	if (t.t_type == token_sym&&t.t_pos == 7) flag = true;
	else flag = false;
	if(flag) tokenpos++;
	return flag;
}

bool E1();
bool T();
bool T1();
bool F();

bool E()
{
	if(T()) return E1();
	return false;
}

bool E1()
{
	//if (iscam) return true;
	if (isw0()) {
		if (T()) {
			return E1();
		}
		else return false;
	}
	return true;
}

bool T()
{
	if (F()) return T1();
	else {
		return false;
	}
}


bool T1()
{
	//if (iscam) return true;
	if (isw1()) {
		if (F()) return T1();
		else return false;
	}
	else {
		return true;
	}
}

bool F()
{
	
	//if (iscam) return false;
	if (isl()) {
		return true;
	}
	else if (iskl()) {
		if (E()) {
				if (iskr()) {
					return true;
				}
		}
	}
	return false;
}


bool Syntax()
{
	
	tokenpos = 0;
	//cout << (*recu).t_pos << " " << token[0].t_pos << endl;
	token_type tmp;
	tmp.t_type = token_sym;
	tmp.t_pos = 7;
	//token.push_back(tmp);
	if (E()) {
			if (isj()) return true;
	}
	return false;
}

LL intToLL(int a)
{
	switch (a)
	{
		case 0:return LL_E;
		case 1:return LL_E1;
		case 2:return LL_T;
		case 3:return LL_T1;
		case 4:return LL_F;
		case 5:return LL_W0;
		case 6:return LL_W1;
		case 7:return LL_I;
		case 8:return LL_L;
		case 9:return LL_R;
		case 10:return LL_J;
		case 11:return LL_N;
		default: return LL_N;
	}
	return LL_N;
}

void setLL()//��ʼ�����
{
	tab tmp;
	for (int i = 0; i <= 11; i++)//����ֵ
	{
		for (int j = 0; j <= 11; j++)
		{
			tmp.fir = intToLL(i);
			tmp.end = intToLL(j);
			LLtable[tmp] = -1;
		}
	}

	tmp.fir = LL_E, tmp.end = LL_I, LLtable[tmp] = 1;
	tmp.end = LL_L, LLtable[tmp] = 1;

	tmp.fir = LL_E1, tmp.end = LL_W0, LLtable[tmp] = 2;
	tmp.end = LL_R, LLtable[tmp] = 3;
	tmp.end = LL_J, LLtable[tmp] = 3;

	tmp.fir = LL_T, tmp.end = LL_I, LLtable[tmp] = 4;
	tmp.end = LL_L, LLtable[tmp] = 4;

	tmp.fir = LL_T1, tmp.end = LL_W0, LLtable[tmp] = 6;
	tmp.end = LL_W1, LLtable[tmp] = 5;
	tmp.end = LL_R, LLtable[tmp] = 6;
	tmp.end = LL_J, LLtable[tmp] = 6;

	tmp.fir = LL_F, tmp.end = LL_I, LLtable[tmp] = 7;
	tmp.end = LL_L, LLtable[tmp] = 8;

	transGrammer[0].clear();
	transGrammer[1] = { LL_T,LL_E1 };
	transGrammer[2] = { LL_W0,LL_T,LL_GEW0,LL_E1 };
	transGrammer[3].clear();
	transGrammer[4] = { LL_F,LL_T1 };
	transGrammer[5] = { LL_W1,LL_F,LL_GEW1,LL_T1 };
	transGrammer[6].clear();
	transGrammer[7] = { LL_I ,LL_PUSH};
	transGrammer[8] = { LL_L,LL_E,LL_R };
}

bool isVn(LL a)//�ж��Ƿ�Ϊ���ս�����Ƿ��ս������true���ս������false
{
	switch (a)
	{
	case LL_E:return true;
		break;
	case LL_E1:return true;
		break;
	case LL_T:return true;
		break;
	case LL_T1:return true;
		break;
	case LL_F:return true;
		break;
	case LL_W0:return false;
		break;
	case LL_W1:return false;
		break;
	case LL_I:return false;
		break;
	case LL_L:return false;
		break;
	case LL_R:return false;
		break;
	case LL_J:return false;
		break;
	case LL_N:return false;
		break;
	default:return false;//
		break;
	}
}

bool isAction(LL a)
{
	switch (a)
	{
	case LL_GEW0: return true;
		break;
	case LL_GEW1:return true;
		break;
	case LL_PUSH:return true;
		break;
	default:return false;
		break;
	}
}

LL tokenToLL()
{
	if (isw0()) return LL_W0;
	else if (isw1())  return LL_W1;
	else if (iskl()) return  LL_L;
	else if (iskr()) return LL_R;
	else if (isj()) return LL_J;
	else if (isl()) return LL_I;
	else return LL_E;
}

bool LLanalysis()//LL(1)����
{
	setLL();
	tokenpos = 0;

	/*
	while (tokenpos<token.size())//��token����ת��Ϊ�ս������
	{
		if (isw0()) anaqueue.push(LL_W0);
		else if (isw1()) anaqueue.push(LL_W1);
		else if (iskl()) anaqueue.push(LL_L);
		else if (iskr()) anaqueue.push(LL_R);
		else if (isj()) anaqueue.push(LL_J);
		else if (isl()) anaqueue.push(LL_I);
		else return false;
	}
	*/
	anastack.push(LL_J), anastack.push(LL_E);
	tab tmp;
	//for (int i = 0; i < token.size(); i++) anaqueue.push(token[i]);
	while (!anastack.empty()|(tokenpos<token.size()))//���з���
	{
		tmp.fir = anastack.top();
		tmp.end = tokenToLL(), tokenpos--;
		if (isVn(tmp.fir)) {//����Ƿ��ս���ҷ����嶯��
			if (LLtable[tmp] == -1) {
				return false;
			}
			else {
				int pos = LLtable[tmp];
				if (transGrammer[pos].empty()) {//����Ƴ���
					anastack.pop();
				}
				else {
					anastack.pop();
					for (int i = transGrammer[pos].size() - 1; i >= 0;i--) {//
						anastack.push(transGrammer[pos][i]);
						if (transGrammer[pos][i] == LL_GEW0) {
							ac_w0.push_back(token[tokenpos]);
						}
						else if (transGrammer[pos][i] == LL_GEW1) {
							ac_w1.push_back(token[tokenpos]);
						}
						else if (transGrammer[pos][i] == LL_PUSH) {
							ac_push.push_back(token[tokenpos]);
						}
					}
				}
			}
		}
		else if (isAction(tmp.fir)) {//��������嶯��
			if (tmp.fir == LL_PUSH) {
				sem.push(ac_push[ac_push.size() - 1]);
				ac_push.pop_back();
			}
			else if (tmp.fir == LL_GEW0) {
				siyuan s_tmp;
				s_tmp.thr = sem.top(), sem.pop();
				s_tmp.se = sem.top(), sem.pop();
				s_tmp.fi = ac_w0[ac_w0.size() - 1], ac_w0.pop_back();
				token_type si_token;
				string si_tmp = "t" + to_string(indextmp++);
				si_token.t_type = token_ind;
				ind.push_back(si_tmp);
				si_token.t_pos = ind.size() - 1;
				sem.push(si_token);
				s_tmp.fou = si_token;
				qt.push_back(s_tmp);
			}
			else if(tmp.fir==LL_GEW1){
				siyuan s_tmp;
				s_tmp.thr = sem.top(), sem.pop();
				s_tmp.se = sem.top(), sem.pop();
				s_tmp.fi = ac_w1[ac_w1.size() - 1], ac_w1.pop_back();
				token_type si_token;
				string si_tmp = "t" + to_string(indextmp++);
				si_token.t_type = token_ind;
				ind.push_back(si_tmp);
				si_token.t_pos = ind.size() - 1;
				sem.push(si_token);
				s_tmp.fou = si_token;
				qt.push_back(s_tmp);
			}
			//else return false;
			anastack.pop();
		}
		else {//������ս��
			if (tmp.fir == tmp.end) {
				anastack.pop();
				//anaqueue.pop();
				tokenpos++;
			}
			else {
				return false;
			}
		}
	}
	return true;

}

int main()
{

	//�ļ������д��string��
	fstream file("test.txt");
	if (!file.is_open()) {
		cout << "Error opening file" << endl;
		return 0;
	}
	stringstream ss;
	ss << file.rdbuf();
	string str = ss.str();
	token.clear();
	automatan(str);
	setToken();
	savetoken();
	bool res;

	res=Syntax();//�ݹ��½��ӳ���
	cout << "�ݹ��ӳ��򷨣�";
	if (res) cout << "true" << endl;
	else cout << "false" << endl;

	res = LLanalysis();//LL(1)����
	cout << "LL(1)��������";
	if (res) cout << "true" << endl;
	else cout << "false" << endl;
	for (int i = 0; i < qt.size(); i++) {//������Ԫʽ
		printf("(%s,", sym[qt[i].fi.t_pos].c_str());
		if (qt[i].se.t_type == token_ind) {
			printf("%s,", ind[qt[i].se.t_pos].c_str());
		}
		else {
			int tmp = cnt[qt[i].se.t_pos];
			printf("%d,", tmp);
		}
		if (qt[i].thr.t_type == token_ind) {
			printf("%s,", ind[qt[i].thr.t_pos].c_str());
		}
		else {
			int tmp = cnt[qt[i].thr.t_pos];
			printf("%d,", tmp);
		}
		printf("%s)\n", ind[qt[i].fou.t_pos].c_str());
	}
	
	return 0;
}
