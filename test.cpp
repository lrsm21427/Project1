#include <iostream>
#include <string>
using namespace std;

/*
* 设计要求：
* [1] 设计可用于该实验的进程控制块，进程控制块至少包括 进程号、状态(进入时间+优先级) 和 要求服务时间
*
* [2] 动态或静态创建多个进程
*
* [3] 模拟操作系统四种进程调度算法：先进先出、短作业优先、高优先级优先、高相应比优先中的任意两种
*
* [4] 调度所创建的进程并显示调度结果
*/

typedef struct Process_Control_Block
{
	int num;
	int enter_Tim;
	int start_Tim;
	int sev_Tim;
	int save_Sev_Tim;
	int over_Tim;
	int priority_Rank;		// 优先级
	bool finish_Flag;		// 是否以服务完的标志
}PCB;

void FCFS_Algorithm();		// 先来先服务算法 FCFS (First Come First Service)
void SJF_Algorithm();		// 最短作业优先算法 SJF (Shortest Job First)
void HPF_Algorithm();		// 最高优先级优先算法 HPR (Highest Priority First)
void HRN_Algorithm();		// 最高响应比优先算法 HRN (Highest Response Ratio Next)
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
		cout << "请选择要实现的算法：";
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
	/* 输入模块 */
	cout << "+---------------------------------------+" << endl;
	cout << "|\t>>> 算法清单 <<<\t\t|" << endl;
	cout << "|\t1.先来先服务算法(FCFS)\t\t|" << endl << "|\t2.最短作业优先算法(SJF)\t\t|" << endl;
	cout << "|\t3.最高优先级优先算法(HPR)\t|" << endl << "|\t4.最高响应比优先算法(HRN)\t|" << endl;
	cout << "|\t0.退出\t\t\t\t|" << endl;
	cout << "+---------------------------------------+" << endl;
}

void Init(int* n, PCB*& Pro_Array, int HPR_Flag)
{
	cout << "请输入在单道环境下，需调度的作业个数 n 为：";
	cin >> *n;
	Pro_Array = new PCB[*n];

	cout << "请分别输入这 " << *n << " 个进程的进程号：（空格区分）";
	for (int i = 0; i < *n; i++)
	{
		cin >> Pro_Array[i].num;
		Pro_Array[i].finish_Flag = false;
	}
	cout << "请分别输入这 " << *n << " 个进程达到系统的时刻：（空格区分）";
	for (int i = 0; i < *n; i++)
	{
		cin >> Pro_Array[i].enter_Tim;
		Pro_Array[i].start_Tim = -1;
	}

	cout << "请分别输入这 " << *n << " 个进程需要的服务时间：（空格区分）";
	for (int i = 0; i < *n; i++)
	{
		cin >> Pro_Array[i].sev_Tim;
		Pro_Array[i].save_Sev_Tim = Pro_Array[i].sev_Tim;
	}
	if (HPR_Flag == 1)
	{
		cout << "请分别输入这 " << *n << " 个进程需要的优先级：（空格区分）";
		for (int i = 0; i < *n; i++)
			cin >> Pro_Array[i].priority_Rank;
	}
}

void Print_Res(int* m, PCB*& Pro_Array)
{
	/* 输出模块*/
	int n = *m;

	/* 输出模块一：表 */
	cout << endl << "| 进程号\t| 进入时间\t| 服务时间\t| 开始时间\t| 结束时间\t| 周转时间\t| 带权周转时间\t|" << endl;
	for (int i = 0; i < n; i++)
	{
		int cicle_Time = Pro_Array[i].over_Tim - Pro_Array[i].enter_Tim;	// 周转时间
		double carry_Weight_Cicle_Time = 1.0 * cicle_Time / Pro_Array[i].save_Sev_Tim;	// 带权周转时间
		cout.precision(4);
		cout << "| 进程\t" << Pro_Array[i].num << "\t| " << Pro_Array[i].enter_Tim << "\t\t| " << Pro_Array[i].save_Sev_Tim\
			<< "\t\t| " << Pro_Array[i].start_Tim << "\t\t| " << Pro_Array[i].over_Tim << "\t\t| " << cicle_Time << "\t\t| "\
			<< carry_Weight_Cicle_Time << "\t\t|" << endl;
	}
	cout << endl;

	/* 输出模块二：其他内容 */
	/* [1]输出：每个进程的周转时间 */
	for (int i = 0; i < n; i++)
	{
		int cicle_Time = Pro_Array[i].over_Tim - Pro_Array[i].enter_Tim;
		cout << Pro_Array[i].num << "进程的周转时间为：" << cicle_Time << endl;
	}
	cout << endl;

	/* [2]输出：每个进程的带权周转时间 */
	for (int i = 0; i < n; i++)
	{
		int cicle_Time = Pro_Array[i].over_Tim - Pro_Array[i].enter_Tim;
		int actual_execution_Time = Pro_Array[i].save_Sev_Tim;
		cout << Pro_Array[i].num << "进程的带权周转时间为：" << 1.0 * cicle_Time / actual_execution_Time << endl;
	}
	cout << endl;

	/* [3]输出：所有进程的平均周转时间 */
	int tol_Tim_1 = 0;
	for (int i = 0; i < n; i++)
	{
		int cicle_Time = Pro_Array[i].over_Tim - Pro_Array[i].enter_Tim;
		tol_Tim_1 += cicle_Time;
	}
	cout << "所有进程的平均周转时间为：" << 1.0 / n * tol_Tim_1 << endl;
	cout << endl;

	/* [4]输出：所有进程的带权平均周转时间 */
	double tol_Tim_2 = 0;
	for (int i = 0; i < n; i++)
	{
		int cicle_Time = Pro_Array[i].over_Tim - Pro_Array[i].enter_Tim;
		int actual_execution_Time = Pro_Array[i].save_Sev_Tim;
		tol_Tim_2 += 1.0 * cicle_Time / actual_execution_Time;
	}
	cout << "所有进程的带权平均周转时间为：" << 1.0 / n * tol_Tim_2 << endl;
	cout << endl;
}

