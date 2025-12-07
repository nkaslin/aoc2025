#include "template.h"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ifstream fin ("in.txt");
    ofstream fout ("out.txt");
    long long res = 0;

    string line;
    vector<long long> counts(1000, 0ll);
    getline(fin, line);
    for (int i=0; i<line.length(); i++) {
        if (line[i] == 'S') {
            counts[i]++;
        }
    }

    int n = line.length();
    while (getline(fin, line)) {
        vector<long long> next_counts(1000, 0ll);
        for (int i=0; i<1000; i++) {
            if (counts[i] != 0) {
                if (line[i] == '^') {
                    if (i-1 >= 0) {
                        next_counts[i-1] += counts[i];
                    } 
                    if (i+1 < n) {
                        next_counts[i+1] += counts[i];
                    }
                    res += counts[i];
                } else {
                    next_counts[i] += counts[i];
                }
            }
        }
        counts = next_counts;
    }

    fout << res + 1 << '\n';
    return 0;
}
