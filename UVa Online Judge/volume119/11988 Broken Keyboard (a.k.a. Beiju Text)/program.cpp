// Broken Keyboard (a.k.a. Beiju Text)
// UVa ID: 11988
// Verdict: Accepted
// Submission Date: 2018-01-05
// UVa Run Time: 0.140s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

inline int nextChar()
{
    const int LENGTH = 1048576;
    static char buffer[LENGTH], *p = buffer, *end = buffer;
    if (p == end) {
        if ((end = buffer + fread(buffer, 1, LENGTH, stdin)) == buffer) return EOF;
        p = buffer;
    }
    return *p++;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    char c;
    int home = 0;
    list<char> line;
    list<char>::iterator it;

    while ((c = nextChar()) != EOF)
    {
        if (c == '[')
        {
            home = 1;
            it = line.begin();
        }
        else if (c == ']')
        {
            home = 0;
        }
        else if (c == '\n')
        {
            home = 0;
            for (auto cc : line) cout << cc;
            cout << '\n';
            line.clear();
        }
        else
        {
            if (home)
            {
                line.insert(it, c);
            }
            else
            {
                line.push_back(c);
            }
        }
    }

    return 0;
}
