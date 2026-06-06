#include "graph.hpp"
#include "build.hpp"
#include <iostream>
#include <assert.h>
#include <fstream>

bool contains(std::string &s, std::string t){
    return s.find(t) != std::string::npos;
}

std::string extract_node(std::string &s){
    int i = 0;
    while(s[i] != '(') i++;
    i++;

    std::string r = "";
    while(s[i] != ')'){
        if(s[i] != ' ') r += s[i];
        i++;
    }

    return r;
}

void set_is_oriented(Graph &g, std::string &s){
    g.is_oriented = contains(s, "s");
}

std::tuple<std::string, std::string, int> extract_edge(std::string &s){
    int i = 0;
    while(s[i] != '(') i++;
    i++;

    std::string u, v;
    
    while(s[i] != ','){
        if(s[i] != ' ') u += s[i];
        i++;
    }
    
    i++;
    while(s[i] != ','){
        if(s[i] != ' ') v += s[i];
        i++;
    }
    
    i++;
    
    int d = 0;
    while(s[i] != ')'){
        if(s[i] != ' '){
            d*=10;
            d += s[i] - '0';
        }
        i++;
    }

    return make_tuple(u, v, d);
}

void add_edge_cost(Graph &g, std::string &s){
    auto [u, v, d] = extract_edge(s);

    g.node_edges[u].push_back({v, d});
    if(!g.is_oriented) g.node_edges[v].push_back({u, d});
}

void add_edge_heuristic(Graph &g, std::string &s){
    auto [u, v, d] = extract_edge(s);    
    assert(v == g.endNode);
    
    g.node_heuristic[u] = d;    
}

Graph build(const std::string& filename){
    Graph g;
    std::string s;
    std::ifstream file(filename);
    while(std::getline(file, s)){        
        if(contains(s, "ponto_inicial")) g.startNode = extract_node(s);
        else if(contains(s, "ponto_final")) g.endNode = extract_node(s);
        else if(contains(s, "orientado")) set_is_oriented(g, s);
        else if(contains(s, "pode_ir")) add_edge_cost(g, s);
        else add_edge_heuristic(g, s);
    }
    file.close();
    return g;
}