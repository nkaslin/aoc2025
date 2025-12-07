#include "template.h"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ifstream fin ("in.txt");
    ofstream fout ("out.txt");
    long long res = 0;

    string line;
    vector<vector<long long>> nums;
    while (getline(fin, line)) {
        if (line[0] != '+' && line[0] != '*') {
            stringstream ss(line);
            long long x;
            vector<long long> cur_line;
            while (ss >> x) {
                cur_line.push_back(x);
            }
            nums.push_back(cur_line);
        }
    }
    int ptr = 0;
    for (int i=0; i<nums[0].size(); i++) {
        long long cur = nums[0][i];
        for (int j=1; j<nums.size(); j++) {
            if (line[ptr] == '+') {
                cur += nums[j][i];
            } else {
                cur *= nums[j][i];
            }
        }
        res += cur;
        ptr++;
        while (ptr < line.length() && line[ptr] == ' ') {
            ptr++;
        }
    }

    fout << res << '\n';
    return 0;
}
