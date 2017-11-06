// NAME 	: DIPUNJ GUPTA
// REG  	: 20154061
// LAB  	: OS
// SESSION 	: 2017-18
// CODE		: ROUND ROBIN AT SAME ARRIVAL

#include <stdio.h>
struct process
{
	unsigned int pid;
	unsigned int burst;
	unsigned int wait;
	unsigned int TAT;
	unsigned int arrival;
};

int compar_ID(const void *a, const void *b)
{
	unsigned int l = ((struct process*)a)->pid;
	unsigned int r = ((struct process*)b)->pid;
	return (l-r);
}
int compar_AT(const void *a, const void *b)
{
	unsigned int l = ((struct process*)a)->arrival;
	unsigned int r = ((struct process*)b)->arrival;
	return (l-r);
}
void findWaitTime(int n, struct process proc[n])
{
	int i;
	proc[0].wait = 0;
	for(i = 1; i < n ; i++)
		proc[i].wait = proc[i-1].wait + proc[i-1].burst;
}
void printTable(int n, struct process proc[n])
{
	int i;
	printf("\n%10s | %10s | %10s | %10s | %10s","P.NO.","ARRIVAL","BURST","WAIT","TAT");
	printf("\n------------------------------------------------------------------");
	for(i = 0; i < n ; i++)
		printf("\n%10d | %10d | %10d | %10d | %10d",proc[i].pid,proc[i].arrival,proc[i].burst,proc[i].wait,proc[i].TAT);
}
int main()
{
	// FCFS scheduling at different arrival
	int i,n;
	
	printf("Enter the number of processes : ");
	scanf("%d",&n);

	struct process proc[n];
	printf("Enter burst times of processes in order\n");
	
	for(i=0;i<n;i++)
	{
		proc[i].pid = i+1;
		printf("Enter burst time : ");
		scanf("%d",&proc[i].burst);
		printf("Enter Arrival time :");
		scanf("%d",&proc[i].arrival);
	}
	
	qsort(proc,n,sizeof(struct process),compar_AT);
	findWaitTime(n,proc);
	
	for(i = 0; i < n ; i++)
		proc[i].TAT = proc[i].burst + proc[i].wait;
	
	qsort(proc,n,sizeof(struct process),compar_ID);	
	printTable(n,proc);
	
	printf("\n");
	return 0;
}
