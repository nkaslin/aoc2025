#include "template.h"

vector<string> get_neighbors(string& line) {
    vector<string> neighbors;
    for (int i=5; i<line.length(); i+=4) {
        neighbors.push_back(line.substr(i, 3));
    }
    return neighbors;
}

long long dfs(
    unordered_map<string, vector<string>>& graph, 
    unordered_map<string, long long>& paths_to_x,
    string node) 
{
    if (paths_to_x.contains(node)) {
        return paths_to_x[node];
    }
    long long pto = 0;
    for (auto neigh: graph[node]) {
        pto += dfs(graph, paths_to_x, neigh);
    }
    paths_to_x[node] = pto;
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

    unordered_map<string, long long> dac_to_out, fft_to_out, fft_to_dac, dac_to_fft, svr_to_fft, svr_to_dac;
    dac_to_out["out"] = 1;
    fft_to_out["out"] = 1;
    fft_to_dac["dac"] = 1;
    svr_to_dac["dac"] = 1;
    dac_to_fft["fft"] = 1;
    svr_to_fft["fft"] = 1;

    long long d2o = dfs(graph, dac_to_out, "dac");
    long long f2o = dfs(graph, fft_to_out, "fft");
    long long f2d = dfs(graph, fft_to_dac, "fft");
    long long s2d = dfs(graph, svr_to_dac, "svr");
    long long d2f = dfs(graph, dac_to_fft, "dac");
    long long s2f = dfs(graph, svr_to_fft, "svr");

    // cout << "s2d: " << s2d << endl;
    // cout << "d2f: " << d2f << endl;
    // cout << "f2o: " << f2o << endl;
    // cout << "s2f: " << s2f << endl;
    // cout << "f2d: " << f2d << endl;
    // cout << "d2o: " << d2o << endl;

    long long res = (s2d * d2f * f2o) + (s2f * f2d * d2o); 
    fout << res << '\n';
    return 0;
}
