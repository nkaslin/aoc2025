#include "template.h"

auto parse2 = [](const string& s) {
    long long x, y;
    const char* p = s.c_str();
    x = strtol(p, (char**)&p, 10); ++p;
    y = strtol(p, nullptr, 10);
    return tuple{x, y};
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ifstream fin ("in.txt");
    ofstream fout ("out.txt");
    long long res = 0;

    string line;
    vector<long long> X, Y;
    while (getline(fin, line)) {
        auto [x, y] = parse2(line);
        X.push_back(x);
        Y.push_back(y);
    }
    int n = X.size();

    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            res = max(res, (1 + abs(X[i] - X[j])) * (1 + abs(Y[i] - Y[j])));
        }
    }

    fout << res << '\n';
    return 0;
}
