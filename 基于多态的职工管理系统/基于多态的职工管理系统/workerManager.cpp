

#include "workerManager.h"
#include "worker.h"
#include "boss.h"
#include "employee.h"
#include "manager.h"



WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//文件不存在情况
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl; //测试输出
		this->m_EmpNum = 0;  //初始化人数
		this->m_FileIsEmpty = true; //初始化文件为空标志
		this->m_EmpArray = NULL; //初始化数组
		ifs.close(); //关闭文件
		return;
	}

	//文件存在，并且没有记录
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

	//文件存在，并且有记录
	int num = this->get_EmpNum();
	//cout << "职工个数为：" << num << endl;  //测试代码
	this->m_EmpNum = num;  //更新成员属性

	//开辟空间 把信息存储到堆区
	this->m_EmpArray = new Worker *[num];
	init_Emp();

	//测试代码
	//for (int i = 0; i < m_EmpNum; i++)
	//{
	//	cout << "职工号： " << this->m_EmpArray[i]->m_Id
	//		<< " 职工姓名： " << this->m_EmpArray[i]->m_Name
	//		<< " 部门编号： " << this->m_EmpArray[i]->m_DeptId << endl;
	//}
}




WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
	}
}


void WorkerManager::Show_Menu()
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


void WorkerManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}


//增加职工
void WorkerManager::Add_Emp()
{
	cout << "请输入增加职工数量： " << endl;

	int addNum = 0;
	cin >> addNum;

	if (addNum > 0)
	{
		//计算新空间大小
		int newSize = this->m_EmpNum + addNum;

		//开辟新空间
		Worker** newSpace = new Worker * [newSize];

		//将原空间下内容存放到新空间下
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//输入新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;

			cout << "请输入第 " << i + 1 << " 个新职工编号：" << endl;
			cin >> id;


			cout << "请输入第 " << i + 1 << " 个新职工姓名：" << endl;
			cin >> name;


			cout << "请选择该职工的岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;


			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1: //普通员工
				worker = new Employee(id, name, 1);
				break;
			case 2: //经理
				worker = new Manager(id, name, 2);
				break;
			case 3:  //老板
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}

			newSpace[this->m_EmpNum + i] = worker;
		}

		//释放原有空间C++告诉我们在回收用 new 分配的单个对象的内存空间的时候用 delete，
		//回收用 new[] 分配的一组对象的内存空间的时候用 delete[]。
		delete[] this->m_EmpArray;

		//指向新的空间
		this->m_EmpArray = newSpace;

		//更新新的个数
		this->m_EmpNum = newSize;

		//更新职工不为空标志
		this->m_FileIsEmpty = false;
		//提示信息
		cout << "成功添加" << addNum << "名新职工！" << endl;

		//保存带文件中
		this->save();
	}
	else
	{
		cout << "输入有误" << endl;
	}

	system("pause");
	system("cls");//清屏

}


//统计人数
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//记录人数
		num++;
	}
	ifs.close();

	return num;
}


//保存文件
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out); // 用输出的方式打开文件  -- 写文件

	//将每个人数据写入到文件中
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}

	//关闭文件
	ofs.close();

}

//初始化员工
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	int index = 0;

	while (ifs>>id && ifs>>name && ifs>>dId)
	{
		Worker* worker = NULL;

		if (dId == 1)
		{
			worker = new Employee(id,name,dId);
		}
		else if (dId == 2)
		{
			worker = new Manager(id, name, dId);
		}
		else if (dId == 3)
		{
			worker = new Boss(id,name,dId);
		}

		this->m_EmpArray[index] = worker;
		index++;
	}
}


//显示职工
void WorkerManager::Show_Emp()
{

	if (this->m_FileIsEmpty)
	{
		cout << "文件为空!" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
		
	}

	system("pause");
	system("cls");


}


