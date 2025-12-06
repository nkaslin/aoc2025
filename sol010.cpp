#include "template.h"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ifstream fin ("in.txt");
    ofstream fout ("out.txt");

    int cur = 50, res = 0;
    string line;

    while (fin >> line) {
    	// fout << line << endl;
        int x = 0;
        int mul = 1;
        for (int i=line.length()-1; i>0; i--) {
            x += (line[i] - '0') * mul;
            mul *= 10;
        }
        cur += 1000000;
        if (line[0] == 'L') {
            cur -= x;
        } else {
            cur += x;
        }
        cur %= 100;
        if (cur == 0) {
            res++;
        }
        // fout << (line[0] == 'L' ? '-' : '+') << " " << x << endl;
    }
    fout << res << endl;

    return 0;
}
