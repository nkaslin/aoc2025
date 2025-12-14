#include "template.h"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ifstream fin ("in.txt");
    ofstream fout ("out.txt");

    int res = 0;
    string line;

    vector<int> sizes = {7, 7, 6, 7, 5, 7};
    // cleaned input first manually: removed the tiles and converted one-digit to two-digit (9 -> 09)
    while (getline(fin, line)) {
        int n = stoi(line.substr(0, 2));
        int m = stoi(line.substr(3, 2));
        int sm = 0;
        int ptr = 0;
        for (int i=7; i<25; i+=3) {
            sm += sizes[ptr++] * stoi(line.substr(i, 2));
        }
        res += n * m > sm;
    }

    fout << res << '\n';
    return 0;
}
