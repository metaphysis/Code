// Bigger or Smaller
// UVa ID: 12930
// Verdict: Accepted
// Submission Date: 2022-01-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases = 1;
    string A, B;
    while (cin >> A >> B)
    {
        cout << "Case " << cases++ << ": ";
        int pa = A.find('.');
        string Ai = A.substr(0, pa), Af = A.substr(pa + 1);
        int pb = B.find('.');
        string Bi = B.substr(0, pb), Bf = B.substr(pb + 1);
        if (Ai.length() != Bi.length())
            cout << (Ai.length() > Bi.length() ? "Bigger" : "Smaller");
        else
        {
            int same = 1;
            for (int i = 0; i < Ai.length() && same; i++)
                if (Ai[i] != Bi[i])
                {
                    cout << (Ai[i] > Bi[i] ? "Bigger" : "Smaller");
                    same = 0;
                }
            if (same)
            {
                int L = max(Af.length(), Bf.length());
                while (Af.length() < L) Af.push_back('0');
                while (Bf.length() < L) Bf.push_back('0');
                for (int i = 0; i < Af.length() && same; i++)
                    if (Af[i] != Bf[i])
                    {
                        cout << (Af[i] > Bf[i] ? "Bigger" : "Smaller");
                        same = 0;
                    }
            }
            if (same) cout << "Same";
        }
        cout << '\n';
    }
    return 0;
}
