// Add All
// UVa ID: 10954
// Verdict: Accepted
// Submission Date: 2017-02-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int N, number;
    
    while (cin >> N, N)
    {
        priority_queue<int, vector<int>, greater<int>> sequence;
        for (int i = 0; i < N; i++)
        {
            cin >> number;
            sequence.push(number);
        }
        
        int minimal_cost = 0;
        while (sequence.size() >= 2)
        {
            int added = sequence.top();
            sequence.pop();
            
            added += sequence.top();
            sequence.pop();
            
            minimal_cost += added;
            sequence.push(added);
        }
        
        cout << minimal_cost << '\n';
    }
    
    return 0;
}
