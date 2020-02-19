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
//InfectStatistic.exe list -date 2020-01-23 -type sp ip dead -log C:/Users/�񵰻���/Desktop/�������/���ٵڶ�����ҵ/InfectStatistic-main/221701336/log/ -out C:/Users/�񵰻���/Desktop/�������/���ٵڶ�����ҵ/InfectStatistic-main/221701336/src/out.txt 
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
	int flag;
	struct ListNode *next; 	
}Node,*PNode;

void input(string path,Node p);
void output(string path,Node p);
void readLog(string date,string path);

PNode CreatList(void)
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
	cout << "argc: " << argc << endl;
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


void AddIP(string province1,int num,PNode head)
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

void AddSP(string province1,int num,PNode head)
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

void MoveIP(string province1,string province2,int num,PNode head)
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

void operate(string op_province1,string op_province2,int op,int number,PNode head)
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
			//���ƻ�������
			break;
		case 4:
			//����
			break;
		case 5:
			//����
			break;
		case 6:
			//���ƻ���ȷ���Ⱦ
			break;
		case 7:
			//�ų�����
			break;
		default :
			break;
	}		
}


string Utf8ToGbk(const char *src_str)
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
			    if(idx != string::npos )
			    {	
			    	op_province[count]=buf_province;
			    	count++;			    	
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
	string s="*.txt";
	string logPath=path;
	path=path+s;
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
    	if(FileInfo.name<=date)
        {
        	logPath=logPath+FileInfo.name;
        	char fname[100];
			strcpy(fname,logPath.c_str());
            cout<<"Ҫ�򿪵��ļ���ַ��:"<<fname<<endl;
            readTxt(fname,head);          
        }
        while(_findnext(Handle,&FileInfo)==0)//�ɹ�����0��ʧ�ܷ���-1
        {
            if(FileInfo.name<=date)
            {
                logPath=logPath+FileInfo.name;
            	//cout<<logPath<<endl;
            }
            latestLog=FileInfo.name;
        } 
		if(latestLog<date)
		{
			cout<<"���ڳ�����Χ"<<endl;	
		}     
    }
}


/*void input(string path,string date,pNode p)
{
	
	
} */

void outNode(ostream &outFile,PNode p,string type[])
{
	outFile<<p->province; 
	if(type[0]=="0")
	{
		outFile<<" ��Ⱦ����"<<p->numOfIP <<"��";
		outFile<<" ���ƻ���"<<p->numOfSP <<"��";
		outFile<<" ����"<<p->numOfCured<<"��";
		outFile<<" ����"<<p->numOfDead<<"��"<<endl; 
	}
	else
	{
		for(int i=0;i<4;i++)
		{
			if(type[i]=="ip")
			{
				outFile<<" ��Ⱦ����"<<p->numOfIP <<"��";
			}
			else if(type[i]=="sp")
			{
				outFile<<" ���ƻ���"<<p->numOfSP <<"��";
			}
			else if(type[i]=="cure")
			{
				outFile<<" ����"<<p->numOfCured<<"��";	
			}
			else if(type[i]=="dead")
			{
				outFile<<" ����"<<p->numOfDead<<"��"<<endl; 	
			}
			else
			{
				break;
			}
		}
	}
}

void output(string path,PNode p,PNode head,string type[],string province[])
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
	string date="9999-12-31";//��Ҫ��ĵ����� 
	string type[4]={"0","0","0","0"};
	string outPath;
	string log;
	string province[33];
	
	for(int i=0;i<33;i++)
	{
		province[i]="0";
	}
	
	date=getDate(argc,argv);	
	cout<<"Ҫ������:"<<date<<endl; 	
	
	log=getLog(argc,argv);
	cout<<"Ҫ���Ŀ¼:"<<log<<endl; 
	
	outPath=getOutPath(argc,argv);
	cout<<"Ҫ�������ַ:"<<outPath<<endl;
	
	getType(argc,argv,type);
	cout<<"Ҫ���������";	
	for(int i=0;i<4;i++)
	{
		cout<<type[i]<<endl;
	}
	getProvince(argc,argv,province);
	cout<<"Ҫ�����ʡ��";
	for(int i=0;i<33;i++)
	{
		if(province[i]!="0") 
		{
			cout<<province[i]<<endl;
		}	
	}
	
	PNode head=CreatList();	
	PNode p=head;	
	readLog(date,log,head);//��ȡĿ¼ 
	
	//Node pp={"����",6,3,15,20,NULL};
	output(outPath,p,head,type,province);//��� 
	system("pause");
}



