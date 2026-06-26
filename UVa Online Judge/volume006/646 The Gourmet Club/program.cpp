// The Gourmet Club
// UVa ID: 646
// Verdict: Accepted
// Submission Date: 2026-06-26
// UVa Run Time: 0.050s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<string> tables, rawLines;
vector<int> options[16];
int cases = 0, found = 0, seen[16], cache[4];

string getTable(int mask) {
    string s;
    while (mask) {
        int cln = __builtin_ctz(mask);
        s += char('A' + cln);
        mask ^= (1 << cln);
    }
    return s;
}

bool check() {
    int local[16];
    memcpy(local, seen, sizeof seen);
    vector<int> day4And5Tables;
    for (int i = 0; i < 4; i++) {
        string t = getTable(cache[i]);
        for (int x = 0; x < 4; x++)
            for (int y = 0; y < 4; y++)
                local[t[x] - 'A'] |= 1 << (t[y] - 'A');
    }
    set<int> day5Tables;
    for (int p = 0; p < 16; p++) {
        int day5Member = ~local[p] & 65535;
        if (__builtin_popcount(day5Member) != 3) return false;
        day5Tables.insert(day5Member | (1 << p));
    }
    if (day5Tables.size() != 4) return false;
    for (int i = 0; i < 4; i++) day4And5Tables.push_back(cache[i]);
    for (auto m : day5Tables) day4And5Tables.push_back(m);
    // 必须原样输出前三行，否则算法正确也照样会Wrong Answer，这个问题我花了一整天时间才找出来，WTF！
    for (int i = 0; i < 3; i++) cout << rawLines[i] << '\n';
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 4; j++)
            cout << getTable(day4And5Tables[i * 4 + j]) << " \n"[j == 3];
    return true;
}

void dfs(int depth, int day4Available) {
    if (found) return;
    if (depth == 4) {
        if (check()) found = 1;
        return;
    }
    int p = __builtin_ctz(day4Available);
    for (auto day4Used : options[p]) {
        if ((day4Used & day4Available) != day4Used) continue;
        cache[depth] = day4Used;
        dfs(depth + 1, day4Available ^ day4Used);
    }
}

bool isValid(vector<int> day4Member) {
    for (int i = 0; i < day4Member.size(); i++)
        for (int j = i + 1; j < day4Member.size(); j++)
            if (seen[day4Member[i]] & (1 << day4Member[j]) || seen[day4Member[j]] & (1 << day4Member[i]))
                return false;
    return true;
}

void solve() {
    if (cases++) cout << '\n';
    memset(seen, 0, sizeof seen);
    for (int i = 0; i < 3; ++i) {
        stringstream ss(rawLines[i]);
        string token;
        while (ss >> token) tables.push_back(token);
    }
    for (string t : tables) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                seen[t[i] - 'A'] |= (1 << (t[j] - 'A'));
    }
    vector<int> remaining[16];
    for (int p = 0; p < 16; p++) {
        remaining[p].clear();
        for (int j = 0; j < 16; j++)
            if (~seen[p] & (1 << j))
                remaining[p].push_back(j);
    }
    for (int b = 0; b < 64; b++)
        if (__builtin_popcount(b) == 3) {
            for (int p = 0; p < 16; p++) {
                vector<int> day4Member;
                for (int i = 0; i < 6; i++)
                    if (b & (1 << i))
                        day4Member.push_back(remaining[p][i]);
                if (isValid(day4Member)) {
                    int mask = 0;
                    for (auto m : day4Member) mask |= 1 << m;
                    mask |= 1 << p;
                    options[p].push_back(mask);
                }
            }
        }
    found = 0;
    dfs(0, 65535);
    if (!found) cout << "It is not possible to complete this schedule.\n";
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    string line;
    while (getline(cin, line)) {
        if (!line.empty()) rawLines.push_back(line);
        if (rawLines.size() == 3) {
            solve();
            rawLines.clear();
            tables.clear();
            for (int p = 0; p < 16; p++) options[p].clear();
        }
    }
    return 0;
}
