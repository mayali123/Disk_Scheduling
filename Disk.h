#pragma once
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#define PI acos(-1.0)
using namespace std;
class Disk {

public:
	Disk(vector<int> Seq, int StartPos);
	void InitUI();
	void showText(int R, double Angle, TCHAR* str, COLORREF color );
	void showLine(int R, double Angle);
	void AGotoB(int a, int b);
	double getAngle(int a);
	void display();

private:
	// XPoint Բx���� YPointԲy���� R Բ�İ뾶
	int XPoint = 320, YPoint = 240, Radius = 150;
	// ������
	int DiskNum;
	// ���
	double interval;
	// �ŵ��� �� ȥ�ز����������
	vector<int> Seq, SortSeq;
	unordered_map<int, int> ind;
	TCHAR s[10];
};