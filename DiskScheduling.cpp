#include "DiskScheduling.h"


// 初始化
DiskScheduling::DiskScheduling(int diskNum, int startPos, int maxPos)
{
	srand(time(NULL));
	for(int i=0;i<diskNum;i++)
		diskInputSeq.push_back(rand() % (maxPos + 1));

	cout << "随机生成的磁道号：\n";
	// 输出
	for (auto num : diskInputSeq)
		cout << num << " ";
	cout << endl;
	// 开始的位置
	diskStartPos = startPos;
}

DiskScheduling::DiskScheduling(int* num, int len, int startPos)
{
	for (int i = 0; i < len; i++)
		diskInputSeq.push_back(num[i]);
	// 开始的位置
	diskStartPos = startPos;
}

DiskScheduling::DiskScheduling(vector<int> num , int startPos)
{
	diskInputSeq = num;
	// 开始的位置
	diskStartPos = startPos;
}


// 先进先出算法
void DiskScheduling::FCFS()
{
	diskOutputSeq = diskInputSeq;
	// 计算步长
	for (int i = 1; i + 1< diskInputSeq.size(); i++)
	{
		sumStep += abs(diskInputSeq[i + 1] - diskInputSeq[i]);
	}
	sumStep += abs(diskStartPos  - diskInputSeq[0]);
}


// 最短寻道时间优先算法
void DiskScheduling::SSTF()
{
	vector<int> diskTemp = diskInputSeq;
	sort(diskTemp.begin(), diskTemp.end());
	int Min = INF,ind = 0,len = diskTemp.size();
	for (int i = 0; i < len; i++)
	{
		if (abs(diskStartPos - diskTemp[i]) < Min)
		{
			Min = abs(diskStartPos - diskTemp[i]);
			ind = i;
		}
	}
	/*printf("ind %d \n",ind);*/

	int L = ind - 1, R = ind + 1,mid = diskTemp[ind];
	diskOutputSeq.push_back(mid);
	sumStep += abs(diskStartPos -mid);
	while (L >= 0 && R < len)
	{
		if (abs(diskTemp[L] - mid) > abs(diskTemp[R] - mid))
		{
			sumStep += abs(diskTemp[R] - mid);
			mid = diskTemp[R];
			R++;
		}
		else
		{
			sumStep += abs(diskTemp[L] - mid);
			mid = diskTemp[L];
			L--;
		}
		diskOutputSeq.push_back(mid);
	}
	while (L >= 0)
	{
		sumStep += abs(diskTemp[L] - mid);
		mid = diskTemp[L];
		L--;
		diskOutputSeq.push_back(mid);
	}
	while (R < len)
	{
		sumStep += abs(diskTemp[R] - mid);
		mid = diskTemp[R];
		R++;
		diskOutputSeq.push_back(mid);
	}
}


// 电梯算法
// dir = true 移动方向为磁盘号小到大的方向
// opt = 0 为 SCNF算法 opt = 1 为 CSCNF算法
// 
void DiskScheduling::ScanCscanHelper(int dir, int opt) 
{
		vector<int> diskTemp(diskInputSeq);
		sort(diskTemp.begin(), diskTemp.end(), [dir](const int& first, const int& second) {
			return dir ? first > second: first < second;
			});
		
		auto i = diskTemp.begin();
		for (; i != diskTemp.end() - 1; i++) {
			if ((*i - diskStartPos) * (*(i + 1) - diskStartPos) <= 0) {
				if ((*(i + 1) - diskStartPos) == 0) i++;
				break;
			}
		}
		reverse(diskTemp.begin(), i + 1);
		if (opt == 1) reverse(i + 1, diskTemp.end());
		diskOutputSeq = diskTemp;
		for (auto j = diskOutputSeq.begin(); j != diskOutputSeq.end() - 1; ++j) {
			sumStep += abs(*j - *(j + 1));
		}
		sumStep += abs(diskStartPos - diskOutputSeq[0]);
}

// SCNF算法
void DiskScheduling::SCNF(bool dir = true)
{
	ScanCscanHelper(dir, 0);
}

// CSCNF算法
void DiskScheduling::CSCNF(bool dir = true)
{
	ScanCscanHelper(dir, 1);
}

// 初始化
void DiskScheduling::clear()
{
	sumStep = 0;
	diskOutputSeq.clear();
}

// 输出信息
void DiskScheduling::print()
{
	cout << "磁道起始位置为："<< diskStartPos<<endl;
	cout << "磁道待访问顺序\t\n";
	for (int diskNow : diskInputSeq)
		cout << diskNow << " ";
	cout << "\n磁道实际访问顺序\t\n";
	for (int diskActual : diskOutputSeq)
		cout << diskActual << " ";
	cout << "\n移动的磁道总数\t" << sumStep << endl;
	cout << "平均寻道数\t" << sumStep / diskOutputSeq.size() << "\n\n\n";
}

// 可视化
void DiskScheduling::show()
{
	// 输出信息
	print();
	// 
	Disk D(diskOutputSeq, diskStartPos);
	// 清理
	clear();
}