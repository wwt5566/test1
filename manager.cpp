#include"manager.h"

Manager::Manager(int id, string name, int did)
{
	this->m_ID = id;
	this->m_name = name;
	this->m_DeptID = did;
}
//显示个人信息
void Manager::showInfo()
{
	cout << "职工编号: " << this->m_ID
		<< "\t职工姓名: " << this->m_name
		<< "\t岗位: " << this->getDeptName()
		<< "\t岗位职责：完成老板交给的任务，并下发任务给员工" << endl;
}
//获取岗位名称
string Manager::getDeptName()
{
	return "经理";
}