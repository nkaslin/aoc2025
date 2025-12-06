#include "template.h"

long long check(long long lower, long long upper) {
    long long res = 0;
    for (long long i = lower; i <= upper; i++) {
        string si = to_string(i);
        int len = si.length();

        for (int j=1; j<len; j++) {
            int ptr = j;
            string s = si.substr(0, j);
            while (ptr < len && s == si.substr(ptr, j)) {
                ptr += j;
            }
            if (ptr >= len) {
                res += i;
                cout << i << endl;
                break;
            }
        }
    }
    return res;
}


int main() {
    cin.tie(0)->sync_with_stdio(0);
    ifstream fin ("in.txt");
    ofstream fout ("out.txt");

    string line;
    fin >> line;
    line += ',';

    int n = line.length();

    long long res = 0;

    int ptr = 0;
    vector<long long> lower, upper;
    for (int i=0; i<n; i++) {
        if (line[i] == '-' || line[i] == ',') {
            long long cur = 0, mult = 1;
            for (int j=i-1; j>=ptr; j--) {
                cur += (line[j] - '0') * mult;
                mult *= 10;
            }
            ptr = i+1;
            if (line[i] == '-') lower.push_back(cur);
            if (line[i] == ',') upper.push_back(cur);
        }
    }

    for (int i=0; i<upper.size(); i++) {
        res += check(lower[i], upper[i]);
    }
    fout << res;

    return 0;
}
