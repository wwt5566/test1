#pragma once
#include"worker.h"

class Employee : public Worker
{
public:
	Employee(int id , string name , int did);
	//显示个人信息
	virtual void showInfo();
	//获取岗位名称
	virtual string getDeptName();

};