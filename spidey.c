#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

pid_t var1,status,ret,mainID;

int spidey(int **M, int n, int L, int R, int status)
{	

if(status==0)
{		
		if(R==n-1)			//Check only bottom & create only 1 left child
		{
			var1 = fork();
			if(var1==0)
			{			
				if(M[L+1][R] == 1)
				{
					status = 1;
					//printf("I am a LEAF child. PID = %d ; status = %d ; Parent ID = %d\n",getpid(),status,getppid());
					exit(status);
				}
				else 
				{
					if(M[L+1][R] == 2)
						status = 2;
					//printf("I am a LEFT child. PID = %d ; status = %d ; Parent ID = %d\n",getpid(),status,getppid());
								
					status = spidey(M,n,L+1,R,status);	
					exit(status);
				}
			}
			else	//parent
			{
				ret = waitpid(var1,&status,0);
				if((status/256)==2)
					{
						printf("(%d,%d)-> ",L+1,R);
						if(!(L==0 && R==0))
							exit(status/256);
						else
							return(status/256);
					}
			}	
			
		}

/*	---------------------------------------------------------------	*/	
	
		if(L==n-1)			//Check only right & create only 1 right child
		{
			var1 = fork();
			if(var1==0)
			{
				if(M[L][R+1] == 1)
				{
					status = 1;
					//printf("I am a LEAF child. PID = %d ; status = %d ; Parent ID = %d\n",getpid(),status,getppid());
					exit(status);
				}
				else 
				{
					if(M[L][R+1] == 2)
					{
						status = 2;			
					}
					//printf("I am a RIGHT child. PID = %d ; status = %d ; Parent ID = %d\n",getpid(),status,getppid());
					
					status = spidey(M,n,L,R+1,status);
					exit(status);
				}
			}
			else	//parent
			{
				ret = waitpid(var1,&status,0);
				if((status/256)==2)
					{
						printf("(%d,%d)-> ",L,R+1);
						if(!(L==0 && R==0))
							exit(status/256);
						else
							return(status/256);
					}	
			}
		}

/*	---------------------------------------------------------------	*/		
		
		if(M[L][R+1] == 0)	//right path exists
			{
				var1 = fork();
				if(var1==0)
				{
					//printf("I am a RIGHT child. PID = %d ; status = %d ; Parent ID = %d\n",getpid(),status,getppid());
					if(L==0 && R==0)
					{
						mainID = getppid();
					}
					status = spidey(M,n,L,R+1,status);	
					exit(status);
				}
				else	//parent
				{
					ret = waitpid(var1,&status,0);
					if((status/256)==2)
					{
						printf("(%d,%d)-> ",L,R+1);
						if(!(L==0 && R==0))
							exit(status/256);
						else
							return(status/256);
					}	
				}
			}
			
		if((L==0 && R==0) || M[L][R+1] == 1)
			{
				var1 = fork();
				if(var1==0)
				{
					status = 1;	
					//printf("I am a LEAF child. PID = %d ; status = %d ; Parent ID = %d\n",getpid(),status,getppid());
					if(L==0 && R==0)
					{
						mainID = getppid();
					}
					exit(status);
				}	
				else	//parent
				{
					ret = waitpid(var1,&status,0);
				}	
			}
/*	---------------------------------------------------------------	*/
			
		if(M[L+1][R] == 0)	//left path exists
			{
				var1 = fork();
				if(var1==0)
				{
					status = 0;
					//printf("I am a LEFT child. PID = %d ; status = %d ; Parent ID = %d\n",getpid(),status,getppid());
					
					status = spidey(M,n,L+1,R,status);		
					exit(status);
				}
				else 	//parent
				{
					ret = waitpid(var1,&status,0);
					if((status/256)==2)
					{
						printf("(%d,%d)-> ",L+1,R);
						if(!(L==0 && R==0))
							exit(status/256);
						else
							return(status/256);
					}
				}
			}
			
		else
			{
				var1 = fork();
				if(var1==0)
				{
					status = 1;
					//printf("I am a LEAF child. PID = %d ; status = %d ; Parent ID = %d\n",getpid(),status,getppid());
					exit(status);
				}
				else	//parent
				{
					ret = waitpid(var1,&status,0);
				}	
			}	
	
}	//end of status = 0


if(status==2)
	{
		printf("\nFOUND MARY JANE :)\n");
		exit(status);
	}	

}

