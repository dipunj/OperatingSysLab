#include <stdio.h>

void findWaitTime(int n, int burst[n], int wait[n])
{
	int i;
	wait[0] = 0;
	for(i = 1; i < n ; i++)
		wait[i] = wait[i-1] + burst[i-1];
}
void printTable(int n, int burst[n], int wait[n], int TAT[n])
{
	int i;
	printf("\n%10s | %10s | %10s | %10s","P.NO.","BURST","WAIT","TAT");
	printf("%*c\n",30,"-");
	for(i = 0; i < n ; i++)
		printf("\n%10d | %10d | %10d | %10d",i,burst[i],wait[i],TAT[i]);
}
int main()
{
	// FCFS scheduling
	int i,n;
	printf("Enter the number of processes : ");
	scanf("%d",&n);

	int burst[n];
	printf("Enter burst times of processes in order\n");
	for(i=0;i<n;i++)
		scanf("%d",&burst[i]);

	int wait[n];
	int TAT[n];

	findWaitTime(n,burst,wait);
	for(i = 0; i < n ; i++)
		TAT[i] = burst[i] + wait[i];

	printTable(n,burst,wait,TAT);
	return 0;
}
