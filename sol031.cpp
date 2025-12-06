#include "template.h"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ifstream fin ("in.txt");
    ofstream fout ("out.txt");

    string s;


    cout << s<< endl;

    regex pattern(R"(mul\((\d+),(\d+)\)|do\(\)|don't\(\))");



    smatch matches;
    int x, y;
    ll res = 0;

    int cur = 1;

    while (getline(fin, s)) {
        string::const_iterator searchStart(s.cbegin());

        
        while (regex_search(searchStart, s.cend(), matches, pattern)) {
            if (matches[0].str().find("mul") == 0) {
                x = stoi(matches[1]);
                y = stoi(matches[2]);
                res += x * y * cur;
            } else if (matches[0] == "do()") {
                cur = 1;
            } else if (matches[0] == "don't()") {
                cur = 0;
            }

            searchStart = matches.suffix().first;
        }

    }

    fout << res << "\n";

    return 0;
}
