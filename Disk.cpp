#include "Disk.h"
// 初始化
Disk::Disk(vector<int> seq , int StartPos) {
	// 初始的序列
	Seq = seq;
	
	Seq.insert(Seq.begin(), StartPos);
	
	// 排序并去重序列
	SortSeq = Seq;
	// 排序
	sort(SortSeq.begin(), SortSeq.end());
	// 去重
	SortSeq.erase(unique(SortSeq.begin(), SortSeq.end()), SortSeq.end());
	// 磁道数
	DiskNum = SortSeq.size();
	// 间隔
	interval = (2 * PI) / DiskNum;

	// 保存下标 方便后续操作
	for (int i = 0; i < SortSeq.size(); i++)
		ind[SortSeq[i]] = i;

	// 初始化界面
	InitUI();
}

// 显示磁道号
void Disk::showText(int R, double Angle, TCHAR* str, COLORREF color = WHITE)
{
	int flag = Angle > PI;
	// 计算字符串宽 w
	int w = textwidth(str);

	// 根据角度计算 坐标
	int X = XPoint + R * sin(Angle) - flag * w;
	int Y = YPoint - R * cos(Angle);

	settextcolor(color);
	outtextxy(X, Y, str);
}

// 初始化界面
void Disk::InitUI() {
	// 初始化 640 x 480 的绘图窗口 
	initgraph(640, 480, EW_SHOWCONSOLE | EW_NOCLOSE);

	// 设置 XOR 绘图模式
	setwritemode(R2_XORPEN);
	// 画圆
	circle(XPoint, YPoint, Radius);
	// 显示磁盘号
	for (int i = 0; i < DiskNum; i++)
	{
		_stprintf_s(s, _T("%d"), SortSeq[i]);
		showText(Radius + 20, (2 * PI * i) / DiskNum,s);
	}
	
	// 保存字体
	LOGFONT font;
	gettextstyle(&font);
	setcolor(RED);
	settextstyle(font.lfHeight * 2, font.lfWidth* 2 ,L"宋体");
	outtextxy(10, 10, L"按任意键开始演示");
	settextstyle(&font);
	setcolor(WHITE);

	// 指向开始的磁盘号
	showLine(Radius - 20, getAngle(ind[Seq[0]]));


	// 等待按下
	_getch();
	// 檫去之前画的线
	
	showLine(Radius - 20, getAngle(ind[Seq[0]]));

	setcolor(BLACK);
	settextstyle(font.lfHeight * 2, font.lfWidth * 2, L"宋体");
	outtextxy(10, 10, L"按任意键开始演示");
	settextstyle(&font);
	setcolor(WHITE);

	// 开始展示
	display();

	setcolor(RED);
	settextstyle(font.lfHeight * 2, font.lfWidth * 2,L"宋体");
	outtextxy(10, 10, L"按任意键关闭窗口");
	settextstyle(&font);
	setcolor(WHITE);


	// 按下后在关闭画图程序
	_getch();
	closegraph();
}

// 直线
void Disk::showLine(int R,double Angle)
{
	// 根据角度计算 坐标
	int X = XPoint + R * sin(Angle);
	int Y = YPoint - R * cos(Angle);

	setlinestyle(PS_SOLID, 1);
	settextcolor(WHITE);
	// 画直线
	line(XPoint, YPoint, X, Y);
}

// 显示从 a 到 b 
void Disk::AGotoB(int a, int b)
{
	double speed = PI / 32;
	double start = getAngle(a), end = getAngle(b);

	// 变成白色

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
	// 到达 B
	// 将 B 边成红色

	_stprintf_s(s, _T("%d"), SortSeq[b]);
	showText(Radius+20, end, s, RED);

	Sleep(500);
	showLine(Radius - 20, start);
	
}

// 将下标转换成对应的 角度
double Disk::getAngle(int a)
{
	return a * interval;
}

// 展示 磁道的调用过程
void Disk::display()
{
	for (int i = 0; i + 1 < Seq.size(); i++)
	{
		AGotoB(ind[Seq[i]], ind[Seq[i+1]]);
	}
	showLine(Radius - 20, getAngle(ind[Seq.back()]));
}
