#ifndef PRINT_H
#define PRINT_H
#include "graph.hpp"
#include <vector>
#include <tuple>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <set>

#define BLOCK_SEPARATOR std::cout << "-----------------------\n"

void print_graph(Graph &g);
void print_result(std::string endNode, std::map<std::string, std::string> parent_map, int distance, int attempt_cnt);
void print_iteration(int iteration, std::queue<Node> frontier, int attempt_cnt, bool is_test);
void print_iteration(int iteration, const std::set<Node, std::less<Node>, std::allocator<Node>> &frontier, int attempt_cnt, bool is_test);
void print_available_distance(int max_distance, int curr_distance);

#endif