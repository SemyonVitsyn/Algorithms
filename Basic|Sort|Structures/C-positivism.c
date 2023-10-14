#include <stdio.h>
#include <stdlib.h>

int main()
{
	int N = 0, M = 0;
	scanf("%d %d", &N, &M);
	int **matrix = calloc(N, sizeof(int*));
	for (int i = 0; i < M; i++)
		matrix[i] = calloc(M, sizeof(int));
	int *sum_arr = calloc(N + M, sizeof(int));
	int val = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			scanf("%d", &val);
			matrix[i][j] = val;
			sum_arr[i] += val;
			sum_arr[N+j] += val;
		}
	for (int i = 0; i < N + M; i++)
		printf("%d\n", sum_arr[i]);
	return 0;
}
