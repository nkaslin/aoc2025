#include "template.h"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ifstream fin ("in.txt");
    ofstream fout ("out.txt");

    string line;
    long long res = 0;

    while (getline(fin, line)) {
        stringstream ss(line);
        
        stack<long long> s;
        int n = line.length();
        for (int i=0; i<n; i++) {
            long long x = line[i] - '0';
            while (!s.empty() && s.size() + n - i - 1 >= 12 && x > s.top()) {
                s.pop();
            }
            if (s.size() < 12) {
                s.push(x);
            }   
        }

        long long cur = 0, mul = 1;
        while (!s.empty()) {
            cur += s.top() * mul;
            mul *= 10;
            s.pop();
        }
        res += cur;
    }

    fout << res << '\n';
    return 0;
}