#include "table.h"
#include "parser.h"
using namespace std;
check parserTable::checkList(string cur,string top)
{
	check t;
	map<int, string>::iterator it;
	for (it = parserList.begin(); it != parserList.end(); it++)  //用迭代器遍历查分析表表
	{
		production tmp = pro[it->first];
		cout << tmp.left << "->" << tmp.right << " " << it->second<<endl;
		if (it->second == cur && tmp.left == top)   //查到
		{
			t.flag = true;
			t.proIndex = it->first;
			break;
		}
		else
		{
			t.flag = false;
			t.proIndex = -1;
		}
	}
	return t;
}

void parserTable::creatProduction()  //test
{
	production t;
	t.left = "E";
	t.right = "i";
	pro.push_back(t);
	t.left = "A";
	t.right = "a";
	pro.push_back(t);
	t.left = "C";
	t.right = "a";
	pro.push_back(t);
}

void parserTable::travelProduction()  //test
{
	for (auto u : pro)
	{
		cout << u.left << "->" << u.right << endl;
	}
}

void parserTable::creatParserList()  //test
{
	creatProduction();
	parserList[0] = "i";
	parserList[1] = "a";
	parserList[2] = "a";
}

void parserTable::getToken()
{

}

production parserTable::getProduction(int index)
{
	return pro[index];
}

bool parserTable::isNotTer(char c)
{
	for (auto u : notTerTable)
	{
		if (u == c)
		{
			return true;
		}
		else
			return false;
	}
}

bool parserTable::isTer(string c)
{
	for (auto u : terTable)
	{
		if (u == c)
		{
			return true;
		}
		else
			return false;
	}
}
int main()
{
	parserTable table;
	table.creatParserList();
	table.travelProduction();
	check t = table.checkList("i","E");
	if (t.flag)
	{
		cout << "true" << endl;
		production tmp = table.getProduction(t.proIndex);
		cout << tmp.left << "->" << tmp.right;
	}
	else
		cout << "false" << endl;
	return 0;
}



