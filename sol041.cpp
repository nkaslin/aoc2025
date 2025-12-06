#include "template.h"

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ifstream fin ("in.txt");
    ofstream fout ("out.txt");

    string line;
    int res = 0;

    vector<string> board, next_board;

    while (getline(fin, line)) {
        stringstream ss(line);
        board.push_back(line);
    }
    next_board = board;

    int rows = board.size(), cols = board[0].size();
    bool changed = true;
    while (changed) {
        changed = false;
        for (int r=0; r<rows; r++) {
            for (int c=0; c<cols; c++) {
                if (board[r][c] == '.') {
                    continue;
                }
                int cnt = 0;
                for (int i=-1; i<2; i++) {
                    for (int j=-1; j<2; j++) {
                        if (i == 0 && j == 0) {
                            continue;
                        }
                        if (r + i < 0 || r + i == rows || c + j < 0 || c + j == cols) {
                            continue;
                        }
                        cnt += board[r+i][c+j] == '@';
                    }
                }
                if (cnt < 4) {
                    next_board[r][c] = '.';
                    res++;
                    changed = true;
                }
            }
        }
        board = next_board;
    }
    
    fout << res << '\n';
    return 0;
}
