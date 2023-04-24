#include "basic.h"
#include <iostream>
#include <string>
using namespace std;
int n = 0;
pnode* proot; //system process tree root
pnode* plink; //system process link head
//create process

void show() {
	/* ���ģ��*/
	//int n = *m;
	pnode* p;
	p = (pnode*)malloc(100);
	p = plink->next;
	/* ���ģ��һ���� */
	//cout << endl << "| ���̺�\t| ����ʱ��\t| ����ʱ��\t| ��ʼʱ��\t| ����ʱ��\t| ��תʱ��\t| ��Ȩ��תʱ��\t|" << endl;
	for (; p;)
	{
		//cout << p->node->enter_time << endl;
		int cicle_Time = p->node->over_time - p->node->enter_time;	// ��תʱ��
		double carry_Weight_Cicle_Time = 1.0 * cicle_Time / p->node->save_sev_time;	// ��Ȩ��תʱ��
		cout.precision(4);
		//cout << "| ����\t" << p->node->pid << "\t " << p->node->enter_time << "\t\t  " << p->node->save_sev_time << "\t\t   " << p->node->start_time << "\t\t " << p->node->over_time << "\t\t " << cicle_Time << "\t\t " << carry_Weight_Cicle_Time << endl;
		//cout << "| ����\t" << p->node->pid <<" " << p->node->enter_time << " " << p->node->save_sev_time << " " << p->node->start_time << " " << p->node->over_time << " " << cicle_Time << " " << carry_Weight_Cicle_Time << endl;
		//cout << "| ����\t" << p->node->pid << "\t| " << p->node->enter_time << "\t\t| " << p->node->save_sev_time<< "\t\t| " << p->node->start_time << "\t\t| " << p->node->over_time << "\t\t| " << cicle_Time << "\t\t| "<< carry_Weight_Cicle_Time << "\t\t|" << endl;
		
		cout << "| ����\t" << p->node->pid << "  ����ʱ��:" << p->node->enter_time << "    ����ʱ��:" << p->node->save_sev_time;
		cout << "    ��ʼʱ��:" << p->node->start_time << " ";
		cout << "    ����ʱ��:" << p->node->over_time << " ";
		cout << "     ��תʱ��:" << cicle_Time << "   ��Ȩ��תʱ��:" << carry_Weight_Cicle_Time << endl;
		p->node->finish_Flag = false;
		p->node->sev_time = p->node->save_sev_time = p->node->old_sev_time;
		p = p->next;
	}
	cout << endl;
}
void FCFS_Algorithm()		// �����ȷ����㷨 FCFS (First Come First Service)
{
	/* ����ģ�� */
	//int n;
	//PCB* Pro_Array = NULL;
	//Init(&n, Pro_Array, 0);
	pnode* p, * p1;
	p = plink->next;
	p1 = plink->next;
	/* FCFS�㷨���ģ�� */
	int over_Job_Num = 0;
	int i = 0;	// ��ǰ���������±�
	int cur_Time = p->node->enter_time;	// ��ǰʱ��, ��ʼ��Ϊ��һ�����̵Ŀ�ʼʱ��
	//cout << "time:" << cur_Time;
	while (over_Job_Num < n)
	{
		if (p->node->finish_Flag == false)	// ��ǰ���̻�δ������
		{
			p->node->start_time = cur_Time;	// ��ʼʱ��
			p->node->finish_Flag = true;	// �ȵ��ȷ���
			over_Job_Num++;
			p->node->sev_time = 0;			// �ý�����Ҫ��ķ���ʱ������
			cur_Time += p->node->save_sev_time;	// ��ǰʱ������ƽ�
			p->node->over_time = cur_Time;	// ��¼�ý��̵Ľ���ʱ��
		}
		p = p->next;
	}

	/* ���ģ��*/
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
	/* HPR�㷨���ģ�� */
	int over_Job_Num = 0;
	int i = 0;	// ��ǰ���������±�
	int cur_Time = p->node->enter_time;	// ��ǰʱ��, ��ʼ��Ϊ��һ�����̵Ŀ�ʼʱ��
	while (over_Job_Num < n)
	{
		//cout << i << endl;
		if (p->node->finish_Flag == false)	// ��ǰ���̻�δ������
		{
			//int ind;
			//ind = Find_Max_Priority_Pro(n, Pro_Array, cur_Time);	 // �ҵ�������ȼ��Ľ���(���ѵ���ϵͳ�Ľ�������)
			//cout << p->node->enter_time << endl;
			int j, ind, max_Pri_Rank = -999999;
			p2 = plink->next;
			//cout <<"ͷ"<< plink->node->pid << endl;
			for (j = 0; j < n; j++)
			{
				if (p2->node->enter_time > cur_Time)	// ������̶���û�н���ϵͳ, �򲻽��бȽ�(��ֱ������)
				{
					if (j == n - 1)
					{
						
					}
					continue;
				}
					
				if (p2->node->finish_Flag == true)	// ��������Ѿ�ִ�й���, �򲻽��бȽ�(��ֱ������)
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

			p1->node->start_time = cur_Time;	// ��ʼʱ��
			
			p1->node->finish_Flag = true;	// ������ý���
			over_Job_Num++;
			p1->node->sev_time = 0;			// �ý�����Ҫ��ķ���ʱ������
			cur_Time += p1->node->save_sev_time;	// ��ǰʱ������ƽ�
			p1->node->over_time = cur_Time;	// ��¼�ý��̵Ľ���ʱ��
		}
		i++;
		p = p->next;
		if (i == n)		// ����ѭ��
		{
			p = plink->next;
			i = 0;
		}
	}

	/* ���ģ��*/
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
	cout <<"��ǰ�Ľ�����"<< n << endl;
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
			cout <<"�����ȷ����㷨:" << endl;
			FCFS_Algorithm();
			cout << "������ȼ������㷨:" << endl;
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






	

