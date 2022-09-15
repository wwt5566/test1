#include"workerManager.h"

//构造函数
WorkerManager::WorkerManager()
{
	//1.文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		//初始化
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//2.文件存在且数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空!" << endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}
	//3.文件存在并且数据存在
	int num = this->get_EmpNum();
	cout << "职工人数为： " << num << endl;
	//初始化职工人数
	this->m_EmpNum = num;
	//初始化职工数组
	this->m_EmpArray = new Worker*[this->m_EmpNum];
	//将文件中的数据存到数组中
	this->init_Emp();

	////测试代码
	//for (int i = 0; i < m_EmpNum; i++)
	//{
	//	cout << "职工号： " << this->m_EmpArray[i]->m_ID
	//		<< " 职工姓名： " << this->m_EmpArray[i]->m_name
	//		<< " 部门编号： " << this->m_EmpArray[i]->m_DeptID<< endl;
	//}
}
//析构函数
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
	}
}
//展示菜单
void WorkerManager::show_menu()
{
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}
//退出系统
void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

//添加职工
void WorkerManager::Add_Emp()
{
	cout << "请输入添加职工的数量： " << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		//添加
		//计算添加新空间大小
		int newSize = this->m_EmpNum + addNum;//新空间人数
		//开辟新空间
		Worker** newspace =new Worker* [newSize*sizeof(Worker)];
		//Worker** newspace = new Worker * [newSize];
		//将原来空间下数据拷贝到新空间下
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newspace[i] = this->m_EmpArray[i];
			}
		}
		//添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;//部门选择
			cout << "请输入第" << i + 1 << "个新职工编号： " << endl;
			cin >> id;
			if (this->IsExist(id) != -1)
			{
				cout << "已存在该编号" << endl;
				system("pause");
				system("cls");
				return;
			}
			cout << "请输入第" << i + 1 << "个新职工姓名： " << endl;
			cin >> name;
			cout << "请选择该职工岗位： " << endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.总裁" << endl;
			cin >> dSelect;

			Worker * worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			//将创建的职工指针保存到数组中
			newspace[(this->m_EmpNum) + i] = worker;
		}
		//释放原有的空间
		delete[] this->m_EmpArray;
		//更改新空间指向
		this->m_EmpArray = newspace;
		//跟新职工人数
		this->m_EmpNum = newSize;
		//更新职工不为空标志
		this->m_FileIsEmpty = false;
		//提示成功
		cout << "成功添加" << addNum << "名新职工！" << endl;
		//保持数据到文件中
		this->save();

	}
	else
	{
		cout << "输入有误" << endl;
	}
	system("pause");
	system("cls");
}
//添加文件
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	//将数据写入
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_ID << " "
			<< this->m_EmpArray[i]->m_name << " "
			<< this->m_EmpArray[i]->m_DeptID << endl;
	}
	ofs.close();
}
//统计人数
int  WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int did;

	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> did)
	{
		//记录人数
		num++;
	}
	ifs.close();

	return num;
}
//初始化职工
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int did;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		Worker* worker = NULL;
		if (did == 1)
		{
			worker = new Employee(id, name, did);
		}
		else if (did == 2)
		{
			worker= new Manager(id, name, did);
		}
		else
		{
			worker = new Boss(id, name, did);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	//关闭文件
	ifs.close();

}
//显示职工
void WorkerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//利用多态调用接口
			this->m_EmpArray[i]->showInfo();
		}
	}

	system("pause");
	system("cls");
}
//按照职工编号判断职工是否存在,若存在返回职工在数组中位置，不存在返回-1
int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_ID == id)
		{
			//找到职工
			index = i;
			break;
		}
	}
	return index;
}
//删除职工
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		//按职工编号删除
		cout << "请输入想要删除的职工号：" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);
		
		if (index != -1)//职工存在并删除
		{
			//数据前移
			for (int i = index; i < this->m_EmpNum; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//更新数组成员个数
			//数据同步跟新到文件中
			this->save();
			cout << "删除成功！" << endl;
		}
		else
		{
			cout << "删除失败，未找到该职工" << endl;
		}
	}
	if(this->m_EmpNum==0)this->m_FileIsEmpty = true;
	system("pause");
	system("cls");
}
//修改职工
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入修改职工的编号：" << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//查找到编号的职工
			delete this->m_EmpArray[ret];

			int newID = 0;
			string newName = "";
			int dSelect = 0;

			cout << "查到： " << id << "号职工，请输入新职工号： " << endl;
			cin >> newID;

			cout << "请输入新姓名： " << endl;
			cin >> newName;

			cout << "请输入岗位： " << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newID, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newID, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newID, newName, dSelect);
				break;
			default:
				break;
			}
			//更改数据 到数组中
			this->m_EmpArray[ret] = worker;

			cout << "修改成功！" << endl;

			//保存到文件中
			this->save();
		}
		else
		{
			cout << "修改失败，查无此人" << endl;
		}
	}
	system("pause");
	system("cls");
}
//查找职工
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入查找的方式： " << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按姓名查找" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			//按职工编号查找
			int id;
			cout<< "请输入查找的职工编号：" << endl;
			cin >> id;
			int ret = this->IsExist(id);
			if (ret != -1)
			{
				//找到该职工
				cout << "查找成功，该职工的信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查找失败，查无此人" << endl;
			}
		}
		else if (select == 2)
		{
			//按姓名查找
			string name;
			cout << "请输入查找的姓名：" << endl;
			cin >> name;

			bool flag = false;  //查找到的标志
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_name == name)
				{
					cout << "查找成功,职工编号为："
						<< m_EmpArray[i]->m_ID
						<< " 号的信息如下：" << endl;

					flag = true;

					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				//查无此人
				cout << "查找失败，查无此人" << endl;
			}
		}
		else
		{
			cout << "输入有误" << endl;
		}
	}
	system("pause");
	system("cls");
}
//排序职工
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式： " << endl;
		cout << "1、按职工号进行升序" << endl;
		cout << "2、按职工号进行降序" << endl;

		int select = 0;
		cin >> select;
		//选择排序
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i;
			for (int j = i; j < this->m_EmpNum; j++)
			{
				if (select == 1)//升序
				{
					if (this->m_EmpArray[j]->m_ID < this->m_EmpArray[minOrMax]->m_ID)
					{
						minOrMax = j;
					}
				}
				else
				{
					if (this->m_EmpArray[j]->m_ID > this->m_EmpArray[minOrMax]->m_ID)
					{
						minOrMax = j;
					}
				}

			}
			if (i != minOrMax)
			{
				Worker* temp = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = this->m_EmpArray[i];
				this->m_EmpArray[i] = temp;
			}
		}
		cout << "排序成功,排序后结果为：" << endl;
		this->save();
		this->Show_Emp();

	}
}
//清空文件
void WorkerManager::Clean_File()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//打开模式 ios::trunc 如果存在删除文件并重新创建
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			//删除堆区的每个职工对象
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];//释放内存
					this->m_EmpArray[i] = NULL;//置空指针
				}
				//删除堆区数组指针
				delete[] this->m_EmpArray;
				this->m_EmpArray = NULL;
				this->m_EmpNum = 0;
				this->m_FileIsEmpty = true;

			}
			cout << "清空成功！" << endl;
		}
	}
	system("pause");
	system("cls");
}