/*
* 先来先服务算法FCFS(First Come First Service)：
* 即调度程序只靠率一个参数———作业到达系统的时间，谁先到就先给谁提供服务。
*/
void FCFS_Algorithm()		// 先来先服务算法 FCFS (First Come First Service)
{
	/* 输入模块 */
	int n;
	PCB* Pro_Array = NULL;
	Init(&n, Pro_Array, 0);

	/* FCFS算法设计模块 */
	int over_Job_Num = 0;
	int i = 0;	// 当前服务对象的下标
	int cur_Time = Pro_Array[i].enter_Tim;	// 当前时刻, 初始化为第一个进程的开始时刻
	while (over_Job_Num < n)
	{
		if (Pro_Array[i].finish_Flag == false)	// 当前进程还未服务完
		{
			Pro_Array[i].start_Tim = cur_Time;	// 开始时间
			Pro_Array[i].finish_Flag = true;	// 先到先服务
			over_Job_Num++;
			Pro_Array[i].sev_Tim = 0;			// 该进程所要求的服务时间清零
			cur_Time += Pro_Array[i].save_Sev_Tim;	// 当前时间向后推进
			Pro_Array[i].over_Tim = cur_Time;	// 记录该进程的结束时间
		}
		i++;
	}

	/* 输出模块*/
	Print_Res(&n, Pro_Array);

	delete[] Pro_Array;
	return;
}

/*
* 最短作业优先算法 SJF (Shortest Job First):【非抢占式的算法】
* 即我们也只考虑一个参数———进程的CPU的执行时间，计算量越小的进程将会优先得到系统的服务。
*/
int Find_Min_SevTime_Pro(int n, PCB* Pro_Array, int cur_Time)
{
	int i, ind, min_SevTime = 999999;
	for (i = 0; i < n; i++)
	{
		if (Pro_Array[i].enter_Tim > cur_Time)	// 如果进程都还没有进入系统, 则不进行比较(即直接跳过)
			continue;
		if (Pro_Array[i].finish_Flag == true)	// 如果进程已经执行过了, 则不进行比较(即直接跳过)
			continue;

		if (Pro_Array[i].sev_Tim < min_SevTime)
		{
			min_SevTime = Pro_Array[i].sev_Tim;
			ind = i;
		}
	}
	return ind;
}
void SJF_Algorithm()		// 最短作业优先算法 SJF (Shortest Job First)
{
	/* 输入模块 */
	int n;
	PCB* Pro_Array = NULL;
	Init(&n, Pro_Array, 0);

	/* FCFS算法设计模块 */
	int over_Job_Num = 0;
	int i = 0;	// 当前服务对象的下标
	int cur_Time = Pro_Array[i].enter_Tim;	// 当前时刻, 初始化为第一个进程的开始时刻
	while (over_Job_Num < n)
	{
		if (Pro_Array[i].finish_Flag == false)	// 当前进程还未服务完
		{
			int ind;
			ind = Find_Min_SevTime_Pro(n, Pro_Array, cur_Time);	 // 找到计算量最小的进程(在已到达系统的进程中找)

			Pro_Array[ind].start_Tim = cur_Time;	// 开始时间
			Pro_Array[ind].finish_Flag = true;	// 处理完该进程
			over_Job_Num++;
			Pro_Array[ind].sev_Tim = 0;			// 该进程所要求的服务时间清零
			cur_Time += Pro_Array[ind].save_Sev_Tim;	// 当前时间向后推进
			Pro_Array[ind].over_Tim = cur_Time;	// 记录该进程的结束时间
		}
		i++;
		if (i == n)		// 设置循环
			i = 0;
	}

	/* 输出模块*/
	Print_Res(&n, Pro_Array);

	delete[] Pro_Array;
	return;
}

