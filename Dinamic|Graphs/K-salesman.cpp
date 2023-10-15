#include <iostream>
#include <vector>
#include <climits>

void get_min_sum(int N, int M) {
	int** matrix = new int*[N];
	for (int i = 0; i < N; i++)
		matrix[i] = new int[M];

	int val = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			std::cin >> val;
			matrix[i][j] = val;
		}

	for (int j = 1; j < M; j++)
		for (int i = 0; i < N; i++)
			matrix[i][j] += std::min(matrix[i][j-1],
			                        std::min( (i-1 >= 0)? matrix[i-1][j-1] : INT_MAX,
			                                  (i+1 < N)? matrix[i+1][j-1] : INT_MAX));

	int min = INT_MAX;
	int idx = 0;
	for (int i = 0; i < N; i++)
		if (min > matrix[i][M-1]) {
			min = matrix[i][M-1];
			idx = i;
		}

	std::vector<int> trace;

	trace.push_back(idx + 1);
	int i = 0;
	for (int j = M-2; j >= 0; j--) {
		if (((idx-1 >= 0)? matrix[idx-1][j] : INT_MAX) > matrix[idx][j])
			i = idx;
		else
			i = idx - 1;
		if (((idx+1 < N)? matrix[idx+1][j] : INT_MAX) < matrix[i][j])
			i = idx + 1;
		idx = i;
		trace.push_back(idx + 1);
	}

	for (int j = 0; j < N; j++)
		delete[] matrix[j];
	delete[] matrix;

	for (int j = M - 1; j >= 0; j--)
		std::cout << trace[j] << " ";
	std::cout << "\n";

	std::cout << min;
}

int main() {
	int N = 0, M = 0;
	std::cin >> N >> M;
	get_min_sum(N, M);
	return 0;
}
