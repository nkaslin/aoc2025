#include "template.h"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ifstream fin ("in.txt");
    ofstream fout ("out.txt");

    int cur = 50, res = 0;
    string line;

    while (fin >> line) {
        int x = 0;
        int mul = 1;
        for (int i=line.length()-1; i>0; i--) {
            x += (line[i] - '0') * mul;
            mul *= 10;
        }

        res += x / 100;
        x %= 100;
        int zero_pre = cur == 0;
        if (line[0] == 'L') {
            cur -= x;
        } else {
            cur += x;
        }

        if (cur >= 100 || cur <= 0) {
            res++;
        }

        if (cur <= 0) {
            res -= zero_pre;
        }
        cur = (cur + 1000000) % 100;
        // fout << cur << " " << line << " " << res << endl;

    }
    fout << res << endl;

    return 0;
}
