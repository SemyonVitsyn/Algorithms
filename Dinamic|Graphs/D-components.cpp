#include <iostream>
#include <vector>
#include <queue>

std::vector<int> components(const std::vector<std::vector<int>>& graph) {
	std::vector<bool> visited(graph.size(), false);
	std::vector<int> component_num(graph.size(), 0);

	std::queue<int> q;
	int curr_component = 1;

	for (int i = 0; i < graph.size(); ++i) {
		if (visited[i])
			continue;

		visited[i] = true;
		component_num[i] = curr_component;
		q.push(i);

		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (int j = 0; j < graph[v].size(); ++j) {
				if (visited[graph[v][j]])
					continue;

				visited[graph[v][j]] = true;
				component_num[graph[v][j]] = curr_component;
				q.push(graph[v][j]);
			}
		}

		curr_component++;
	}

	std::cout << curr_component - 1 << '\n';
	return component_num;
}

int main() {
	int N = 0, M = 0;
	std::cin >> N >> M;

	std::vector<std::vector<int>> graph(N);
	for (int i = 0; i < M; ++i) {
		int v1 = 0, v2 = 0;
		std::cin >> v1 >> v2;
		graph[v1-1].push_back(v2-1);
		graph[v2-1].push_back(v1-1);
	}

	std::vector<int> component_num = components(graph);
	for (int i = 0; i < N; ++i)
		std::cout << component_num[i] << " ";
	return 0;
}
