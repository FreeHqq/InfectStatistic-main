/**
 * InfectStatistic
 * TODO
 *
 * @author 221701336
 * @version 1.0
 * @since 2020.02.13
 */ 
#include <algorithm>
#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

struct pNode
{
    string province;//ʡ�� 
	int numOfDead;//number of dead patients ������������ 
	int numOfIP;//number of infection patients ��Ⱦ�������� 
	int numOfSP;//number of suspected patients ���ƻ������� 
	int numOfCured;//number of cured patients  ��Ȭ���������� 
	//struct pNode *next;
};

void output(string path,pNode p);

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
	string date; //��Ҫ��ĵ����� 
	string inPath;//Ŀ¼��ַ 
	char outPath[100]="C:/Users/�񵰻���/Desktop/�������/���ٵڶ�����ҵ/out.txt";//�����ַ 
	string path;
	path=outPath;
	pNode p={"����",6,3,15,20};
	output(path,p);
	system("pause");
}



