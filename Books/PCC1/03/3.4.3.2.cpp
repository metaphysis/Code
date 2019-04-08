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
    while (i < s.length() && j < p.length()) {
        if (j == 0 || s[i] == p[j]) i++, j++;
        else j = fail[j];
    }
    return j >= p.length();
}

void getFail2(string &p)
{
    fail[1] = 0;
    int i = 1, j = 0;
    while (i < p.length()) {
        if (j == 0 || p[i] == p[j]) {
            i++, j++;
            if (p[i] != p[j]) fail[i] = j;
            else fail[i] = fail[j];
        } else j = fail[j];
    }
}

bool kmp2(string &s, string &p)
{
    int i = 0, j = 1;
    while (i < s.length() && j < p.length()) {
        if (j == 0 || s[i] == p[j]) i++, j++;
        else j = fail[j];
    }
    return j >= p.length();
}

void getFail3(string &p)
{
    fail[0] = -1;
    int i = 0, j = -1;
    while (i < p.length() - 1) {
        if (j == -1 || p[i] == p[j]) {
            i++, j++;
            if (p[i] != p[j]) fail[i] = j;
            else fail[i] = fail[j];
        } else j = fail[j];
    }
}

bool kmp3(string &s, string &p)
{
    int i = 0, j = 0;
    while (i < s.length() && j < (int)p.length()) {
        if (j == -1 || s[i] == p[j]) i++, j++;
        else j = fail[j];
    }
    return j == p.length();
}

void getFail4(string &p)
{
    fail[0] = fail[1] = 0;
    for (int i = 1, j = 0; i < p.length(); i++) {
        while (j && p[j] != p[i]) j = fail[j];
        if (p[j] == p[i]) j++;
        fail[i + 1] = j;
    }
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
    string p = " abcabcdabcde";

    getFail2(p);
    for (int i = 1; i < p.length(); i++)
        cout << ' ' << fail[i];
    cout << '\n';

    return 0;
}
