#include "table.h"
#include "parser.h"
using namespace std;
check parserTable::checkList(string cur)
{
	check t;
	/*map<string, map<char,string>>::iterator it;
	it = parserList.find(cur);
	if (it != parserList.end())
	{
		t.flag = true;
		t.production = it->second;
		//cout << it->first;
	}
	else
		t.flag = false;
	return t;*/
	map<string, production>::iterator it;
	it = parserl.find(cur);
	if (it != parserl.end())
	{
		t.flag = true;
		t.p = it->second;
	}
	else
		t.flag = false;
	return t;
}

void parserTable::creatParserList()
{
	//struct  production t('E', "ab");
	/*production t;
	t.pro['E'] = "a";
	parserList["i"] = t;*/
	map<char, string> t;
	t['E'] = "a";
	parserList["i"] = t;
	production p;
	p.left = 'E';
	p.right = "i";
	parserl["i"] = p;
	
}

void parserTable::getToken()
{

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
	check t = table.checkList("i");
	if (t.flag)
	{
		cout << "true" << endl;
		cout << t.p.left << "->" << t.p.right;
	}
	else
		cout << "false" << endl;
	/*map<char, string>::iterator it;
	check t = table.checkList("i");
	it = t.p.find('E');
	if (t.flag)
	{
		cout << "true";
		cout <<"\t"<< it->first << "->" << it->second;
		
	}
	else
		cout << "false";*/
	
	return 0;
}



