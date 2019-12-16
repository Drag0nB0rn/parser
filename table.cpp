#include "table.h"

table idTable;	//��ʶ���������ű�

vector<fourelement> four;			//��Ԫʽ����

void table::clear()//�����ʼ��
{
	synblTable.clear();
	tapelTable.clear();
	ainflTable.clear();
	rinflTable.clear();
	pfinflTable.clear();
	conslTable.clear();
	lenlTable.clear();
	vallTable.clear();
}

table::table()
{

	clear();


}

string table::getFunName(int pos)
{
	return synblTable[pos].name;
}

int table::getAddr(int pos)
{
	return synblTable[pos].addr;
}

synblCat table::getCat(int pos)
{

	return synblTable[pos].cat;
}

synblTval table::getTval(int pos)
{
	return synblTable[pos].type;
}

int table::size()
{
	return synblTable.size();
}

bool table::isactive(int pos)
{
	return synblTable[pos].active;
}

int table::getValue(int pos)
{
	if (synblTable[pos].type == tvalInt) {//Ӧ����ֵ����ʱ���ص�ַ�������޸�
		return synblTable[pos].addr;
	}
	return 0;
}

bool table::isTmp(int pos)
{
	return false;
}
