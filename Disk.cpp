#include "Disk.h"
// ��ʼ��
Disk::Disk(vector<int> seq , int StartPos) {
	// ��ʼ������
	Seq = seq;
	
	Seq.insert(Seq.begin(), StartPos);
	
	// ����ȥ������
	SortSeq = Seq;
	// ����
	sort(SortSeq.begin(), SortSeq.end());
	// ȥ��
	SortSeq.erase(unique(SortSeq.begin(), SortSeq.end()), SortSeq.end());
	// �ŵ���
	DiskNum = SortSeq.size();
	// ���
	interval = (2 * PI) / DiskNum;

	// �����±� �����������
	for (int i = 0; i < SortSeq.size(); i++)
		ind[SortSeq[i]] = i;

	// ��ʼ������
	InitUI();
}

// ��ʾ�ŵ���
void Disk::showText(int R, double Angle, TCHAR* str, COLORREF color = WHITE)
{
	int flag = Angle > PI;
	// �����ַ����� w
	int w = textwidth(str);

	// ���ݽǶȼ��� ����
	int X = XPoint + R * sin(Angle) - flag * w;
	int Y = YPoint - R * cos(Angle);

	settextcolor(color);
	outtextxy(X, Y, str);
}

// ��ʼ������
void Disk::InitUI() {
	// ��ʼ�� 640 x 480 �Ļ�ͼ���� 
	initgraph(640, 480, EW_SHOWCONSOLE | EW_NOCLOSE);

	// ���� XOR ��ͼģʽ
	setwritemode(R2_XORPEN);
	// ��Բ
	circle(XPoint, YPoint, Radius);
	// ��ʾ���̺�
	for (int i = 0; i < DiskNum; i++)
	{
		_stprintf_s(s, _T("%d"), SortSeq[i]);
		showText(Radius + 20, (2 * PI * i) / DiskNum,s);
	}
	
	// ��������
	LOGFONT font;
	gettextstyle(&font);
	setcolor(RED);
	settextstyle(font.lfHeight * 2, font.lfWidth* 2 ,L"����");
	outtextxy(10, 10, L"���������ʼ��ʾ");
	settextstyle(&font);
	setcolor(WHITE);

	// ָ��ʼ�Ĵ��̺�
	showLine(Radius - 20, getAngle(ind[Seq[0]]));


	// �ȴ�����
	_getch();
	// ��ȥ֮ǰ������
	
	showLine(Radius - 20, getAngle(ind[Seq[0]]));

	setcolor(BLACK);
	settextstyle(font.lfHeight * 2, font.lfWidth * 2, L"����");
	outtextxy(10, 10, L"���������ʼ��ʾ");
	settextstyle(&font);
	setcolor(WHITE);

	// ��ʼչʾ
	display();

	setcolor(RED);
	settextstyle(font.lfHeight * 2, font.lfWidth * 2,L"����");
	outtextxy(10, 10, L"��������رմ���");
	settextstyle(&font);
	setcolor(WHITE);


	// ���º��ڹرջ�ͼ����
	_getch();
	closegraph();
}

// ֱ��
void Disk::showLine(int R,double Angle)
{
	// ���ݽǶȼ��� ����
	int X = XPoint + R * sin(Angle);
	int Y = YPoint - R * cos(Angle);

	setlinestyle(PS_SOLID, 1);
	settextcolor(WHITE);
	// ��ֱ��
	line(XPoint, YPoint, X, Y);
}

// ��ʾ�� a �� b 
void Disk::AGotoB(int a, int b)
{
	double speed = PI / 32;
	double start = getAngle(a), end = getAngle(b);

	// ��ɰ�ɫ

	_stprintf_s(s, _T("%d"), SortSeq[a]);
	showText(Radius+20, start, s, WHITE);

	int flag = start >= end ? -1 : 1;
	while (true)
	{
		showLine(Radius - 20 ,start);
		if (fabs(start - end) < speed)
			break;
		Sleep(100);
		showLine(Radius - 20 ,start);
		start += flag * speed;
		//printf("%lf %lf\n", start, end);
	}
	// ���� B
	// �� B �߳ɺ�ɫ

	_stprintf_s(s, _T("%d"), SortSeq[b]);
	showText(Radius+20, end, s, RED);

	Sleep(500);
	showLine(Radius - 20, start);
	
}

// ���±�ת���ɶ�Ӧ�� �Ƕ�
double Disk::getAngle(int a)
{
	return a * interval;
}

// չʾ �ŵ��ĵ��ù���
void Disk::display()
{
	for (int i = 0; i + 1 < Seq.size(); i++)
	{
		AGotoB(ind[Seq[i]], ind[Seq[i+1]]);
	}
	showLine(Radius - 20, getAngle(ind[Seq.back()]));
}
