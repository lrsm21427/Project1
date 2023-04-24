#include "basic.h"
#include <iostream>
#include <string>
using namespace std;
int n = 0;
pnode* proot; //system process tree root
pnode* plink; //system process link head
//create process

void show() {
	/* 输出模块*/
	//int n = *m;
	pnode* p;
	p = (pnode*)malloc(100);
	p = plink->next;
	/* 输出模块一：表 */
	//cout << endl << "| 进程号\t| 进入时间\t| 服务时间\t| 开始时间\t| 结束时间\t| 周转时间\t| 带权周转时间\t|" << endl;
	for (; p;)
	{
		//cout << p->node->enter_time << endl;
		int cicle_Time = p->node->over_time - p->node->enter_time;	// 周转时间
		double carry_Weight_Cicle_Time = 1.0 * cicle_Time / p->node->save_sev_time;	// 带权周转时间
		cout.precision(4);
		//cout << "| 进程\t" << p->node->pid << "\t " << p->node->enter_time << "\t\t  " << p->node->save_sev_time << "\t\t   " << p->node->start_time << "\t\t " << p->node->over_time << "\t\t " << cicle_Time << "\t\t " << carry_Weight_Cicle_Time << endl;
		//cout << "| 进程\t" << p->node->pid <<" " << p->node->enter_time << " " << p->node->save_sev_time << " " << p->node->start_time << " " << p->node->over_time << " " << cicle_Time << " " << carry_Weight_Cicle_Time << endl;
		//cout << "| 进程\t" << p->node->pid << "\t| " << p->node->enter_time << "\t\t| " << p->node->save_sev_time<< "\t\t| " << p->node->start_time << "\t\t| " << p->node->over_time << "\t\t| " << cicle_Time << "\t\t| "<< carry_Weight_Cicle_Time << "\t\t|" << endl;
		
		cout << "| 进程\t" << p->node->pid << "  进入时间:" << p->node->enter_time << "    服务时间:" << p->node->save_sev_time;
		cout << "    开始时间:" << p->node->start_time << " ";
		cout << "    结束时间:" << p->node->over_time << " ";
		cout << "     周转时间:" << cicle_Time << "   带权周转时间:" << carry_Weight_Cicle_Time << endl;
		p->node->finish_Flag = false;
		p->node->sev_time = p->node->save_sev_time = p->node->old_sev_time;
		p = p->next;
	}
	cout << endl;
}
void FCFS_Algorithm()		// 先来先服务算法 FCFS (First Come First Service)
{
	/* 输入模块 */
	//int n;
	//PCB* Pro_Array = NULL;
	//Init(&n, Pro_Array, 0);
	pnode* p, * p1;
	p = plink->next;
	p1 = plink->next;
	/* FCFS算法设计模块 */
	int over_Job_Num = 0;
	int i = 0;	// 当前服务对象的下标
	int cur_Time = p->node->enter_time;	// 当前时刻, 初始化为第一个进程的开始时刻
	//cout << "time:" << cur_Time;
	while (over_Job_Num < n)
	{
		if (p->node->finish_Flag == false)	// 当前进程还未服务完
		{
			p->node->start_time = cur_Time;	// 开始时间
			p->node->finish_Flag = true;	// 先到先服务
			over_Job_Num++;
			p->node->sev_time = 0;			// 该进程所要求的服务时间清零
			cur_Time += p->node->save_sev_time;	// 当前时间向后推进
			p->node->over_time = cur_Time;	// 记录该进程的结束时间
		}
		p = p->next;
	}

	/* 输出模块*/
	//Print_Res(&n, Pro_Array);
     show();
	//p->node->finish_Flag == false;
	//delete[] Pro_Array;
	return;
}
void hpr() {
	pnode* p, * p1, * p2,*p3;
	p= (pnode*)malloc(100);
	p1 = (pnode*)malloc(100);
	p1 = NULL;
	p2 = (pnode*)malloc(100);
	p3 = (pnode*)malloc(100);
	p = plink->next;
	p3 = plink->next;
	/* HPR算法设计模块 */
	int over_Job_Num = 0;
	int i = 0;	// 当前服务对象的下标
	int cur_Time = p->node->enter_time;	// 当前时刻, 初始化为第一个进程的开始时刻
	while (over_Job_Num < n)
	{
		//cout << i << endl;
		if (p->node->finish_Flag == false)	// 当前进程还未服务完
		{
			//int ind;
			//ind = Find_Max_Priority_Pro(n, Pro_Array, cur_Time);	 // 找到最高优先级的进程(在已到达系统的进程中找)
			//cout << p->node->enter_time << endl;
			int j, ind, max_Pri_Rank = -999999;
			p2 = plink->next;
			//cout <<"头"<< plink->node->pid << endl;
			for (j = 0; j < n; j++)
			{
				if (p2->node->enter_time > cur_Time)	// 如果进程都还没有进入系统, 则不进行比较(即直接跳过)
				{
					if (j == n - 1)
					{
						
					}
					continue;
				}
					
				if (p2->node->finish_Flag == true)	// 如果进程已经执行过了, 则不进行比较(即直接跳过)
				{
					if (j == n - 1)
					{
					
					}
					continue;
				}
					//continue;

				if (p2->node->prio > max_Pri_Rank)
				{
					max_Pri_Rank = p2->node->prio;
					p1 = p2;
					if (j == n - 1)
					{
						
					}
					//cout <<"id"<< p2->node->pid << endl;
					//cout <<"id"<< p1->node->pid << endl;
				}
				p2 = p2->next;
			}

			p1->node->start_time = cur_Time;	// 开始时间
			
			p1->node->finish_Flag = true;	// 处理完该进程
			over_Job_Num++;
			p1->node->sev_time = 0;			// 该进程所要求的服务时间清零
			cur_Time += p1->node->save_sev_time;	// 当前时间向后推进
			p1->node->over_time = cur_Time;	// 记录该进程的结束时间
		}
		i++;
		p = p->next;
		if (i == n)		// 设置循环
		{
			p = plink->next;
			i = 0;
		}
	}

	/* 输出模块*/
	//Print_Res(&n, Pro_Array);

	//delete[] ;
	
	show();
	return;
}
int createpc(int* para)
{
	//add your code here
	pnode* p, * p1, * pp = NULL;
	int pflag;
	pflag = 0;
	for (p = plink; p; p = p->next)
	{
		if (p->node->pid == para[0]) //check if this pid is already exist
		{
			printf("pid %d is already exist!\n", para[0]);
			return -1;
		}
		if (p->node->pid == para[1]) //find parent pcb
		{
			pflag = 1;
			pp = p;
		}
	}
	if (!pflag)
	{
		printf("parent id %d is not exist!\n", para[1]);
		return -2;
	}
	//init new pcb
	p1 = new pnode;
	p1->node = new pcb;
	p1->node->pid = para[0];
	p1->node->ppid = para[1];
	p1->node->prio = para[2];
	p1->node->enter_time = para[3];
	p1->node->sev_time = para[4];
	p1->node->save_sev_time = para[4];
	p1->node->old_sev_time = para[4];
	p1->node->finish_Flag = false;
	p1->sub = NULL;
	p1->next = NULL;
	p1->brother = NULL;
	//add to process tree
	if (!pp->sub)
		pp->sub = p1;
	else
	{
		for (p = pp->sub; p->brother; p = p->brother);
		p->brother = p1;
	}
	// add to process link
	for (p = plink; p->next; p = p->next);
	p->next = p1;
	n++;
	return 0;
}

