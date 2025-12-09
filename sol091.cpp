#include "template.h"

auto parse2 = [](const string& s) {
    long long x, y;
    const char* p = s.c_str();
    x = strtol(p, (char**)&p, 10); ++p;
    y = strtol(p, nullptr, 10);
    return tuple{x, y};
};

int dim = 100000;
vector<vector<int>> board(dim, vector<int>(dim, 0));
vector<int> dirs = {1, 0, -1, 0, 1};

bool dfs(int x, int y) {
    cout << x << " " << y << endl;
    if (x < 0 || y < 0 || y > dim-1 || x > dim-1) {
        return false;
    }
    if (board[x][y] == 1) {
        return true;
    }
    board[x][y] = 1;
    for (int i=0; i<4; i++) {
        int nx = x + dirs[i];
        int ny = y + dirs[i+1];
        if (!dfs(nx, ny)) {
            board[x][y] = 0;
            return false;
        }
    }
    return true;
}

void connect(int x1, int x2, int y1, int y2) {
    if (x1 == x2) {
        if (y1 > y2) {
            for (int i=y2; i<=y1; i++) {
                board[x1][i] = 1;
            }
        } else {
            for (int i=y1; i<=y2; i++) {
                board[x1][i] = 1;
            }
        }
    } else {
        if (x1 > x2) {
            for (int i=x2; i<=x1; i++) {
                board[i][y1] = 1;
            }
        } else {
            for (int i=x1; i<=x2; i++) {
                board[i][y1] = 1;
            }
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ifstream fin ("in.txt");
    ofstream fout ("out.txt");
    int res = 0;

    string line;
    vector<int> X, Y;
    while (getline(fin, line)) {
        auto [x, y] = parse2(line);
        X.push_back(x);
        Y.push_back(y);
        int s = X.size();
        if (s < 2) continue;
        connect(X[s-1], X[s-2], Y[s-1], Y[s-2]);
    }
    connect(X.front(), X.back(), Y.front(), Y.back());

    int n = X.size();

    for (int i=-1; i<2; i++) {
        for (int j=-1; j<2; j++) {
            dfs(X.front() + i, Y.front() + j);
        }
    }

    cout << 1 << endl;

    vector<vector<int>> pre(dim, vector<int>(dim, 0));
    for (int i=0; i<dim; i++) {
        for (int j=0; j<dim; j++) {
            // cout << i << " " << j << endl;
            int val = board[i][j];

            int up = (i > 0 ? pre[i - 1][j] : 0);
            int left = (j > 0 ? pre[i][j - 1] : 0);
            int diag = (i > 0 && j > 0 ? pre[i - 1][j - 1] : 0);

            pre[i][j] = val + up + left - diag;
        }
    }


    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            int x_upper = max(X[i], X[j]);
            int x_lower = min(X[i], X[j]);
            int y_upper = max(Y[i], Y[j]);
            int y_lower = min(Y[i], Y[j]);
            int area = (x_upper - x_lower + 1) * (y_upper - y_lower + 1);
            int n_filled = pre[x_upper][y_upper] - pre[x_lower-1][y_upper] - pre[x_upper][y_lower-1] + pre[x_lower-1][y_lower-1];
            // cout << X[i] << " " << Y[i] << " " << X[j] << " " << Y[j] << " " << area << " " << n_filled << endl;
            if (area == n_filled)
                res = max(res, area);
        }
    }

    // n = 20;
    // for (int i=0; i<n; i++) {
    //     for (int j=0; j<n; j++) {
    //         cout << pre[i][j];
    //     }
    //     cout << endl;
    // }

    fout << res << '\n';
    return 0;
}
