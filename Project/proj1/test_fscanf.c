#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
int main(void) {
	char *filename = "testin.txt";
	FILE *file = fopen(filename, "r");
	int a1, a2, a3;
	char word[30];
	fscanf(file, "%30s %d %d", word, &a2, &a3);
	printf("Successfully read: %s %3d %3d", word, a2, a3);
	fclose(file);

	return 0;
}
