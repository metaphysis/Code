// Killer Problem
// UVa ID: 11898
// Verdict: Accepted
// Submission Date: 2016-08-02
// UVa Run Time: 0.140s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases;
    cin >> cases;

    int number[200010];
    
    for (int i = 1; i <= cases; i++)
    {
        int N, Q;

        cin >> N;
        for (int j = 1; j <= N; j++)
            cin >> number[j];
        
        cin >> Q;
        for (int j = 1; j <= Q; j++)
        {
            int l, r;
            cin >> l >> r;
            
            if (r - l >= 10000)
            {
                cout << "0\n";
                continue;
            }
            
            bool min_diff_found = false;
            
            map<int, int> counter;
            for (int k = l; k <= r; k++)
            {
                counter[number[k]]++;
                if (counter[number[k]] > 1)
                {
                    cout << "0\n";
                    min_diff_found = true;
                    break;
                }
            }
            
            if (min_diff_found == false)
            {
                int min_diff = 10000, pre_number = -1;
                for (auto pair : counter)
                {
                    if (pre_number == -1)
                        pre_number = pair.first;
                    else
                    {
                        min_diff = min(min_diff, pair.first - pre_number);
                        pre_number = pair.first;
                    }
                }
                
                cout << min_diff << '\n';
            }
        }
    }
    
	return 0;
}
