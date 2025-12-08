#include "template.h"

auto parse3 = [](const string& s) {
    long long x, y, z;
    const char* p = s.c_str();
    x = strtol(p, (char**)&p, 10); ++p;
    y = strtol(p, (char**)&p, 10); ++p;
    z = strtol(p, nullptr, 10);
    return tuple{x, y, z};
};

double dist(
    long long x1, long long y1, long long z1, 
    long long x2, long long y2, long long z2
) {
    long long dx = x1 - x2;
    long long dy = y1 - y2;
    long long dz = z1 - z2;
    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

vector<int> parent(2000), size_(2000);
void make_set(int v) {
    parent[v] = v;
    size_[v] = 1;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return find_set(parent[v]);
}

bool union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a == b)
        return false;
    if (size_[a] < size_[b])
        swap(a, b);
    parent[b] = a;
    size_[a] += size_[b];
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ifstream fin ("in.txt");
    ofstream fout ("out.txt");
    int res = 1;

    string line;
    vector<long long> X, Y, Z;
    while (getline(fin, line)) {
        auto [x, y, z] = parse3(line);
        X.push_back(x);
        Y.push_back(y);
        Z.push_back(z);
    }
    int n = X.size();

    vector<tuple<double, int, int>> dists;
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            double d = dist(X[i], Y[i], Z[i], X[j], Y[j], Z[j]);
            dists.push_back({d, i, j});
        }
    }
    sort(dists.begin(), dists.end());

    for (int i=0; i<n; i++) {
        make_set(i);
    }

    for (int k=0; k<1000; k++) {
        auto [_, i, j] = dists[k];
        union_sets(i, j);
    }

    vector<int> sizes(n);
    for (int i=0; i<n; i++) {
        int p = find_set(i);
        sizes[p] = size_[p];
    }

    sort(sizes.begin(), sizes.end(), std::greater<int>());
    for (int i=0; i<3; i++) {
        res *= sizes[i];
    }

    fout << res << '\n';
    return 0;
}
