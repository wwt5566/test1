#pragma once
#include<iostream>
using namespace std;

class Worker
{
public:
	//��ʾ������Ϣ
	virtual void showInfo() = 0;
	//��ȡ��λ����
	virtual string getDeptName() = 0;

	int m_ID;//ְ�����
	string m_name;//ְ������
	int m_DeptID;//ְ�����ڲ��ű��

};

