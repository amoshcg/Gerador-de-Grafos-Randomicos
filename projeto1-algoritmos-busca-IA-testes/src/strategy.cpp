#include "strategy.hpp"
#include "print.hpp"

#include <iostream>
#include <vector>
#include <tuple>
#include <set>
#include <queue>
#include <functional>
#include <map>

// If tot_dist = -1, the starting node cannot reach the finish node
DATA bfs(Graph &g, int max_distance, bool is_test){
    bool limit_distance = max_distance != -1;
    std::queue<Node> q;
    q.push(Node(g.startNode, 0, 0));
    std::set<std::string> generated_nodes;
    std::map<std::string, std::string> parent_map;
    
    int iteration = 0;
    bool found = false;
    int tot_dist = -1;        
    generated_nodes.insert(g.startNode);
    int attempt_cnt = 1;

    while(!q.empty() and !found){        
        Node node = q.front(); q.pop();

        if(node.state == g.endNode){
            tot_dist = node.g;
            found = true;
        } 
        
        if(!found){            
            for(auto [u, d] : g.node_edges[node.state]){
                attempt_cnt++;
                if(!generated_nodes.count(u) and (!limit_distance or d + node.g <= max_distance)){                       
                    generated_nodes.insert(u);
                    parent_map[u] = node.state;
                    q.push(Node(u, d + node.g, 0));
                }  
            } 
            
            iteration++;
            // print_iteration(iteration, q, attempt_cnt, is_test);
            // if(limit_distance)  print_available_distance(max_distance, node.g);
        }
    }
    
    // print_result(g.endNode, parent_map, tot_dist, attempt_cnt);
    return {iteration, tot_dist, attempt_cnt};
}

// It tot_dist = -1, the starting node cannot reach the finish node
DATA a_star(Graph &g, bool is_test){
    std::set<Node> frontier;    
    frontier.insert(Node(g.startNode, 0, g.node_heuristic[g.startNode]));

    std::map<std::string, int> generated_nodes;
    std::map<std::string, std::string> parent_map;
    generated_nodes[g.startNode] = g.node_heuristic[g.startNode];

    int iteration = 0;
    bool found = false;
    int tot_dist = -1;    
    int attempt_cnt = 1;

    while(!frontier.empty() and !found){        
        auto fbegin = frontier.begin();
        Node node = *fbegin;
        frontier.erase(fbegin);        
        
        if(node.state == g.endNode){
            tot_dist = node.g;            
            found = true;
        } 
        
        if(!found){
            for(auto [u, d] : g.node_edges[node.state]){                
                Node prox(u, d + node.g, g.node_heuristic[u]);                
                attempt_cnt++;
                if(!generated_nodes.count(u) or generated_nodes[u] > prox.g){        
                    if(generated_nodes.count(u)) frontier.erase(Node(u, generated_nodes[u], g.node_heuristic[u]));
                    
                    generated_nodes[u] = prox.g;
                    parent_map[u] = node.state;                    
                    frontier.insert(prox);                    
                }                
            }     
                                
            iteration++;
            // print_iteration(iteration, frontier, attempt_cnt, is_test);
        }
    }
    
    // print_result(g.endNode, parent_map, tot_dist, attempt_cnt);
    return {iteration, tot_dist, attempt_cnt};
}