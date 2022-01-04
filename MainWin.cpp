#include "DiskScheduling.h"

void InitUi()
{
	DiskScheduling* disk = NULL;
	int diskNum, startPos, maxPos;
	while (1)
	{
		cout <<"**********************************************\n";
		cout <<"            欢迎来到磁盘调度系统              \n";
		cout <<"**********************************************\n";
		cout <<"           随机生成磁盘号请按1                \n";
		cout <<"             输入磁盘号请按2                  \n";
		cout <<"          使用FCFS调度算法请按3               \n";
		cout <<"          使用SSTF调度算法请按4               \n";
		cout <<"          使用SCAN调度算法请按5               \n";
		cout <<"         使用CSCAN调度算法请按6               \n";
		cout <<"                退出请按7                     \n";
		cout << "**********************************************\n";
		cout << "请输入你要选择的功能：";

		// 用户输入key
		int InputKey;
		cin >> InputKey;
		//cout << "InputKey=" << InputKey << "end "<<endl;
		if (disk == NULL && 3<=InputKey&& InputKey <=6)
		{
			cout << "没有输入磁盘号！请输入之后再使用调度算法" << endl;
			Sleep(1000);
			system("cls");
			continue;
		}
		switch (InputKey)
		{
		case   1:
		{
			// 清屏
			system("cls");
			cout << "请输入磁道数:";
			cin >> diskNum;
			cout << "请输入磁道起始位置:";
			cin >> startPos;
			cout << "请输入磁道的最大值:";
			cin >> maxPos;
			if (disk != NULL)
				delete disk;
			disk = new DiskScheduling(diskNum, startPos, maxPos);

			break;
		}
		case  2:
		{
			// 清屏
			system("cls");
			cout << "请输入磁道数:";
			cin >> diskNum;
			cout << "请输入磁道起始位置:";
			cin >> startPos;
			cout << "请输入磁道号:";
			// 保存磁号
			int* num = new int[diskNum + 10];
			for (int i = 0; i < diskNum; i++)
				cin >> num[i];
			if (disk != NULL)
				delete disk;
			// 初始化
			disk = new DiskScheduling(num, diskNum, startPos);
			// 释放空间
			delete[] num;
			break;
		}
		case 3:
		{
			cout << "使用使用FCFS算法调度磁盘" << endl;
			disk->FCFS(); // 使用FCFS算法
			disk->show();
			break;
		}
		case 4:
		{
			cout << "使用使用SSTF算法调度磁盘" << endl;
			disk->SSTF(); // 使用SSTF算法
			disk->show();
			break;
		}
		case 5:
		{	
			bool dir;
			cout << "\n从小到大的方向请输入 1，反之请输入 0:";
			cin >> dir;
			cout << "使用使用SCNF算法调度磁盘" << endl;
			disk->SCNF(dir); // 使用SSTF算法
			disk->show();
			break;
		}
		case 6:
		{
			bool dir;
			cout << "\n从小到大的方向请输入 1，反之请输入 0:";
			cin >> dir;
			cout << "使用使用CSCNF算法调度磁盘" << endl;
			disk->CSCNF(dir); // 使用SSTF算法
			disk->show();
			break;
		}
		case 7:
		{
			printf("即将退出系统，欢迎再次使用^.^\n");
			// 释放空间
			if(disk != NULL)
				delete disk;
			return;
			break;
		}
		default:
		{
			printf("输入格式错误，请重新输入\n");
			Sleep(1000);
		}
		}
		//getchar();
		// 实现 按任意键继续...
		system("pause");
		system("cls");
	}
}

int main()
{
	InitUi();
}

