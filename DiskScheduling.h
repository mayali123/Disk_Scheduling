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
	int diskStartPos;			// ��ʼ�Ĵŵ��� or ���̻�е�۵�ǰλ��
	double sumStep = 0;			// ���ʵ��ܲ���
	vector<int> diskInputSeq;	// �ŵ�������˳��
	vector<int> diskOutputSeq;	// �ŵ�ʵ�ʵķ���˳��
};