#include <iostream>
#include <unordered_map>

uint64_t count(uint64_t mask, std::unordered_map<uint64_t, uint64_t>& map, int N, int M) {
	if (map.find(mask) != map.end())
		return map[mask];

	uint64_t sum = 0;
	int cnt = 0, i = -1, j = -1;
	for (int idx_i = N-1; idx_i >= 0; --idx_i)
		for (int idx_j = M-1; idx_j >= 0; --idx_j)
			if (mask & ((uint64_t)1<<(M * idx_i + idx_j))) {
				if (i == -1 && j == -1) {
					i = idx_i;
					j = idx_j;
				}
				cnt++;
			}

	if (cnt <= 1)
		return map[mask] = 0;


	if (i >= 1)
		if (mask & ((uint64_t)1<<((i-1) * M + j))) {
			if (cnt == 2)
				return map[mask] = 1;
			else
				sum += count(mask - ((uint64_t)1<<((i-1) * M + j)) - ((uint64_t)1<<(i * M + j)), map, N, M);
		}

	if (i >= 2)
		if (mask & ((uint64_t)1<<((i-1) * M + j)) && mask & ((uint64_t)1<<((i-2) * M + j))) {
			if (cnt == 3)
				return map[mask] = 1;
			else
				sum += count(mask - ((uint64_t)1<<((i-2) * M + j)) - ((uint64_t)1<<((i-1) * M + j)) - ((uint64_t)1<<(i * M + j)), map, N, M);
		}

	if (j >= 1)
		if (mask & ((uint64_t)1<<(i * M + j - 1))) {
			if (cnt == 2)
				return map[mask] = 1;
			else
				sum += count(mask - ((uint64_t)1<<(i * M + j - 1)) - ((uint64_t)1<<(i * M + j)), map, N, M);
		}

	if (j >= 2)
		if (mask & ((uint64_t)1<<(i * M + j - 1)) && mask & ((uint64_t)1<<(i * M + j - 2))) {
			if (cnt == 3)
				return map[mask] = 1;
			else
				sum += count(mask - ((uint64_t)1<<(i * M + j - 2)) - ((uint64_t)1<<(i * M + j - 1)) - ((uint64_t)1<<(i * M + j)), map, N, M);
		}

	return map[mask] = sum;
}

int main()
{
	int N = 0, M = 0;
	std::cin >> N >> M;

	std::unordered_map<uint64_t, uint64_t> map;

	if (N < M)
		std::swap(N, M);

	std::cout << count(((uint64_t)1<<(N*M))-1, map, N, M);

	return 0;
}