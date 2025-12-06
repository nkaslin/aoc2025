#include "template.h"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ifstream fin ("in.txt");
    ofstream fout ("out.txt");

    string line;
    int res = 0;

    while (getline(fin, line)) {
        stringstream ss(line);
        
        int mx1 = 0, mx2 = 0;
        int n = line.length();
        for (int i=0; i<n; i++) {
            int x = line[i] - '0';
            if (x > mx1 && i < n - 1) {
                mx1 = x;
                mx2 = 0;
            } else if (x > mx2) {
                mx2 = x;
            }
        }
        res += 10 * mx1 + mx2;

    }
    fout << res << '\n';
    return 0;
}
