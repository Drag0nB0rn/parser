#include"tableExtern.h"

using namespace std;

extern table idTable;

vector<fourelement> res;	//�����Ԫʽ
vector<fourelement> basicBlock;//������
vector<fourelement> tmpRes;//�Ż���Ļ�����

struct node
{
	int number;//�ڵ���
	//int value;//����ǳ���������ֵ
	string fix;//�ڵ������
	vector<int> ele;		//�ڵ�Ԫ��
	int left, right;//���ҽڵ�
};

vector<node> father;//��¼���еĸ��ڵ�,ÿ�β��붼Ҫ����������

/*



*/
int find(int pos)
{
	for (int i = father.size() - 1; i >= 0; i--) {
		for (int j = 0; j < father[i].ele.size(); j++) {
			if (father[i].ele[j] == pos) {
				return i;
			}
		}
	}
	return -1;
}

int findConst(int curConst)//
{
	for (int i = father.size() - 1; i >= 0; i--) {//����ǳ�������һ����ǰ��
		if (idTable.isConst(father[i].ele[0])) {
			if (curConst == idTable.getConst(father[i].ele[0]))
				return i;
		}
	}
	return -1;
}


int findCom(int pos)
{
	bool flag = false;
	for (int i = father.size(); i>=0; i--) {
		if (father[i].fix == basicBlock[pos].fix) {
			if (father[i].left != -1) {
				for (auto it : father[father[i].left].ele) {
					if (it == basicBlock[pos].pos1) {
						flag = true;
						break;
					}
				}
				if (flag) {//�����ֵ��ͬ
					flag = false;
					if (father[i].right != -1) {
						for (auto it : father[father[i].right].ele) {
							if (it == basicBlock[pos].pos2) {
								flag = true;
								break;
							}
						}
					}
					if (flag) {//�����ֵҲ��ͬ
						return i;
					}
				}
			}
		}
	}
	return -1;
}

void dagSwap(int pos)
{
	if (idTable.isTmp(father[pos].ele[0])) {
		for (int i = 1; i < father[pos].ele.size(); i++) {
			if (!idTable.isTmp(father[pos].ele[i])) {
				swap(father[pos].ele[0], father[pos].ele[i]);
				return;
			}
		}
	}
}

bool isCacu(string s)
{
	if (s == "+" | s == "-" | s == "*" | s == "/" | s == ">" | s == "<" |s=="=")
		return true;
	return false;
}

void deleM(int dad,int i)
{
	if (idTable.isTmp(basicBlock[i].pos3)) {
		for (int j = father.size()-1; j>=0, j != dad; j--) {//��AΪ����ǣ���ɾ��
			vector<int>::iterator it = father[j].ele.begin()+1;
			if(!father[i].ele.empty()){
				for (; it != father[j].ele.end(); it++) {
					if ((*it) == basicBlock[i].pos3) {
						father[j].ele.erase(it);
						break;
					}
				}
			}
		}
	}
}


void fourEq(int i)
{
	int dad;
	dad = find(basicBlock[i].pos1);
	if (dad != -1) {//����ҵ���B
		father[dad].ele.push_back(basicBlock[i].pos3);
		//if (!idTable.isTmp(basicBlock[i].pos3)) {//���������ʱ����������Ϊ�����
			//swap(father[dad].ele[0], father[dad].ele[father[dad].ele.size() - 1]);
		//}
	}
	else {//���û�ҵ�B
		node newNode;
		newNode.number = father.size();
		newNode.ele.push_back(basicBlock[i].pos1);
		newNode.ele.push_back(basicBlock[i].pos3);
		newNode.left = newNode.right = -1;
		//if (!idTable.isTmp(basicBlock[i].pos3)) {
			//swap(newNode.ele[0], newNode.ele[1]);
		//}
		father.push_back(newNode);
	}
	deleM(dad, i);
}

int CaculateConst(int i)
{
	int resConst=0;
	int  const1 = idTable.getConst(basicBlock[i].pos1), const2 = idTable.getConst(basicBlock[i].pos2);
	if (basicBlock[i].fix == "+") {
		resConst = const1 + const2;
	}
	else if (basicBlock[i].fix == "-") {
		resConst = const1 - const2;
	}
	else if (basicBlock[i].fix == "*") {
		resConst = const1*const2;
	}
	else if (basicBlock[i].fix == "/") {
		resConst = const1 - const2;
	}
	else if (basicBlock[i].fix == ">") {
		resConst = (const1 > const2) ? 1 : 0;
	}
	else if (basicBlock[i].fix == "<") {
		resConst = (const1 < const2) ? 1 : 0;
	}
	return resConst;
}

