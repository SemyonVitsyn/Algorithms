#include <iostream>

int minAttempts(int N, int K) {
	if (N == 1)
		return 0;

	int** dp = new int*[2];
	for (int i = 0; i < 2; ++i)
		dp[i] = new int[K+1]();

	for (int i = 1; i < N; ++i)
		for (int j = 1; j <= K; ++j) {
			if (i == 1)
				dp[i%2][j] = 2;
			else if (j == 1)
				dp[i%2][j] = dp[(i+1)%2][j] + 1; // dp[i][j] = dp[i-1][j] + 1;
			else
				dp[i%2][j] = dp[(i+1)%2][j-1] + dp[(i+1)%2][j]; // dp[i][j] = dp[i-1][j-1] + dp[i-1][j];

			if (dp[i%2][j] >= N) {
				delete[] dp[0];
				delete[] dp[1];
				delete[] dp;

				return i;
			}
		}

	return -1;
}

int main()
{
	int N = 0, K = 0;
	std::cin >> N >> K;
	std::cout << minAttempts(N, K);
	return 0;
}
