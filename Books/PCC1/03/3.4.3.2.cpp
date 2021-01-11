#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010;

int fail[MAXN];

void getFail1(string &p)
{
    fail[1] = 0;
    int i = 1, j = 0;
    while (i < p.length()) {
        if (j == 0 || p[i] == p[j]) {
            i++, j++;
            fail[i] = j;
        } else j = fail[j];
    }
}

bool kmp1(string &s, string &p)
{
    int i = 1, j = 1;
    while (i < s.length()) {
        if (j == 0 || s[i] == p[j]) i++, j++;
        else j = fail[j];
        if (j > p.length()) return true;
    }
    return false;
}

void kmpAllMatch(string &s, string &p)
{
    int i = 1, j = 1;
    while (i < s.length()) {
        if (j == 0 || s[i] == p[j]) i++, j++;
        else j = fail[j];
        if (j > p.length()) {
            cout << i - j + 1 << '\n';
            j = fail[j];
        }
    }
}


void getFail2(string &p)
{
    fail[1] = 0;
    int i = 1, j = 0;
    while (i < p.length()) {
        if (j == 0 || p[i] == p[j]) {
            i++, j++;
            int k = j;
            while (k && p[i] == p[k]) k = fail[k];
            fail[i] = k;
        } else j = fail[j];
    }
}

bool kmp2(string &s, string &p)
{
    int i = 0, j = 1;
    while (i < s.length()) {
        if (j == 0 || s[i] == p[j]) i++, j++;
        else j = fail[j];
        if (j > p.length()) return true;
    }
    return false;
}

void getFail3(string &p)
{
    fail[0] = -1;
    int i = 0, j = -1;
    while (i < p.length() - 1) {
        if (j == -1 || p[i] == p[j]) {
            i++, j++;
            int k = j;
            while (k != -1 && p[i] == p[k]) k = fail[k];
            fail[i] = k;
        } else j = fail[j];
    }
}

bool kmp3(string &s, string &p)
{
    int i = 0, j = 0;
    while (i < s.length()) {
        if (j == -1 || s[i] == p[j]) i++, j++;
        else j = fail[j];
        if (j == p.length()) return true;
    }
    return false;
}

void getFail4(string &p)
{
    int i = 1, j = 0;
    for (fail[i] = j; i < p.length(); i++, j++, fail[i] = j)
        while (j && p[j] == p[i]) j = fail[j];
}

bool kmp4(string &s, string &p)
{
    for (int i = 0, j = 0; i < s.length(); i++) {
        while (j && p[j] != s[i]) j = fail[j];
        if (p[j] == s[i]) j++;
        if (j == p.length()) return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    string t = "abce", p = "abcd";
    getFail1(p);
    for (int i = 1; i < p.length(); i++) cout << ' ' << fail[i];
    cout << '\n';
    cout << (kmp1(t, p) ? "Find a match\n" : "None match found\n");

    return 0;
}
