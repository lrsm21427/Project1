#include <iostream>
#include <string>
using namespace std;

/*
* ���Ҫ��
* [1] ��ƿ����ڸ�ʵ��Ľ��̿��ƿ飬���̿��ƿ����ٰ��� ���̺š�״̬(����ʱ��+���ȼ�) �� Ҫ�����ʱ��
*
* [2] ��̬��̬�����������
*
* [3] ģ�����ϵͳ���ֽ��̵����㷨���Ƚ��ȳ�������ҵ���ȡ������ȼ����ȡ�����Ӧ�������е���������
*
* [4] �����������Ľ��̲���ʾ���Ƚ��
*/

typedef struct Process_Control_Block
{
	int num;
	int enter_Tim;
	int start_Tim;
	int sev_Tim;
	int save_Sev_Tim;
	int over_Tim;
	int priority_Rank;		// ���ȼ�
	bool finish_Flag;		// �Ƿ��Է�����ı�־
}PCB;

void FCFS_Algorithm();		// �����ȷ����㷨 FCFS (First Come First Service)
void SJF_Algorithm();		// �����ҵ�����㷨 SJF (Shortest Job First)
void HPF_Algorithm();		// ������ȼ������㷨 HPR (Highest Priority First)
void HRN_Algorithm();		// �����Ӧ�������㷨 HRN (Highest Response Ratio Next)
int Find_Min_SevTime_Pro(int, PCB*, int);
int Find_Max_Priority_Pro(int, PCB*, int);

void Init(int*, PCB*&, int);
void Print_Menu();
void Print_Res(int*, PCB*&);

int main()
{
	int choice;
	do
	{
		Print_Menu();
		cout << "��ѡ��Ҫʵ�ֵ��㷨��";
		cin >> choice;
		switch (choice)
		{
		case 1:
			FCFS_Algorithm();
			break;
		case 2:
			SJF_Algorithm();
			break;
		case 3:
			HPF_Algorithm();
			break;
		case 4:
			HRN_Algorithm();
			break;
		case 0:
			break;
		}
		system("pause");
		system("cls");
	} while (choice);
	return 0;
}

void Print_Menu()
{
	/* ����ģ�� */
	cout << "+---------------------------------------+" << endl;
	cout << "|\t>>> �㷨�嵥 <<<\t\t|" << endl;
	cout << "|\t1.�����ȷ����㷨(FCFS)\t\t|" << endl << "|\t2.�����ҵ�����㷨(SJF)\t\t|" << endl;
	cout << "|\t3.������ȼ������㷨(HPR)\t|" << endl << "|\t4.�����Ӧ�������㷨(HRN)\t|" << endl;
	cout << "|\t0.�˳�\t\t\t\t|" << endl;
	cout << "+---------------------------------------+" << endl;
}

void Init(int* n, PCB*& Pro_Array, int HPR_Flag)
{
	cout << "�������ڵ��������£�����ȵ���ҵ���� n Ϊ��";
	cin >> *n;
	Pro_Array = new PCB[*n];

	cout << "��ֱ������� " << *n << " �����̵Ľ��̺ţ����ո����֣�";
	for (int i = 0; i < *n; i++)
	{
		cin >> Pro_Array[i].num;
		Pro_Array[i].finish_Flag = false;
	}
	cout << "��ֱ������� " << *n << " �����̴ﵽϵͳ��ʱ�̣����ո����֣�";
	for (int i = 0; i < *n; i++)
	{
		cin >> Pro_Array[i].enter_Tim;
		Pro_Array[i].start_Tim = -1;
	}

	cout << "��ֱ������� " << *n << " ��������Ҫ�ķ���ʱ�䣺���ո����֣�";
	for (int i = 0; i < *n; i++)
	{
		cin >> Pro_Array[i].sev_Tim;
		Pro_Array[i].save_Sev_Tim = Pro_Array[i].sev_Tim;
	}
	if (HPR_Flag == 1)
	{
		cout << "��ֱ������� " << *n << " ��������Ҫ�����ȼ������ո����֣�";
		for (int i = 0; i < *n; i++)
			cin >> Pro_Array[i].priority_Rank;
	}
}

