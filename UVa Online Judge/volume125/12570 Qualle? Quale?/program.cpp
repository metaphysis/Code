#include <bits/stdc++.h>
using namespace std;

int n, m;
char tab[26][5];
int fixedLang[26], matchR[26], visL[26];
int curMask, langOrder[5], langCount;

bool aug(int row) {
    int lang, c;
    if (fixedLang[row] != -1) {
        lang = fixedLang[row];
        c = tab[row][lang] - 'A';
        if (tab[row][lang] == '-' || visL[c])
            return false;
        visL[c] = 1;
        if (matchR[c] == -1 || aug(matchR[c])) {
            matchR[c] = row;
            return true;
        }
        return false;
    }
    for (c = 0; c < 26; c++) {
        if (visL[c])
            continue;
        bool ok = false;
        for (lang = 0; lang < m; lang++)
            if ((curMask >> lang) & 1 && tab[row][lang] == 'A' + c) {
                ok = true;
                break;
            }
        if (!ok)
            continue;
        visL[c] = 1;
        if (matchR[c] == -1 || aug(matchR[c])) {
            matchR[c] = row;
            return true;
        }
    }
    return false;
}

bool canMatch() {
    int row;
    for (int c = 0; c < 26; c++)
        matchR[c] = -1;
    for (row = 0; row < n; row++) {
        for (int c = 0; c < 26; c++)
            visL[c] = 0;
        if (!aug(row))
            return false;
    }
    return true;
}

bool searchRep(int dep) {
    int lang, row;
    if (!canMatch())
        return false;
    if (dep == langCount)
        return true;
    lang = langOrder[dep];
    for (row = 0; row < n; row++) {
        if (fixedLang[row] != -1 || tab[row][lang] == '-')
            continue;
        fixedLang[row] = lang;
        if (searchRep(dep + 1))
            return true;
        fixedLang[row] = -1;
    }
    return false;
}

bool checkSet(int mask) {
    int lang, row, cnt;
    curMask = mask;
    langCount = 0;
    for (lang = 0; lang < m; lang++)
        if ((mask >> lang) & 1)
            langOrder[langCount++] = lang;
    for (int i = 0; i < langCount; i++) {
        for (int j = i + 1; j < langCount; j++) {
            int cntI = 0, cntJ = 0;
            for (row = 0; row < n; row++) {
                if (tab[row][langOrder[i]] != '-')
                    cntI++;
                if (tab[row][langOrder[j]] != '-')
                    cntJ++;
            }
            if (cntI > cntJ)
                swap(langOrder[i], langOrder[j]);
        }
    }
    for (row = 0; row < n; row++)
        fixedLang[row] = -1;
    return searchRep(0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCase;
    cin >> testCase;
    for (int tc = 1; tc <= testCase; tc++) {
        cin >> n >> m;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin >> tab[i][j];
        string ans[32];
        int ansCount = 0;
        for (int mask = 1; mask < (1 << m); mask++) {
            if (!checkSet(mask))
                continue;
            string cur;
            for (int lang = 0; lang < m; lang++)
                if ((mask >> lang) & 1)
                    cur += char('1' + lang);
            ans[ansCount++] = cur;
        }
        sort(ans, ans + ansCount, [](const string &a, const string &b) {
            if (a.size() != b.size())
                return a.size() < b.size();
            return a < b;
        });
        cout << "Case " << tc << ":";
        if (ansCount == 0) {
            cout << " -1\n";
            continue;
        }
        for (int i = 0; i < ansCount; i++)
            cout << ' ' << ans[i];
        cout << '\n';
    }
    return 0;
}
