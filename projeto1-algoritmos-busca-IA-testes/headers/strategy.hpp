#ifndef STRATEGY_H
#define STRATEGY_H
#include "graph.hpp"

struct DATA{
    int iteration, tot_dist, attempt_cnt;
};

DATA bfs(Graph &g, int max_distance, bool is_test);
DATA a_star(Graph &g, bool is_test);
int conected_component_size(Graph &g);

#endif