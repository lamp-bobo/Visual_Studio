#pragma once

#include <iostream>
#include "worker.h"
using namespace std;
#include <fstream>
#define  FILENAME "empFile.txt"

class WorkerManager
{
public:

	//���캯��
	WorkerManager();

	void Show_Menu();

	void exitSystem();

	//����ְ��
	void Add_Emp();

	//ͳ������
	int get_EmpNum();

	//��ʼ��Ա��
	void init_Emp();

	//��ʾְ��
	void Show_Emp();
	//����ְ������ж�ְ���Ƿ����, �����ڷ���ְ����������λ�ã������ڷ��� - 1
	int IsExist(int id);

	//ɾ��ְ��
	void Del_Emp();

	//�޸�ְ��
	void Mod_Emp();

	//����ְ��
	void Find_Emp();

	//����ְ��
	void Sort_Emp();

	//����ļ�
	void Clean_File();

	//�����ļ�
	void save();

	//��������
	~WorkerManager();


	//��¼�ļ��е���������
	int m_EmpNum;

	//Ա�������ָ��
	Worker ** m_EmpArray;

	//��־�ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;
};

