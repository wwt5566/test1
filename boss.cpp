#include"boss.h"



Boss::Boss(int id, string name, int did)
{
	this->m_ID = id;
	this->m_name = name;
	this->m_DeptID = did;
}
//显示个人信息
void Boss::showInfo()
{
	cout << "职工编号: " << this->m_ID
		<< "\t职工姓名: " << this->m_name
		<< "\t岗位: " << this->getDeptName()
		<< "\t岗位职责：管理公司所有事务" << endl;
}
//获取岗位名称
string Boss::getDeptName()
{
	return "总裁";
}