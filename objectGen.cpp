#include"tableExtern.h"
#include<stack>

using namespace std;


struct reg     //�Ĵ���
{
	bool act;	//��ʶ�����жϵ�ǰֵ�Ƿ��Ծ

	int value;	//��ǰ��ַ����ʱֻ����int
};
reg ax;//���Ĵ���

string obj;				//Ŀ�����

string ifProcess;//if������
int ifProNum;//if���̱��
stack<string> iEndfStack;
stack<string> elseStack;

string whiProcess;//while������
int whiProNum;//while���̱��
stack<string> whileEndStack;
stack<string> doStack;

string cmpProcess;//�Ƚϲ����Ĺ���
int cmpProNum;//�ȽϹ��̱��

void saveax()		//��Ҫ�ı�axʱ���ж�ax��ǰֵ�Ƿ��Ծ�����ж��Ƿ񱣴�
{
	if (ax.act) {	//MOV [ax.value],ax
		obj += "MOV [";
		obj += ax.value;
		obj += "],ax";
	}
}

void setax(int pos)
{
	ax.value = idTable.getAddr(pos);
	ax.act = idTable.isactive(pos);
}

//ÿ�θı�ax�����Ƕ�Ҫ�ж��Ƿ�Ҫ����֮ǰax�е�ֵ��
void opeAxPos(string ope, int pos)   //ope ax,[pos]
{
	int par = idTable.getAddr(pos);
	saveax();
	obj += ope;
	obj += " ax,[";
	obj += par;
	obj += "]\n";
	setax(pos);
}


void opePosAx(string ope, int pos)	//ope [pos],ax
{
	int par = idTable.getAddr(pos);
	obj += ope;
	obj += " [";
	obj += par;
	obj += "],ax\n";
}


void opePosPos(string ope, int pos1, int pos2)//ope [pos1],[pos2]
{
	opeAxPos("MOV",pos1);//MOV  ax,[pos1]
	opeAxPos(ope, pos2);//ope ax,pos2
}

void ope_1(string ope,int pos)//+  -  *  /
{
	int pos1, pos2, pos3;

	fourelement curfour;
	curfour = four[pos];//��ǰ��Ԫʽ

	//���������ĵ�ַ
	pos1 = curfour.pos1;
	pos2 = curfour.pos2;
	pos3 = curfour.pos3;

	//���Ҫ��axָ��pos3���ڸı�ax֮ǰ����pos3��Ծ��񣬾����Ƿ�axд��pos3
	if (ax.value != pos1&&ax.value != pos2) {//ax!=pos1 && ax!=pos2
		opePosPos(ope, pos1, pos2);
	}
	else if (ax.value == pos2) {//ax==pos2    ADD ax,[pos1]
		if (ope == "ADD" | ope == "MUL") {
			opeAxPos(ope, pos1);
		}
		else {
			opePosPos(ope, pos1, pos2);
		}
	}
	else {//ax==pos1	 |	ax==pos&&ax==pos2			ADD ax,[pos2]  
		opeAxPos(ope, pos2);
	}

	setax(pos3);//��axָ��pos3

}

void opeCmp(string ope, int pos)
{
	int pos1, pos2, pos3;
	pos1 = idTable.getAddr( four[pos].pos1), pos2 = idTable.getAddr(four[pos].pos2), pos3 = idTable.getAddr(four[pos].pos3);
	//CMP [pos1],[pos2]
	obj += "CMP ";
	obj += "[", obj += pos1, obj += "],";
	obj += "[", obj += pos2, obj += "]\n";

	//ope cmpProcess1
	obj += ope,obj+=" ", obj += cmpProcess, obj += to_string(cmpProNum);

	//MOV [pos3],1
	obj += "\nMOV [", obj += pos3, obj += "],1\n";

	//JMP cmpProcess2
	obj += "JMP ", obj += cmpProcess, obj += to_string(cmpProNum + 1);

	//cmpProcess1:
	obj += cmpProcess, obj += to_string(cmpProNum), obj += ":\n";

	//MOV t,0
	obj+="MOV [", obj += pos3, obj += "],0\n";

	//cmpProcess2:
	obj += cmpProcess, obj += to_string(cmpProNum + 1), obj += ":\n";

}