void dag()
{
	tmpRes.clear();
	father.clear();
	int left, right,dad;
	for (int i = 0; i < basicBlock.size(); i++)//����������ڵ�DAG
	{
		if (basicBlock[i].fix == "=") {
			fourEq(i);
		}
		else if (isCacu(basicBlock[i].fix)) {
			if (idTable.isConst(basicBlock[i].pos1) && idTable.isConst(basicBlock[i].pos2)) {//����ǳ������ʽ
				int  resConst=CaculateConst(i);
				int constPos = findConst(resConst);
				if (constPos != -1) {//����ҵ���Ӧ����
					father[constPos].ele.push_back(basicBlock[i].pos3);
				}
				else {//���û�У����ڷ��ű��в���ó��������½��ڵ�
					node newNode;
					int pos = idTable.insertConst(resConst);//�ڷ��ű��в����µĳ���
					newNode.left = newNode.right = -1;
					newNode.number = father.size();
					newNode.ele.push_back(pos);
					newNode.ele.push_back(basicBlock[i].pos3);
					father.push_back(newNode);
					constPos = father.size() - 1;
				}
				deleM(constPos, i);
			}
			else {//����ǳ�����ʽ
				int pos = findCom(i);
				if (pos != -1) {//������ڹ������ʽ
					father[pos].ele.push_back(basicBlock[i].pos3);
				}
				else {//���������
					node newNode;
					newNode.fix = basicBlock[i].fix;
					int leftPos, rightPos;
					leftPos = find(basicBlock[i].pos1);//Ѱ���Ƿ����������ڵ�
					if (leftPos == -1) {//���������ڵ㲻���ڣ��򴴽��������ڵ�
						node leftNode;
						leftNode.left = leftNode.right = -1;
						leftNode.ele.push_back(basicBlock[i].pos1);
						leftPos=leftNode.number = father.size();
						father.push_back(leftNode);
					}
					rightPos = find(basicBlock[i].pos2);//Ѱ�����������
					if (rightPos == -1) {//���������ڵ㲻����
						node rightNode;
						rightNode.left = rightNode.right = -1;
						rightNode.ele.push_back(basicBlock[i].pos1);
						rightPos= rightNode.number = father.size();
						father.push_back(rightNode);
					}
					newNode.left = leftPos;
					newNode.right = rightPos;
					newNode.number = father.size();
					newNode.fix = basicBlock[i].fix;
					newNode.ele.push_back(basicBlock[i].pos3);
					father.push_back(newNode);
					pos = father.size() - 1;
				}
				deleM(pos, i);//ɾ�������ڵ��е�pos3
			}
		}
	}

	fourelement tmp;
	if (!isCacu(basicBlock[0].fix)) {
		tmpRes.push_back(basicBlock[0]);
	}

	for (int i = 0; i < father.size(); i++) {
		tmp.fix = father[i].fix;
		if (father[i].left == -1 && father[i].right == -1) {//�����Ҷ�ڵ�
			tmp.pos1 = father[i].ele[0];
			if (!father[i].ele.empty()) {
				for (int j = 1; j < father[i].ele.size(); j++) {
					if (!idTable.isTmp(father[i].ele[j])) {
						tmp.pos3 = father[i].ele[j];
						tmpRes.push_back(tmp);
					}
				}
			}
		}
		else {//����Ҷ�ڵ�
			if (!father[i].ele.empty()) {
				if (father[i].left != -1) {
					tmp.pos1 = father[father[i].left].ele[0];
				}
				if (father[i].right != -1) {
					tmp.pos2 = father[father[i].right].ele[0];
				}
				tmpRes.push_back(tmp);
				for (int j = 1; j < father[i].ele.size(); j++) {
					if (!idTable.isTmp(father[i].ele[j])) {
						tmp.fix = "=";
						tmp.pos1 = father[i].ele[0];
						tmp.pos3 = father[i].ele[j];
						tmpRes.push_back(tmp);
					}
				}
			}
		}
	}

	if (!isCacu(basicBlock[basicBlock.size() - 1].fix)) {
		tmpRes.push_back(basicBlock[basicBlock.size() - 1]);
	}

	for (int i = 0; i < tmpRes.size(); i++)//��������Ԫʽ
		res.push_back(tmpRes[i]);
}
int divedBlock(int start)
{
	basicBlock.clear();
	tmpRes.clear();
	int pos = start;
	string fix;
	while (pos<four.size())
	{
		fix = four[pos].fix;
		if ((fix == "if") | (fix == "ifEnd") | (fix == "else") | (fix == "elseEnd")) {//���� if ifEnd else elseEnd��һ�����������
			tmpRes.push_back(four[pos]);
			pos++;
			break;
		}
		if ((fix == "while")|(fix=="funStart")) {//
			break;
		}
		if ((fix == "do") | (fix == "endWhile")|(fix=="funEnd")) {//
			tmpRes.push_back(four[pos]);
			pos++;
			break;
		}
		if (fix == "call") {
			tmpRes.push_back(four[pos]);
			pos++;
			break;
		}
		tmpRes.push_back(four[pos]);
		pos++;
	}
	basicBlock = tmpRes;
	return pos;
}

void activeSet()//���û�Ծ��Ϣ����
{
	for (int i = 0; i < idTable.size(); i++) {
		if (idTable.isTmp(i)) {
			idTable.setActive(i, false);
		}
		else {
			idTable.setActive(i, true);
		}
	}
	for (int i = res.size(); i >= 0; i--) {
		res[i].active3 = idTable.isactive(res[i].pos3);
		idTable.setActive(res[i].pos3, false);
		res[i].active2 = idTable.isactive;
		idTable.setActive(res[i].pos2, true);
		res[i].active1 = idTable.isactive(res[i].pos1);
		idTable.setActive(res[i].pos1, true);
	}
}

void optimize()
{
	int pos = 0;
	while (pos < four.size()) {
		pos=divedBlock(pos);
		dag();
	}
	activeSet();//���û�Ծ��Ϣ����

}
