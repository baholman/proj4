#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define WIKI_ARRAY_SIZE 1000000
#define WIKI_STRING_SIZE 2000
#define WORDS_ARRAY_SIZE 50000
#define WORDS_STRING_SIZE 9

char wiki_array[WIKI_ARRAY_SIZE][WIKI_STRING_SIZE];
char words_array[WORDS_ARRAY_SIZE][WORDS_STRING_SIZE];

struct timeval t1, t2;
double elapsedTime;
int numSlots, line_num, myVersion = 1;

void read_to_memory()
{
	char *fileName = "../../wiki.50short";
	FILE* file = fopen(fileName, "r"); /* should check the result */
	char line_wiki[WIKI_STRING_SIZE];
	line_num = 0;
	while (fgets(line_wiki, sizeof(line_wiki), file)) {
		strcpy(wiki_array[line_num], line_wiki);
		line_num++;
	}
	fclose(file);

	printf("Load Memory: %s, %d\n", fileName, line_num);

	fileName = "../../words_4-8chars75";
	file = fopen(fileName, "r"); /* should check the result */
	char line_words[WORDS_STRING_SIZE];
	line_num = 0;
	while (fgets(line_words, sizeof(line_words), file)) {
		strcpy(words_array[line_num], line_words);
		line_num++;
	}
	fclose(file);

	for (int i = 0; i < WORDS_ARRAY_SIZE; i++) {
		printf("%s\n", words_array[i]);
	}

	printf("Load Memory: %s, %d\n", fileName, line_num);
}

int main() {

	gettimeofday(&t1, NULL);

	printf("DEBUG: starting loop on %s\n", getenv("HOST"));

	//DO PROCESSING HERE
	//init_arrays();
	read_to_memory();
	//find_word_in_wiki();
	//count_array();
	//print_results();

	gettimeofday(&t2, NULL);

	elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; //sec to ms
	elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; // us to ms
	printf("DATA, %d, %s, %f\n", myVersion, getenv("NSLOTS"), elapsedTime);
}