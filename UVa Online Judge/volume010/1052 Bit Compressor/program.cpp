// Bit Compressor
// UVa ID: 1052
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int L, N, onesAt[64], matched;
string S;

void dfs(int idx, int cLength, int cOnes)
{
    if (matched > 1) return;
    if (cLength + (S.length() - idx) > L || cOnes + onesAt[idx] > N) return;
    if (cLength + (S.length() - idx) == L && cOnes + onesAt[idx] == N) { matched++; return; }
    if (idx >= S.length()) return;
    
    while (idx < S.length() && S[idx] == '0') idx++, cLength++;

    int nextIdx = idx, nextLength = cLength, nextOnes = cOnes;
    while (nextIdx < S.length() && S[nextIdx] == '1')
        nextIdx++, nextLength++, nextOnes++;
    dfs(nextIdx, nextLength, nextOnes);
    
    int bits = 0;
    while (idx < S.length())
    {
        bits = (bits << 1) | (S[idx] - '0');
        if (bits > 2)
        {
            if (cLength + bits > L) break;
            if ((idx + 1 < S.length() && S[idx + 1] == '0') || (idx + 1) == S.length())
            {
                dfs(idx + 1, cLength + bits, cOnes + bits);
            }
        }
        idx++; 
    } 
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> L)
    {
        if (L == 0) break;
        cin >> N >> S;

        int ones = count(S.begin(), S.end(), '1');
        memset(onesAt, 0, sizeof(onesAt));
        for (int i = 0; i < S.length(); i++)
            if (S[i] == '1') onesAt[i] = ones--;
            else onesAt[i] = ones;
        
        matched = 0;
        dfs(0, 0, 0);

        cout << "Case #" << ++cases << ": ";
        if (matched == 0) cout << "NO";
        if (matched == 1) cout << "YES";
        if (matched > 1) cout << "NOT UNIQUE";
        cout << '\n';
    }

    return 0;
}
