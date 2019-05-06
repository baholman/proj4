#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include "omp.h"
#define MAXCHAR 2200
int NUM_THREADS=12;
char** file_array;
int file_lines;

void freeArray(int **arr, int length){
	for (int i = 0; i<length;i++){
	 free(arr[i]);
	}
	free(arr);
}

void printLCSubStr(char* X, char* Y, int m, int n,int l1,int l2)
{
	int **LCSuff = malloc((m+1) * sizeof(int *));;
	for(int k=0; k<(m+1);k++)
		LCSuff[k] =(int*)malloc((n+1)*sizeof(int));

    int len = 0;
    int row, col;
 
   for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                LCSuff[i][j] = 0;
        
	    else if (X[i - 1] == Y[j - 1]) {
                LCSuff[i][j] = LCSuff[i - 1][j - 1] + 1;
                if (len < LCSuff[i][j]) {
                    len = LCSuff[i][j];
                    row = i;
                    col = j;
                }
            } else
                LCSuff[i][j] = 0;
        }
    }
    if (len == 0) {
        printf("%d-%d: No Common Substring\n",l1,l2);
        return;
    }
    char* resultStr = (char*)malloc((len + 1) * sizeof(char));

    resultStr[len] = '\0';
   while (LCSuff[row][col] != 0) {
        resultStr[--len] = X[row - 1];
 
        row--;
        col--;
    }
	freeArray(LCSuff, m);

	size_t length;
    if((length = strlen(resultStr)) >0){
		if(resultStr[length-1] == '\n')
			resultStr[length-1] ='\0';
	 }
	

   printf("%d-%d: %s\n",l1,l2,resultStr);
   free(resultStr);
   
}

void LCS_runner(int id){//void *id){
	int s1,s2;
	int startPos =  id * ceil((double)file_lines / NUM_THREADS);
	int endPos = startPos + ceil((double)file_lines / NUM_THREADS);	
	int line1 = startPos;
	int line2 = line1 + 1;
	int i;
	
	for( i =startPos; (i < endPos) &&(i+1 < file_lines); i++){
		s1 = strlen(file_array[i]);
		s2 = strlen(file_array[i+1]);
			
		printLCSubStr(file_array[i], file_array[i+1], s1, s2, line1, line2);
		line1 = line2; 
		line2++;
	}
}

int main(int argc, char *argv[])
{

	struct timeval t1, t2;
	double elapsedTime;
	int myVersion = 1;
	
	int i;	
	gettimeofday(&t1, NULL);
								

	//read file
	FILE *fp;
	int problem_size;
	char* filename;
	if((argc == 2)){
		filename = argv[1]; 
	}
	else if(argc == 4){
		filename = argv[1];
		problem_size = strtol(argv[2], NULL, 10);
		NUM_THREADS = strtol(argv[3], NULL, 10);
	}
	else{
		printf("Usage: ./program <file> | <problem size> <thread count>\n");
        return 1;
	}
	
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file: %s\n",filename);
		printf("Usage: ./program <file> | <problem size> <thread count>\n");
        return 1;
    }
    
	int ch = 0;
	while(!feof(fp))
	{
	  ch = fgetc(fp);
	  if(ch == '\n')
	  {
		file_lines++;
	  }
	}
	if((argc > 2) && (problem_size < file_lines)){
		file_lines = problem_size;
	}
	
	rewind(fp);

	file_array = malloc(sizeof(char*) * file_lines);	
	
	for(i =0; i < file_lines; i++){
		if(ferror(fp) || feof(fp)){
			break;			
		}
		file_array[i] = malloc(sizeof(char) * MAXCHAR);
		fgets(file_array[i], MAXCHAR, fp);
	}

	omp_set_num_threads(NUM_THREADS);

	#pragma omp parallel
	{
	  	LCS_runner(omp_get_thread_num());
	}

	freeArray((int **)file_array,file_lines);

    fclose(fp);
	
	gettimeofday(&t2, NULL);

	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; //sec to ms
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; // us to ms
	printf("Version: %d, Slurm_CPUs_on_node: %s, Time elapsed (ms): %f\n", myVersion, getenv("SLURM_CPUS_ON_NODE"),  elapsedTime);
  return 0;
}
