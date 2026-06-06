#include "print.hpp"
#include "graph.hpp"
#include <vector>
#include <tuple>
#include <iostream>
#include <iomanip>
#include <algorithm>


void print_graph(Graph &g){
    for(auto [s, e] : g.node_edges){
        std::cout << s << '\n';
        for(auto [t, d] : e) std::cout << " " << t << " " << d << '\n';
    }
    BLOCK_SEPARATOR;
    std::cout << g.startNode << " - " << g.endNode << " orientado? " << g.is_oriented << '\n';
}


void print_result(std::string endNode, std::map<std::string, std::string> parent_map, int distance, int attempt_cnt){
    BLOCK_SEPARATOR;
    std::cout << "Fim da execução\n";
    if(distance == -1){
        std::cout << "Não foi possível encontrar um caminho\n";
        BLOCK_SEPARATOR;
        return;
    }

    std::cout << "Distância: " << distance <<"\n";    
    std::vector<std::string> path;
    while(endNode != ""){
        path.push_back(endNode);
        endNode = parent_map[endNode];
    }
    std::reverse(path.begin(), path.end());
    std::cout << "Caminho: ";
    for(int i = 0; i < (int) path.size(); i++){
        std::string u = path[i];
        std::cout << u;
        if(i < (int) path.size() - 1) std::cout << " - ";
    }

    std::cout << "\nQuantidade de tentativas de inserções na fronteira: " << attempt_cnt << "\n";   
    BLOCK_SEPARATOR;
}

void print_iteration(int iteration, const std::set<Node, std::less<Node>, std::allocator<Node>> &frontier, int attempt_cnt, bool is_test){    
    if(is_test) return;

    BLOCK_SEPARATOR;
    std::cout << "Iteração: " << iteration << ":\n";
    std::cout << "Lista: ";
    for(Node node : frontier){
        std::cout << "(" << node.state << ": " << node.g << " + " << node.h << " = " << node.f() << ") "; 
    }
    std::cout << "\nQuantidade de tentativas de inserções na fronteira: " << attempt_cnt << "\n";       
}

void print_iteration(int iteration, std::queue<Node> frontier, int attempt_cnt, bool is_test){    
    if(is_test) return;

    BLOCK_SEPARATOR;
    std::cout << "Iteração: " << iteration << ":\n";
    std::cout << "Fila: ";
    while(!frontier.empty()){
        Node node = frontier.front(); frontier.pop();
        std::cout << "(" << node.state << ": " << node.g << " + " << node.h << " = " << node.f() << ") "; 
    }    
    std::cout << "\nQuantidade de tentativas de inserções na fronteira: " << attempt_cnt << "\n";       
}

void print_available_distance(int max_distance, int curr_distance){
    std::cout << "Distância disponível: ";
    int diff = std::max(max_distance - curr_distance, 0);

    std::cout << diff;
    if(diff == 0) std::cout << " - Caminho descartado";
    std::cout << "\n";
}