//show process detail
void showdetail()
{
	//add your code here
	//FCFS_Algorithm();
	//hpr();
	pnode* p, * p1;
	p = (pnode*)malloc(100);
	p1 = (pnode*)malloc(100);
	p = plink;
	cout <<"当前的进程数"<< n << endl;
	for (; p;) //print all pcb info
	{
		printf("%d(prio %d enter_time %d sev_time %d): ", p->node->pid, p->node->prio, p->node->enter_time ,p->node->old_sev_time);
		p1 = p->sub;
		for (; p1;) //print sub pcb
		{
			printf("%d(prio %d enter_time %d sev_time %d) ", p1->node->pid, p1->node->prio,p1->node->enter_time, p1->node->old_sev_time);
			p1 = p1->brother;
		}
		printf("\n");
		p = p->next;
	}
	printf("\n");




}

void deletepc(pnode* parent, pnode* currect) //delete process 
{
	if (currect->sub == NULL) //if the sub of the process which will be delete is NULL
	{
		if (parent->sub == currect)
		{
			parent->sub = currect->brother;
		}
		else
		{
			pnode* p = NULL;
			for (pnode* p = parent->sub; p->brother != currect; p = p->brother);
			p->brother = currect->brother;
		}
		pnode* tempperent;
		for (tempperent = plink; tempperent; tempperent = tempperent->next) //delete the process from the plink
		{
			
			if (tempperent->next->node->pid == currect->node->pid)
			{
				n--;
				tempperent->next = tempperent->next->next;
				break;
			}
		}
	}
	else //recursion transfer
	{
		deletepc(currect, currect->sub);
		deletepc(parent, currect);
		
	}
}
//don't change
int main()
{
	initerror();
	short cflag, pflag;
	char cmdstr[32];
	proot = new pnode;
	proot->node = new pcb;
	proot->node->pid = 0;
	proot->node->ppid = -1;
	proot->node->prio = 0;
	proot->node->enter_time = 0;
	proot->node->sev_time = 0;
	proot->node->old_sev_time = 0;
	proot->next = NULL;
	proot->sub = NULL;
	proot->brother = NULL;
	plink = proot;
	for (;;)
	{
		cflag = 0; pflag = 0;
		printf("cmd:");
		cin >> cmdstr;
		if (!strcmp(cmdstr, "exit")) //exit the program
			break;
		if (!strcmp(cmdstr, "showdetail"))
		{
			cflag = 1;
			pflag = 1;
			showdetail();
		}
		else if (!strcmp(cmdstr, "dispatch")) {
			cout <<"先来先服务算法:" << endl;
			FCFS_Algorithm();
			cout << "最高优先级优先算法:" << endl;
			hpr();
			cflag = 1;
			pflag = 1;
		}
		else
		{
			int* para;
			char* s, * s1,*s2;
			s = strstr(cmdstr, "createpc"); //create process
			s2 = strstr(cmdstr, "deletepc"); //delete process
			if (s)
			{
				cflag = 1;
				para = (int*)malloc(5);
				//getparameter
				s1 = substr(s, instr(s, '(') + 1, strlen(s) - 2); //get param string
				para = stroarray(s1); //get parameter
				createpc(para); //create process
				pflag = 1;
			}
			else if (s2)
			{
				cflag = 1;
				para = (int*)malloc(2);
				//getparameter
				s1 = substr(s2, instr(s2, '(') + 1, strlen(s2) - 2); //get param string
				para = stroarray(s1); //get parameter
				pnode* pp = plink;
				pnode* pc = plink;
				pnode* p, * p1;
				bool findflag = false;
				for (p = plink; p; p = p->next)
				{
					if ((p->node->pid) == para[0]) //search the process which will be delete from plink
					{
						for (p1 = plink; p1; p1 = p1->next)
						{
							if ((p1->node->pid) == p->node->ppid) //search the parent process
							{
								pp = p1;
								pc = p;
								break;
							}
						}

						findflag = true;
						break;

					}
				}
				if (findflag)
				{
					if (pp == pc) //if the process will be delete is 0 process
					{
						printf("you cann't delete the 0 process!\n");
					}
					else
						deletepc(pp, pc); //delete process
				}
				else
					geterror(2);

				pflag = 1;
			}
		}
		if (!cflag)
			geterror(0);
		else if (!pflag)
			geterror(1);
	}
    return 0;
}






	

