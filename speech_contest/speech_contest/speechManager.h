#pragma once
#include<iostream>
#include<map>
#include<vector>
#include"speaker.h"

using namespace std;

//�ݽ�������
class SpeechManager
{
public:

	//���캯��
	SpeechManager();

	void show_Menu();

	void exitSystem();

	//��ʼ������
	void initSpeech();

	//��ʼ������12��ѡ��
	void createSpeaker();

	//��ʼ���� - �������̿���
	void startSpeech();

	//��ǩ
	void speechDraw();

	//����
	void speechContest();

	//��ʾ�������
	void showScore();

	//�����¼
	void saveRecord();

	//��ȡ��¼
	void loadRecord();

	//��ռ�¼
	void clearRecord();

	//��ʾ����÷�
	void showRecord();

	//��������
	~SpeechManager();

	//����ѡ�� ����  12��
	vector<int>v1;

	//��һ�ֽ�������  6��
	vector<int>v2;

	//ʤ��ǰ��������  3��
	vector<int>vVictory;

	//��ű�� �Լ���Ӧ�� ����ѡ�� ����
	map<int, Speaker> m_Speaker;

	int m_Index;
	//�ļ�Ϊ�յı�־
	bool fileIsEmpty;
	//�����¼
	map<int, vector<string>> m_Record;

};