/*
* 最高优先级优先 HPR (Highest Priority First):
* 调度程序总是挑选优先级最高的进程或作业，并分配给其资源。
*/
int Find_Max_Priority_Pro(int n, PCB* Pro_Array, int cur_Time)
{
	int i, ind, max_Pri_Rank = -999999;
	for (i = 0; i < n; i++)
	{
		if (Pro_Array[i].enter_Tim > cur_Time)	// 如果进程都还没有进入系统, 则不进行比较(即直接跳过)
			continue;
		if (Pro_Array[i].finish_Flag == true)	// 如果进程已经执行过了, 则不进行比较(即直接跳过)
			continue;

		if (Pro_Array[i].priority_Rank > max_Pri_Rank)
		{
			max_Pri_Rank = Pro_Array[i].priority_Rank;
			ind = i;
		}
	}
	return ind;
}
void HPF_Algorithm()		// 最高优先级优先 HPR (Highest Priority First)
{
	/* 输入模块 */
	int n;
	PCB* Pro_Array = NULL;
	Init(&n, Pro_Array, 1);

	/* HPR算法设计模块 */
	int over_Job_Num = 0;
	int i = 0;	// 当前服务对象的下标
	int cur_Time = Pro_Array[i].enter_Tim;	// 当前时刻, 初始化为第一个进程的开始时刻
	while (over_Job_Num < n)
	{
		if (Pro_Array[i].finish_Flag == false)	// 当前进程还未服务完
		{
			int ind;
			ind = Find_Max_Priority_Pro(n, Pro_Array, cur_Time);	 // 找到最高优先级的进程(在已到达系统的进程中找)
			Pro_Array[ind].start_Tim = cur_Time;	// 开始时间
			Pro_Array[ind].finish_Flag = true;	// 处理完该进程
			over_Job_Num++;
			Pro_Array[ind].sev_Tim = 0;			// 该进程所要求的服务时间清零
			cur_Time += Pro_Array[ind].save_Sev_Tim;	// 当前时间向后推进
			Pro_Array[ind].over_Tim = cur_Time;	// 记录该进程的结束时间
		}
		i++;
		if (i == n)		// 设置循环
			i = 0;
	}

	/* 输出模块*/
	Print_Res(&n, Pro_Array);

	delete[] Pro_Array;
	return;
}

/*
* 最高响应比优先算法 HRN (Highest Response Ratio Next):
* 调度程序总是挑选响应比最大的进程或作业，并分配给其资源。
* 响应比计算公式 = 1 + (作业已等待时间/作业需要处理的时间)
*/
int Find_Max_Response_Ratio_Pro(int n, PCB* Pro_Array, int cur_Time)
{
	int i, ind;
	double max_Pri_Rank = -999999;
	for (i = 0; i < n; i++)
	{
		if (Pro_Array[i].enter_Tim > cur_Time)	// 如果进程都还没有进入系统, 则不进行比较(即直接跳过)
			continue;
		if (Pro_Array[i].finish_Flag == true)	// 如果进程已经执行过了, 则不进行比较(即直接跳过)
			continue;

		int has_WaitTime = cur_Time - Pro_Array[i].enter_Tim;	// 该进程已等待的时间
		double response_Ratio = 1 + (1.0 * has_WaitTime / Pro_Array[i].sev_Tim);	// 响应比计算公式

		if (response_Ratio > max_Pri_Rank)
		{
			max_Pri_Rank = response_Ratio;
			ind = i;
		}
	}
	return ind;
}
void HRN_Algorithm()		// 最高响应比优先算法 HRN (Highest Response Ratio Next)
{
	/* 输入模块 */
	int n;
	PCB* Pro_Array = NULL;
	Init(&n, Pro_Array, 0);

	/* HRN 算法设计模块 */
	int over_Job_Num = 0;
	int i = 0;	// 当前服务对象的下标
	int cur_Time = Pro_Array[i].enter_Tim;	// 当前时刻, 初始化为第一个进程的开始时刻
	while (over_Job_Num < n)
	{
		if (Pro_Array[i].finish_Flag == false)	// 当前进程还未服务完
		{
			int ind;
			ind = Find_Max_Response_Ratio_Pro(n, Pro_Array, cur_Time);	 // 找到最大响应比的进程(在已到达系统的进程中找)
			Pro_Array[ind].start_Tim = cur_Time;	// 开始时间
			Pro_Array[ind].finish_Flag = true;	// 处理完该进程
			over_Job_Num++;
			Pro_Array[ind].sev_Tim = 0;			// 该进程所要求的服务时间清零
			cur_Time += Pro_Array[ind].save_Sev_Tim;	// 当前时间向后推进
			Pro_Array[ind].over_Tim = cur_Time;	// 记录该进程的结束时间
		}
		i++;
		if (i == n)		// 设置循环
			i = 0;
	}

	/* 输出模块 */
	Print_Res(&n, Pro_Array);

	delete[] Pro_Array;
	return;
}
