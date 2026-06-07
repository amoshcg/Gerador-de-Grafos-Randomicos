#include "build.hpp"
#include "graph.hpp"
#include "print.hpp"
#include "strategy.hpp"
#include "graph_generator.hpp"
#include <iostream>

int main(){
    std::string filename = "teste";
    cout << "numero de vertices: ";

    int n = 100, m = 100, v, max_weight = 100, probability, oriented;
    cin >> v;


        oriented = 1;

        for(int k = 30; k <= 30; k += 10){

            probability = k;

            cout << "verices: " << v << ", probabilidade: " << probability << ", orientado: " << oriented << endl;

            ofstream output_file("vertices_" + to_string(v) + "_probabilidade_" + to_string(probability) + "_" + "orientado_" + to_string(oriented) + ".csv");

            output_file << "vertices," << "probability," << "oriented,";

            output_file << "algorithm," << "iteration," << "tot_dist," << "attempt_cnt" << endl;


            for(int i = 0; i < 100; i++){

                // Creates the file
                // Parameters: (const int n, const int m, const int v, const int max_weight, const int probability, string file_name, bool oriented)
                graph_to_file(n, m, v, max_weight, probability, filename, oriented);
                Graph g = build(filename + ".txt");

                // int c_size = conected_component_size(g);

                // print_graph(g);

                auto result1 = bfs(g, -1, true);
                auto result2 = a_star(g, true);

                // iteration, tot_dist, attempt_cnt

                output_file << v << "," << probability << "," << oriented << ",";
                output_file << "BFS," << result1.iteration << "," << result1.tot_dist << "," << result1.attempt_cnt << endl;
                output_file << v << "," << probability << "," << oriented << ",";
                output_file << "A*," << result2.iteration << "," << result2.tot_dist << "," << result2.attempt_cnt << endl;
            }
        }
}