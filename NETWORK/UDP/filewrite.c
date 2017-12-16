#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#define FILE_SIZE 100*1024*1024
char content[FILE_SIZE];

void seq_File_Write()
{
	
	long int loopahead = FILE_SIZE;
	
	
	int ahead=0;

	FILE *fptr;
	char filename[20];
	char string[]="FileRead.txt";
	

	fptr = fopen(string,"w");
	
	for(ahead = 0;ahead<loopahead;ahead++)
	{
		fwrite(content,1,1,fptr);
	}
	
	fclose(fptr);

}
int main()
{
int i=0,j;
	while(i<FILE_SIZE){
		content[i++] = 'C';
		content[i++] = 'L';
		content[i++] = 'O';
		content[i++] = 'U';
		content[i++] = 'D';	
	}
seq_File_Write();
return 0;
}
