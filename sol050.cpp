#include "template.h"

bool check(vector<pair<long long, long long>>& ranges, long long x) {
    for (auto &p: ranges) {
        if (x >= p.first && x <= p.second) {
            return true;
        }
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ifstream fin ("in.txt");
    ofstream fout ("out.txt");

    vector<pair<long long, long long>> ranges;
    vector<long long> nums;
    int res = 0;

    string line;
    while (fin >> line) {
        size_t dash = line.find('-');
        if (dash != string::npos) {
            long long a = stoll(line.substr(0, dash));
            long long b = stoll(line.substr(dash + 1));
            ranges.emplace_back(a, b);
        } else {
            nums.push_back(stoll(line));
        }
    }

    for (auto x: nums) {
        res += check(ranges, x);
    }

    fout << res << '\n';
    return 0;
}
