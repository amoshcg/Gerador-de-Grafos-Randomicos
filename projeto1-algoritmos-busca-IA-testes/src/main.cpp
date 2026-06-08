#include "build.hpp"
#include "graph.hpp"
#include "print.hpp"
#include "strategy.hpp"
#include "graph_generator.hpp"
#include <iostream>

int main(){
    std::string filename = "teste";
    cout << "numero de vertices: ";
    int v;
    cin >> v;

    int n = 100, m = 100, max_weight = 100;
    for(int oriented = 0; oriented < 2; oriented++){
        for(int probability = 10; probability <= 100; probability += 10){

            cout << "verices: " << v << ", probabilidade: " << probability << ", orientado: " << oriented << endl;

            ofstream output_file("vertices_" + to_string(v) + "_probabilidade_" + to_string(probability) + "_" + "orientado_" + to_string(oriented) + ".csv");

            output_file << "vertices," << "probability," << "oriented,";

            output_file << "algorithm," << "iteration," << "tot_dist," << "attempt_cnt" << endl;


            for(int i = 0; i < 100; i++){

                // Parameters: (const int n, const int m, const int v, const int max_weight, const int probability, string file_name, bool oriented)
                graph_to_file(n, m, v, max_weight, probability, filename, oriented);
                Graph g = build(filename + ".txt");

                auto result1 = bfs(g, -1, true);
                auto result2 = a_star(g, true);

                output_file << v << "," << probability << "," << oriented << ",";
                output_file << "BFS," << result1.iteration << "," << result1.tot_dist << "," << result1.attempt_cnt << endl;
                output_file << v << "," << probability << "," << oriented << ",";
                output_file << "A*," << result2.iteration << "," << result2.tot_dist << "," << result2.attempt_cnt << endl;
            }
        }
    }
}