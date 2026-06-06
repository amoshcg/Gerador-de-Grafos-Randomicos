#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <vector>
#include <string>
#include <utility>

struct Graph{
    std::map<std::string, std::vector<std::pair<std::string, int>>> node_edges;
    std::map<std::string, int> node_heuristic;
    std::string startNode;
    std::string endNode;
    bool is_oriented = false;
};

struct Node{
    std::string state;
    int g;
    int h;

    Node(std::string s, int g_cost, int h_cost);
    int f() const;
    bool operator<(const Node& other) const;
};

#endif