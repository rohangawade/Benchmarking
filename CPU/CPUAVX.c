#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/time.h>
#include<time.h>
#include <math.h>
#include<immintrin.h>

struct timeval st,et;

double start_time, end_time;

void* FLOATOperation()
{
	
	
	
	__m256 num1 = _mm256_set_ps(10.0, 11.1, 12.2, 13.3, 14.4, 15.5, 16.6, 17.7);
  	__m256 num2 = _mm256_set_ps(20.0, 21.1, 22.2, 23.3, 24.4, 25.5, 26.6, 27.7);


  	
	int i=0;
	while(i<1000000000)
		{

		__m256 addition = _mm256_add_ps(num1, num2);
		
		i++;
		}
	return NULL;
}



void* INTOperation()
{
	
	__m128i num3 = _mm_set_epi32(30, 31, 32, 33);
  	__m128i num4 = _mm_set_epi32(40, 41, 42, 43);


  	
	int i=0;
	while(i<1000000000)
		{

		__m128i subtraction = _mm_sub_epi32(num3, num4);
		
		i++;
		}
	return NULL;
}



int main()
{	
	struct timeval start,end;





	double giops_Count;
	double diff; 
	int thread[4]={1,2,4,8};
	int i;
	int count;


	//-----------------Integer Operation-----------------
	printf("\n---Integer Operation---");
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
	giops_Count = ((thread[i]*6)/ diff);
	printf("\nExcution Time = %lf Sec",diff);
	printf("\nGIOPS = %lf\n", giops_Count);
	}



	//--------------Float Operation----------------------
	printf("\n---FLOAT Operation---");
	for(i=0;i<4;i++)
	{
	pthread_t tid[thread[i]];
	gettimeofday(&start, NULL);
	start_time= start.tv_sec+(start.tv_usec/1000000.0);
	//printf("\nStart Time = %lf",start_time);
	for(count=0;count<thread[i];count++){
		pthread_create(&(tid[count]),NULL,FLOATOperation,NULL);
	}
	for(count=0;count<thread[i];count++){
		pthread_join(tid[count],NULL);
	}

	gettimeofday(&end, NULL);
	end_time= end.tv_sec+(end.tv_usec/1000000.0);	
	//printf("\nEnd Time = %lf",end_time);
	diff= (end_time-start_time);
	printf("\nThread = %d",thread[i]);		
	giops_Count = ((thread[i]*10)/ diff);
	printf("\nExcution Time = %lf Sec",diff);
	printf("\nGIOPS = %lf\n", giops_Count);


	}




	
      	return 0;
		
}	







