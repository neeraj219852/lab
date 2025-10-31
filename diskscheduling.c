#include<stdio.h>
#include<stdlib.h>
void sort(int rq[],int n)
{
	int temp,i,j;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-1-i;j++)
		{
			if(rq[j]>rq[j+1])
			{
				temp = rq[j];
				rq[j] = rq[j+1];
				rq[j+1] = temp;
			}
		}
	}
}
void fcfs(int rq[],int n,int initial)
{
	int i,j,thm=0;
	printf("the sequence is:\n");
	printf("%d\t",initial);
	for(i=0;i<n;i++)
	{
		printf("%d\t",rq[i]);
		thm += abs(initial-rq[i]);
		initial = rq[i];
	}
	printf("\nThe total seek time is %d\n",thm);
	
}
void scan(int rq[],int n,int initial,int size)
{
	int i,thm=0,pos;
	sort(rq,n);
	for(i=0;i<n;i++)
	{
		if(rq[i]>=initial)
		{
			pos = i;
			break;
		}
	}
	printf("The sequence is:\n");
	printf("%d\t",initial);
	for(i=pos;i<n;i++)
	{
		printf("%d\t",rq[i]);
		thm += abs(initial-rq[i]);
		initial = rq[i];
	}
	if(rq[n-1]<size-1)
	{
		printf("%d\t",size-1);
		thm += abs(initial-(size-1));
		initial = size-1;
	}
	for(i=pos-1;i>=0;i--)
	{
		printf("%d\t",rq[i]);
		thm += abs(initial-rq[i]);
		initial = rq[i];
	}
	printf("\nThe total seek time is: %d\n",thm);
}
void cscan(int rq[],int n,int initial,int size)
{
	int i,thm=0,pos;
	sort(rq,n);
	for(i=0;i<n;i++)
	{
		if(rq[i]>=initial)
		{
			pos = i;
			break;
		}
	}
	printf("The sequence is:\n");
	printf("%d\t",initial);
	for(i=pos;i<n;i++)
	{
		printf("%d\t",rq[i]);
		thm += abs(initial-rq[i]);
		initial = rq[i];
	}
	if(rq[n-1]<size-1)
	{
		printf("%d\t",size-1);
		thm += abs(initial-(size-1));
		initial = size-1;
	}
	printf("0\t");
	thm += abs(initial-0);
	initial=0;
	for(i=0;i<pos;i++)
	{
		printf("%d\t",rq[i]);
		thm += abs(initial-rq[i]);
		initial = rq[i];
	}
	printf("\nThe total seek time is %d\n",thm);
}
void main()
{
	int n,i,j,rq[100],initial,choice,size;
	printf("Enter the number of requests:\n");
	scanf("%d",&n);
	printf("Enter the requests:\n");
	for(i=0;i<n;i++)
	{
		scanf("%d",&rq[i]);
	}
	printf("Enter the initial head position:\n");
	scanf("%d",&initial);
	printf("Enter the size of the disk:\n");
	scanf("%d",&size);
	do{
		printf("Enter the choice\n1.FCFS\n2.SCAN\n3.CSCAN\n4.EXIT\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: fcfs(rq,n,initial);
				break;
			case 2: scan(rq,n,initial,size);
				break;
			case 3: cscan(rq,n,initial,size);
				break;
			case 4: printf("Exiting....\n");
				break;
			default:printf("Invalid choice\n");
				break;
		}
	}while(choice!=4);
}
