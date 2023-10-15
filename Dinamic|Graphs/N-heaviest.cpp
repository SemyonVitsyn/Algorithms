#include <iostream>

long long maxRectangleWeight(long long** matrix, int N, int M) {
	long long max_sum = matrix[1][1];

	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= M; ++j)
			matrix[i][j] += matrix[i][j-1];

	long long sum = 0, min_sum = 0;

	for (int start = 1; start <= M; ++start)
		for (int end = M; start <= end; --end) {
			sum = 0, min_sum = 0;
			for (int i = 1; i <= N; ++i) {
				sum += matrix[i][end] - matrix[i][start - 1];
				max_sum = std::max(max_sum, sum - min_sum);
				min_sum = std::min(min_sum, sum);
			}
		}

	return max_sum;
}

int main() {
	int N = 0, M = 0;
	std::cin >> N >> M;

	long long** matrix = new long long*[N+1];
	for (int i = 0; i <= N; ++i)
		matrix[i] = new long long[M+1]();

	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= M; ++j)
			std::cin >> matrix[i][j];

	std::cout << maxRectangleWeight(matrix, N, M);

	for (int i = 0; i <= N; ++i)
		delete[] matrix[i];
	delete[] matrix;
	return 0;
}
