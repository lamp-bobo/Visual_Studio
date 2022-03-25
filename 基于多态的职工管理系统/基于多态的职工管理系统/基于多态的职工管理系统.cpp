﻿// 基于多态的职工管理系统.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include "workerManager.h"

using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"



int main()
{

	WorkerManager wm;
	int choice = 0;


	while (true)
	{
		wm.Show_Menu();
		cout << "请输入您的选择:" << endl;
		cin >> choice;

		switch (choice)
		{
	
		case 0://退出系统
			wm.exitSystem();
			break;
		case 1://添加职工
			wm.Add_Emp();
			break;
		case 2://显示职工
			wm.Show_Emp();
			break;
		case 3://删除职工
			wm.Del_Emp();
			break;
		case 4://修改职工
			wm.Mod_Emp();
			break;
		case 5: //查找职工
			wm.Find_Emp();
			break;
		case 6://排序职工
			wm.Sort_Emp();
			break;
		case 7://清空文件
			wm.Clean_File();
			break;
		default:
			break;
		}

	}
	
	system("pause");
	system("cls");
	return 0;
}
