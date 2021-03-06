#include "speechManager.h"
#include<algorithm>
#include<deque>
#include<numeric>
#include <fstream>

SpeechManager::SpeechManager()
{
	this->initSpeech();

	//创建选手
	this->createSpeaker();

	this->loadRecord();
}

SpeechManager::~SpeechManager()
{
}


//初始化属性
void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Record.clear();

	//初始化比赛轮数
	this->m_Index = 1;

}

void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i=0;i<nameSeed.size(); i++)
	{
		Speaker sp;
		sp.m_Name = "选手";
		sp.m_Name += nameSeed[i];

		sp.m_Score[0] = 0;
		sp.m_Score[1] = 0;

		this->v1.push_back(i + 10001); //选手编号
		this->m_Speaker.insert(make_pair(i + 10001,sp));
	}
}


void SpeechManager::startSpeech()
{
	//第一轮比赛
	//1、抽签
	this->speechDraw();

	//2、比赛
	this->speechContest();

	//3、显示晋级结果
	this->showScore();

	//第二轮比赛
	this->m_Index = 2;
	//1、抽签
	this->speechDraw();

	//2、比赛
	this->speechContest();

	//3、显示最终结果
	this->showScore();

	//4、保存分数
	this->saveRecord();

	//重置记录
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();

	cout << "本届比赛结束" << endl;
	system("pause");
	system("cls");
}

void myPrint(int val)
{
	cout << val << " ";
}
void SpeechManager::speechDraw()
{
	cout << "第 << " << this->m_Index << " >> 轮比赛选手正在抽签" << endl;
	cout << "---------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;

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
	cout << "------------- 第" << this->m_Index << "轮正式比赛开始：------------- " << endl;
	multimap<double, int, greater<int>> groupScore; //临时容器，保存key分数 value 选手编号 降序排列

	int num = 0; //记录人员数，6个为1组
	vector <int>v_Src;   //比赛的人员容器
	if (this->m_Index == 1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//遍历所有参赛选手
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//10个评委给选手打分，去掉最高分和最低分，求平均分
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double tempscore = (rand() % 401 + 600) / 10.f;
			d.push_back(tempscore);
		}

		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();
		d.pop_back();
		double sum = accumulate(d.begin(), d.end(), 0.0f);				//获取总分
		double avg = sum / (double)d.size();							//获取平均分
		//把平均分放入选手中
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg; //根据选手编号取出选手

		//6个人一组，用临时容器保存
		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次：" << endl;

			//展示成绩 把前三名的成绩放入下一轮的容器中，如果已经是最后一轮的话就放入冠亚军名单中
			for (multimap<double, int, greater<int>>::iterator it= groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号: " << it->second << " 姓名： " << this->m_Speaker[it->second].m_Name << " 成绩： " 
					<< this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
			}

			int count = 0;
			//取前三名的选手
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
	cout << "------------- 第" << this->m_Index << "轮比赛完毕  ------------- " << endl;
	system("pause");
}
//显示比赛结果
void SpeechManager::showScore()
{
	cout << "---------第" << this->m_Index << "轮晋级选手信息如下：-----------" << endl;
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
		cout << "选手编号：" << *it << " 姓名： " << m_Speaker[*it].m_Name << " 得分： "
			 << m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->show_Menu();
}

//保存记录 本届比较的前三成绩
void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (vector<int>::iterator it=this->vVictory.begin(); it != this->vVictory.end(); it++)
	{
		ofs << *it << ","
			<< this->m_Speaker[*it].m_Score[1]<<","; //第二轮的成绩
	}
	ofs << endl;

	ofs.close();
	cout << "记录已经保存" << endl;
	this->fileIsEmpty == false;
}

//读取记录
void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);

	if (!ifs.is_open()) //打开失败
	{
		this->fileIsEmpty = true;
		//cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空!" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	this->fileIsEmpty = false;
	ifs.putback(ch); //读取的单个字符放回去

	string data;
	int index = 0;
	while (ifs >> data) //读取一行
	{
		//cout << data << endl;
		vector<string> v;
		int pos = -1;
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);//从0位置开始查找

			if (pos == -1)
			{
				break; //找不到break返回
			}
			string tmp = data.substr(start, pos - start); //找到了,进行分割 参数1 起始位置，参数2 截取长度
			v.push_back(tmp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v)); //把选手的编号和分数都一起放进这个容器中了
		index++;
	}

	ifs.close();
}


//显示往届得分
void SpeechManager::showRecord()
{
	
	if (this->fileIsEmpty == false)
	{
		for (int i = 0; i < this->m_Record.size(); i++)
		{
			cout << "第" << i + 1 << "届 " <<
				"冠军编号：" << this->m_Record[i][0] << " 得分：" << this->m_Record[i][1] << " "
				"亚军编号：" << this->m_Record[i][2] << " 得分：" << this->m_Record[i][3] << " "
				"季军编号：" << this->m_Record[i][4] << " 得分：" << this->m_Record[i][5] << endl;
		}

	}
	else
	{
		cout << "没有记录" << endl;
	}
	system("pause");
	system("cls");
}

//清空记录
void SpeechManager::clearRecord()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、返回" << endl;

	int choice = 0; //用来存储用户的选项
	cout << "请输入您的选择： " << endl;
	cin >> choice;

	if (choice == 1)
	{
		
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		//初始化属性
		this->initSpeech();

		//创建选手
		this->createSpeaker();

		//获取往届记录
		this->loadRecord();

		cout << "清空成功！" << endl;
	}
		system("pause");
		system("cls");
}

void SpeechManager::show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*************  欢迎参加演讲比赛 ************" << endl;
	cout << "*************  1.开始演讲比赛  *************" << endl;
	cout << "*************  2.查看往届记录  *************" << endl;
	cout << "*************  3.清空比赛记录  *************" << endl;
	cout << "*************  0.退出比赛程序  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;

}


void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}




