/**
 * InfectStatistic
 * TODO
 *
 * @author 221701336
 * @version 1.0
 * @since 2020.02.13
 */ 
 
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <io.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <cassert>
#include <windows.h>

//cd C:\Users\�񵰻���\Desktop\�������\���ٵڶ�����ҵ\InfectStatistic-main\221701336\src
//InfectStatistic.exe list -date 2020-01-25 -type sp ip dead -out C:/Users/�񵰻���/Desktop/�������/���ٵڶ�����ҵ/InfectStatistic-main/221701336/src/out.txt 
//-log C:/Users/�񵰻���/Desktop/�������/���ٵڶ�����ҵ/InfectStatistic-main/221701336/log/ 
//InfectStatistic.exe list -date 2020-01-23 -province ���� ���� -type sp -log C:/Users/�񵰻���/Desktop/�������/���ٵڶ�����ҵ/InfectStatistic-main/221701336/log/ -out C:/Users/�񵰻���/Desktop/�������/���ٵڶ�����ҵ/InfectStatistic-main/221701336/src/out.txt 
using namespace std;

string province[32]={"����","����","����","����","����","�㶫","����","����","����","�ӱ�","����","������",
"����","����","����","����","����","����","���ɹ�","����","�ຣ","ɽ��","ɽ��"
,"����","�Ϻ�","�Ĵ�","���","����","�½�","����","�㽭","ȫ��"}; 

string situation[8]={"���� ��Ⱦ����","���� ���ƻ���","��Ⱦ���� ����","���ƻ��� ����","����","����","���ƻ��� ȷ���Ⱦ","�ų� ���ƻ���"};

typedef struct ListNode
{
    char province[8];//ʡ�� 
	int numOfDead;//number of dead patients ������������ 
	int numOfIP;//number of infection patients ��Ⱦ�������� 
	int numOfSP;//number of suspected patients ���ƻ������� 
	int numOfCured;//number of cured patients  ��Ȭ����������
	int flag;//���ھ����ýڵ��Ƿ���Ҫ��� flag=1��� flag=0����� 
	struct ListNode *next;//ָ����һ���ڵ��ָ��	
}Node,*PNode;


PNode CreatList(void)//��ʼ������ 
{
	int len=31;
	PNode PHead =(PNode)malloc(sizeof(Node));
	if(PHead==NULL)
	{
		cout<<"�ռ����ʧ��"<<endl;
	}
	PHead->numOfCured=0;
	PHead->numOfDead=0;
	PHead->numOfIP=0;
	PHead->numOfSP=0;
	PHead->flag=0;
	strcpy(PHead->province,province[31].c_str());
		 
	PNode pNew=(PNode)malloc(sizeof(Node));
	if(pNew==NULL)
	{
		cout<<"�����½ڵ�ʧ��"<<endl;
	}
	pNew->numOfCured=0;
	pNew->numOfDead=0;
	pNew->numOfIP=0;
	pNew->numOfSP=0;
	pNew->flag=0;
	strcpy(pNew->province,province[0].c_str());
	pNew->next=NULL;
	
	PHead->next=pNew;
	PNode PTail=pNew;
	PTail->next=NULL;
	
	for(int i=1;i<len;i++)
	{
		PNode p=(PNode)malloc(sizeof(Node));
		if(p==NULL)
		{
			cout<<"�����½ڵ�ʧ��"<<endl;
		}
		p->numOfCured=0;
		p->numOfDead=0;
		p->numOfIP=0;
		p->numOfSP=0;
		p->flag=0;
		strcpy(p->province,province[i].c_str());
		PTail->next=p; 
		p->next=NULL;
		PTail=p;
	}
	cout<<"��������ɹ�"<<endl;
	return PHead;
}

string getDate(int argc, char *argv[])//��������в����е����� 
{
	string s1,s2;
	s2="9999-12-31";
	for (int i = 0; i < argc; i++)
    {
		s1=argv[i]; 
        if(s1=="-date")
        {       
			s2=argv[i+1]; 	
		}
    } 
    return s2;
}

string getLog(int argc, char *argv[])//��������в����е�Ŀ¼ 
{
	string s1;
    string s2="NULL";
	for (int i = 0; i < argc; i++)
    {
		s1=argv[i]; 
        if(s1=="-log")
        {        	
        	s2=argv[i+1];
		}
    }
	return s2; 
}

string getOutPath(int argc, char *argv[])//��������в����е����·�� 
{
	string s1;
    string s2="NULL";
	for (int i = 0; i < argc; i++)
    {
		s1=argv[i]; 
        if(s1=="-out")
        {        	
        	s2=argv[i+1];
		}
    }
	return s2; 
}

