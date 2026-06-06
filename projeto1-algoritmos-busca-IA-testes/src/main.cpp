#include "build.hpp"
#include "graph.hpp"
#include "print.hpp"
#include "strategy.hpp"
#include "graph_generator.hpp"
#include <iostream>

int main(){
    std::string filename = "teste";
    // int is_test;
    // std::cout << "Executar como teste: ";
    // std::cin >> is_test;

    // std::cout << "Digite o nome do arquivo de entrada: ";
    // std::cin >> filename;

    cout << "numero de iteracoes: ";

    int iterations = 0;
    cin >> iterations;

    cout << "numero de vertices, probabilidade, se e orientado: ";

    int n = 100, m = 100, v, max_weight = 100, probability, oriented;
    cin >> v >> probability >> oriented;

    ofstream output_file("vertices_" + to_string(v) + "_probabilidade_" + to_string(probability) + "_" + "orientado_" + to_string(oriented) + ".csv");

    output_file << "vertices," << "probability," << "oriented,";

    output_file << "algorithm," << "iteration," << "tot_dist," << "attempt_cnt" << endl;

    for(int i = 0; i < iterations; i++){
        Graph g = build(filename + ".txt");

        // Creates the file
        // Parameters: (const int n, const int m, const int v, const int max_weight, const int probability, string file_name, bool oriented)
        graph_to_file(n, m, v, max_weight, probability, filename, oriented);

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

    

    // while(1){
    //     std::cout << "Escolha uma das opções abaixo:\n";
    //     std::cout << "(0) Sair\n";
    //     std::cout << "(1) BFS\n";
    //     std::cout << "(2) A*\n";
    //     std::cout << "(3) BFS - distância máxima\n";
    //     int option;
    //     std::cin >> option;

    //     if(option == 1) bfs(g, -1, is_test);
    //     else if(option == 2) a_star(g, is_test);
    //     else if (option == 3){
    //         int max_distance;
    //         std::cout << "Qual a distância máxima?\n";
    //         std::cin >> max_distance;
    //         bfs(g, max_distance, is_test);
    //     }
    //     else break;
    // }    
}