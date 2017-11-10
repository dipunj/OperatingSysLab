#include <stdio.h>
#include <string.h>
#include "sched_algo.h"
// FCFS with arrival time

int main(int argc, char const *argv[])
{
	int n,op;
	printf("Enter the number of processes : ");
	scanf("%d",&n);

	struct process procs[n],procs_bak[n];
	getInput(procs,n);
	for (int i = 0; i < n; ++i)
		procs_bak[i] = procs[i];
	for(;;)
	{
		printf("What algo do you want to use?\n\t1.FCFS\n\t2.RR\n\t3.SJF\n\t4.SRTF\n\t5.LRTF\n");
		scanf("%d",&op);
		switch(op)
		{
			case 1:
			{
				FCFS(procs,n);
				break;
			}
			case 2:
			{	RR(procs,n);
				break;
			}
			case 3:
			{	SJF(procs,n);
				break;
			}
			case 4:
			{	SRTF(procs,n);
				break;
			}
			case 5:
			{
				LRTF(procs,n);
				break;
			}
			
		}
		
	for (int i = 0; i < n; ++i)
		procs[i] = procs_bak[i];
	}
	return 0;
}