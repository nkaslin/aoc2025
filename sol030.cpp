#include "template.h"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ifstream fin ("in.txt");
    ofstream fout ("out.txt");

    string s;


    cout << s<< endl;

    regex pattern(R"(mul\((\d+),(\d+)\))");

    smatch matches;
    int x, y;
    ll res = 0;


    while (getline(fin, s)) {
        string::const_iterator searchStart(s.cbegin());

        
        while (regex_search(searchStart, s.cend(), matches, pattern)) {
            x = stoi(matches[1]);
            y = stoi(matches[2]);

            res += x * y;

            cout << x<<" "<<y<<endl;

            cout<< matches.suffix()<<endl;

            searchStart = matches.suffix().first;
        }

    }
    

    fout << res << "\n";

    return 0;
}
