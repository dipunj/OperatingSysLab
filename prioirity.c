#include <stdio.h>
struct process
{
	unsigned int prior;
	unsigned int pid;
	unsigned int burst;
	unsigned int wait;
	unsigned int TAT;
};

int compar_ID(const void *a, const void *b)
{
	unsigned int l = ((struct process*)a)->pid;
	unsigned int r = ((struct process*)b)->pid;
	return (l-r);
}
int compar_PRIOR(const void *a, const void *b)
{
	unsigned int l = ((struct process*)a)->prior;
	unsigned int r = ((struct process*)b)->prior;
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
	printf("\n%10s | %10s | %10s | %10s | %10s","P.No","PRIORITY","BURST","WAIT","TAT");
	printf("\n--------------------------------------------------------------------------");
	for(i = 0; i < n ; i++)
		printf("\n%10d | %10d | %10d | %10d | %10d",proc[i].pid,proc[i].prior,proc[i].burst,proc[i].wait,proc[i].TAT);
}
int main()
{
	// PRIORITY scheduling
	int i,n;

	printf("Enter the number of processes : ");
	scanf("%d",&n);

	struct process proc[n];

	printf("Enter priority and burst times of processes in order\n");
	for(i=0;i<n;i++)
	{
		proc[i].pid = i+1;
		printf("Enter priority : ");
		scanf("%d",&proc[i].prior);
		printf("Enter Burst Time: ");
		scanf("%d",&proc[i].burst);
	}

	qsort(proc,n,sizeof(struct process),compar_PRIOR);
	findWaitTime(n,proc);

	// Calculating TAT
	for(i = 0; i < n ; i++)
		proc[i].TAT = proc[i].burst + proc[i].wait;
	
	// Sorting the output according to id
	qsort(proc,n,sizeof(struct process),compar_ID);	
	printTable(n,proc);
	printf("\n");
	return 0;
}
