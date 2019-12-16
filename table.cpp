#include "table.h"

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

int table::getAddr(const int pos)
{
	return synblTable[pos].addr;
}

synblCat table::getCat(const int pos)
{

	return synblTable[pos].cat;
}

synblTval table::getTval(const int pos)
{
	return synblTable[pos].type;
}

int table::size()
{
	return synblTable.size();
}

bool table::isactive(const int pos)
{
	return synblTable[pos].active;
}

int table::getValue(const int pos)
{
	if (synblTable[pos].type == tvalInt) {//Ӧ����ֵ����ʱ���ص�ַ�������޸�
		return synblTable[pos].addr;
	}
	return 0;
}

bool table::istmp(const int pos)
{
	return false;
}
