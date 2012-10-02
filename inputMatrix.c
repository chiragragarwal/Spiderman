#include <stdio.h>
#include <stdlib.h>

int **inputMatrix()
{
	int **a, i, j, t, n;
		
	FILE *f = fopen("input.txt","r");
	fscanf(f,"%d",&n);
	
	if(f == NULL)
	{
		printf("ERROR\n");
		exit(1);
	}	
	
	a = malloc(n*sizeof(int *));
	
	for(i=0;i<n;i++)
		a[i] = (int *)malloc(n*sizeof(int));	
	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			fscanf(f,"%d",&t);
			a[i][j] = t;		
		}
		
	fclose(f);
	return a;
}
