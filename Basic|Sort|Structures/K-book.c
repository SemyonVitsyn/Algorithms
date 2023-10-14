#include <stdio.h>
#include <stdlib.h>

#define max(elem1, elem2) ((elem1 > elem2) ? elem1 : elem2)

int check(int const *arr, int K, int N, int M)
{
	int val = 0, count = 0;
	while (count < K)
	{
		for (int i = 0; i < N; i++)
		{
			val += arr[i];
			if (val > M && i != N-1)
			{
				val = arr[i];
				count++;
			}
			else if (i == N-1)
			{
				count++;
				if (val > M)
					count++;
			}
		}
		if (count > K)
		{
			count = 0;
			val = 0;
			M++;
		}
		else
			break;
	}
	return M;
}

int main()
{
	int K = 0, N = 0;
	scanf("%d %d", &K, &N);
	int *arr = calloc(N, sizeof(int));
	int sum = 0, max_val = 0;
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &arr[i]);
		sum += arr[i];
		if (arr[i] > max_val)
			max_val = arr[i];
	}
	int M = max(max_val, sum / K);
	M = check(arr, K, N, M);
	printf("%d", M);
	free(arr);
	return 0;
}
