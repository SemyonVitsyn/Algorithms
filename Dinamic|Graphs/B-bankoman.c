#include <stdio.h>
#include <stdlib.h>

int min_val(int a, int b)
{
	return (a < b)? a : b;
}

int main()
{
	int N = 0;
	scanf("%d", &N);

	int* arr = calloc(N, sizeof(int));
	for (int i = 0; i < N; i++)
		scanf("%d", &arr[i]);

	int X = 0;
	scanf("%d", &X);

	int* cache = calloc(X + 1, sizeof(int));
	cache[0] = 0;

	int min = 0;
	for (int i = 1; i <= X; i++)
	{
		min = -1;

		for (int j = 0; j < N; j++)
		{
			if (i - arr[j] >= 0 && cache[i - arr[j]] != -1)
			{
				if (min == -1)
					min = cache[i - arr[j]] + 1;
				else
					min = min_val(min, cache[i - arr[j]] + 1);
			}
		}

		cache[i] = min;
	}

	printf("%d\n", cache[X]);

	if (cache[X] != -1)
	{
		int rk = cache[X], idx = X;
		while (rk > 0)
		{
			idx--;
			if (cache[idx] == rk - 1)
			{
				printf("%d ", X - idx);
				X = idx;
				rk--;
			}
		}
	}

	free(arr);
	free(cache);
	return 0;
}
