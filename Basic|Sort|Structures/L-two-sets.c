//В массивах A размером N и B размером M значения строго возрастают, Требуется найти пересечение этих массивов.
//
//2 ⩽ N,M ⩽ 100000. Элементы массива не превосходят по абсолютной величине 100000000;

#include <stdio.h>
#include <stdlib.h>

void cross(int const *A, int const *B, int N, int M)
{
	int i = 0, j = 0;
	while (i < N || j < M)
	{
		if (i < N && j < M)
		{
			if (A[i] == B[j])
			{
				printf("%d ", A[i]);
				i++;
				j++;
			}
			else if (A[i] < B[j])
				i++;
			else if (A[i] > B[j])
				j++;
		}
		else
			break;
	}
}

int main()
{
	int N = 0, M = 0;
	scanf("%d %d", &N, &M);
	int *A = calloc(N, sizeof(int));
	int *B = calloc(M, sizeof(int));
	for (int i = 0; i < N; i++)
		scanf("%d", &A[i]);
	for (int i = 0; i < M; i++)
		scanf("%d", &B[i]);
	cross(A, B, N, M);
	free(A);
	free(B);
	return 0;
}