//按照职工编号判断职工是否存在, 若存在返回职工在数组中位置，不存在返回 - 1
int WorkerManager::IsExist(int id)
{
	int index = -1;

	for (int i = 0;i < this->m_EmpNum;i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
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
		cout << "文件不存在" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		cout << "请输入你要删除的员工的ID：" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);

		if (index != -1)
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i+1];
			}
			this->m_EmpNum--;

			this->save();
			cout << "删除成功！" << endl;
		}
		else
		{
			cout << "删除失败，未找到该职工" << endl;
		}
	}

	system("pause");
	system("cls");
}


//修改职工
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		cout << "请输入你要修改的员工的ID：" << endl;
		int id = 0;
		cin >> id;
		int index = this->IsExist(id);

		if (index != -1)
		{
			int newId;
			string newName;
			int dSelect;

			//有数组索引了
			cout << "请输入你要修改的员工的新ID" << endl;
			cin >> newId;


			cout << "请输入你要修改的员工新职工姓名：" << endl;
			cin >> newName;


			cout << "请选择该职工的岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}

			this->m_EmpArray[index] = worker;
			cout << "修改成功！" << endl;
			//保存到文件中
			this->save();
		}
		else
		{
			cout << "修改失败，未找到该职工" << endl;
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
		system("pause");
		system("cls");
		return;
	}
	else
	{
		cout << "请输入查找的方式：" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按姓名查找" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			cout << "请输入你要查找的员工的ID：" << endl;
			int id = 0;
			cin >> id;
			int index = this->IsExist(id);

			if (index != -1)
			{
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_EmpArray[index]->showInfo();
			}
			else
			{
				cout << "查找失败，查无此人" << endl;
			}

		}
		else if (select == 2)
		{
			cout << "请输入你要查找的员工的姓名：" << endl;
			string name;
			cin >> name;

			bool flag = false;  //查找到的标志
			for (int i = 0; i < this->m_EmpNum;i++)
			{
				if (name == m_EmpArray[i]->m_Name)
				{
					cout << "查找成功！该职工信息如下：" << endl;
					this->m_EmpArray[i]->showInfo();

					flag = true;
					break;
				}
			}

			if (flag == false)
			{
				cout << "查找失败，查无此人" << endl;
			}

		}
		else
		{
			cout << "输入有误！" << endl;
		}
	}
	system("pause");
	system("cls");
}

//template<class T>
//void SwapArr(T &a,T&b)
//{
//	T temp=a;
//	a = b;
//	b = temp;
//
//}
//
////选择排序,模板函数 ud 表示升序还是降序
//template<class T>
//void Selectsort(T arr[],int len,int ud)
//{
//	for (int i = 0; i < len; i++)
//	{
//		int minOrMax = i;
//
//		for (int j = i+1; j < len; j++)
//		{
//			if (ud == 1)//升序
//			{
//				if (arr[minOrMax] > arr[j])
//				{
//					minOrMax = j;
//				}
//			}
//			else if (ud == 2)//降序
//			{
//				if (arr[minOrMax] < arr[j])
//				{
//					minOrMax = j;
//				}
//			}
//		}
//		if (i != minOrMax)
//		{
//			//交换
//			SwapArr(arr[minOrMax],arr[i]);
//		}
//	}
//	
//}

//排序职工
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		cout << "请选择排序方式： " << endl;
		cout << "1、按职工号进行升序" << endl;
		cout << "2、按职工号进行降序" << endl;

		int select = 0;
		cin >> select;

		if (select != 1 && select != 2)
		{
			cout << "输入有误！" << endl;
			system("pause");
			system("cls");
			return; //输入有误就直接返回了

		}
		
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i;

			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1) //升序
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else if (select == 2)//降序
				{
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}
			if (minOrMax != i)
			{
				Worker* temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minOrMax];
				m_EmpArray[minOrMax] = temp;
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
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
				}
			}
			this->m_EmpNum = 0;
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功！" << endl;
	}
	else if (select == 2)
	{
		return;
	}
	else
	{
		cout << "输入有误！" << endl;
	}
	system("pause");
	system("cls");
}