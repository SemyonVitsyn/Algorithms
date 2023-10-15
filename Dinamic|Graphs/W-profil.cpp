#include <iostream>

bool compatibility(int prf1, int prf2, int size) {
	for (int i = 0; i < size - 1; ++i)
		if (prf1 % 4 == prf2 % 4 && (prf1 % 4 == 0 || prf1 % 4 == 3))
			return false;
		else {
			prf1 = prf1 >> 1;
			prf2 = prf2 >> 1;
		}

	return true;
}

long long combinationsCount(int N, int M) {
	bool **dp = new bool*[1<<N];
	for (int i = 0; i < 1<<N; ++i)
		dp[i] = new bool[1<<N]();

	long long** matrix = new long long*[M];
	for (int i = 0; i < M; ++i)
		matrix[i] = new long long[1<<N]();

	for (int i = 0; i < 1<<N; ++i)
		for (int j = 0; j < 1<<N; ++j)
			if (compatibility(i, j, N))
				dp[i][j] = true;
			else
				dp[i][j] = false;

	for (int j = 0; j < 1<<N; ++j)
		matrix[0][j] = 1;

	for (int k = 1; k < M; ++k)
		for (int i = 0; i < 1<<N; ++i)
			for (int j = 0; j < 1<<N; ++j)
				matrix[k][i] += matrix[k-1][j] * dp[j][i];

	long long answer = 0;
	for (int i = 0; i < 1<<N; ++i)
		answer += matrix[M-1][i];

	for (int i = 0; i < 1<<N; ++i)
		delete[] dp[i];
	delete[] dp;

	for (int i = 0; i < M; ++i)
		delete[] matrix[i];
	delete[] matrix;

	return answer;
}

int main() {
	int M = 0, N = 0;
	std::cin >> M >> N;

	std::cout << ((N < M)? combinationsCount(N, M) : combinationsCount(M, N));

	return 0;
}
