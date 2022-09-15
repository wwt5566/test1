#include"workerManager.h"

//���캯��
WorkerManager::WorkerManager()
{
	//1.�ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		//��ʼ��
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//2.�ļ�����������Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��!" << endl;
		this->m_EmpNum = 0;
		this->m_FileIsEmpty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}
	//3.�ļ����ڲ������ݴ���
	int num = this->get_EmpNum();
	cout << "ְ������Ϊ�� " << num << endl;
	//��ʼ��ְ������
	this->m_EmpNum = num;
	//��ʼ��ְ������
	this->m_EmpArray = new Worker*[this->m_EmpNum];
	//���ļ��е����ݴ浽������
	this->init_Emp();

	////���Դ���
	//for (int i = 0; i < m_EmpNum; i++)
	//{
	//	cout << "ְ���ţ� " << this->m_EmpArray[i]->m_ID
	//		<< " ְ�������� " << this->m_EmpArray[i]->m_name
	//		<< " ���ű�ţ� " << this->m_EmpArray[i]->m_DeptID<< endl;
	//}
}
//��������
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
	}
}
//չʾ�˵�
void WorkerManager::show_menu()
{
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
	cout << "*************  0.�˳���������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}
//�˳�ϵͳ
void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

//����ְ��
void WorkerManager::Add_Emp()
{
	cout << "����������ְ���������� " << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0)
	{
		//����
		//���������¿ռ��С
		int newSize = this->m_EmpNum + addNum;//�¿ռ�����
		//�����¿ռ�
		Worker** newspace =new Worker* [newSize*sizeof(Worker)];
		//Worker** newspace = new Worker * [newSize];
		//��ԭ���ռ������ݿ������¿ռ���
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newspace[i] = this->m_EmpArray[i];
			}
		}
		//����������
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;//����ѡ��
			cout << "�������" << i + 1 << "����ְ����ţ� " << endl;
			cin >> id;
			if (this->IsExist(id) != -1)
			{
				cout << "�Ѵ��ڸñ��" << endl;
				system("pause");
				system("cls");
				return;
			}
			cout << "�������" << i + 1 << "����ְ�������� " << endl;
			cin >> name;
			cout << "��ѡ���ְ����λ�� " << endl;
			cout << "1.��ͨԱ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ܲ�" << endl;
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
			//��������ְ��ָ�뱣�浽������
			newspace[(this->m_EmpNum) + i] = worker;
		}
		//�ͷ�ԭ�еĿռ�
		delete[] this->m_EmpArray;
		//�����¿ռ�ָ��
		this->m_EmpArray = newspace;
		//����ְ������
		this->m_EmpNum = newSize;
		//����ְ����Ϊ�ձ�־
		this->m_FileIsEmpty = false;
		//��ʾ�ɹ�
		cout << "�ɹ�����" << addNum << "����ְ����" << endl;
		//�������ݵ��ļ���
		this->save();

	}
	else
	{
		cout << "��������" << endl;
	}
	system("pause");
	system("cls");
}
//�����ļ�
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	//������д��
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_ID << " "
			<< this->m_EmpArray[i]->m_name << " "
			<< this->m_EmpArray[i]->m_DeptID << endl;
	}
	ofs.close();
}
//ͳ������
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
		//��¼����
		num++;
	}
	ifs.close();

	return num;
}
//��ʼ��ְ��
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
	//�ر��ļ�
	ifs.close();

}
//��ʾְ��
void WorkerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//���ö�̬���ýӿ�
			this->m_EmpArray[i]->showInfo();
		}
	}

	system("pause");
	system("cls");
}
//����ְ������ж�ְ���Ƿ����,�����ڷ���ְ����������λ�ã������ڷ���-1
int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_ID == id)
		{
			//�ҵ�ְ��
			index = i;
			break;
		}
	}
	return index;
}
//ɾ��ְ��
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		//��ְ�����ɾ��
		cout << "��������Ҫɾ����ְ���ţ�" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);
		
		if (index != -1)//ְ�����ڲ�ɾ��
		{
			//����ǰ��
			for (int i = index; i < this->m_EmpNum; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//���������Ա����
			//����ͬ�����µ��ļ���
			this->save();
			cout << "ɾ���ɹ���" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}
	}
	if(this->m_EmpNum==0)this->m_FileIsEmpty = true;
	system("pause");
	system("cls");
}
//�޸�ְ��
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "�������޸�ְ���ı�ţ�" << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//���ҵ���ŵ�ְ��
			delete this->m_EmpArray[ret];

			int newID = 0;
			string newName = "";
			int dSelect = 0;

			cout << "�鵽�� " << id << "��ְ������������ְ���ţ� " << endl;
			cin >> newID;

			cout << "�������������� " << endl;
			cin >> newName;

			cout << "�������λ�� " << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
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
			//�������� ��������
			this->m_EmpArray[ret] = worker;

			cout << "�޸ĳɹ���" << endl;

			//���浽�ļ���
			this->save();
		}
		else
		{
			cout << "�޸�ʧ�ܣ����޴���" << endl;
		}
	}
	system("pause");
	system("cls");
}
//����ְ��
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ�� " << endl;
		cout << "1����ְ����Ų���" << endl;
		cout << "2������������" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			//��ְ����Ų���
			int id;
			cout<< "��������ҵ�ְ����ţ�" << endl;
			cin >> id;
			int ret = this->IsExist(id);
			if (ret != -1)
			{
				//�ҵ���ְ��
				cout << "���ҳɹ�����ְ������Ϣ���£�" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else if (select == 2)
		{
			//����������
			string name;
			cout << "��������ҵ�������" << endl;
			cin >> name;

			bool flag = false;  //���ҵ��ı�־
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_name == name)
				{
					cout << "���ҳɹ�,ְ�����Ϊ��"
						<< m_EmpArray[i]->m_ID
						<< " �ŵ���Ϣ���£�" << endl;

					flag = true;

					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				//���޴���
				cout << "����ʧ�ܣ����޴���" << endl;
			}
		}
		else
		{
			cout << "��������" << endl;
		}
	}
	system("pause");
	system("cls");
}
//����ְ��
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ�� " << endl;
		cout << "1����ְ���Ž�������" << endl;
		cout << "2����ְ���Ž��н���" << endl;

		int select = 0;
		cin >> select;
		//ѡ������
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i;
			for (int j = i; j < this->m_EmpNum; j++)
			{
				if (select == 1)//����
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
		cout << "����ɹ�,�������Ϊ��" << endl;
		this->save();
		this->Show_Emp();

	}
}
//����ļ�
void WorkerManager::Clean_File()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//��ģʽ ios::trunc �������ɾ���ļ������´���
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			//ɾ��������ÿ��ְ������
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];//�ͷ��ڴ�
					this->m_EmpArray[i] = NULL;//�ÿ�ָ��
				}
				//ɾ����������ָ��
				delete[] this->m_EmpArray;
				this->m_EmpArray = NULL;
				this->m_EmpNum = 0;
				this->m_FileIsEmpty = true;

			}
			cout << "��ճɹ���" << endl;
		}
	}
	system("pause");
	system("cls");
}