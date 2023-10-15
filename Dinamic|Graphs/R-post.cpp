#include <iostream>
#include <vector>
#include <climits>

void minDist(std::vector<int>& X, int N, int M)
{
	std::vector<std::vector<int>> dp(M, std::vector<int>(N, 0));
	std::vector<std::vector<int>> path(M, std::vector<int>(N, 0));

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < i; j++)
			dp[0][i] += (X[i] - X[j]);

	int sum = 0;
	for (int i = 1; i < M; ++i)
		for (int j = i + 1; j < N; ++j)
		{
			dp[i][j] = INT_MAX;
			for (int k = 0; k < j; ++k)
			{
				sum = 0;
				sum += dp[i - 1][k];
				for (int l = k + 1; l < j; ++l)
					sum += std::min(X[l] - X[k], X[j] - X[l]);
				if (dp[i][j] > sum)
				{
					dp[i][j] = sum;
					path[i][j] = k;
				}
			}
		}

	int idx = 0;
	int answer = INT_MAX;
	for (int i = M - 1; i < N; ++i)
	{
		sum = 0;
		sum += dp[M - 1][i];
		for (int j = i + 1; j < N; ++j)
			sum += X[j] - X[i];
		if (answer > sum)
		{
			answer = sum;
			idx = i;
		}
	}
/*
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j)
			std::cout << path[i][j];
		std::cout << '\n';
	}*/

	std::vector<int> result;
	result.push_back(X[idx]);
	for (int i = M - 1; i > 0; --i) {
		idx = path[i][idx];
		result.push_back(X[idx]);
	}

	std::cout << answer << '\n';

	for (int i = M - 1; i >= 0; --i)
		std::cout << result[i] << " ";
}

int main()
{
	int N = 0, M = 0;
	std::cin >> N >> M;

	std::vector<int> X(N);
	for (int i = 0; i < N; ++i)
		std::cin >> X[i];

	minDist(X, N, M);

	return 0;
}
