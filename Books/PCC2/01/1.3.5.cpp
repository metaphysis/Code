#include <bits/stdc++.h>

using namespace std;

const int LENGTH = (1 << 20);

inline int nextChar()
{
    static char buffer[LENGTH], *p = buffer, *end = buffer;
    if (p == end) {
        if ((end = buffer + fread(buffer, 1, LENGTH, stdin)) == buffer) return EOF;
        p = buffer;
    }
    return *p++;
}

inline bool nextInt(int &x)
{
    static char negative = 0, c = nextChar();
    negative = 0, x = 0;
    while ((c < '0' || c > '9') && c != '-')
    { if (c == EOF) return false; c = nextChar(); }
    if (c == '-') { negative = 1; c = nextChar(); }
    do x = (x << 3) + (x << 1) + c - '0'; while ((c = nextChar()) >= '0');
    if (negative) x = -x;
    return true;
}

inline void nextWord(string &w)
{
    register char c = 0;
    w.clear();
    while (!isalpha(c)) c = nextChar();
    do w += c; while (isalpha(c = nextChar()));
}

inline void nextString(string &s)
{
    register char c = 0;
    s.clear();
    while (c <= ' ') c = nextChar();
    do s += c; while ((c = nextChar()) > ' ');
}

int main(int argc, char *argv[])
{
    // 需要在进行任何输入输出前使用。
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    //cin.tie(NULL); cout.tie(NULL); ios_base.sync_with_stdio(false);

    // 后续不能将scanf，printf与cin，cout混用。输出换行符时，避免使用endl，否则
    // 每次输出时均会刷新缓冲区，增加时间消耗。

    // 后续代码...

    string w;
    nextWord(w); cout << w << '\n';
    nextWord(w); cout << w << '\n';

    string s;
    nextString(s); cout << s << '\n';

    int x;
    while (nextInt(x)) cout << x << '\n';

    return 0;
}
