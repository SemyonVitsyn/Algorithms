#include <iostream>

std::string min(const std::string& first, const std::string& second) {
	return (first.size() < second.size() || first > second || first == "?")? second : first;
}

std::string copy_str(const std::string& src, int from, int to) {
	std::string res;
	for (int i = from; i < to; ++i)
		res.push_back(src[i]);
	return res;
}

int main() {
	std::string first, second;
	std::cin >> first >> second;

	int** arr = new int*[2];
	arr[0] = new int[first.size()+1]();
	arr[1] = new int[first.size()+1]();

	int max = 0;
	std::string temp, answer;
	answer = "?";

	for (int j = 1; j <= first.size(); j++)
		if (first[j-1] == second[0]) {
			arr[0][j] = 1;
			max = 1;
			temp = second[0];
			answer = min(answer, temp);
		}
		else
			arr[0][j] = 0;

	for (int i = 1; i <= second.size(); i++) {
		for (int j = 1; j <= first.size(); j++)
			if (first[j-1] == second[i-1]) {
				arr[i%2][j] = arr[(i-1)%2][j-1] + 1;
				if (arr[i%2][j] >= max) {
					max = arr[i%2][j];
					temp = copy_str(first, j - max, j);
					answer = min(answer, temp);
				}
			}
			else
				arr[i%2][j] = 0;
	}

	if (answer != "?")
		std::cout << answer;

	delete[] arr[0];
	delete[] arr[1];
	delete[] arr;

	return 0;
}
