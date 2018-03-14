// A Mid-Summer Night's Dream
// UVa ID: 10057
// Verdict: Accepted
// Submission Date: 2018-01-12
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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
    while ((c < '0' || c > '9') && c != '-') { if (c == EOF) return false; c = nextChar(); }
    if (c == '-') { negative = 1; c = nextChar(); }
    do x = (x << 3) + (x << 1) + c - '0'; while ((c = nextChar()) >= '0');
    if (negative) x = -x;
    return true;
}

void countingSort(int data[], int n, int C)
{
    int *bucket = new int[C]();
    
    for (int i = 0; i < n; i++) bucket[data[i]]++;
    
    for (int i = 0, index = 0; i < C; i++)
        while (bucket[i]-- > 0)
            data[index++] = i;
            
    delete [] bucket;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, numbers[1000010];
    
    while (nextInt(n))
    {
        for (int i = 0; i < n; i++) nextInt(numbers[i]);

        countingSort(numbers, n, 65550);

        if (n & 1)
        {
            int middle = numbers[n / 2];
            int cnt = count(numbers, numbers + n, middle);
            int total = 1;
            cout << middle << ' ' << cnt << ' ' << total << '\n';
        }
        else
        {
            int left = numbers[n / 2 - 1], right = numbers[n / 2];
            int cnt = 0;
            for (int i = 0; i < n; i++)
            {
                if (numbers[i] < left) continue;
                if (numbers[i] > right) break;
                cnt++;
            }
            int total = right - left + 1;
            cout << left << ' ' << cnt << ' ' << total << '\n';
        }
    }

    return 0;
}
