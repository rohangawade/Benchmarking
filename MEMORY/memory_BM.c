#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#define MEMORY_SIZE 1024*1024*1000

struct timeval start,end;
typedef struct thread_data{
   int  nthread;
   int  blck;

} th_data;

double start_time, end_time,execution_time;

void *sequential_RW(void *threadarg)
{
	th_data *my_data;
	my_data = (th_data *) threadarg;
	int block = my_data->blck;
	int thread =my_data->nthread;	
	
	int loopahead = MEMORY_SIZE/block/thread;
	
	char *mem_source= (char*)malloc(MEMORY_SIZE*sizeof(char));;
	char *mem_dest= (char*)malloc(MEMORY_SIZE*sizeof(char));;
	
	
	strncat(mem_source,"CloudComputing",MEMORY_SIZE*sizeof(char));
	int ahead=0;

	for(ahead = 0;ahead<loopahead;ahead++)
	{
		memcpy(mem_dest+ahead,mem_source+ahead,block);
	}
	
	free(mem_source);
	free(mem_dest);
	pthread_exit(NULL);
}

void *random_RW(void *threadarg)
{
	th_data *my_data;
	my_data = (th_data *) threadarg;
	int block = my_data->blck;
	int thread =my_data->nthread;	
	
	int loopahead = MEMORY_SIZE/block/thread;

	int random_acc_loc = 0;

	
	char *mem_source= (char*)malloc(MEMORY_SIZE*sizeof(char));;
	char *mem_dest= (char*)malloc(MEMORY_SIZE*sizeof(char));;
	
	
	strncat(mem_source,"CloudComputing",MEMORY_SIZE*sizeof(char));
	int ahead=0;

	int flag =1;
	for(ahead = 0;ahead<loopahead;ahead++)
	{
		random_acc_loc = rand()%(loopahead);
		memcpy(mem_dest+random_acc_loc,mem_source+random_acc_loc,block);
	}
	
	free(mem_source);
	free(mem_dest);
	pthread_exit(NULL);
}

void *random_Write(void *threadarg)
{
	th_data *my_data;
	my_data = (th_data *) threadarg;
	int block = my_data->blck;
	int thread =my_data->nthread;	
	int loopahead = MEMORY_SIZE/block/thread;

	int random_acc_loc = 0;

	
	char *mem_source= (char*)malloc(MEMORY_SIZE*sizeof(char));;

	
	

	int ahead=0;

	int flag =1;
	for(ahead = 0;ahead<loopahead;ahead++)
	{
		random_acc_loc = rand()%(loopahead);
		memset(mem_source+random_acc_loc,'C',block);
	}
	
	free(mem_source);

	pthread_exit(NULL);
}

void *sequential_Write(void *threadarg)
{
	th_data *my_data;
	my_data = (th_data *) threadarg;
	int block = my_data->blck;
	int thread =my_data->nthread;	
	int loopahead = MEMORY_SIZE/block/thread;

	int random_acc_loc = 0;

	
	char *mem_source= (char*)malloc(MEMORY_SIZE*sizeof(char));;
	int ahead=0;

	for(ahead = 0;ahead<loopahead;ahead++)
	{
		memset(mem_source+ahead,'C',block);
	}
	free(mem_source);
	pthread_exit(NULL);
}

void display_BenchMark(double starttime, double endtime,int num_Threads,int block)
{
	execution_time = endtime - starttime;

printf("Throughput is: %lf MBPS\n",(((double)MEMORY_SIZE)/execution_time)/(1024*1024));
	double iterations = ((double)MEMORY_SIZE/block);
	iterations = iterations/num_Threads;
printf("Latency is: %0.12lf usec\n",((double)execution_time*1000000)/((double)MEMORY_SIZE)/num_Threads);		
}
char * getBlockSizeInMB(int bl){
	char* blockS;
	if(bl == 8)
		blockS = "8B";
	else if(bl == 8192)
		blockS = "8KB";
	else if(bl == 8388608)
		blockS = "8MB";
	else 
		blockS = "80MB";	
	
	return blockS;
}
int main()
{
	long int size_Block[4] = {8,8192,8388608,83886080};
	int num_thread[4] = {1,2,4,8};
	int sb,nt;
	printf("\n Block size:  8B=8, 8KB=8192, 8MB=8388608, 80MB = 83886080:");
	int i,j;
	printf("Menu \n 1. Sequential Read Write \n2. Random Read Write \n3. Sequential Write  \n 4. Random Write\n");
	int option;
	printf("Enter choice : ");
	scanf("%d",&option);
	
	char* operation;
	if(option == 1)
	{
		operation = "Sequential Read Write";
	}
	else if(option == 2)
	{
		operation = "Random Read Write";
	}
	else if(option == 3)
	{
		operation = "Sequential write";
	}
	else if(option == 4)
	{
		operation ="Random write";
	}
	printf("\n---%s---\n",operation);
	
	

	
	//block size loop
	for(sb= 0;sb<4;sb++)
	{
		int bs = size_Block[sb];
		char* blck = getBlockSizeInMB(bs);		
		//number of threads loop
		for(nt = 0;nt<4;nt++)
		{
			int noOfThreads = num_thread[nt];
			printf("\nPerforming %s access on memory benchmark for %s and %d threads",operation,blck,noOfThreads);
			pthread_t threads[noOfThreads];
			th_data data;
			data.blck = bs;
			data.nthread = noOfThreads;
			
 			gettimeofday(&start, NULL);
			start_time= start.tv_sec+(start.tv_usec/1000000.0);
        		
			for(i=0; i<noOfThreads; i++)
			{
				if(option == 1)
				{
					pthread_create(&threads[i],NULL,sequential_RW,(void *) &data);
				}
				else if(option == 2)
				{
					pthread_create(&threads[i],NULL,random_RW,(void *) &data);
				}
				else if(option == 3)
				{
					pthread_create(&threads[i],NULL,sequential_Write,(void *) &data);
				}
				else if(option == 4)
				{
					pthread_create(&threads[i],NULL,random_Write,(void *) &data);
				}

			}
        		for(j=0; j<noOfThreads; j++)
                		pthread_join(threads[j],NULL);

			gettimeofday(&end, NULL);
			end_time= end.tv_sec+(end.tv_usec/1000000.0);
			
			//calculating benchmark	
			display_BenchMark(start_time,end_time,noOfThreads,bs);
			
		}	
	}	

	return 0;
}
