#include <bits/stdc++.h>
using namespace std;

using Cd = complex<double>;
const double Pi = acos(-1.0);

void fft(vector<Cd>& a, bool inv) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * Pi / len * (inv ? -1 : 1);
        Cd wLen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            Cd w(1);
            for (int j = 0; j < len / 2; j++) {
                Cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wLen;
            }
        }
    }
    if (inv) {
        for (int i = 0; i < n; i++) a[i] /= n;
    }
}

int getId(char ch) {
    if (ch == 'A') return 0;
    if (ch == 'C') return 1;
    if (ch == 'G') return 2;
    return 3;
}

vector<int> getScore(const string& s1, const string& s2) {
    int n = s1.size(), m = s2.size(), len = 1;
    while (len < n + m - 1) len <<= 1;
    vector<int> score(n + m - 1);
    for (int ch = 0; ch < 4; ch++) {
        vector<Cd> a(len), b(len);
        for (int i = 0; i < n; i++) {
            if (getId(s1[i]) == ch) a[i] = 1;
        }
        for (int i = 0; i < m; i++) {
            if (getId(s2[i]) == ch) b[m - 1 - i] = 1;
        }
        fft(a, false);
        fft(b, false);
        for (int i = 0; i < len; i++) a[i] *= b[i];
        fft(a, true);
        for (int i = 0; i < n + m - 1; i++) score[i] += (int)round(a[i].real());
    }
    return score;
}

string buildAns(const string& s1, const string& s2, int pos) {
    int n = s1.size(), m = s2.size(), left = min(0, pos), right = max(n, pos + m);
    string ans;
    for (int x = left; x < right; x++) {
        char c1 = 0, c2 = 0;
        if (x >= 0 && x < n) c1 = s1[x];
        if (x >= pos && x < pos + m) c2 = s2[x - pos];
        if (!c1) ans += c2;
        else if (!c2 || c1 == c2) ans += c1;
        else ans += 'X';
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s1, s2;
    while (cin >> s1 >> s2) {
        int n = s1.size(), m = s2.size(), best = -1, pos = 0;
        vector<int> score = getScore(s1, s2);
        for (int i = 0; i < (int)score.size(); i++) {
            int cur = score[i], d = i - m + 1;
            if (cur >= best) best = cur, pos = d;
        }
        cout << best << '\n';
        if (best == 0) cout << "No matches\n\n";
        else cout << buildAns(s1, s2, pos) << "\n\n";
    }
    return 0;
}
