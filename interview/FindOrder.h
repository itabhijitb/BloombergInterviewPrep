#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <set>
#include <functional>
#include <algorithm>
class Graph {
	typedef char Node;
	std::map<Node, std::vector<Node>> adjList;
	std::set<Node> nodes;
public:
	auto addEdge(Node u, Node v) {
		adjList[u].push_back(v);
		nodes.insert(u);
		nodes.insert(v);
	}
	auto topoSort();
	auto edges(Node u) {
		return adjList[u];
	}
};


auto Graph::topoSort() {
	std::stack<Graph::Node> stack;
	size_t nodeCount = nodes.size();
	std::vector<bool> visited(nodeCount);
	std::function<void(Graph::Node)> topoUtil = [&](size_t u) {
		visited[u] = true;
		for (auto v : adjList[u]) {
			if (visited[v] == false) {
				topoUtil(v);
			}
		}
		stack.push(u);
	};
	for (size_t u = 0; u < nodeCount; u++) {
		if (visited[u] == false) {
			topoUtil(u);
		}
	}

	return stack;
}

auto findOrder(std::vector<std::string> words) {
	size_t n = words.size();
	Graph graph;
	for (size_t i = 0; i < words.size() - 1; i++) {
		auto word1 = words[i], word2 = words[i + 1];
		for (size_t idxCh = 0; idxCh <= std::min(word1.size(), word2.size()); idxCh++) {
			if (word1[idxCh] != word2[idxCh]) {
				graph.addEdge(word1[idxCh], word2[idxCh]);
				break;
			}
		}
	}	
	auto result = graph.topoSort();
	for (; !result.empty();result.pop()) {
		std::cout << result.top() << "," << std::endl;
	}
}