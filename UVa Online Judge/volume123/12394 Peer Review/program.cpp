// Peer Review
// UVa ID: 12394
// Verdict: Accepted
// Submission Date: 2021-12-18
// UVa Run Time: 0.010s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int K, N;
    while (cin >> K >> N)
    {
        if (K == 0) break;
        int bugged[2010] = {0};
        map<int, string> belongs;
        map<int, set<int>> peers;
        string institution;
        int paper;
        for (int i = 1; i <= N; i++)
        {
            cin >> institution;
            belongs[i] = institution;
            for (int j = 1; j <= K; j++)
            {
                cin >> paper;
                if (peers[paper].count(i)) bugged[paper] = 1;
                else peers[paper].insert(i);
            }
        }
        for (int i = 1; i <= N; i++)
        {
            if (peers[i].size() != K) bugged[i] = 1;
            else
            {
                for (auto p : peers[i])
                    if (belongs[p] == belongs[i])
                    {
                        bugged[i] = 1;
                        break;
                    }
            }
        }
        int problems = 0;
        for (int i = 1; i <= N; i++) problems += bugged[i];
        if (problems == 0) cout << "NO PROBLEMS FOUND";
        else
        {
            if (problems == 1) cout << "1 PROBLEM FOUND";
            else cout << problems << " PROBLEMS FOUND";
        }
        cout << '\n';
    }

    return 0;
}
