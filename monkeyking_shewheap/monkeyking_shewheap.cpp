// monkeyking_shewheap.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "shewheap.h"
#include <vector>
#include <chrono>
#include <fstream>
#define random(x) (rand()%x + 1) //1~x
#define SIZE 50000
using namespace std;
using namespace chrono;

ofstream mycout("result.txt");
int main()
{
	srand((int)time(0));
	void beginToFight(const vector<double> & monkeysPower, const vector<vector<int>> & monkeysFight);
	/*
	vector<double> monkeysPower = { 0, 50, 16, 10, 10, 4, 40};
	vector<vector<int>> monkeysFight = { { 2, 6 },{ 3, 4 },{ 1, 5 },{ 6, 5 },{ 1, 3 }, {4, 6} };
	*/

	vector<double> monkeysPower;
	vector<vector<int>> monkeysFight;
	vector<int> tmp = {0, 0};
	monkeysPower.push_back(0); // 猴子的编号从1开始，容器中的0下标压入0值做冗余
	for (int i = 0; i < SIZE; i++) {
		monkeysPower.push_back((double)random(500));
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
	vector<ShewHeap<double> *> monkeysFrom;
	long monkeys = monkeysPower.size() - 1; //减去0下标的冗余
	long fights = monkeysFight.size();
	for (int i = 0; i < monkeys + 1; ++i) {
		monkeysFrom.push_back(NULL);
	}
	ShewHeap<double> *h1, *h2;
	for (int i = 0; i < fights; ++i) {
		int monkey1 = monkeysFight[i][0];
		int monkey2 = monkeysFight[i][1];
		if (monkeysFrom[monkey1] == NULL) {
			h1 = new ShewHeap<double>();
			h1->insert(monkeysPower[monkey1]);
			monkeysFrom[monkey1] = h1;
		}
		else h1 = monkeysFrom[monkey1];

		if (monkeysFrom[monkey2] == NULL) {
			h2 = new ShewHeap<double>();
			h2->insert(monkeysPower[monkey2]);
			monkeysFrom[monkey2] = h2;
		}
		else h2 = monkeysFrom[monkey2];

		if (h1->merge(h2) == -1) {
			//cout << -1 << endl;
			mycout << -1 << endl;
		}
		else {
			for (int index = 0; index < monkeys + 1; ++index) {
				if (monkeysFrom[index] == h2)
					monkeysFrom[index] = h1;
			}
			double print = h1->getMaxKey() / 2;
			//cout << print << endl;
			mycout << print << endl;
			h1->deleteMax();
			h1->insert(print);
		}
	}

	
}