void Print_Res(int* m, PCB*& Pro_Array)
{
	/* ���ģ��*/
	int n = *m;

	/* ���ģ��һ���� */
	cout << endl << "| ���̺�\t| ����ʱ��\t| ����ʱ��\t| ��ʼʱ��\t| ����ʱ��\t| ��תʱ��\t| ��Ȩ��תʱ��\t|" << endl;
	for (int i = 0; i < n; i++)
	{
		int cicle_Time = Pro_Array[i].over_Tim - Pro_Array[i].enter_Tim;	// ��תʱ��
		double carry_Weight_Cicle_Time = 1.0 * cicle_Time / Pro_Array[i].save_Sev_Tim;	// ��Ȩ��תʱ��
		cout.precision(4);
		cout << "| ����\t" << Pro_Array[i].num << "\t| " << Pro_Array[i].enter_Tim << "\t\t| " << Pro_Array[i].save_Sev_Tim\
			<< "\t\t| " << Pro_Array[i].start_Tim << "\t\t| " << Pro_Array[i].over_Tim << "\t\t| " << cicle_Time << "\t\t| "\
			<< carry_Weight_Cicle_Time << "\t\t|" << endl;
	}
	cout << endl;

	/* ���ģ������������� */
	/* [1]�����ÿ�����̵���תʱ�� */
	for (int i = 0; i < n; i++)
	{
		int cicle_Time = Pro_Array[i].over_Tim - Pro_Array[i].enter_Tim;
		cout << Pro_Array[i].num << "���̵���תʱ��Ϊ��" << cicle_Time << endl;
	}
	cout << endl;

	/* [2]�����ÿ�����̵Ĵ�Ȩ��תʱ�� */
	for (int i = 0; i < n; i++)
	{
		int cicle_Time = Pro_Array[i].over_Tim - Pro_Array[i].enter_Tim;
		int actual_execution_Time = Pro_Array[i].save_Sev_Tim;
		cout << Pro_Array[i].num << "���̵Ĵ�Ȩ��תʱ��Ϊ��" << 1.0 * cicle_Time / actual_execution_Time << endl;
	}
	cout << endl;

	/* [3]��������н��̵�ƽ����תʱ�� */
	int tol_Tim_1 = 0;
	for (int i = 0; i < n; i++)
	{
		int cicle_Time = Pro_Array[i].over_Tim - Pro_Array[i].enter_Tim;
		tol_Tim_1 += cicle_Time;
	}
	cout << "���н��̵�ƽ����תʱ��Ϊ��" << 1.0 / n * tol_Tim_1 << endl;
	cout << endl;

	/* [4]��������н��̵Ĵ�Ȩƽ����תʱ�� */
	double tol_Tim_2 = 0;
	for (int i = 0; i < n; i++)
	{
		int cicle_Time = Pro_Array[i].over_Tim - Pro_Array[i].enter_Tim;
		int actual_execution_Time = Pro_Array[i].save_Sev_Tim;
		tol_Tim_2 += 1.0 * cicle_Time / actual_execution_Time;
	}
	cout << "���н��̵Ĵ�Ȩƽ����תʱ��Ϊ��" << 1.0 / n * tol_Tim_2 << endl;
	cout << endl;
}

/*
* �����ȷ����㷨FCFS(First Come First Service)��
* �����ȳ���ֻ����һ��������������ҵ����ϵͳ��ʱ�䣬˭�ȵ����ȸ�˭�ṩ����
*/
void FCFS_Algorithm()		// �����ȷ����㷨 FCFS (First Come First Service)
{
	/* ����ģ�� */
	int n;
	PCB* Pro_Array = NULL;
	Init(&n, Pro_Array, 0);

	/* FCFS�㷨���ģ�� */
	int over_Job_Num = 0;
	int i = 0;	// ��ǰ���������±�
	int cur_Time = Pro_Array[i].enter_Tim;	// ��ǰʱ��, ��ʼ��Ϊ��һ�����̵Ŀ�ʼʱ��
	while (over_Job_Num < n)
	{
		if (Pro_Array[i].finish_Flag == false)	// ��ǰ���̻�δ������
		{
			Pro_Array[i].start_Tim = cur_Time;	// ��ʼʱ��
			Pro_Array[i].finish_Flag = true;	// �ȵ��ȷ���
			over_Job_Num++;
			Pro_Array[i].sev_Tim = 0;			// �ý�����Ҫ��ķ���ʱ������
			cur_Time += Pro_Array[i].save_Sev_Tim;	// ��ǰʱ������ƽ�
			Pro_Array[i].over_Tim = cur_Time;	// ��¼�ý��̵Ľ���ʱ��
		}
		i++;
	}

	/* ���ģ��*/
	Print_Res(&n, Pro_Array);

	delete[] Pro_Array;
	return;
}

