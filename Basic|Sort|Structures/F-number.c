#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *x1, const void *x2)
{
	char str1[201] = {0}, str2[201] = {0};
	strcpy(str1, *(char**)x1);
	strcpy(str2, *(char**)x2);
	strcat(str1, *(char**)x2);
	strcat(str2, *(char**)x1);
	return strcmp(str2, str1);
}

void max_num(char *str_arr[100], int size)
{
	qsort(str_arr, size, sizeof(str_arr[0]), compare);
	for (int i = 0; i < size; i++)
		printf("%s", str_arr[i]);
}

int main()
{
	char *str_arr[100];
	char **s = str_arr;
	char buf[100];
	int size = 0;
	while (scanf("%100s", buf) != EOF)
	{
		*(s+size) = calloc(100, sizeof(char));
		strcpy(*(s+size), buf);
		size++;
	}
	max_num(str_arr, size);
	for (int i = 0; i < size; i++)
		free(*(s+i));
	return 0;
}
