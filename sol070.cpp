#include "template.h"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ifstream fin ("in.txt");
    ofstream fout ("out.txt");
    int res = 0;

    string line;
    unordered_set<int> pos;
    getline(fin, line);
    for (int i=0; i<line.length(); i++) {
        if (line[i] == 'S') {
            pos.insert(i);
        }
    }

    int n = line.length();
    while (getline(fin, line)) {
        unordered_set<int> next_pos;
        for (auto i: pos) {
            if (line[i] == '^') {
                if (i-1 >= 0) {
                    next_pos.insert(i-1);
                } 
                if (i+1 < n) {
                    next_pos.insert(i+1);
                }
                res++;
            } else {
                next_pos.insert(i);
            }
        }
        pos = next_pos;
    }

    fout << res << '\n';
    return 0;
}
