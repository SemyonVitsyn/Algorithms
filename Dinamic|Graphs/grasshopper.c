#include <stdio.h>
#include <stdlib.h>

int* paths_count(int N, int M)
{
	int* dp = calloc(N, sizeof(int));
	dp[0] = 1;
	for (int i = 1; i < N; i++)
	{
		if (i < M)
			dp[i] = 1;
		for (int j = 1; j <= M; j++)
			if (i - j >= 0)
				dp[i] += dp[i - j];
	}
	return dp;
}

int main()
{
	int N = 0, M = 0;
	scanf("%d %d", &N, &M);
	int* dp = paths_count(N, M);
	printf("%d", dp[N-1]);
	free(dp);
	return 0;
}
