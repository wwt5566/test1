#pragma once
#include<iostream>
using namespace std;
#include"worker.h"
#include"boss.h"
#include"employee.h"
#include"manager.h"
#include<fstream>
#define FILENAME "empFile.text"

class WorkerManager
{
public:
	WorkerManager();
	
	void show_menu();
	//�˳�ϵͳ
	void ExitSystem();
	//���ְ��
	void Add_Emp();
	//�����ļ�
	void save();
	//ͳ������
	int get_EmpNum();
	//��ʼ��ְ��
	void init_Emp();
	//��ʾְ��
	void Show_Emp();
	//ɾ��ְ��
	void Del_Emp();
	//����ְ������ж�ְ���Ƿ����,�����ڷ���ְ����������λ�ã������ڷ���-1
	int IsExist(int id);
	//�޸�ְ��
	void Mod_Emp();
	//����ְ��
	void Find_Emp();
	//����ְ��
	void Sort_Emp();
	//����ļ�
	void Clean_File();

	~WorkerManager();

	//�ж��ļ��Ƿ�Ϊ�� ��־
	bool m_FileIsEmpty;
	//��¼�ļ�������
	int m_EmpNum;
	//Ա������ָ��
	Worker** m_EmpArray;

};


