/**
 * InfectStatistic
 * TODO
 *
 * @author 221701336
 * @version 1.0
 * @since 2020.02.13
 */ 
#include<algorithm>
#include<iostream>
#include<fstream>
#include<cstring>
#include<io.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>

//cd C:\Users\�񵰻���\Desktop\�������\���ٵڶ�����ҵ\InfectStatistic-main\221701336\src
//InfectStatistic.exe list -date 2020-01-22 -type sp ip dead -out C:/Users/�񵰻���/Desktop/�������/���ٵڶ�����ҵ/InfectStatistic-main/221701336/src/out.txt 

using namespace std;

string province[32]={"����","����","����","����","����","�㶫","����","����","����","�ӱ�","����","������",
"����","����","����","����","����","����","���ɹ�","����","�ຣ","ɽ��","ɽ��"
,"����","�Ϻ�","�Ĵ�","���","����","�½�","����","�㽭","ȫ��"}; 

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
void readDir(string date,string path);

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

string getOutPath(int argc, char *argv[])
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

void getType(int argc, char *argv[],string type[])
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

void getProvince(int argc,char *argv[],string province[])
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

void readDir(string date,string path)
{
	string s="*.txt";
	path=path+s;
	char dirPath[100];
	strcpy(dirPath,path.c_str());
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
            printf("%s\n", FileInfo.name);
        }
        while(_findnext(Handle,&FileInfo)==0)//�ɹ�����0��ʧ�ܷ���-1
        {
            if(FileInfo.name<=date)
            {
                printf("%s\n", FileInfo.name);
                //��ȡ���� 
            }
            else
            {
				_findclose(Handle);
			} 
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
	//readDir(date,log);//��ȡĿ¼ 
	
	//Node pp={"����",6,3,15,20,NULL};
	output(outPath,p,head,type,province);//��� 
	system("pause");
}



