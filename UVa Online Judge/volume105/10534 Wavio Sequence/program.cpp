// Wavio Sequence
// UVa ID: 10534
// Verdict: Accepted
// Submission Date: 2017-11-04
// UVa Run Time: 0.040s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

void lis(vector<int> &M, int data[], int length[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (M.size())
        {
            if (data[i] > M.back())
            {
                M.push_back(data[i]);
                length[i] = M.size();
            }
            else if (data[i] == M.back())
            {
                length[i] = M.size();
            }
            else
            {
                int j = upper_bound(M.begin(), M.end(), data[i]) - M.begin();
                if (j)
                {
                    if (data[i] > M[j - 1])
                    {
                        M[j] = data[i], length[i] = j + 1;
                    }
                    else
                    {
                        M[j - 1] = data[i], length[i] = j;
                    }
                }
                else
                {
                    M[j] = data[i], length[i] = j + 1;
                }
            }
        }
        else
        {
            M.push_back(data[i]);
            length[i] = 1;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, data[10010], length1[10010], length2[10010];
    while (cin >> n)
    {
        vector<int> M1, M2;
        for (int i = 0; i < n; i++)
            cin >> data[i];
            
        lis(M1, data, length1, n);

        reverse(data, data + n);
        lis(M2, data, length2, n);

        int longest = 0;
        for (int i = 0; i < n; i++)
        {
            int length = 1 + min(length1[i] - 1, length2[n - 1 - i] - 1) * 2;
            longest = max(longest, length);
        }
        
        cout << longest << '\n';
    }
    
    return 0;
}
