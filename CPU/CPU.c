#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/time.h>
#include<time.h>
#include <math.h>


struct timeval st,et;

double start_time, end_time;
double diff;
void* INTOperation()
{
	int a = 10,b =20;
	int i=0;;
	
	while(i<1000000000)
		{
		a+b;
		a*b;
		a+b;
		a-b;
		b/a;
		a+b;
		a*b;
		a+b;
		a-b;
		b/a;
		a+b;
		a*b;
		a+b;
		a-b;
		b/a;
		a+b;
		a*b;
		a+b;
		a-b;
		b/a;

		i++;
		}
	return NULL;
}


void* Float_Operation()
{
	int a = 100.29f,b =2234.44f;
	int i=0;;
	while(i<1000000000)
		{
		a+b;
		a*b;
		a+b;
		a-b;
		b/a;
		a+b;
		a*b;
		a+b;
		a-b;
		b/a;
		a+b;
		a*b;
		a+b;
		a-b;
		b/a;
		a+b;
		a*b;
		a+b;
		a-b;
		b/a;

		i++;
		}
	return NULL;
}

int main()
{	
	struct timeval start,end;

	int count;
	double gflops_Count,elapsed;
	double giops_Count;
	 
	int thread[4]={1,2,4,8};

	//------------------Integer Operation----------------------
	printf("\n---Integer Operation---");
	int i=0;
	for(i=0;i<4;i++)
	{
	pthread_t tid[thread[i]];
	gettimeofday(&start, NULL);
	start_time= start.tv_sec+(start.tv_usec/1000000.0);
	//printf("\nStart Time = %lf",start_time);
	for(count=0;count<thread[i];count++){
		pthread_create(&(tid[count]),NULL,INTOperation,NULL);
	}
	for(count=0;count<thread[i];count++){
		pthread_join(tid[count],NULL);
	}

	gettimeofday(&end, NULL);
	end_time= end.tv_sec+(end.tv_usec/1000000.0);	
	//printf("\nEnd Time = %lf",end_time);
	diff= (end_time-start_time);
	printf("\nThread = %d",thread[i]);		
	giops_Count = ((thread[i]*22)/ diff);
	printf("\nExecution Time = %lf Sec",diff);
	printf("\nGIOPS = %lf\n", giops_Count);
	}

	//----------------Float Opeartion-------------------
	printf("\n---Floating Operation---"); 
	for(i=0;i<4;i++)
	{
	pthread_t tid[thread[i]];
	gettimeofday(&start, NULL);
	start_time= start.tv_sec+(start.tv_usec/1000000.0);
	//printf("\nStart Time = %lf",start_time);
	for(count=0;count<thread[i];count++){
		pthread_create(&(tid[count]),NULL,Float_Operation,NULL);
	}
	for(count=0;count<thread[i];count++){
		pthread_join(tid[count],NULL);
	}

	gettimeofday(&end, NULL);
	end_time= end.tv_sec+(end.tv_usec/1000000.0);	
	//printf("\nEnd Time = %lf",end_time);
	diff= (end_time-start_time);
	printf("\nThread = %d",thread[i]);		
	gflops_Count = ((thread[i]*22)/ diff);
	printf("\nExecution Time = %lf Sec",diff);
	printf("\nGFLOPS = %lf\n", gflops_Count);
	}
      	return 0;
		
}	







