#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct process
{
	int pid;

	int at;
	int bt;
	int rem_bt;

	int wt;
};

void getInput(struct process procs[],int n)
{
	int i;
	for (i = 0; i < n; ++i)
	{
		procs[i].pid = i+1;
		printf("Enter Details for process %d\n",i+1);
		printf("Arrival time: ");
		scanf("%d",&procs[i].at);
		printf("Burst time : ");
		scanf("%d",&procs[i].bt);
		procs[i].rem_bt = procs[i].bt;
	}
}

int byAT_in(const void *a, const void *b)
{
	int l = ((struct process*)a)->at;
	int r = ((struct process*)b)->at;
	int lp = ((struct process*)a)->pid;
	int rp = ((struct process*)b)->pid;
	if(l - r != 0)
		return l - r;
	else
		return lp - rp;
	// increasing order
}

int byBT_in(const void *a, const void *b)
{
	int l = ((struct process*)a)->bt;
	int r = ((struct process*)b)->bt;
	int lp = ((struct process*)a)->pid;
	int rp = ((struct process*)b)->pid;

	if (l - r != 0 )
		return l - r;
	else
		return lp - rp;
}

int byID_in(const void *a, const void *b)
{
	int lp = ((struct process*)a)->pid;
	int rp = ((struct process*)b)->pid;

	return lp - rp;
}


void printTable(struct process procs[],int n)
{
	qsort(procs,n,sizeof(struct process),byID_in);
	int i,avg_wait=0,avg_tat=0;
	printf("\n%10s | %10s | %10s | %10s | %10s","P.NO.","ARRIVAL","BURST","WAIT","TAT");
	printf("\n------------------------------------------------------------------");
	for(i = 0; i < n ; i++)
		printf("\n%10d | %10d | %10d | %10d | %10d",procs[i].pid,procs[i].at,procs[i].bt,procs[i].wt,procs[i].wt+procs[i].bt);

	for (i = 0; i < n; ++i)
	{
		avg_tat += procs[i].bt+procs[i].wt;
		avg_wait += procs[i].wt;
	}
	printf("\nAverage Wait Time is : %f\n",((float)avg_wait)/(float)n);
	printf("Average Turn Around Time is :%f\n", ((float)avg_tat)/(float)n);
}

void FCFS(struct process procs[],int n)
{
	qsort(procs,n,sizeof(struct process),byAT_in);
	int i;
	procs[0].wt = 0;

	// wt[i] = wt[i-1] + bt[i-1]
	for (i = 1; i < n; ++i)
		procs[i].wt = procs[i-1].wt + procs[i-1].bt;

	printf("FCFS :\n");
	printTable(procs,n);
}

void RR(struct process procs[],int n)
{
	int i;
	int t_elapsed = 0;
	int quantum;
	printf("Enter Time quantum : ");
	scanf("%d",&quantum);

	// flag == 1 implies there are processes which have non-zero rem_bt
	// flag == 0 implies all processes are done.
	int flag = 1;
	while(flag == 1)
	{
		flag = 0;
		for (i = 0; i < n ; ++i)
		{
			if(procs[i].rem_bt > 0)
			{
				flag = 1;
				if (procs[i].rem_bt > quantum)
				{
					t_elapsed += quantum;
					procs[i].rem_bt -= quantum;
				}
				else
				{
					t_elapsed += procs[i].rem_bt;
					// This block will be visited exactly ONCE
					// for each pid
					// so at this moment is t_elapsed = TAT
					procs[i].wt = t_elapsed - procs[i].bt;
					procs[i].rem_bt = 0;
				}
			}
		}
	}

	printf("Round Robin :\n");
	printTable(procs,n);
}

void SJF(struct process procs[],int n)
{
	int i;
	qsort(procs,n,sizeof(struct process),byBT_in);

	// SJF has to be non-pre-emptive...pre-emptive SJF is SRTF

	// waiting time
	procs[0].wt = 0;

	for (i = 1; i < n; ++i)
		procs[i].wt = procs[i-1].wt + procs[i-1].bt;

	printf("Shortest Job First:\n");
	printTable(procs,n);
}
void SRTF(struct process procs[],int n)
{
	int clk = 0;
	int smallest,i;
	int num_cmplt = 0;
	struct process procs_cpy[n+1];
	
	for (int i = 0; i < n; ++i)
		procs_cpy[i] = procs[i];

	// Adding sentinel - largest burst time and last arrival time.
	procs_cpy[n].pid = n+1;
	procs_cpy[n].rem_bt = INT_MAX;
	procs_cpy[n].at = INT_MAX;

	while(num_cmplt < n)
	{
		clk++;
		smallest = n;
		for (i = 0; i < n; ++i)
		{
			if((procs_cpy[i].rem_bt > 0) && (procs_cpy[i].at <= clk) && (procs_cpy[i].rem_bt < procs_cpy[smallest].rem_bt))
				smallest = i;
		}
		procs_cpy[smallest].rem_bt--;
		if (procs_cpy[smallest].rem_bt == 0)
		{
			// process done
			num_cmplt++;
			procs_cpy[smallest].wt = clk - procs_cpy[smallest].bt;
		}
	}

	printf("Shortest Remaining Time First:\n");
	// print only 0..n-1 elements as n is sentinel
	printTable(procs_cpy,n);
}
void LRTF(struct process procs[],int n)
{
	int clk = 0;
	int largest,i;
	int num_cmplt = 0;
	struct process procs_cpy[n+1];

	for (int i = 0; i < n; ++i)
		procs_cpy[i] = procs[i];

	// Adding sentinel - largest burst time and last arrival time.
	procs_cpy[n].pid = n+1;
	procs_cpy[n].rem_bt = INT_MIN;
	procs_cpy[n].at = INT_MIN;

	while(num_cmplt < n)
	{
		clk++;
		largest = n;
		for (i = 0; i < n; ++i)
		{
			if(procs_cpy[i].rem_bt > 0 && procs_cpy[i].at <= clk && procs_cpy[i].rem_bt > procs_cpy[largest].rem_bt)
				largest = i;
		}
		procs_cpy[largest].rem_bt--;

		if (procs_cpy[largest].rem_bt == 0)
		{
			// process done
			num_cmplt++;
			procs_cpy[largest].wt = clk - procs_cpy[largest].bt;
		}
	}

	printf("Largest Remaining Time First:\n");
	// print only 0..n-1 elements as n is sentinel
	printTable(procs_cpy,n);
}
