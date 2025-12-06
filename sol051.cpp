#include "template.h"

// taken from https://leetcode.com/problems/merge-intervals/submissions/1513459791/
vector<vector<long long>> merge_intervals(vector<vector<long long>>& segs) {
    sort(segs.begin(), segs.end());
    vector<vector<long long>> merged;

    long long xprev = -1, yprev = -1;

    for (auto s: segs) {
        if (xprev == -1 && yprev == -1) {
            xprev = s[0];
            yprev = s[1];
            continue;
        }
        if (s[0] > yprev) {
            merged.push_back({xprev, yprev});
            xprev = s[0];
            yprev = s[1];
        } else {
            yprev = max(yprev, s[1]);
        }
    }
    merged.push_back({xprev, yprev});
    return merged;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ifstream fin ("in.txt");
    ofstream fout ("out.txt");

    vector<vector<long long>> intervals;
    vector<long long> nums;
    long long res = 0;

    string line;
    while (fin >> line) {
        size_t dash = line.find('-');
        if (dash != string::npos) {
            long long a = stoll(line.substr(0, dash));
            long long b = stoll(line.substr(dash + 1));
            intervals.push_back({a, b});
        } else {
            nums.push_back(stoll(line));
        }
    }

    sort(intervals.begin(), intervals.end(),
        [](const vector<long long>& a, const vector<long long>& b) {
            return a[0] < b[0];
        }
    );

    auto merged = merge_intervals(intervals);
    for (int i=0; i<merged.size(); i++) {
        res += merged[i][1] - merged[i][0] + 1;
        // cout << merged[i][0] << " " << merged[i][1] << endl;
    }

    fout << res << '\n';
    return 0;
}
