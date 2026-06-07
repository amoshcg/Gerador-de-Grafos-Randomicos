#include <bits/stdc++.h>
using namespace std;

// Returns the cartesian product of A and B
// A is the set that contains the numbers from a consecutive integer sequence from 0 to n
// B is the set that contains the numbers from a consecutive integer sequence from 0 to m
set<pair<int,int>> cartesian_product(const int n, const int m){
    set<pair<int,int>> points;
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= m; j++){
            points.insert({i, j});
        }
    }
    return points;
}

// Returns randomly selected integer pairs from the cartesian product of A and B
// A is the set that contains the numbers from a consecutive integer sequence from 0 to n
// B is the set that contains the numbers from a consecutive integer sequence from 0 to m
set<pair<int,int>> make_vertices(const int n, const int m, const int v){
    set<pair<int,int>> points = cartesian_product(n, m);
    set<pair<int,int>> result;

    random_device rd;
    for(int i = 0; i < v; i++){
        uniform_int_distribution<int> distribution(0, points.size() - 1);
        int random_number = distribution(rd);
        auto it = points.begin();
        for(int i = 0; i < random_number; i++) it++;
        auto vertex = *it;
        result.insert(vertex);
        points.erase(vertex);
    }
    return result;
}

// Returns a pair of points
pair<pair<int,int>,pair<int,int>> random_points(set<pair<int,int>> &vertices){
    random_device rd;
    uniform_int_distribution<int> distribution(0, vertices.size() - 1);
    int random_number = distribution(rd);

    auto it = vertices.begin();
    for(int i = 0; i < random_number; i++) it++;

    auto removido = *it;
    vertices.erase(*it);

    uniform_int_distribution<int> distribution2(0, vertices.size() - 1);
    random_number = distribution2(rd);
    it = vertices.begin();
    for(int i = 0; i < random_number; i++) it++;

    vertices.insert(removido);
    return {removido, *it};
}

// Returns the floored Euclidian Distance
int distance(pair<int,int> a, pair<int,int> b){
    int ax = a.first, ay = a.second;
    int bx = b.first, by = b.second;
    return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}

// Adds zeros in front of the strings x and y until their size is equal to the size argument
string add_pref(string x, string y, int size){
    string pref1, pref2;
    for(int i = 0; i < size - x.size(); i++) pref1 += "0";
    for(int i = 0; i < size - y.size(); i++) pref2 += "0";
    return pref1 + x + pref2 + y;
}

vector<pair<string, int>> make_heuristic(int n, int m, int v){
    vector<pair<string, int>> result;
    auto points = make_vertices(n, m, v);
    auto [start, finish] = random_points(points);

    points.erase(start);
    points.erase(finish);

    int biggest = max(n, m), size = 0;
    while(biggest){
        biggest /= 10;
        size++;
    }

    string start_name = add_pref(to_string(start.first), to_string(start.second), size);
    string finish_name = add_pref(to_string(finish.first), to_string(finish.second), size);
    result.push_back({"s" + start_name, distance(start, finish)});
    result.push_back({"f" + finish_name, distance(finish, finish)});

    for(auto v:points){
        string name = add_pref(to_string(v.first), to_string(v.second), size);
        result.push_back({"p" + name, distance(v, finish)});
    }

    // for(int i = 0; i < result.size(); i++){
    //     cout << result[i].first << " " << result[i].second << endl;
    // }
    return result;
}

map<string, set<string>> make_edges(vector<pair<string, int>> heuristic, int max_weight){
    map<string, set<string>> result;

    for(int i = 0; i < heuristic.size(); i++){
        for(int j = 0; j < heuristic.size(); j++){
            if(i == j) continue;

            string a = heuristic[i].first, b = heuristic[j].first;
            result[a].insert(b);
        }
    }
    return result;
}

struct graph{
    vector<pair<string, int>> heuristic;
    map<string, set<string>> edges;
};

// The probability must be in percentage
graph prune_edges(const int n, const int m, const int v, const int max_weight, const int probability){
    vector<pair<string, int>> heuristic = make_heuristic(n, m, v);
    map<string, set<string>> edges = make_edges(heuristic, max_weight);

    random_device rd;
    uniform_int_distribution<int> distribution(1, 100);

    for(int i = 0; i < heuristic.size(); i++){
        set<string> removed;

        auto &neighbours = edges[heuristic[i].first];
        for(auto &e:neighbours){
            int random_number = distribution(rd);
            if(random_number > probability) removed.insert(e);
        }
        for(auto r:removed) neighbours.erase(r);
    }

    // for(int i = 0; i < heuristic.size(); i++){
    //     cout << edges[heuristic[i].first].size() << endl;
    // }

    return {heuristic, edges};
}

map<string, set<string>> remove_duplicates(map<string, set<string>> edges){
    for(auto &[current, neighbours]:edges){
        vector<string> removed;

        for(auto &neighbour:neighbours){
            if (edges[neighbour].count(current)) removed.push_back(neighbour);
        }
        for(auto r:removed) neighbours.erase(r);
    }
    return edges;
}

void graph_to_file(const int n, const int m, const int v, const int max_weight, const int probability, string file_name, bool oriented){
    ofstream output_file(file_name + ".txt");

    if(!output_file.is_open()){
        cout << "Error in opening file" << file_name << endl;
        return;
    }

    auto [heuristic, edges] = prune_edges(n, m, v, max_weight, probability);

    if(!oriented){
        edges = remove_duplicates(edges);
    }

    string start, finish;
    for(auto &[name, h]:heuristic){
        if(name.front() == 's') start = name;
        if(name.front() == 'f') finish = name;
    }

    output_file << "ponto_inicial(" << start << ")." << "\n";
    output_file << "ponto_final(" << finish << ")." << "\n";

    output_file << "orientado(s)." << "\n";

    random_device rd;
    uniform_int_distribution<int> distribution(1, max_weight);

    for(int i = 0; i < heuristic.size(); i++){
        string name = heuristic[i].first;
        int dis = heuristic[i].second;
        for(auto &e:edges[name]){
            output_file << "pode_ir(" << name << "," << e << "," << distribution(rd) + dis << ")." << "\n";
        }
    }

    for(auto &[name, h_value]:heuristic){
        output_file << "h(" <<  name << "," << finish << "," << h_value << ")." << "\n";
    }
}

// int main(){
//     int n, m, v, max_weight, probability, oriented;
//     cin >> n >> m >> v >> max_weight >> probability >> oriented;

//     string file_name;
//     cin >> file_name;

//     graph_to_file(n, m, v, max_weight, probability, file_name, oriented);
// }