/*
* �����ҵ�����㷨 SJF (Shortest Job First):������ռʽ���㷨��
* ������Ҳֻ����һ���������������̵�CPU��ִ��ʱ�䣬������ԽС�Ľ��̽������ȵõ�ϵͳ�ķ���
*/
int Find_Min_SevTime_Pro(int n, PCB* Pro_Array, int cur_Time)
{
	int i, ind, min_SevTime = 999999;
	for (i = 0; i < n; i++)
	{
		if (Pro_Array[i].enter_Tim > cur_Time)	// ������̶���û�н���ϵͳ, �򲻽��бȽ�(��ֱ������)
			continue;
		if (Pro_Array[i].finish_Flag == true)	// ��������Ѿ�ִ�й���, �򲻽��бȽ�(��ֱ������)
			continue;

		if (Pro_Array[i].sev_Tim < min_SevTime)
		{
			min_SevTime = Pro_Array[i].sev_Tim;
			ind = i;
		}
	}
	return ind;
}
void SJF_Algorithm()		// �����ҵ�����㷨 SJF (Shortest Job First)
{
	/* ����ģ�� */
	int n;
	PCB* Pro_Array = NULL;
	Init(&n, Pro_Array, 0);

	/* FCFS�㷨���ģ�� */
	int over_Job_Num = 0;
	int i = 0;	// ��ǰ���������±�
	int cur_Time = Pro_Array[i].enter_Tim;	// ��ǰʱ��, ��ʼ��Ϊ��һ�����̵Ŀ�ʼʱ��
	while (over_Job_Num < n)
	{
		if (Pro_Array[i].finish_Flag == false)	// ��ǰ���̻�δ������
		{
			int ind;
			ind = Find_Min_SevTime_Pro(n, Pro_Array, cur_Time);	 // �ҵ���������С�Ľ���(���ѵ���ϵͳ�Ľ�������)

			Pro_Array[ind].start_Tim = cur_Time;	// ��ʼʱ��
			Pro_Array[ind].finish_Flag = true;	// ������ý���
			over_Job_Num++;
			Pro_Array[ind].sev_Tim = 0;			// �ý�����Ҫ��ķ���ʱ������
			cur_Time += Pro_Array[ind].save_Sev_Tim;	// ��ǰʱ������ƽ�
			Pro_Array[ind].over_Tim = cur_Time;	// ��¼�ý��̵Ľ���ʱ��
		}
		i++;
		if (i == n)		// ����ѭ��
			i = 0;
	}

	/* ���ģ��*/
	Print_Res(&n, Pro_Array);

	delete[] Pro_Array;
	return;
}

