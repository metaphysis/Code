// Find the Format String
// UVa ID: 12134
// Verdict: Accepted
// Submission Date: 2019-01-28
// UVa Run Time: 0.010s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string alpha = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string A, B;
    int n, cases = 0;
    while (cin >> n, n > 0)
    {
        int out[128] = {}, in[128] = {};
        bool undone = false;
        for (int k = 0; k < n; k++)
        {
            cin >> A >> B;

            if (undone) continue;

            A.erase(A.begin());
            A.pop_back();
            B.erase(B.begin());
            B.pop_back();

            for (auto b : B) 
                if (!out[b])
                    in[b] = 1;

            string block;
            for (auto a : A)
            {
                if (in[a]) block += a;
                else
                {
                    out[a] = 1;
                    break;
                }
            }
            if (block != B) undone = true;
        }
        cout << "Case " << ++cases << ": ";
        if (undone) cout << "I_AM_UNDONE\n";
        else
        {
            string pattern;
            int cnt = 0;
            for (int i = alpha.size(); i >= 0; i--)
                if (in[alpha[i]])
                {
                    cnt++;
                    for (int j = 0; j <= i; j++)
                        if (!out[alpha[j]])
                            pattern += alpha[j];
                    break;
                }
            if (cnt == 0)
            {
                for (int i = 0; i < alpha.size(); i++)
                {
                    if (!out[alpha[i]])
                    {
                        pattern += alpha[i];
                        break;
                    }
                }
            }
            if (pattern.length() > 0) cout << '[' << pattern << "]\n";
            else cout << "I_AM_UNDONE\n";
        }
    }

    return 0;
}