void getType(int argc, char *argv[],string type[])//��������в����еĲ������� 
{
	string s1;
	string s2;
	for (int i = 0; i < argc; i++)
    {
		s1=argv[i]; 
        if (s1=="-type")
        {	
			for(int j=i+1;j<argc;j++)
			{
				s2=argv[j];
				if(s2=="ip"||s2=="sp"||s2=="cure"||s2=="dead")
				{
					type[j-i-1]=s2;
				}
			}	        	
		}
    }
}

void getProvince(int argc,char *argv[],string province[])//��������в����е�Ҫ��ʡ�� 
{
	string s1;
	string s2;
	for(int i=0;i<argc;i++)
	{
		s1=argv[i];
		if(s1=="-province")
		{
			for(int j=i+1;j<argc;j++)
			{
				s2=argv[j];
				if(s2!="-log"&&s2!="-out"&&s2!="-date"&&s2!="-type"&&s2!="province")
				{
					province[j-i-1]=s2;
				}
			}
		}
	}
}

void AddIP(string province1,int num,PNode head)//ͳ��������Ⱦ���ߵ���� 
{
	//ofstream outFile;
	//outFile.open(("C:/Users/�񵰻���/Desktop/�������/���ٵڶ�����ҵ/InfectStatistic-main/221701336/src/out.txt"),ios::app);
	PNode p=head;
	while(p!=NULL)
	{
		if(p->province==province1)
		{
			p->numOfIP=p->numOfIP+num;
			p->flag=1;
		}
		p=p->next;
	}
	head->numOfIP=head->numOfIP+num; 
	head->flag=1;
}

void AddSP(string province1,int num,PNode head)//ͳ���������ƻ��ߵ����
{
	//ofstream outFile;
	//outFile.open(("C:/Users/�񵰻���/Desktop/�������/���ٵڶ�����ҵ/InfectStatistic-main/221701336/src/out.txt"),ios::app);
	PNode p=head;
	while(p!=NULL)
	{
		if(p->province==province1)
		{
			p->numOfSP=p->numOfSP+num;
			p->flag=1;
		}
		p=p->next;
	}
	head->numOfSP=head->numOfSP+num; 
	head->flag=1;
}

void MoveIP(string province1,string province2,int num,PNode head)//ͳ�Ƹ�Ⱦ����������ʡ�����
{
	//ofstream outFile;
	//outFile.open(("C:/Users/�񵰻���/Desktop/�������/���ٵڶ�����ҵ/InfectStatistic-main/221701336/src/out.txt"),ios::app);
	PNode p=head;
	while(p!=NULL)
	{
		if(p->province==province1)
		{
			p->numOfIP=p->numOfIP-num;
			p->flag=1;
		}
		if(p->province==province2)
		{
			p->numOfIP=p->numOfIP+num;
			p->flag=1;
		}
		p=p->next;
	}
}

void MoveSP(string province1,string province2,int num,PNode head)//ͳ�����ƻ���������ʡ�����
{
	//ofstream outFile;
	//outFile.open(("C:/Users/�񵰻���/Desktop/�������/���ٵڶ�����ҵ/InfectStatistic-main/221701336/src/out.txt"),ios::app);
	PNode p=head;
	while(p!=NULL)
	{
		if(p->province==province1)
		{
			p->numOfSP=p->numOfSP-num;
			p->flag=1;
		}
		if(p->province==province2)
		{
			p->numOfSP=p->numOfSP+num;
			p->flag=1;
		}
		p=p->next;
	}
}

void Dead(string province1,int num,PNode head)//ͳ�Ƹ�Ⱦ�������������
{
	PNode p=head;
	while(p!=NULL)
	{
		if(p->province==province1)
		{
			p->numOfIP=p->numOfIP-num;
			p->numOfDead=p->numOfDead+num;
			p->flag=1;
		}
		p=p->next;
	}
	head->numOfIP=head->numOfIP-num;
	head->numOfDead=head->numOfDead+num; 
	head->flag=1;
}

void Cure(string province1,int num,PNode head)//ͳ�Ƹ�Ⱦ�������������
{
	PNode p=head;
	while(p!=NULL)
	{
		if(p->province==province1)
		{
			p->numOfIP=p->numOfIP-num;
			p->numOfCured=p->numOfCured+num;
			p->flag=1;
		}
		p=p->next;
	}
	head->numOfIP=head->numOfIP-num;
	head->numOfCured=head->numOfCured+num; 
	head->flag=1;
}

void Diagnosis(string province1,int num,PNode head)//ͳ�����ƻ���ȷ������
{
	PNode p=head;
	while(p!=NULL)
	{
		if(p->province==province1)
		{
			p->numOfSP=p->numOfSP-num;
			p->numOfIP=p->numOfIP+num;
			p->flag=1;
		}
		p=p->next;
	}
	head->numOfSP=head->numOfSP-num;
	head->numOfIP=head->numOfIP+num; 
	head->flag=1;
}

