#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

std::vector<int> junctions(const std::vector<std::vector<int>>& graph)
{
	std::vector<int> articulation_points;
	std::vector<int> tin(graph.size());
	std::vector<int> up(graph.size());
	std::vector<int> parent(graph.size(), -1);
	std::vector<bool> visited(graph.size(), false);
	std::vector<bool> cutppint(graph.size(), false);
	std::stack<int> st;
	int time = 0;

	for (int i = 0; i < graph.size(); ++i)
		if (!visited[i])
		{
			tin[i] = up[i] = ++time;
			visited[i] = true;
			st.push(i);

			while (!st.empty()) {
				int v = st.top(), count = 0, max_up = 0;
				for (int j = 0; j < graph[v].size(); ++j) {
					if (graph[v][j] == parent[v])
						continue;

					if (!visited[graph[v][j]]) {
						tin[graph[v][j]] = up[graph[v][j]] = ++time;
						parent[graph[v][j]] = v;
						visited[graph[v][j]] = true;
						st.push(graph[v][j]);
						count++;
					} else {
						up[v] = std::min(up[v], up[graph[v][j]]);
						max_up = std::max(max_up, up[graph[v][j]]);
					}
				}

				if (count == 0 )
			}

			articulation_points.insert(articulation_points.end(), local_points.begin(), local_points.end());
		}

	std::sort(articulation_points.begin(), articulation_points.end());
	return articulation_points;
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

	std::vector<int> articulation_points = junctions(graph);
	std::cout << articulation_points.size() << '\n';
	for (int i = 0; i < articulation_points.size(); ++i)
		std::cout << articulation_points[i] << " ";

	return 0;
}
