#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> coef;
vector<vector<char>> has;
int dig[26], used;
bool lead[26];

bool solveCol(int col, int carry);

bool fillCol(int idx, const vector<int> &vars, int col, int carry) {
    if (idx == (int)vars.size()) {
        int sum = carry;
        for (int i = 0; i < 26; i++) sum += coef[col][i] * dig[i];
        if (sum % 10 != 0) return false;
        return solveCol(col + 1, sum / 10);
    }
    int x = vars[idx];
    for (int d = 0; d <= 9; d++) {
        if (used & (1 << d)) continue;
        if (lead[x] && d == 0) continue;
        dig[x] = d;
        used |= 1 << d;
        if (fillCol(idx + 1, vars, col, carry)) return true;
        used ^= 1 << d;
        dig[x] = -1;
    }
    return false;
}

bool solveCol(int col, int carry) {
    if (col == (int)coef.size()) return carry == 0;
    vector<int> vars;
    for (int i = 0; i < 26; i++)
        if (has[col][i] && dig[i] == -1) vars.push_back(i);
    return fillCol(0, vars, col, carry);
}

void parseLine(const string &line) {
    coef.clear();
    has.clear();
    memset(lead, 0, sizeof(lead));
    memset(dig, -1, sizeof(dig));
    used = 0;
    stringstream ss(line);
    string tok;
    int side = 1, op = 1;
    while (ss >> tok) {
        if (tok == "=") {
            side = -1;
            op = 1;
        } else if (tok == "+" || tok == "-") {
            op = tok == "+" ? 1 : -1;
        } else {
            int len = tok.size();
            if (len > 1) lead[tok[0] - 'A'] = true;
            for (int j = 0; j < len; j++) {
                int pos = len - 1 - j, x = tok[j] - 'A';
                while ((int)coef.size() <= pos) {
                    coef.push_back(vector<int>(26, 0));
                    has.push_back(vector<char>(26, 0));
                }
                coef[pos][x] += side * op;
                has[pos][x] = 1;
            }
            op = 1;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        parseLine(line);
        if (solveCol(0, 0)) {
            string ans(10, '*');
            for (int c = 0; c < 26; c++) {
                if (dig[c] == -1) continue;
                ans[dig[c]] = char('A' + c);
            }
            cout << ans << '\n';
        } else {
            cout << "**********\n";
        }
    }
    return 0;
}
