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

int main()
{
	string date="2020-01-25"; //��Ҫ��ĵ����� 
	char inPath[100]="F:/�½��ļ���/InfectStatistic-main/example/log/";//�����ַ 
	string dirPath;//Ŀ¼��ַ 
	dirPath=inPath; 
	readDir(date,dirPath);
	
	
	char outPath[100]="C:/Users/�񵰻���/Desktop/�������/���ٵڶ�����ҵ/out.txt";//�����ַ 
	string path;
	path=outPath;
	pNode p={"����",6,3,15,20};
	//output(path,p);
	system("pause");
}



