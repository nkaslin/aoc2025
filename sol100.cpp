#include "template.h"
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>

struct ParsedData {
    string lights;
    vector<vector<int>> buttons;
    vector<int> joltages;
};

ParsedData parse(const string& s) {
    ParsedData out;
    {
        regex re(R"(\[(.*?)\])");
        smatch m;
        if (regex_search(s, m, re)) {
            out.lights = m[1];
        }
    }
    {
        regex re(R"(\((.*?)\))");
        for (auto it = sregex_iterator(s.begin(), s.end(), re);
            it != sregex_iterator(); ++it) {

            string inner = (*it)[1];
            vector<int> values;

            stringstream ss(inner);
            string tok;
            while (getline(ss, tok, ',')) {
                if (!tok.empty()) {
                    values.push_back(stoi(tok));
                }
            }

            out.buttons.push_back(values);
        }
    }
    {
        regex re(R"(\{(.*?)\})");
        smatch m;
        if (regex_search(s, m, re)) {
            string inner = m[1];
            stringstream ss(inner);
            string tok;
            while (getline(ss, tok, ',')) {
                out.joltages.push_back(stoi(tok));
            }
        }
    }

    return out;
}

int find_min(int target, vector<int>& switches) {
    int n = switches.size();
    int res = 1000000;
    for (int mask=0; mask<(1<<n); mask++) {
        int cur = 0;
        for (int i=0; i<n; i++) {
            if (mask & (1 << i)) {
                cur ^= switches[i];
            }
        }
        if (cur == target) {
            res = min(res, __builtin_popcount(mask));
        }
    }
    return res;
}


int main() {
    cin.tie(0)->sync_with_stdio(0);
    ifstream fin ("in.txt");
    ofstream fout ("out.txt");
    int res = 0;

    string line;
    ParsedData p;
    while (getline(fin, line)) {
        p = parse(line);
        int target = 0;
        string target_string = p.lights;
        for (int i=0; i<target_string.length(); i++) {
            if (target_string[i] == '#') {
                target |= 1 << i;
            }
        }
        vector<int> switches;
        for (auto& v : p.buttons) {
            int cur = 0;
            for (int i=0; i<v.size(); i++) {
                cur |= 1 << v[i];
            }
            switches.push_back(cur);
        }
        res += find_min(target, switches);
    }    

    fout << res << '\n';
    return 0;
}
