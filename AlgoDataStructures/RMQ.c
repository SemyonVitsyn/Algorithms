#include <stdio.h>
#include <stdlib.h>

int max(int x1, int x2)
{
	return (x1 > x2)? x1 : x2;
}

int* precalc_log(int max)
{
	int* log2 = calloc(max + 1, sizeof(int));
	for (int i = 0, j = 0; i <= max; i++)
	{
		if (1 << (j + 1) <= i)
			j++;
		log2[i] = j;
	}
	return log2;
}

int** build_sparse_table(int N, int size)
{
	int** table = calloc(size, sizeof (int*));
	for (int i = 0; i < size; i++)
		table[i] = calloc(N, sizeof(int));

	for (int i = 0; i < N; i++)
		scanf("%d", &table[0][i]);

	for (int i = 1; i < size; i++)
		for (int j = 0; j + (1 << i) <= N; j++)
			table[i][j] = max(table[i-1][j], table[i-1][j + (1 << (i - 1))]);

	return table;
}

inline int find_max(int** table, int power, int left, int right)
{
	if (table[power][left] >= table[power][right - (1 << power) + 1])
		return table[power][left];
	else
		return table[power][right - (1 << power) + 1];
}

int main()
{
	int N = 0, M = 0, left = 0, right = 0;
	scanf("%d %d", &N, &M);
	int* log2 = precalc_log(N);
	int** table = build_sparse_table(N, log2[N] + 1);
	for (int i = 0; i < M; i++)
	{
		scanf("%d %d", &left, &right);
		printf("%d\n", find_max(table, log2[right-left+1], left, right));
	}
	for (int i = 0; i < log2[N] + 1; i++)
		free(table[i]);
	free(table);
	free(log2);
	return 0;
}
