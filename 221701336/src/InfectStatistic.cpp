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

//cd C:\Users\�񵰻���\Desktop\�������\���ٵڶ�����ҵ\InfectStatistic-main\221701336\src
//InfectStatistic.exe list -date 2020-01-25 -type sp ip dead -out C:/Users/�񵰻���/Desktop/�������/���ٵڶ�����ҵ/InfectStatistic-main/221701336/src/out.txt 
//-log C:/Users/�񵰻���/Desktop/�������/���ٵڶ�����ҵ/InfectStatistic-main/221701336/log/ 
 
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

void getOperation(char buffer[])//��ȡÿ���ļ��еĲ��� 
{
    string op_province[2];//��Ų���ʡ�� 
    int op;//��Ų�����     
    int number=0;//�������
    
    int count=0;//��¼������ʡ�ݸ��� 
   
    string buf_situation;
    string buf_province;
    
	string operation=buffer; 	
    string::size_type idx; 
	
	for(int i=0;i<8;i++)//��ȡָ�� 
    {
    	buf_situation=situation[i];
	    idx=operation.find(buf_situation);//��a�в���b.
	    if(idx != string::npos )
	    {	
	    	cout<<buf_situation<<endl;
			op=i;			
			for(int j=0;j<32;j++)//��ȡ���� 
		    {
		    	buf_province=province[j];
			    idx=operation.find(buf_province);//��a�в���b.
			    if(idx != string::npos )
			    {	
			    	op_province[count]=buf_province;
			    	cout<<"����"<<count+1<<"Ϊ"<<op_province[count]<<endl;
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
	   
}

void AddIP()
{
	
}

void operation(string op_province[],int op,int number,PNode p,PNode head)
{
	switch (op)
	{
		case 1:
			//������Ⱦ���� 
			break;
		case 2:
			//�������ƺ���
			break;
		case 3:
			//��Ⱦ��������
			break;
		case 4: 
			//���ƻ�������
			break;
		case 5:
			//����
			break;
		case 6:
			//����
			break;
		case 7:
			//���ƻ���ȷ���Ⱦ
			break;
		case 8:
			//�ų�����
			break;
	}		
}

void readTxt(char fname[])//���ж�ȡ�ļ������� 
{
	char buffer[256];
	string strLine;
	string str;
    ifstream outFile;
    outFile.open(fname,ios::in);
    while(getline(outFile,strLine))
    {
    	strcpy(buffer,strLine.c_str());
		if(buffer[0]=='/'||buffer[0]==' ')
		{
            continue;
        }
        getOperation(buffer);		
    }
}

void readLog(string date,string path)//��ȡ��ӦĿ¼�µ��ļ� 
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
            readTxt(fname);          
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
			if(p->flag==0)
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
				if(p->flag==0&&p->province==province[i])
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
	
	getProvince(argc,argv,province);
	
	PNode head=CreatList();	
	PNode p=head;	
	readLog(date,log);//��ȡĿ¼ 
	
	//Node pp={"����",6,3,15,20,NULL};
	output(outPath,p,head,type,province);//��� 
	system("pause");
}



