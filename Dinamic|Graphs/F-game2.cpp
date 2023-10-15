#include <iostream>
#include <vector>

void get_winner(int X, int Y) {
	std::vector<std::vector<bool>> dp(X, std::vector<bool> (Y));

	for (int i = 0 ; i < X; i++)
		for (int j = Y - 1; j >= 0; j--) {
			dp[i][j] = 0;

			for (int x_step = j + 1; x_step < Y; x_step++)
				if (dp[i][x_step] == 0) {
					dp[i][j] = 1;
					break;
				}

			if (dp[i][j] == 1)
				continue;

			for (int y_step = i - 1; y_step >= 0; y_step--)
				if (dp[y_step][j] == 0) {
					dp[i][j] = 1;
					break;
				}

			if (dp[i][j] == 1)
				continue;

			for (int x_step = j + 1, y_step = i - 1; x_step < Y && y_step >= 0; x_step++, y_step--)
				if (dp[y_step][x_step] == 0) {
					dp[i][j] = 1;
					break;
				}
		}

	/*for (int i = 0 ; i < X; i++) {
		for (int j = 0; j < Y; j++)
			std::cout << dp[i][j] << " ";
		std::cout << "\n";
	}*/

	if (dp[X-1][0] == 1)
		std::cout << "F";
	else
		std::cout << "S";
}

int main() {
	int X = 0, Y = 0;
	std::cin >> X >> Y;
	get_winner(X, Y);
	return 0;
}
