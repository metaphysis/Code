// Joseph
// UVa ID: 305
// Verdict: Accepted
// Submission Date: 2016-06-26
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    map<int, int> cache;
    
    int k;
    while (cin >> k, k)
    {
        if (cache.find(k) != cache.end())
        {
            cout << cache[k] << endl;
            continue;
        }
        
        int start = k;
        while (true)
        {
            bool answerIsHere = false;
            for (int i = start + 1; i <= start + k; i++)
            {
                int n = 2 * k, counter = 0, index = 0;
                while (counter < k)
                {
                    index = (index + i - 1) % n;
                    if (index < k)
                        break;
                    counter++;
                    index = index < (n - 1) ? index : 0;
                    n--;
                }
                
                if (counter >= k)
                {
                    cout << i << endl;
                    cache[k] = i;
                    answerIsHere = true;
                    break;
                }
            }
            
            if (answerIsHere)
                break;
                
            start += k;
        }
    }
    
	return 0;
}
