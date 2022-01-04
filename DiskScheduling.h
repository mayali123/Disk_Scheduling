#pragma once
#include <iostream>
#include <vector>
#include <random>
#include "Disk.h"
#define INF 0x3f3f3f3f
using namespace std;
class DiskScheduling {

public:
	DiskScheduling(int diskNum, int startPos, int maxPos);
	DiskScheduling(int* num,int len, int startPos);
	DiskScheduling(vector<int> num, int startPos);
	void FCFS();
	void SSTF();
	void ScanCscanHelper(int dir, int opt);
	void SCNF(bool dir);
	void CSCNF(bool dir);
	void clear();
	void print();

	void show();

	
private:
	int diskStartPos;			// 起始的磁道号 or 磁盘机械臂当前位置
	double sumStep = 0;			// 访问的总步数
	vector<int> diskInputSeq;	// 磁道待访问顺序
	vector<int> diskOutputSeq;	// 磁道实际的访问顺序
};