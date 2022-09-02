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
		/*  1 | 0x01 */ { 8, 4 },
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

	auto calc_possible_games = [](Graph& graph) {

		std::vector<size_t> sect1, sect2;					// they store the shortest path to the "root"
		std::vector<size_t> steps, intersection {  };		// = sect1\cap sect2


		auto find_min_steps = [&]() {

			// count the steps, which are needed to move to a node from to nodes
			for (auto possible_end : intersection) {

				size_t next = possible_end, counter = 0;
				while ((next = sect1[next]) != BFS_NOT_VISITED) counter++;					// count the first section path (by moving to the "root"-element)

				steps.push_back(counter);			// "save" counted value
				counter = 0;							// ... and reset!

				while ((possible_end = sect2[possible_end]) != BFS_NOT_VISITED) counter++;	// count the second section path

				steps.back() = std::max(steps.back(), counter);					// the maximum is of course required
			}

		};


		sect1 = bfs(graph, 0);
		sect2 = bfs(graph, 1);

		// get the intersection of nodes which could be reached
		for (size_t t = 0; t < graph.size(); t++) {
			if (sect1[t] != BFS_NOT_VISITED && sect2[t] != BFS_NOT_VISITED)
				intersection.push_back(t);
		}

		find_min_steps();

		return std::make_tuple(intersection, steps);
	};

	return 0;
}

