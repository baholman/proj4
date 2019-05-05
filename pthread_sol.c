#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <pthread.h>

#define NUM_THREADS 12

#define MAXCHAR 2200

char** file_array;
int file_lines;

void freeArray(int **arr, int length){
	for (int i = 0; i<length;i++){
	 free(arr[i]);
	}
	free(arr);
}
//Print; Least Common Substring
//Source: https://www.geeksforgeeks.org/print-longest-common-substring/
//Changes: removes /n, no longer stores dynamic array on the stack
void printLCSubStr(char* X, char* Y, int m, int n,int l1,int l2)
{
    // Create a table to store lengths of longest common
    // suffixes of substrings.   Note that LCSuff[i][j]
    // contains length of longest common suffix of X[0..i-1]
    // and Y[0..j-1]. The first row and first column entries
    // have no logical meaning, they are used only for
    // simplicity of program
//    int LCSuff[m + 1][n + 1]; //segfaults on large strings
	//for a big array
	int **LCSuff = malloc((m+1) * sizeof(int *));;
	for(int k=0; k<(m+1);k++)
		LCSuff[k] =(int*)malloc((n+1)*sizeof(int));
    // To store length of the longest common substring
    int len = 0;
 
    // To store the index of the cell which contains the 
    // maximum value. This cell's index helps in building 
    // up the longest common substring from right to left.
    int row, col;
 
   // Following steps build LCSuff[m+1][n+1] in bottom up fashion. 
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
 
    // if true, then no common substring exists
    if (len == 0) {
        printf("%d-%d: No Common Substring\n",l1,l2);
        return;
    }
 
    // allocate space for the longest common substring
    char* resultStr = (char*)malloc((len + 1) * sizeof(char));
  // char resultStr [len+1];
    resultStr[len] = '\0';
 
    // traverse up diagonally form the (row, col) cell
    // until LCSuff[row][col] != 0
   while (LCSuff[row][col] != 0) {
        resultStr[--len] = X[row - 1]; // or Y[col-1]
 
        // move diagonally up to previous cell
        row--;
        col--;
    }
	freeArray(LCSuff, m);  
    //remove newline char
    //src: https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
	size_t length;
    if((length = strlen(resultStr)) >0){
		if(resultStr[length-1] == '\n')
			resultStr[length-1] ='\0';
	 }
	
    // required longest common substring
   printf("%d-%d: %s\n",l1,l2,resultStr);
   free(resultStr);
   
}

void LCS_runner(int id){
	int s1,s2;
	int startPos = ((int) id) * ceil((double)file_lines / NUM_THREADS);
	int endPos = startPos + ceil((double)file_lines / NUM_THREADS);	
//	if (endPos < file_lines)
//		endPos = file_lines-1;
	int line1 = startPos;
	int line2 = line1 + 1;
	for(int i =startPos; (i < endPos) &&(i+1 < file_lines); i++){
		s1 = strlen(file_array[i]);
		s2 = strlen(file_array[i+1]);
			
		printLCSubStr(file_array[i], file_array[i+1], s1, s2, line1, line2);
		line1 = line2; //update lines
		line2++;
	}
}

int main(int argc, char *argv[])
{
	//timing
	struct timeval t1, t2;
	double elapsedTime;
	int myVersion = 1;
	
	int i;
	gettimeofday(&t1, NULL);
								
	//read file
	FILE *fp;
	//int s1,s2;

	int problem_size;
	char* filename;
	if((argc == 2)){
		filename = argv[1]; //get name from argument
	}
	else if(argc == 3){
		filename = argv[1];
		problem_size = strtol(argv[2], NULL, 10);
	}
	else{
		printf("Usage: ./program <file> <problem size>\n");
        return 1;
	}
	
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file: %s\n",filename);
		printf("Usage: ./program <file> | <problem size>\n");
        return 1;
    }
    
	//read file into array
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
		//printf("%s",file_array[i]);
	}
	//process array in lcs function

	for (i = 0; i < NUM_THREADS; i++ ) {
		LCS_runner(i);
	}
	
	//free the array
	freeArray((int **)file_array,file_lines);
	//close file
    fclose(fp);
	
	//print time
	gettimeofday(&t2, NULL);

	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; //sec to ms
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; // us to ms
	printf("DATA, %d, %s, %f\n", myVersion, getenv("SLURM_CPUS_ON_NODE"),  elapsedTime);

  return 0;
}
