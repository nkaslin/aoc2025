#include "template.h"

vector<string> get_neighbors(string& line) {
    vector<string> neighbors;
    for (int i=5; i<line.length(); i+=4) {
        neighbors.push_back(line.substr(i, 3));
    }
    return neighbors;
}

int dfs(
    unordered_map<string, vector<string>>& graph, 
    unordered_map<string, int>& paths_to_out,
    string node) 
{
    if (paths_to_out.contains(node)) {
        return paths_to_out[node];
    }
    int pto = 0;
    for (auto neigh: graph[node]) {
        pto += dfs(graph, paths_to_out, neigh);
    }
    paths_to_out[node] = pto;
    return pto;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ifstream fin ("in.txt");
    ofstream fout ("out.txt");

    string line;

    unordered_map<string, vector<string>> graph;
    while (getline(fin, line)) {
        
        string node = line.substr(0, 3);
        vector<string> neighs = get_neighbors(line);
        for (auto n: neighs) {
            graph[node].push_back(n);
        }
    }

    unordered_map<string, int> paths_to_out;
    paths_to_out["out"] = 1;

    int res = dfs(graph, paths_to_out, "you");

    fout << res << '\n';
    return 0;
}
