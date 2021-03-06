// monkeyking_shewheap.cpp: 定义控制台应用程序的入口点。

#include "Node.h"
#include <vector>
#include <chrono>
#include <fstream>

#define random(x) (rand()%x + 1) //1~x
#define SIZE 100000
using namespace std;
using namespace chrono;

ofstream mycout("result.txt");
int main()
{
	srand((int)time(0));
	void beginToFight(const vector<double> & monkeysPower, const vector<vector<int> > & monkeysFight);
	/*
	vector<double> monkeysPower = { 0, 20, 16, 10, 10, 4 };
	vector<vector<int>> monkeysFight = { { 2, 3 },{ 3, 4 },{ 3, 5 },{ 4, 5 },{ 1, 5 } };
	*/
		
	vector<double> monkeysPower;
	vector<vector<int>> monkeysFight;
	vector<int> tmp = {0, 0};
	monkeysPower.push_back(0); // 猴子的编号从1开始，容器中的0下标压入0值做冗余
	for (int i = 0; i < SIZE; i++) {
		monkeysPower.push_back((double)random(1000));
	}
	for (int i = 0; i < SIZE; ++i) {
		int x, y;
		do {
			x = random(SIZE);
			y = random(SIZE);
		} while (x == y);
		tmp.at(0) = x;
		tmp.at(1) = y;
		monkeysFight.push_back(tmp);
	}
	
	auto begin = system_clock::now();
	beginToFight(monkeysPower, monkeysFight);
	auto end = system_clock::now();
	auto duration = duration_cast<microseconds>(end - begin);
	cout << "时间花费了：" << double(duration.count()) * microseconds::period::num / microseconds::period::den << "s" << endl;

	system("pause");
	return 0;
}

void beginToFight(const vector<double> & monkeysPower, const vector<vector<int>> & monkeysFight) {
	vector<Node *> monkeys;
	monkeys.push_back(NULL); //猴子编号从1开始
	for (int i = 1; i < monkeysPower.size(); ++i) {
		monkeys.push_back(new Node(monkeysPower[i]));
	}
	for (auto i : monkeysFight) {
		//cout << monkeys.at(i[0])->fight(monkeys.at(i[1])) << endl;
		mycout << monkeys.at(i[0])->fight(monkeys.at(i[1])) << endl;
	}
}

