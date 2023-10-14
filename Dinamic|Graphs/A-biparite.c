#include <iostream>
#include <vector>
#include <queue>

bool bipartite(std::vector<std::vector<int>>& G, int N) {
	std::vector<bool> color(N, false), done(N, false);
	std::queue<int> Q;

	for (int i = 0; i < N; ++i)
		if (!done[i]) {
			Q.push(i);
			color[i] = true;
			done[i] = true;
			while (!Q.empty()) {
				int u = Q.front();
				Q.pop();
				for (int j = 0; j < G[u].size(); ++j)
					if (!done[G[u][j]]) {
						Q.push(G[u][j]);
						color[G[u][j]] = !color[u];
						done[G[u][j]] = true;
 					}
					else if (color[G[u][j]] == color[u])
						return false;
			}
	}

	return true;
}

int main()
{
	int N = 0, M = 0;
	std::cin >> N >> M;
	std::vector<std::vector<int>> G(N);

	for (int i = 0; i < M; ++i) {
		int v1 = 0, v2 = 0;
		std::cin >> v1 >> v2;
		G[v1].push_back(v2);
		G[v2].push_back(v1);
	}

	std::cout << (bipartite(G, N)? "YES" : "NO");

	return 0;
}
