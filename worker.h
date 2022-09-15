#pragma once
#include<iostream>
using namespace std;

class Worker
{
public:
	//显示个人信息
	virtual void showInfo() = 0;
	//获取岗位名称
	virtual string getDeptName() = 0;

	int m_ID;//职工编号
	string m_name;//职工姓名
	int m_DeptID;//职工所在部门编号

};

