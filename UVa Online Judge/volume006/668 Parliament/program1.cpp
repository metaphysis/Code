// Parliament
// UVa ID: 668
// Verdict: Accepted
// Submission Date: 2017-10-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    int cases, n, top, sequence[105];
    
    cin >> cases;
    while(cases--)
    {
        cin >> n;
        top = 0;
        for(int i = 2; n >= i; i++)  sequence[++top] = i, n -= i;
        for(int i = top; n && i; i--) sequence[i]++, n--;
        sequence[top] += n;
        for(int i = 1; i < top; i++) cout << sequence[i] << ' ';
        cout << sequence[top] << '\n';
        if(cases) cout << '\n';
    }
    return 0;
}
