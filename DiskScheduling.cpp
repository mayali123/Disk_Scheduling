#include "DiskScheduling.h"


// ��ʼ��
DiskScheduling::DiskScheduling(int diskNum, int startPos, int maxPos)
{
	srand(time(NULL));
	for(int i=0;i<diskNum;i++)
		diskInputSeq.push_back(rand() % (maxPos + 1));

	cout << "������ɵĴŵ��ţ�\n";
	// ���
	for (auto num : diskInputSeq)
		cout << num << " ";
	cout << endl;
	// ��ʼ��λ��
	diskStartPos = startPos;
}

DiskScheduling::DiskScheduling(int* num, int len, int startPos)
{
	for (int i = 0; i < len; i++)
		diskInputSeq.push_back(num[i]);
	// ��ʼ��λ��
	diskStartPos = startPos;
}

DiskScheduling::DiskScheduling(vector<int> num , int startPos)
{
	diskInputSeq = num;
	// ��ʼ��λ��
	diskStartPos = startPos;
}


// �Ƚ��ȳ��㷨
void DiskScheduling::FCFS()
{
	diskOutputSeq = diskInputSeq;
	// ���㲽��
	for (int i = 1; i + 1< diskInputSeq.size(); i++)
	{
		sumStep += abs(diskInputSeq[i + 1] - diskInputSeq[i]);
	}
	sumStep += abs(diskStartPos  - diskInputSeq[0]);
}


// ���Ѱ��ʱ�������㷨
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


// �����㷨
// dir = true �ƶ�����Ϊ���̺�С����ķ���
// opt = 0 Ϊ SCNF�㷨 opt = 1 Ϊ CSCNF�㷨
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

// SCNF�㷨
void DiskScheduling::SCNF(bool dir = true)
{
	ScanCscanHelper(dir, 0);
}

// CSCNF�㷨
void DiskScheduling::CSCNF(bool dir = true)
{
	ScanCscanHelper(dir, 1);
}

// ��ʼ��
void DiskScheduling::clear()
{
	sumStep = 0;
	diskOutputSeq.clear();
}

// �����Ϣ
void DiskScheduling::print()
{
	cout << "�ŵ���ʼλ��Ϊ��"<< diskStartPos<<endl;
	cout << "�ŵ�������˳��\t\n";
	for (int diskNow : diskInputSeq)
		cout << diskNow << " ";
	cout << "\n�ŵ�ʵ�ʷ���˳��\t\n";
	for (int diskActual : diskOutputSeq)
		cout << diskActual << " ";
	cout << "\n�ƶ��Ĵŵ�����\t" << sumStep << endl;
	cout << "ƽ��Ѱ����\t" << sumStep / diskOutputSeq.size() << "\n\n\n";
}

// ���ӻ�
void DiskScheduling::show()
{
	// �����Ϣ
	print();
	// 
	Disk D(diskOutputSeq, diskStartPos);
	// ����
	clear();
}