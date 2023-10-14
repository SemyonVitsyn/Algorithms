//Имеется массив A из 1⩽N⩽100000 чисел, 10-9⩽Ai⩽109.
//
//К этому массиву Q раз, 1⩽Q⩽100000 применяют следующее: для каждого элемента массива от элемента L до элемента R включительно прибавляют число X.
//
//Требуется вывести этот массив после всех таких преобразований.
//
//Input format
//N Q
//
//A1 A2 ... AN
//
//L1 R1 X1
//
//...
//
//LQ RQ XQ
//
//Output format
//Ровно N элементов массива через пробел после преобразования.

#include <stdio.h>
#include <stdlib.h>

void subadd(int *arr, int N, int Q)
{
	int *temp_arr = calloc(N, sizeof(int));
	int L = 0, R = 0, X = 0;
	for (int i = 0; i < Q; i++)
	{
		scanf("%d %d %d", &L, &R, &X);
		temp_arr[L] += X;
		if (R != N-1)
			temp_arr[R + 1] -= X;
	}
	int temp_val = 0;
	for (int i = 0; i < N; i++)
	{
		temp_val += temp_arr[i];
		arr[i] += temp_val;
	}
	free(temp_arr);
}

int main()
{
	int N = 0, Q = 0;
	scanf("%d %d", &N, &Q);
	int *arr = calloc(N, sizeof(int));
	for (int i = 0; i < N; i++)
		scanf("%d", &arr[i]);
	subadd(arr, N, Q);
	for (int i = 0; i < N; i++)
		printf("%d ", arr[i]);
	free(arr);
	return 0;
}