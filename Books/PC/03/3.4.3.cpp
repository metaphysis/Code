#include <bits/stdc++.h>

using namespace std;

bool bf(string &s, string &p)
{
    int i = 0, j = 0;
    while (i < s.length() && j < p.length()) {
        if (s[i] == p[j]) i++, j++;
        else i++, j = 0;
    }
    return j >= p.length();
}

int main(int argc, char *argv[])
{
    string s = "abcdeabcdeabcdef", p = "cdef";
    cout << (bf(s, p) ? 'y' : 'n') << '\n';
}
