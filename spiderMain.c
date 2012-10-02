#include <stdio.h>
#include <stdlib.h>
#include "HEADER.h"

void main()
{
	int n,i,j,right,left;
	int status = 0;
	
	FILE *f = fopen("input.txt","r");
	fscanf(f,"%d",&n);
	fclose(f);
	
	int **M = inputMatrix();
	int **path, **child;
	
	path = malloc(n*sizeof(int *));
	child = malloc(n*sizeof(int *));
	
	for(i=0 ; i<n ; i++)
	{	
		path[i] = (int *)malloc(n*sizeof(int));
		child[i] = (int *)malloc(n*sizeof(int));
	}	
	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			path[i][j] = -1;
			child[i][j] = 0;
		}
		
	path[0][0] = 0;
	
	//printf("I am the MAIN PROCESS. PID: %d ; status : %d ; Parent ID : %d\n",getpid(),status,getppid());
	status = spidey(M,n,0,0,status);
	
	if(status==2 && M[1][0]==1)
	{
		printf("(0,0)\n\n");
		pid_t var1;
		var1 = fork();
		if(var1==0)
		{
			status = 1;
			//printf("I am a LEAF child. PID = %d ; status = %d ; Parent ID = %d\n",getpid(),status,getppid());
			exit(status);
		}
		else
		{
			wait(NULL);
		}
	}
	
	else if(status==2)
		printf("(0,0)\n\n");
	
	if(status/256==1 || status==0)
		printf("\nCANNOT RESCUE MARY JANE, Sorry !\n\n");
		
	return;
}


