#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

enum color {
	WHITE = 1,
	GREY = 2,
	BLACK = 3
};

std::vector<int> cycle(std::vector<std::vector<int>>& G) {
	std::vector<char> color(N, WHITE);
	std::vector<int> P(N, -1), cycle(0);
	std::vector<bool> mark(N, false);
	std::stack<int> S;

	for (int u = 0; u < N; ++u)
		if (color[u] == WHITE) {
			color[u] = GREY;
			S.push(u);
			while (!S.empty()) {
				int v = S.top(), count  = 0;
				for (int i = 0; i < G[v].size(); ++i)
					if (color[G[v][i]] == GREY) {
						int end = v, start = G[v][i];
						while (end != P[start]) {
							cycle.push_back(end + 1);
							end = P[end];
						}
						return cycle;
					}
					else if (color[G[v][i]] == WHITE) {
						S.push(G[v][i]);
						color[G[v][i]] = GREY;
						P[G[v][i]] = v;
						count++;
					}
				if (count == 0) {
					S.pop();
					color[v] = BLACK;
				}
			}
		}

	return cycle;
}

int main() {
	int N = 0, M = 0;
	std::cin >> N >> M;
	std::vector<std::vector<int>> G(N);

	for (int i = 0; i < M; ++i) {
		int v1 = 0, v2 = 0;
		std::cin >> v1 >> v2;
		G[v1-1].push_back(v2-1);
	}

	std::vector<int> path = cycle(G, N);
	std::reverse(path.begin(), path.end());
	if (!path.empty()) {
		std::cout << "YES" << '\n';
		for (int i = 0; i < path.size(); ++i)
			std::cout << path[i] << " ";
	}
	else
		std::cout << "NO";

	return 0;
}