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

//cd C:\Users\鸟蛋花机\Desktop\软件工程\寒假第二次作业\InfectStatistic-main\221701336\src
//InfectStatistic.exe list -date 2020-01-22 -log D:/log/ -out C:/Users/鸟蛋花机/Desktop/软件工程/寒假第二次作业/InfectStatistic-main/221701336/src/out.txt 

using namespace std;

string province[32]={"安徽","北京","重庆","福建","甘肃","广东","广西","贵州","海南","河北","河南","黑龙江",
"湖北","湖南","吉林","江苏","江西","辽宁","内蒙古","宁夏","青海","山东","山西"
,"陕西","上海","四川","天津","西藏","新疆","云南","浙江","全国"}; 

typedef struct ListNode
{
    char province[8];//省份 
	int numOfDead;//number of dead patients 死亡患者数量 
	int numOfIP;//number of infection patients 感染患者数量 
	int numOfSP;//number of suspected patients 疑似患者数量 
	int numOfCured;//number of cured patients  已痊愈患者数量
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
		cout<<"空间分配失败"<<endl;
	}
	PHead->numOfCured=0;
	PHead->numOfDead=0;
	PHead->numOfIP=0;
	PHead->numOfSP=0;
	strcpy(PHead->province,province[31].c_str());
		 
	PNode pNew=(PNode)malloc(sizeof(Node));
	if(pNew==NULL)
	{
		cout<<"分配新节点失败"<<endl;
	}
	pNew->numOfCured=0;
	pNew->numOfDead=0;
	pNew->numOfIP=0;
	pNew->numOfSP=0;
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
			cout<<"分配新节点失败"<<endl;
		}
		p->numOfCured=0;
		p->numOfDead=0;
		p->numOfIP=0;
		p->numOfSP=0;
		strcpy(p->province,province[i].c_str());
		PTail->next=p; 
		p->next=NULL;
		PTail=p;
	}
	return PHead;
}

string getDate(int argc, char *argv[])//获得命令行参数中的日期 
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

string getLog(int argc, char *argv[])//获得命令行参数中的目录 
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
        printf("没有找到相应目录\n");
    }
    else
    {   	
    	if(FileInfo.name<=date)
        {
            printf("%s\n", FileInfo.name);
        }
        while(_findnext(Handle,&FileInfo)==0)//成功返回0，失败返回-1
        {
            if(FileInfo.name<=date)
            {
                printf("%s\n", FileInfo.name);
                //读取函数 
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



void output(string path,Node p)
{
	FILE *fp;
	char fname[100];
	strcpy(fname,path.c_str());
	fp=fopen(fname,"a+");
	if(fp==NULL)
	{
		cout<<"打开失败"<<endl; 
	}
	fclose(fp);
	ofstream outFile; 
	outFile.open(fname);
	if(outFile.is_open()!=1)
	{
		cout<<"打开失败!"<<endl; 
	} 
	outFile<<p.province; 
	outFile<<" 感染患者"<<p.numOfIP <<"人";
	outFile<<" 疑似患者"<<p.numOfSP <<"人";
	outFile<<" 治愈"<<p.numOfCured<<"人";
	outFile<<" 死亡"<<p.numOfDead<<"人"<<endl; 
	outFile.close(); //关闭文本文件
}

int main(int argc,char *argv[])
{
		
	string date="9999-12-31";//所要求的的日期 
	string type[4]={"0","0","0","0"};
	string outPath;
	string log;
	string province[35];
	
	for(int i=0;i<35;i++)
	{
		province[0]="0";
	}
	
	date=getDate(argc,argv);	
	cout<<"要求日期:"<<date<<endl; 	
	
	log=getLog(argc,argv);
	cout<<"要求打开目录:"<<log<<endl; 
	
	outPath=getOutPath(argc,argv);
	cout<<"要求输出地址:"<<outPath<<endl;
	
	getType(argc,argv,type);	
	
	getProvince(argc,argv,province);
	
	PNode head=CreatList();	
	PNode p=head;
	while(p!=NULL)
	{
		cout<<p->province<<endl;
		p=p->next;
	}
	
	//readDir(date,log);//读取目录 
	
	Node pp={"福建",6,3,15,20,NULL};
	output(outPath,pp);//输出 
	system("pause");
}



