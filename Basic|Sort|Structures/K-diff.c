//Симметрическая разность множеств — множество элементов, входящих строго в одно из множеств-операндов.
//
//Input format
//На вход подаётся последовательность чисел в диапазоне от 1 до 2000000000, разделённых пробелами и заканчивающаяся нулём — ограничителем последовательности, не входящим в множество. Все эти элементы образуют множество A, то есть, среди нет одинаковых пар. После разделителя подаются элементы множества B, тоже завершающиеся нулём, не входящим в множество. Количество элементов в множествах не превосходит 100000.
//Output format
//На выход программы нужно вывести симметрическую разность множеств A и B в порядке возрастания элементов. Элементы выходного множества должны быть разделены пробелами.

#include <stdio.h>
#include <stdlib.h>

int *read_arr(int *size)
{
	int capacity = 2;
	int *arr = calloc(capacity, sizeof(int));
	scanf("%d", &arr[*size]);
	while (arr[*size] != 0)
	{
		(*size)++;
		if (*size == capacity)
		{
			capacity *= 2;
			int *new = realloc(arr, capacity * sizeof(int));
			if (new != NULL)
				arr = new;
		}
		scanf("%d", &arr[*size]);
	}
	return arr;
}

int compare(const void *elem1, const void *elem2)
{
	return *((int*)elem1) - *((int*)elem2);
}

void diff(int *A, int *B, int size1, int size2)
{
	qsort(A, size1, sizeof(int), compare);
	qsort(B, size2, sizeof(int), compare);
	int i = 0, j = 0;
	while (i < size1 || j < size2)
	{
		if (i < size1 && j < size2)
		{
			if (A[i] > B[j])
			{
				printf("%d ", B[j]);
				j++;
			}
			else if (A[i] < B[j])
			{
				printf("%d ", A[i]);
				i++;
			}
			else
			{
				i++;
				j++;
			}
		}
		else if (i < size1)
		{
			printf("%d ", A[i]);
			i++;
		}
		else if (j < size2)
		{
			printf("%d ", B[j]);
			j++;
		}
	}
}

int main()
{
	int size1 = 0, size2 = 0;
	int *A = read_arr(&size1);
	int *B = read_arr(&size2);
	diff(A, B, size1, size2);
	free(A);
	free(B);
	return 0;
}