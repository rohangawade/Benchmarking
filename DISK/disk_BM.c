#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#define FILE_SIZE 1000*1024*1024

struct timeval start,end;
typedef struct thread_data{
   int  nthread;
   int  blck;
} th_data;
double start_time, end_time,execution_time;

char content[FILE_SIZE];
char contentR[FILE_SIZE];

void *seq_File_ReadWrite(void *threadarg)
{
	th_data *my_data;
	my_data = (th_data *) threadarg;
	int block = my_data->blck;
	int thread =my_data->nthread;	
	

	int loopahead = FILE_SIZE/block;
	int ahead=0;

	FILE *fptr;
	FILE *fptrw;
	char filename[]="FileRead.txt";
	char filewrite[]="FileWrite.txt";
	fptr = fopen(filename,"r");
	fptrw = fopen(filewrite,"w");
	

	for(ahead = 0;ahead<loopahead;ahead++)
	{
		fread(contentR,1,block,fptr);
		fwrite(contentR,1,block,fptrw);
	}
	
	fclose(fptr);
	fclose(fptrw);
	pthread_exit(NULL);
}
void *random_File_ReadWrite(void *threadarg)
{
	th_data *my_data;
	my_data = (th_data *) threadarg;
	int block = my_data->blck;
	int thread =my_data->nthread;	
	
	
	int loopahead = FILE_SIZE/block;
	int ahead=0;

	FILE *fptr;
	FILE *fptw;
	char filename[]="FileRead.txt";
	char filewrite[]="FileWrite.txt";
	fptr = fopen(filename,"r");
	fptw = fopen(filewrite,"w");
	for(ahead = 0;ahead<loopahead;ahead++)
	{
		int rseek=rand()%block;
	    	fseek(fptr,rseek,SEEK_SET);
		int rseekw=rand()%block;
		fseek(fptw,rseekw,SEEK_SET);
		fread(contentR,1,block,fptr);
		fwrite(contentR,1,block,fptw);
	}
	
	fclose(fptr);
	fclose(fptw);
	pthread_exit(NULL);
}


void *seq_File_Read(void *threadarg)
{
	th_data *my_data;
	my_data = (th_data *) threadarg;
	int block = my_data->blck;
	int thread =my_data->nthread;	

	int loopahead = FILE_SIZE/block;
	int ahead=0;

	FILE *fptr;
	char filename[]="FileRead.txt";

	fptr = fopen(filename,"r");
	
	for(ahead = 0;ahead<loopahead;ahead++)
	{
		fread(contentR,1,block,fptr);
	}
	
	fclose(fptr);
	pthread_exit(NULL);
}


void *random_File_Read(void *threadarg)
{
	th_data *my_data;
	my_data = (th_data *) threadarg;
	int block = my_data->blck;
	int thread =my_data->nthread;	
	
	
	int loopahead = FILE_SIZE/block;
	int ahead=0;

	FILE *fptr;
	char filename[]="FileRead.txt";

	fptr = fopen(filename,"r");
	
	for(ahead = 0;ahead<loopahead;ahead++)
	{
		int rseek=rand()%block;
	    	fseek(fptr,rseek,SEEK_SET);
		fread(contentR,1,block,fptr);
	}
	
	fclose(fptr);
	pthread_exit(NULL);
}

void display_BenchMark(double starttime, double endtime,int num_Threads,int block)
{
	execution_time = endtime - starttime;
	double fs = 1000*1024*1024;
	

	long double data_write = (num_Threads * fs);
	double totalData = data_write/(1024*1024);
	double throughput = totalData/execution_time;
	double latency = (execution_time * 1000)/totalData;
	printf("\nExecution Time: %lf",execution_time);
        printf("\nThroughput is: %lf MBPS",throughput);
	printf("\nLatency is: %0.12lf ms\n",latency);		
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
	
	//filling the content array with data
	int i=0,j;
	while(i<FILE_SIZE){
		content[i++] = 'C';
		content[i++] = 'L';
		content[i++] = 'O';
		content[i++] = 'U';
		content[i++] = 'D';	
	}
	printf("\n  Block size:  8B=8, 8KB=8192, 8MB=8388608, 80MB = 83886080:");
	
	int option;
	char* operation;
	printf("\n1. Sequential Read Write\n2. Random Read Write \n3. Sequential Read \n4. Random Read\n");
	scanf("%d",&option);   
	if(option == 1)
	{
		operation = "Sequential Read Write";
	}
	else if(option == 2)
	{
		operation = "Random Write";
	}
	else if(option == 3)
	{
		operation = "Sequential Read";
	}
	else if(option == 4)
	{
		operation ="Random Read";
	}
	printf("\n---%s---\n",operation);
	//block size loop
	for(nt = 0;nt<4;nt++)
	{
				
		//number of threads loop
		int noOfThreads = num_thread[nt];
		for(sb= 0;sb<4;sb++)
		{
			int bs = size_Block[sb];
			char* blck = getBlockSizeInMB(bs);
			
			printf("\nPerforming %s using %s and %d threads on 10GB file",operation,blck,noOfThreads);
			pthread_t threads[noOfThreads];
			th_data data;
			data.blck = bs;
			data.nthread = noOfThreads;
			
			//get time
 			gettimeofday(&start, NULL);
			start_time= start.tv_sec+(start.tv_usec/1000000.0);
        		
			for(i=0; i<noOfThreads; i++)
			{
				if(option == 1)
				{
					pthread_create(&threads[i],NULL,seq_File_ReadWrite,(void *) &data);
				}
				else if(option == 2)
				{
					pthread_create(&threads[i],NULL,random_File_ReadWrite,(void *) &data);
				}
				else if(option == 3)
				{
					pthread_create(&threads[i],NULL,seq_File_Read,(void *) &data);
				}
				else if(option == 4)
				{
					pthread_create(&threads[i],NULL,random_File_Read,(void *) &data);
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
}
