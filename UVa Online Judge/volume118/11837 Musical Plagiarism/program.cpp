// Musical Plagiarism
// UVa ID: 11837
// Verdict: Accepted
// Submission Date: 2023-05-16
// UVa Run Time: 0.060s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10010;

int fail[MAXN];

void getFail(string &p)
{
    fail[0] = -1;
    int i = 0, j = -1, np = p.length();
    while (i < np - 1) {
        if (j == -1 || p[i] == p[j]) {
            i++, j++;
            int k = j;
            while (k != -1 && p[i] == p[k]) k = fail[k];
            fail[i] = k;
        } else j = fail[j];
    }
}

bool kmp(string &s, string &p)
{
    int i = 0, j = 0, ns = s.length(), np = p.length();
    while (i < ns) {
        if (j == -1 || s[i] == p[j]) i++, j++;
        else j = fail[j];
        if (j == np) return true;
    }
    return false;
}

map<string, char> sf = {
    {"A", 'a'}, {"Bb", 'b'}, {"A#", 'b'}, {"B", 'c'}, {"Cb", 'c'}, {"C", 'd'}, {"B#", 'd'},
    {"Db", 'e'}, {"C#", 'e'}, {"D", 'f'}, {"Eb", 'g'}, {"D#", 'g'}, {"E", 'h'}, {"Fb", 'h'},
    {"F", 'i'}, {"E#", 'i'}, {"Gb", 'j'}, {"F#", 'j'}, {"G", 'k'}, {"Ab", 'l'}, {"G#", 'l'}};
int n, m;
string s, t[12], w;

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    while (cin >> n >> m, n) {
        s.clear();
        for (int i = 0; i < n; i++) {
            cin >> w;
            s += sf[w];
        }
        for (int i = 0; i < 12; i++) t[i].clear();
        for (int i = 0; i < m; i++) {
            cin >> w;
            char c = sf[w];
            for (int j = 0; j < 12; j++)
                t[j] += (char)('a' + (c - 'a' + j) % 12);
        }
        int flag = 0;
        for (int i = 0; i < 12; i++) {
            getFail(t[i]);
            if (kmp(s, t[i])) { flag = 1; break; }
        }
        cout << (flag ? 'S' : 'N') << '\n';
    }
    return 0;
}
