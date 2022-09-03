#include <iostream>
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


	Graph graph = {
		/*  1 | 0x01 */ { 8, 4, 18 },
		/*  2 | 0x02 */ { 3, 19 },
		/*  3 | 0x03 */ { 6 },
		/*  4 | 0x04 */ {  },
		/*  5 | 0x05 */ { 15, 12 },
		/*  6 | 0x06 */ { 12, 2 },
		/*  7 | 0x07 */ { 5, 8 },
		/*  8 | 0x08 */ { 18, 4 },
		/*  9 | 0x09 */ { 14, 1, 4 },
		/* 10 | 0x0A */ { 3, 18, 12, 16 },
		/* 11 | 0x0B */ { 19 },
		/* 12 | 0x0C */ { 3 },
		/* 13 | 0x0D */ { 7, 10 },
		/* 14 | 0x0E */ { 17, 16, 10, 18, 1 },
		/* 15 | 0x0F */ { 12 },
		/* 16 | 0x10 */ { 17, 11, 19, 20 },
		/* 17 | 0x11 */ { 9, 11 },
		/* 18 | 0x12 */ { 7, 13 },
		/* 19 | 0x13 */ { 20 },
		/* 20 | 0x14 */ { 3, 10 }
	};

	for (auto node = graph.begin(); node != graph.end(); node++)
		for (auto edge = node->begin(); edge != node->end(); edge++)
			*edge -= 1;

	auto calc_best_path = [](Graph& graph, size_t entries) {

		std::vector<std::vector<size_t>> sections;			// they store the shortest path to the "root"
		std::vector<std::vector<size_t>> tmp_paths;
		std::vector<std::vector<size_t>> paths;
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

	auto [sect1, min_count] = calc_best_path(graph, 2);

	std::cout << "minimum possible move count : " << min_count;
	std::cout << "\nsteps for player on position 1 : \n";

	for (auto it = sect1[0].begin(); it != sect1[0].end(); ++it)
		std::cout << "\t" << *it + 1 << " <==\n";

	std::cout << "\nsteps for player on position 1 : \n";
	for (auto it = sect1[1].begin(); it != sect1[1].end(); ++it)
		std::cout << "\t" << *it + 1 << " <==\n";

	return 0;
}