void Exclude(string province1,int num,PNode head)//ͳ�����ƻ��߱��ų������ 
{
	PNode p=head;
	while(p!=NULL)
	{
		if(p->province==province1)
		{
			p->numOfSP=p->numOfSP-num;
			p->flag=1;
		}
		p=p->next;
	}
	head->numOfSP=head->numOfSP-num;
	head->flag=1;
}

void operate(string op_province1,string op_province2,int op,int number,PNode head)//ͳ�ƺ��� 
{
	PNode p=head;
	string province1=op_province1;
	string province2=op_province2;
	int num=number;
	switch (op)
	{
		case 0:
			AddIP(province1,num,p); 
			break;
		case 1:
			AddSP(province1,num,p);
			break;
		case 2:
			MoveIP(province1,province2,num,p);
			break;
		case 3: 
			MoveSP(province1,province2,num,p);
			break;
		case 4:
			Dead(province1,num,p);
			break;
		case 5:
			Cure(province1,num,p);
			break;
		case 6:
			Diagnosis(province1,num,p);
			break;
		case 7:
			Exclude(province1,num,p);
			break;
		default :
			break;
	}		
}

static string Utf8ToGbk(const char *src_str)//���뷽ʽ��UTF-8 ת GBK
{
	int len = MultiByteToWideChar(CP_UTF8, 0, src_str, -1, NULL, 0);
	wchar_t* wszGBK = new wchar_t[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, src_str, -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char* szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	string strTemp(szGBK);
	if (wszGBK) delete[] wszGBK;
	if (szGBK) delete[] szGBK;
	return strTemp;
}

static string GBKToUTF8(const char* strGBK)//���뷽ʽ��GBK ת UTF-8 
{
	int len = MultiByteToWideChar(CP_ACP, 0, strGBK, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, strGBK, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	std::string strTemp = str;
	
	if (wstr) delete[] wstr;
	if (str) delete[] str;
	
	return strTemp;
}

void getOperation(char buffer[],PNode head)//��ȡÿ���ļ��еĲ��� 
{
    string op_province[2];//��Ų���ʡ�� 
    op_province[0]="0";
    op_province[1]="0";
    int op=10;//��Ų�����     
    int number=0;//�������    
    int count=0;//��¼������ʡ�ݸ��� 
   
    string buf_situation;
    string buf_province;
    
	string operation=buffer;
 	operation=Utf8ToGbk(buffer);
	
	//ofstream outFile;
	//outFile.open(("C:/Users/�񵰻���/Desktop/�������/���ٵڶ�����ҵ/InfectStatistic-main/221701336/src/out.txt"),ios::app); 
	op_province[0]=operation.substr(0,4);
	//outFile<<op_province[0]<<endl;
    string::size_type idx; 
	
	for(int i=0;i<8;i++)//��ȡָ�� 
    {

		
    	buf_situation=situation[i];
	    idx=operation.find(buf_situation);//��a�в���b.
	    if(idx != string::npos )
	    {	
	    	//ofstream outFile;
			//outFile.open(("C:/Users/�񵰻���/Desktop/�������/���ٵڶ�����ҵ/InfectStatistic-main/221701336/src/out.txt"),ios::app); 
			//outFile<<buf_situation<<endl;
			op=i;
			for(int j=0;j<32;j++)//��ȡ���� 
		    {
		    	buf_province=province[j];
			    idx=operation.find(buf_province);//��a�в���b.
			    if(idx != string::npos&&province[j]!=op_province[0] )
			    {	
			    	op_province[1]=buf_province;			    	
			    }
			}
		} 							    
	}								
	for (int i = 0; buffer[i] != '\0'; ++i) //��a����Ԫ�ز�Ϊ������ʱ.�����ַ���a.
    {
        if (buffer[i] >= '0'&& buffer[i] <= '9') //���������.
        {
            number*= 10;//�ȳ���10��֤�ȼ�⵽�����ִ��ڸ�λ������Ĵ��ڵ�λ
            number+= buffer[i] - '0'; //�����ַ���ascii-�ַ�'0'��ascii��͵��ڸ�����.         	
        }
    }
	//outFile<<"����:"<<number<<endl;
    string op_province1=op_province[0];
    string op_province2=op_province[1];
	operate(op_province1,op_province2,op,number,head);  
}

void readTxt(char fname[],PNode head)//���ж�ȡ�ļ������� 
{
	char buffer[500];
	string strLine;
    ifstream inFile(fname);
	//ofstream outFile("C:/Users/�񵰻���/Desktop/�������/���ٵڶ�����ҵ/InfectStatistic-main/221701336/src/out.txt"); 
	while(getline(inFile,strLine))
	{
	    strcpy(buffer,strLine.c_str());
	    if(buffer[0]=='/'||buffer[0]==' ')
		{
            break;
        }
        else
        {
        	//ofstream outFile;
			//outFile.open(("C:/Users/�񵰻���/Desktop/�������/���ٵڶ�����ҵ/InfectStatistic-main/221701336/src/out.txt"),ios::app); 
        	//outFile<<buffer<<endl;
        	getOperation(buffer,head);
		}	    		
	}
}

void readLog(string date,string path,PNode head)//��ȡ��ӦĿ¼�µ��ļ� 
{
	string s1="*.txt";
	string s2=".log.txt";
	string bufLogPath=path;
	string logPath=path;
	path=path+s1;
	date=date+s2;
	char dirPath[100];
	strcpy(dirPath,path.c_str());
	string latestLog;
	long Handle;
    struct _finddata_t FileInfo;    
    if((Handle=_findfirst(dirPath,&FileInfo))==-1L)
    {
        printf("û���ҵ���ӦĿ¼\n");
    }
    else
    {   	
        logPath=bufLogPath+FileInfo.name;
        char fname[100];
		strcpy(fname,logPath.c_str());
        readTxt(fname,head);          
        while(_findnext(Handle,&FileInfo)==0)//�ɹ�����0��ʧ�ܷ���-1
        {
            if(FileInfo.name<date||FileInfo.name==date)
            {
                logPath=bufLogPath+FileInfo.name;
            	char fname[100];
				strcpy(fname,logPath.c_str());
            	readTxt(fname,head);
            }
        }      
    }
}

void outNode(ostream &outFile,PNode p,string type[])//�����Ŀ�������Ӧ���� 
{
	outFile<<GBKToUTF8(p->province); 
	if(type[0]=="0")
	{
		outFile<<GBKToUTF8(" ��Ⱦ����")<<p->numOfIP<<GBKToUTF8("��");
		outFile<<GBKToUTF8(" ���ƻ���")<<p->numOfSP<<GBKToUTF8("��");
		outFile<<GBKToUTF8(" ����")<<p->numOfCured<<GBKToUTF8("��");
		outFile<<GBKToUTF8(" ����")<<p->numOfDead<<GBKToUTF8("��")<<endl; 
	}
	else
	{
		for(int i=0;i<4;i++)
		{
			if(type[i]=="ip")
			{
				outFile<<GBKToUTF8(" ��Ⱦ����")<<p->numOfIP <<GBKToUTF8("��");
			}
			else if(type[i]=="sp")
			{
				outFile<<GBKToUTF8(" ���ƻ���")<<p->numOfSP <<GBKToUTF8("��");
			}
			else if(type[i]=="cure")
			{
				outFile<<GBKToUTF8(" ���ƻ���")<<p->numOfCured<<GBKToUTF8("��");	
			}
			else if(type[i]=="dead")
			{
				outFile<<GBKToUTF8(" ���ƻ���")<<p->numOfDead<<GBKToUTF8("��"); 	
			}
			else
			{
				break;
			}
		}
		outFile<<endl;
	}
}

void output(string path,PNode p,PNode head,string type[],string province[])//������ı� 
{
	FILE *fp;
	int i=0;
	char fname[100];
	strcpy(fname,path.c_str());
	fp=fopen(fname,"a+");
	if(fp==NULL)
	{
		cout<<"��ʧ��"<<endl; 
	}
	fclose(fp);	
	ofstream outFile; 
	outFile.open(fname);
	if(outFile.is_open()!=1)
	{
		cout<<"��ʧ��!"<<endl; 
	}
	if(province[i]=="0")
	{
		outNode(outFile,head,type);
		p=p->next;
		while(p!=NULL)
		{
			if(p->flag==1)
			{
				outNode(outFile,p,type);
			}
			p=p->next;
	    }
	}
	else
	{
		while(province[i]!="0")
		{
			while(p!=NULL)
			{
				if(p->flag==1&&p->province==province[i])
				{
					outNode(outFile,p,type);
				}
				p=p->next;
		    }
		    p=head->next;
			i++;	
		}
	}
	outFile.close(); //�ر��ı��ļ�
}

int main(int argc,char *argv[]) 
{		
	string date="9999-12-31"; 
	string type[4]={"0","0","0","0"};
	string outPath;
	string log;
	string province[33];	
	for(int i=0;i<33;i++)
	{
		province[i]="0";
	}	
	date=getDate(argc,argv);		
	log=getLog(argc,argv);	
	outPath=getOutPath(argc,argv);	
	getType(argc,argv,type);	
	getProvince(argc,argv,province);
		
	PNode head=CreatList();	
	PNode p=head;	
	readLog(date,log,head);//��ȡĿ¼ 
	output(outPath,p,head,type,province);//��� 
	system("pause");
}



