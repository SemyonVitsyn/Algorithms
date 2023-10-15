#include <iostream>

long long pathsNumber(int N, int M, int K) {
	long long*** dp = new long long**[K+1];
	for (int step = 0; step <= K; ++step)
		dp[step] = new long long*[N+2];
	for (int step = 0; step <= K; ++step)
		for (int i = 0; i <= N+1; ++i)
			dp[step][i] = new long long[M+2]();

	char elem = 0;
	int i_end = 0, j_end = 0;
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= M; ++j) {
			std::cin >> elem;
			switch(elem) {
				case '@': {
					i_end = i;
					j_end = j;
					break;
				}
				case '+': {
					dp[0][i][j] = -1;
					break;
				}
				case '#': {
					dp[0][i][j] = 1;
					break;
				}
				default:
					break;
			}
		}

	for (int step = 1; step <= K; ++step)
		for (int i = 1; i <= N; ++i)
			for (int j = 1; j <= M; ++j)
				if (dp[step-1][i][j] != -1)
						dp[step][i][j] = ((dp[step-1][i-1][j] > 0) ? dp[step-1][i-1][j] : 0) +
										  ((dp[step-1][i+1][j] > 0) ? dp[step-1][i+1][j] : 0) +
										  ((dp[step-1][i][j-1] > 0) ? dp[step-1][i][j-1] : 0) +
										  ((dp[step-1][i][j+1] > 0) ? dp[step-1][i][j+1] : 0);
				else
					dp[step][i][j] = -1;

	long long answer = dp[K][i_end][j_end];

	for (int step = 0; step <= K; ++step)
		for (int i = 0; i <= N; ++i)
			delete[] dp[step][i];
	for (int step = 0; step <= K; ++step)
		delete[] dp[step];
	delete[] dp;

	return answer;
}

int main() {
	int N = 0, M = 0, K = 0;
	std::cin >> N >> M >> K;

	std::cout << pathsNumber(N, M, K);

	return 0;
}

// Плохое решение, можно без массива матриц