/*
* ������ȼ����� HPR (Highest Priority First):
* ���ȳ���������ѡ���ȼ���ߵĽ��̻���ҵ�������������Դ��
*/
int Find_Max_Priority_Pro(int n, PCB* Pro_Array, int cur_Time)
{
	int i, ind, max_Pri_Rank = -999999;
	for (i = 0; i < n; i++)
	{
		if (Pro_Array[i].enter_Tim > cur_Time)	// ������̶���û�н���ϵͳ, �򲻽��бȽ�(��ֱ������)
			continue;
		if (Pro_Array[i].finish_Flag == true)	// ��������Ѿ�ִ�й���, �򲻽��бȽ�(��ֱ������)
			continue;

		if (Pro_Array[i].priority_Rank > max_Pri_Rank)
		{
			max_Pri_Rank = Pro_Array[i].priority_Rank;
			ind = i;
		}
	}
	return ind;
}
void HPF_Algorithm()		// ������ȼ����� HPR (Highest Priority First)
{
	/* ����ģ�� */
	int n;
	PCB* Pro_Array = NULL;
	Init(&n, Pro_Array, 1);

	/* HPR�㷨���ģ�� */
	int over_Job_Num = 0;
	int i = 0;	// ��ǰ���������±�
	int cur_Time = Pro_Array[i].enter_Tim;	// ��ǰʱ��, ��ʼ��Ϊ��һ�����̵Ŀ�ʼʱ��
	while (over_Job_Num < n)
	{
		if (Pro_Array[i].finish_Flag == false)	// ��ǰ���̻�δ������
		{
			int ind;
			ind = Find_Max_Priority_Pro(n, Pro_Array, cur_Time);	 // �ҵ�������ȼ��Ľ���(���ѵ���ϵͳ�Ľ�������)
			Pro_Array[ind].start_Tim = cur_Time;	// ��ʼʱ��
			Pro_Array[ind].finish_Flag = true;	// ������ý���
			over_Job_Num++;
			Pro_Array[ind].sev_Tim = 0;			// �ý�����Ҫ��ķ���ʱ������
			cur_Time += Pro_Array[ind].save_Sev_Tim;	// ��ǰʱ������ƽ�
			Pro_Array[ind].over_Tim = cur_Time;	// ��¼�ý��̵Ľ���ʱ��
		}
		i++;
		if (i == n)		// ����ѭ��
			i = 0;
	}

	/* ���ģ��*/
	Print_Res(&n, Pro_Array);

	delete[] Pro_Array;
	return;
}

/*
* �����Ӧ�������㷨 HRN (Highest Response Ratio Next):
* ���ȳ���������ѡ��Ӧ�����Ľ��̻���ҵ�������������Դ��
* ��Ӧ�ȼ��㹫ʽ = 1 + (��ҵ�ѵȴ�ʱ��/��ҵ��Ҫ�����ʱ��)
*/
int Find_Max_Response_Ratio_Pro(int n, PCB* Pro_Array, int cur_Time)
{
	int i, ind;
	double max_Pri_Rank = -999999;
	for (i = 0; i < n; i++)
	{
		if (Pro_Array[i].enter_Tim > cur_Time)	// ������̶���û�н���ϵͳ, �򲻽��бȽ�(��ֱ������)
			continue;
		if (Pro_Array[i].finish_Flag == true)	// ��������Ѿ�ִ�й���, �򲻽��бȽ�(��ֱ������)
			continue;

		int has_WaitTime = cur_Time - Pro_Array[i].enter_Tim;	// �ý����ѵȴ���ʱ��
		double response_Ratio = 1 + (1.0 * has_WaitTime / Pro_Array[i].sev_Tim);	// ��Ӧ�ȼ��㹫ʽ

		if (response_Ratio > max_Pri_Rank)
		{
			max_Pri_Rank = response_Ratio;
			ind = i;
		}
	}
	return ind;
}
void HRN_Algorithm()		// �����Ӧ�������㷨 HRN (Highest Response Ratio Next)
{
	/* ����ģ�� */
	int n;
	PCB* Pro_Array = NULL;
	Init(&n, Pro_Array, 0);

	/* HRN �㷨���ģ�� */
	int over_Job_Num = 0;
	int i = 0;	// ��ǰ���������±�
	int cur_Time = Pro_Array[i].enter_Tim;	// ��ǰʱ��, ��ʼ��Ϊ��һ�����̵Ŀ�ʼʱ��
	while (over_Job_Num < n)
	{
		if (Pro_Array[i].finish_Flag == false)	// ��ǰ���̻�δ������
		{
			int ind;
			ind = Find_Max_Response_Ratio_Pro(n, Pro_Array, cur_Time);	 // �ҵ������Ӧ�ȵĽ���(���ѵ���ϵͳ�Ľ�������)
			Pro_Array[ind].start_Tim = cur_Time;	// ��ʼʱ��
			Pro_Array[ind].finish_Flag = true;	// ������ý���
			over_Job_Num++;
			Pro_Array[ind].sev_Tim = 0;			// �ý�����Ҫ��ķ���ʱ������
			cur_Time += Pro_Array[ind].save_Sev_Tim;	// ��ǰʱ������ƽ�
			Pro_Array[ind].over_Tim = cur_Time;	// ��¼�ý��̵Ľ���ʱ��
		}
		i++;
		if (i == n)		// ����ѭ��
			i = 0;
	}

	/* ���ģ�� */
	Print_Res(&n, Pro_Array);

	delete[] Pro_Array;
	return;
}
