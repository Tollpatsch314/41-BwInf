#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <tuple>

/*

# Definition des Graphens


# Sinnvolle Erweiterungen

- mehr als zwei Spieler

*/

typedef std::vector<std::vector<size_t>> Graph;		// simplifies much

#define BFS_NOT_VISITED SIZE_MAX
#define ROOT_NODE SIZE_MAX

auto bfs(Graph& graph, size_t start) {

	std::vector<size_t> visited(graph.size(), BFS_NOT_VISITED);		// Store at visited_i, where i = the current node, the last node
	std::queue<size_t> Q;											// Queue of the next nodes

	size_t current_node, next_node;

	Q.push(start);

	while (not Q.empty()) {

		current_node = Q.front();
		Q.pop();

		for (size_t t = 0; t < graph[current_node].size(); t++) {
			next_node = graph[current_node][t];

			if (visited[next_node] == BFS_NOT_VISITED && next_node != start) {
				visited[next_node] = current_node;
				Q.push(next_node);
			}
		}

	}

	return visited;
}



int main(int argc, char** argv) {

	
	auto read_file = [](std::string file) {
		Graph graph;
		int n, m;

		std::ifstream in(file, std::ios::in);

		if (in.is_open()) {
			std::string in_str = "";
			in >> n >> m;

			graph = Graph(n, std::vector<size_t>());

			for (size_t t = m; t != 0; t--) {
				in >> n >> m;
				graph[n - 1].push_back(m - 1);
			}

			graph.reserve(n);

		}
		else
		{
			throw std::exception("File does not excist!");
		}

		return graph;
	};

	auto calc_best_path = [](Graph& graph, size_t entries) {
		Graph
			sections,			// they store the shortest path to the "root" from every node referenced to the next node
			tmp_paths,			
			paths;				// the paths trough the graph to the node
		size_t min_move_count = SIZE_MAX;

		sections.reserve(entries);

		auto calc_linked_path = [](std::vector<size_t>& linked_path, size_t start) {
			std::vector<size_t> path;

			while (linked_path[start] != BFS_NOT_VISITED) {
				path.push_back(start);
				start = linked_path[start];
			}

			std::reverse(path.begin(), path.end());

			return path;
		};

		// Calc with bfs the shortest path to every node (from the start node)
		for (size_t t = 0; t < entries; t++) {
			sections.push_back(bfs(graph, t));
		}

		// get the intersection of nodes which could be reached
		for (size_t node = 0; node < graph.size(); node++) {

			for (auto section : sections) {
				if (section[node] == BFS_NOT_VISITED) goto no_match;
			}

			{
				size_t max_size = 0;
				tmp_paths.clear();
				tmp_paths.reserve(sections.size());

				// Calc the path lenghts to the "flashpoint"
				for (auto section : sections) {
					tmp_paths.push_back(calc_linked_path(section, node));
					if (max_size < tmp_paths.back().size()) max_size = tmp_paths.back().size();
					if (min_move_count < max_size) goto no_match;
				}

				min_move_count = max_size;
				paths = tmp_paths;
			}

		no_match:;
		}

		return std::make_tuple(paths, min_move_count);
	};

	std::string file = "";

	try {
		while (true) {

			std::cout << "File: ";
			std::getline(std::cin, file);

			Graph graph = read_file(file);

			auto [paths, min_count] = calc_best_path(graph, 2);

			std::cout << "minimum possible move count : " << min_count << "; possible solution: ";
			std::cout << "\n\path for player on position 1 : 1";

			for (auto it = paths[0].begin(); it != paths[0].end(); ++it)
				std::cout << " ==> " << *it + 1;

			std::cout << "\n\path for player on position 2 : 2";
			for (auto it = paths[1].begin(); it != paths[1].end(); ++it)
				std::cout << " ==> " << *it + 1;

		invalid_answer:
			std::cout << "\nNew file? [Y/N]";
			std::getline(std::cin, file);

			if (!(file == "Y" || file == "y"))
				if (file == "N" || file == "n") return 0;
				else goto invalid_answer;

		}
	}
	catch (std::exception e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 0;
	}
}

