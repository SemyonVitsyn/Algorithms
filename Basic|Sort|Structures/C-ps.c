#include <stdio.h>
#include <stdlib.h>

typedef struct command
{
	char type;
	int val;
} Com;

int positivism(int **matrix, int* sum_arr, Com *op_arr, int N, int M)
{
	int size = 0, changed = 1;
	while (changed == 1 && size < N * M)
	{
		changed = 0;
		for (int idx = 0; idx < N + M; idx++)
			if (sum_arr[idx] < 0)
			{
				sum_arr[idx] = -sum_arr[idx];
				changed = 1;
				if (idx < N)
				{
					for (int i = 0; i < M; i++)
					{
						matrix[idx][i] = -matrix[idx][i];
						sum_arr[N + i] += 2 * matrix[idx][i];
					}
					op_arr[size].type = 'l';
					op_arr[size].val = idx;
					size++;
				}
				else
				{
					for (int i = 0; i < N; i++)
					{
						matrix[i][idx-N] = -matrix[i][idx-N];
						sum_arr[i] += 2 * matrix[i][idx-N];
					}
					op_arr[size].type = 'c';
					op_arr[size].val = idx - N;
					size++;
				}
			}
	}
	return size;
}

int main()
{
	int N = 0, M = 0;
	scanf("%d %d", &N, &M);
	int **matrix = calloc(N, sizeof(int*));
	for (int i = 0; i < N; i++)
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
	Com *op_arr = calloc(N * M, sizeof(Com));
	int size = positivism(matrix, sum_arr, op_arr, N, M);
	if (size < N * M)
	{
		for (int i = 0; i < size; i++)
			printf("%c %d\n", op_arr[i].type, op_arr[i].val);
	}
	else
		printf("Impossible\n");
	for (int i = 0; i < N; i++)
		free(matrix[i]);
	free(matrix);
	free(sum_arr);
	free(op_arr);
	return 0;
}