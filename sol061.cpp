#include "template.h"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ifstream fin ("in.txt");
    ofstream fout ("out.txt");
    long long res = 0;

    string line;
    vector<string> input;
    while (getline(fin, line)) {
        input.push_back(line);
    }

    int n = input.size();
    int i = input[0].size() - 1;

    vector<long long> nums;
    long long calc;
    while (i >= 0) {
        long long cur = 0;
        for (int j=0; j<n-1; j++) {
            if (input[j][i] == ' ') {
                continue;
            }
            cur = cur * 10 + (input[j][i] - '0');
        }
        nums.push_back(cur);
        if (input[n-1][i] != ' ') {
            if (input[n-1][i] == '+') {
                res += std::accumulate(nums.begin(), nums.end(), 0ll);
            } else {
                res += std::accumulate(
                    nums.begin(), nums.end(), 1ll,
                    [](long long x, long long y) {
                        return x * y;
                    }
                );
            }
            nums = {};
            i--;
        }
        i--;
    }

    fout << res << '\n';
    return 0;
}
