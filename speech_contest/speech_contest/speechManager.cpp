#include "speechManager.h"
#include<algorithm>
#include<deque>
#include<numeric>
#include <fstream>

SpeechManager::SpeechManager()
{
	this->initSpeech();

	//����ѡ��
	this->createSpeaker();

	this->loadRecord();
}

SpeechManager::~SpeechManager()
{
}


//��ʼ������
void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Record.clear();

	//��ʼ����������
	this->m_Index = 1;

}

void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i=0;i<nameSeed.size(); i++)
	{
		Speaker sp;
		sp.m_Name = "ѡ��";
		sp.m_Name += nameSeed[i];

		sp.m_Score[0] = 0;
		sp.m_Score[1] = 0;

		this->v1.push_back(i + 10001); //ѡ�ֱ��
		this->m_Speaker.insert(make_pair(i + 10001,sp));
	}
}


void SpeechManager::startSpeech()
{
	//��һ�ֱ���
	//1����ǩ
	this->speechDraw();

	//2������
	this->speechContest();

	//3����ʾ�������
	this->showScore();

	//�ڶ��ֱ���
	this->m_Index = 2;
	//1����ǩ
	this->speechDraw();

	//2������
	this->speechContest();

	//3����ʾ���ս��
	this->showScore();

	//4���������
	this->saveRecord();

	//���ü�¼
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();

	cout << "�����������" << endl;
	system("pause");
	system("cls");
}

void myPrint(int val)
{
	cout << val << " ";
}
void SpeechManager::speechDraw()
{
	cout << "�� << " << this->m_Index << " >> �ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "---------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;

	if (this->m_Index == 1)
	{
		random_shuffle(v1.begin(),v1.end());
		for_each(v1.begin(),v1.end(), myPrint);
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for_each(v2.begin(), v2.end(), myPrint);
		cout << endl;
	}
	cout << "---------------------" << endl;
	system("pause");
	cout << endl;
}


void SpeechManager::speechContest()
{
	cout << "------------- ��" << this->m_Index << "����ʽ������ʼ��------------- " << endl;
	multimap<double, int, greater<int>> groupScore; //��ʱ����������key���� value ѡ�ֱ�� ��������

	int num = 0; //��¼��Ա����6��Ϊ1��
	vector <int>v_Src;   //��������Ա����
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//�������в���ѡ��
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//10����ί��ѡ�ִ�֣�ȥ����߷ֺ���ͷ֣���ƽ����
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double tempscore = (rand() % 401 + 600) / 10.f;
			d.push_back(tempscore);
		}

		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();
		d.pop_back();
		double sum = accumulate(d.begin(), d.end(), 0.0f);				//��ȡ�ܷ�
		double avg = sum / (double)d.size();							//��ȡƽ����
		//��ƽ���ַ���ѡ����
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg; //����ѡ�ֱ��ȡ��ѡ��

		//6����һ�飬����ʱ��������
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С��������Σ�" << endl;

			//չʾ�ɼ� ��ǰ�����ĳɼ�������һ�ֵ������У�����Ѿ������һ�ֵĻ��ͷ�����Ǿ�������
			for (multimap<double, int, greater<int>>::iterator it= groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "���: " << it->second << " ������ " << this->m_Speaker[it->second].m_Name << " �ɼ��� " 
					<< this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}

			int count = 0;
			//ȡǰ������ѡ��
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); it != groupScore.end()&& count<3;it++, count++)
			{
				
				if (this->m_Index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}
			}
			groupScore.clear();
			cout << endl;
		}
	}
	cout << "------------- ��" << this->m_Index << "�ֱ������  ------------- " << endl;
	system("pause");
}
//��ʾ�������
void SpeechManager::showScore()
{
	cout << "---------��" << this->m_Index << "�ֽ���ѡ����Ϣ���£�-----------" << endl;
	vector<int>v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "ѡ�ֱ�ţ�" << *it << " ������ " << m_Speaker[*it].m_Name << " �÷֣� "
			 << m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->show_Menu();
}

//�����¼ ����Ƚϵ�ǰ���ɼ�
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (vector<int>::iterator it=this->vVictory.begin(); it != this->vVictory.end(); it++)
	{
		ofs << *it << ","
			<< this->m_Speaker[*it].m_Score[1]<<","; //�ڶ��ֵĳɼ�
	}
	ofs << endl;

	ofs.close();
	cout << "��¼�Ѿ�����" << endl;
	this->fileIsEmpty == false;
}

//��ȡ��¼
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);

	if (!ifs.is_open()) //��ʧ��
	{
		this->fileIsEmpty = true;
		//cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��!" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	this->fileIsEmpty = false;
	ifs.putback(ch); //��ȡ�ĵ����ַ��Ż�ȥ

	string data;
	int index = 0;
	while (ifs >> data) //��ȡһ��
	{
		//cout << data << endl;
		vector<string> v;
		int pos = -1;
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);//��0λ�ÿ�ʼ����

			if (pos == -1)
			{
				break; //�Ҳ���break����
			}
			string tmp = data.substr(start, pos - start); //�ҵ���,���зָ� ����1 ��ʼλ�ã�����2 ��ȡ����
			v.push_back(tmp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v)); //��ѡ�ֵı�źͷ�����һ��Ž������������
		index++;
	}

	ifs.close();
}


//��ʾ����÷�
void SpeechManager::showRecord()
{
	
	if (this->fileIsEmpty == false)
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "��" << i + 1 << "�� " <<
				"�ھ���ţ�" << this->m_Record[i][0] << " �÷֣�" << this->m_Record[i][1] << " "
				"�Ǿ���ţ�" << this->m_Record[i][2] << " �÷֣�" << this->m_Record[i][3] << " "
				"������ţ�" << this->m_Record[i][4] << " �÷֣�" << this->m_Record[i][5] << endl;
		}

	}
	else
	{
		cout << "û�м�¼" << endl;
	}
	system("pause");
	system("cls");
}

//��ռ�¼
void SpeechManager::clearRecord()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int choice = 0; //�����洢�û���ѡ��
	cout << "����������ѡ�� " << endl;
	cin >> choice;

	if (choice == 1)
	{
		
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		//��ʼ������
		this->initSpeech();

		//����ѡ��
		this->createSpeaker();

		//��ȡ�����¼
		this->loadRecord();

		cout << "��ճɹ���" << endl;
	}
		system("pause");
		system("cls");
}

void SpeechManager::show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*************  ��ӭ�μ��ݽ����� ************" << endl;
	cout << "*************  1.��ʼ�ݽ�����  *************" << endl;
	cout << "*************  2.�鿴�����¼  *************" << endl;
	cout << "*************  3.��ձ�����¼  *************" << endl;
	cout << "*************  0.�˳���������  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;

}


void SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}




