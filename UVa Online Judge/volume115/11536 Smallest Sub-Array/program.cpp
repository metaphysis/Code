// Smallest Sub-Array
// UVa ID: 11536
// Verdict: Accepted
// Submission Date: 2018-04-06
// UVa Run Time: 0.760s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int number[1 << 20] = {1, 2, 3};
int lastIdx[1 << 10];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    int T, N, M, K;
    cin >> T;
    for (int c = 1; c <= T; c++)
    {
        cout << "Case " << c << ": ";

        cin >> N >> M >> K;

        // Special case.
        if (K <= 3)
        {
            cout << K << '\n';
            continue;
        }

        set<int> cache;
        queue<int> window, idx;
        memset(lastIdx, 0, sizeof(lastIdx));
        
        for (int i = 0; i <= 2; i++)
            lastIdx[i + 1] = i, window.push(i + 1), idx.push(i), cache.insert(i + 1);

        int flag = 0, smallest = 0x3f3f3f3f;
        for (int i = 3; i < N; i++)
        {
            // Push new number into queue and record the index of it.
            number[i] = (number[i - 3] + number[i - 2] + number[i - 1]) % M + 1;
            if (number[i] <= K) cache.insert(number[i]);
            window.push(number[i]);
            idx.push(i);
            lastIdx[number[i]] = i;

            // Check if needed numbers have been generated or not.
            if (cache.size() == K)
            {
                flag = 1;
                while (!window.empty())
                {
                    smallest = min(smallest, (int)window.size());
                    if (window.front() <= K)
                    {
                        if (idx.front() < lastIdx[window.front()])
                        {
                            idx.pop();
                            window.pop();
                        }
                        else break;
                    }
                    else
                    {
                        idx.pop();
                        window.pop();
                    }
                }
            }
        }
        
        if (flag) cout << smallest << '\n';
        else cout << "sequence nai\n";
    }

    return 0;
}
