#include <stdio.h>
#include <stdlib.h>

#define max(elem1, elem2) (elem1 > elem2) ? elem1 : elem2

int minmax(int const *arr1, int const *arr2, int length)
{
	int min = max(arr1[0], arr2[0]);
	int curr = 0, idx = 1;
	for (int i = 1; i < length; i++)
	{
		curr = max(arr1[i], arr2[i]);
		if (min >= curr)
		{
			min = curr;
			idx = i + 1;
		}
		else
			break;
	}
	return idx;
}

int main()
{
	int N = 0, M = 0, L = 0;
	scanf("%d %d %d", &N, &M, &L);
	int **arr = calloc(N + M, sizeof(int*));
	for (int i = 0; i < N + M; i++)
		arr[i] = calloc(L, sizeof(int));
	for (int i = 0; i < N+M; i++)
		for (int j = 0; j < L; j++)
			scanf("%d", &arr[i][j]);
	int Q = 0, idx1 = 0, idx2 = 0;
	scanf("%d", &Q);
	for (int i = 0; i < Q; i++)
	{
		scanf("%d %d", &idx1, &idx2);
		printf("%d\n", minmax(arr[idx1-1], arr[idx2+N-1], L));
	}
	for (int i = 0; i < N + M; i++)
		free(arr[i]);
	free(arr);
}
