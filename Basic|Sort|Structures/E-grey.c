//Даны все строки длины N, состоящие из нулей и единиц. Говорят, что они образуют код Грея, если они идут в таком порядке, что каждая следующая строка отличается от предыдущей ровно в одной позиции.
//
//Пример кода Грея размерности 2:
//
//00 01 11 10
//
//Необходимо вывести код Грея размера N (вход задачи), начиная со строки, состоящей из одних нулей.

#include <stdio.h>
#include <stdlib.h>

void grey(int N, int *arr, int depth)
{
	if (depth == 0)
		arr[0] = 0;
	else
	{
		int new_num_count = 1 << (depth - 1);
		for (int i = 0; i < new_num_count; i++)
			arr[new_num_count + i] = arr[new_num_count-i-1] + (1 << (depth - 1));
	}
	if (depth != N)
		grey(N, arr, depth + 1);
}

void print_bin_arr(int *arr, int size, int bits_count)
{
	for (int i = 0; i < size; i++)
	{
		for (int bit = 0; bit < bits_count; bit++)
			printf("%d", (arr[i] >> (bits_count-bit-1)) & 1);
		printf("\n");
	}
}

int main()
{
	int N = 0;
	scanf("%d", &N);
	int *arr = calloc(1<<N, sizeof(int));
	grey(N, arr, 0);
	print_bin_arr(arr, 1<<N, N);
	free(arr);
	return 0;
}