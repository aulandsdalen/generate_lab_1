#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sodium.h>
#define NUM_RECORDS 1000000
#define MAXTIME 946598400 /* 1/1/2000 00:00:00 UTC */

struct Record
{
	float value;
	int recorded_at;
};
typedef struct Record Record;

int main(int argc, char const **argv)
{
	int i = 0;
	Record record;
	record.value = 0.0;
	record.recorded_at = 0;
	FILE *output;
	if (argc != 2) {
		printf("Usage: %s <file to write>\n", argv[0]);
		return -1;
	}
	if (sodium_init() == -1) {
		printf("Failed to initialize libsodium, exiting\n");
		return 1;
	}
	if(!(output = fopen(argv[1], "w+"))) {
		printf("Cannot open output file, exiting\n");
		return 2;
	}
	for (i = 0; i < NUM_RECORDS; i++) {
		record.value = (float)randombytes_random()/(float)randombytes_random();
		record.recorded_at = randombytes_uniform(MAXTIME);
		fprintf(output, "%f,%d\n", record.value, record.recorded_at);
	}
	fclose(output);
	return 0;
}