void objGen()
{


	//����Ϊ����ʼ��
	ax.act = false, ax.value = -1;



	int pos = 0;	//ָʾ��
	ifProcess += "ifProc";
	whiProcess += "whiProc";
	cmpProcess += "cmpProc";

	ifProNum = 1;
	whiProNum = 1;
	cmpProNum = 1;
	//����Ŀ���������
	int len = four.size();
	fourelement curfour;
	while (pos < len)
	{

		curfour = four[pos];//��ǰ��Ԫʽ


		if (curfour.fix == "+") {
			ope_1("ADD", pos);
		}
		else if (curfour.fix == "-") {
			ope_1("SUB", pos);
		}
		else if (curfour.fix == "*") {
			ope_1("MUL", pos);
		}
		else if (curfour.fix == "/") {
			ope_1("DIV", pos);
		}
		else if (curfour.fix == "=") {  //(=,  a,   ,t   )
			if (ax.value == idTable.getAddr(curfour.pos1)) {//MOV [pos3],ax
				opePosAx("MOV", curfour.pos3);
			}
			else {// MOV ax,[pos1];   MOV [pos3],ax
				opeAxPos("MOV", curfour.pos1);
				opePosAx("MOV", curfour.pos3);
			}
		}
		else if (curfour.fix == ">") {//cmp pos1,pos2;   
			opeCmp("JB",pos);
		}
		else if (curfour.fix == "<") {
			opeCmp("JA", pos);
		}
		else if (curfour.fix == "if") { //( if , t,  ,_pos )���tΪ�٣�������_pos,����˳��ִ��

			/*
			if(){
				 ifProcess0
				JMP ifProcess2
			}
			else{
				ifProcess1
			}
			ifProcess2
			*/

			//��if�ж�Ϊ�٣���������1  CMP 0,[pos1]
			obj += "CMP 0,[";
			obj += idTable.getAddr(four[pos].pos1);
			obj += "]\n";

			//JE ifProcess1
			obj += "JE ";
			obj += ifProcess;
			obj += to_string(ifProNum);
			obj += "\n";
			string tmp = ifProcess;
			tmp += to_string(ifProNum);
			elseStack.push(tmp);//process1ѹջ
			tmp.clear();
			tmp = ifProcess;
			tmp += to_string(ifProNum + 1);
			elseStack.push(tmp);//process2ѹջ
			iEndfStack.push(tmp);//process2ѹջ��
			ifProNum += 2;
		}
		else if (curfour.fix == "else") {
			//JMP ifProcess2
			obj += "JMP ";//��ִ��ifProcess0������������̺���ת��pocess2��Ҳ����ifelse����
			obj += elseStack.top(), elseStack.pop();
			obj += "\n";

			//ifProcess1:
			obj += elseStack.top(), elseStack.pop();
			obj += ":\n";
		}
		else if (curfour.fix == "ifEnd") {//����else֮������ifelse�ĳ���α�ʶ
			//ifProcess2:
			obj += iEndfStack.top(), iEndfStack.pop();//ifProcess2:
			obj += ":\n";
		}
		else if (curfour.fix == "while") {//while��ʼ

			/*
			pro1:		 while
			//����
			CMP t1,1		do
			JNZ	pro2
			//����
			JMP pro1; endwhile
			pro2:
			*/
			obj += whiProcess;
			obj += to_string(whiProNum);
			obj += ":\n";
			string tmp = whiProcess;
			tmp += to_string(whiProNum+1);
			whileEndStack.push(tmp);//process2ѹջ
			doStack.push(tmp);//process2ѹջ
			tmp.clear();
			tmp = whiProcess;
			tmp += to_string(whiProNum);
			whileEndStack.push(tmp);//process1ѹջ
			whiProNum += 2;
		}
		else if (curfour.fix == "do") {//�ж�����  (do, t,,)
			obj += "CMP [";
			obj += idTable.getAddr(curfour.pos1);
			obj += "],1\n";
			obj += "JNZ ";
			obj += doStack.top(), doStack.pop();
		}
		else if (curfour.fix == "whileEnd") {//while������־�������ж����������Ƿ�Ҫ����
			obj += "JMP ";
			obj += whileEndStack.top(), whileEndStack.pop();
			obj += "\n";
			obj += whileEndStack.top(), whileEndStack.pop();
			obj += ":\n";
		}
		else if (curfour.fix == "call") {//���ú���

		}
		else if (curfour.fix == "return") {//��������

		}
		else if (curfour.fix == "funStart") {//�������忪ʼ
			obj+=idTable.getFunName(curfour.pos1);
			obj += " PROC NEAR\n";
		}
		else if (curfour.fix == "funEnd") {//�����������
			obj += "RET\n";
			obj += idTable.getFunName(curfour.pos1);
			obj += " ENDP\n";
		}

	}

	
}


