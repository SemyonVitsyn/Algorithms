#include <iostream>

int GreatestSubmatrixSize(int N, int** matrix) {

	for (int i = 2; i <= N; i++)
		for (int j = 2; j <= N; j++)
			matrix[i][j] = (matrix[i][j] == 0)? 0 :
					std::min(matrix[i-1][j-1], std::min(matrix[i-1][j], matrix[i][j-1])) + 1;

	int max = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			//std::cout << matrix[i][j] << " ";
			if (max < matrix[i][j])
				max = matrix[i][j];
		}
		//std::cout << "\n";
	}

	return max;
}

int main() {
	int N = 0;
	std::cin >> N;

	int** matrix = new int*[N+1];
	for (int i = 0 ; i <= N; i++)
		matrix[i] = new int[N+1];

	int val = 0;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++) {
			std::cin >> val;
			matrix[i][j] = val;
	}

	std::cout << GreatestSubmatrixSize(N, matrix);

	for (int i = 0; i <= N; i++)
		delete[] matrix[i];
	delete[] matrix;

	return 0;
}
