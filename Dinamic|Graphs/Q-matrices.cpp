#include <iostream>
#include <limits>

long long mult(int* arr, long long** dp, int i, int j) {
	if (dp[i][j] != 0 || i >= j)
		return dp[i][j];

	long long temp = std::numeric_limits<long long int>::max();
	for (int k = i; k < j; ++k)
		temp = std::min(temp, mult(arr, dp, i, k) + mult(arr, dp, k+1, j) + arr[i] * arr[k+1] * arr[j+1]);
	dp[i][j] = temp;
	return temp;
}

long long minOp(int* arr, int N) {
	long long** dp = new long long*[N-1];
	for (int i = 0; i < N - 1; ++i)
		dp[i] = new long long[N-1]();

	for (int i = 0; i < N - 1; ++i)
		for (int j = i; j < N - 1; ++j)
			if (i != j)
				mult(arr, dp, i, j);

	long long answer = dp[0][N-2];

	for (int i = 0; i < N - 1; ++i)
		delete[] dp[i];
	delete[] dp;

	return answer;
}

int main() {
	int N = 0;
	std::cin >> N;
	int* arr = new int[N]();
	for (int i = 0; i < N; ++i) {
		std::cin >> arr[i];
		if (arr[i] == 0) {
			std::cout << 0;
			delete[] arr;
			return 0;
		}
	}

	std::cout << minOp(arr, N);

	delete[] arr;

	return 0;
}