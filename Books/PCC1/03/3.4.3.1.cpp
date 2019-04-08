#include <bits/stdc++.h>

using namespace std;

bool bf(string &s, string &p)
{
    for (int start = 0; start < s.length(); start++) {
        int i = start, j = 0;
        while (i < s.length() && j < p.length() && s[i] == p[j]) i++, j++;
        if (j >= p.length()) return true;
    }
    return false;
}

int main(int argc, char *argv[])
{
    string s = "abcdeabcdeabcdef", p = "cdef";
    cout << (bf(s, p) ? 'y' : 'n') << '\n';
}
