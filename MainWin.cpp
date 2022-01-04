#include "DiskScheduling.h"

void InitUi()
{
	DiskScheduling* disk = NULL;
	int diskNum, startPos, maxPos;
	while (1)
	{
		cout <<"**********************************************\n";
		cout <<"            ��ӭ�������̵���ϵͳ              \n";
		cout <<"**********************************************\n";
		cout <<"           ������ɴ��̺��밴1                \n";
		cout <<"             ������̺��밴2                  \n";
		cout <<"          ʹ��FCFS�����㷨�밴3               \n";
		cout <<"          ʹ��SSTF�����㷨�밴4               \n";
		cout <<"          ʹ��SCAN�����㷨�밴5               \n";
		cout <<"         ʹ��CSCAN�����㷨�밴6               \n";
		cout <<"                �˳��밴7                     \n";
		cout << "**********************************************\n";
		cout << "��������Ҫѡ��Ĺ��ܣ�";

		// �û�����key
		int InputKey;
		cin >> InputKey;
		//cout << "InputKey=" << InputKey << "end "<<endl;
		if (disk == NULL && 3<=InputKey&& InputKey <=6)
		{
			cout << "û��������̺ţ�������֮����ʹ�õ����㷨" << endl;
			Sleep(1000);
			system("cls");
			continue;
		}
		switch (InputKey)
		{
		case   1:
		{
			// ����
			system("cls");
			cout << "������ŵ���:";
			cin >> diskNum;
			cout << "������ŵ���ʼλ��:";
			cin >> startPos;
			cout << "������ŵ������ֵ:";
			cin >> maxPos;
			if (disk != NULL)
				delete disk;
			disk = new DiskScheduling(diskNum, startPos, maxPos);

			break;
		}
		case  2:
		{
			// ����
			system("cls");
			cout << "������ŵ���:";
			cin >> diskNum;
			cout << "������ŵ���ʼλ��:";
			cin >> startPos;
			cout << "������ŵ���:";
			// ����ź�
			int* num = new int[diskNum + 10];
			for (int i = 0; i < diskNum; i++)
				cin >> num[i];
			if (disk != NULL)
				delete disk;
			// ��ʼ��
			disk = new DiskScheduling(num, diskNum, startPos);
			// �ͷſռ�
			delete[] num;
			break;
		}
		case 3:
		{
			cout << "ʹ��ʹ��FCFS�㷨���ȴ���" << endl;
			disk->FCFS(); // ʹ��FCFS�㷨
			disk->show();
			break;
		}
		case 4:
		{
			cout << "ʹ��ʹ��SSTF�㷨���ȴ���" << endl;
			disk->SSTF(); // ʹ��SSTF�㷨
			disk->show();
			break;
		}
		case 5:
		{	
			bool dir;
			cout << "\n��С����ķ��������� 1����֮������ 0:";
			cin >> dir;
			cout << "ʹ��ʹ��SCNF�㷨���ȴ���" << endl;
			disk->SCNF(dir); // ʹ��SSTF�㷨
			disk->show();
			break;
		}
		case 6:
		{
			bool dir;
			cout << "\n��С����ķ��������� 1����֮������ 0:";
			cin >> dir;
			cout << "ʹ��ʹ��CSCNF�㷨���ȴ���" << endl;
			disk->CSCNF(dir); // ʹ��SSTF�㷨
			disk->show();
			break;
		}
		case 7:
		{
			printf("�����˳�ϵͳ����ӭ�ٴ�ʹ��^.^\n");
			// �ͷſռ�
			if(disk != NULL)
				delete disk;
			return;
			break;
		}
		default:
		{
			printf("�����ʽ��������������\n");
			Sleep(1000);
		}
		}
		//getchar();
		// ʵ�� �����������...
		system("pause");
		system("cls");
	}
}

int main()
{
	InitUi();
}

