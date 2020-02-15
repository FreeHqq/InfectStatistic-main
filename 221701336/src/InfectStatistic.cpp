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
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

struct pNode
{
    string province;//ʡ�� 
	int numOfDead;//number of dead patients ������������ 
	int numOfIP;//number of infection patients ��Ⱦ�������� 
	int numOfSP;//number of suspected patients ���ƻ������� 
	int numOfCured;//number of cured patients  ��Ȭ���������� 
	struct pNode *next;
};

void input(string path,pNode p);
void output(string path,pNode p);
void readDir(string date,string path);

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


void output(string path,pNode p)
{
	FILE *fp;
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
	outFile<<p.province; 
	outFile<<" ��Ⱦ����"<<p.numOfIP <<"��";
	outFile<<" ���ƻ���"<<p.numOfSP <<"��";
	outFile<<" ����"<<p.numOfCured<<"��";
	outFile<<" ����"<<p.numOfDead<<"��"<<endl; 
	outFile.close(); //�ر��ı��ļ�
}

int main(int argc,char *argv[])
{
		
	string date="9999-12-31";//��Ҫ��ĵ����� 
	string type[4]={"0","0","0","0"};
	string outPath;
	string log;
	string province[35];
	
	for(int i=0;i<35;i++)
	{
		province[0]="0";
	}
	
	date=getDate(argc,argv);	
	cout<<"Ҫ������:"<<date<<endl; 	
	
	log=getLog(argc,argv);
	cout<<"Ҫ���Ŀ¼:"<<log<<endl; 
	
	outPath=getOutPath(argc,argv);
	cout<<"Ҫ�������ַ:"<<outPath<<endl;
	
	getType(argc,argv,type);	
	
	getProvince(argc,argv,province);
	
	
	//readDir(date,log);//��ȡĿ¼ 
	

	pNode p={"����",6,3,15,20};
	//output(outPath,p);//��� 
	system("pause");
}



