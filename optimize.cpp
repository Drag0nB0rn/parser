#include"tableExtern.h"

using namespace std;

extern table idTable;

vector<fourelement> res;	//�����Ԫʽ

struct node
{
	string value;//�ڵ�ֵ
	string ope;//�ڵ������
	vector<int> ele;		//�ڵ�Ԫ��
	node *left, *right;//���ҽڵ�
};

vector<node*> father;//��¼���еĸ��ڵ�,ÿ�β��붼Ҫ����������

