// Book Signatures
// UVa ID: 999
// Verdict: Accepted
// Submission Date: 2017-03-14
// UVa Run Time: 0.040s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n, m, signature, cases = 0; 
    char semiColon;
    
    while (cin >> n >> semiColon >> m)
    {
        if (cases++ > 0) cout << '\n';
        
        while ((n % (4 * m)) != 0) n++;
        
        signature = n / (4 * m);
        
        int startPage = 1, endPage = startPage + 4 * m - 1;
        
        for (int i = 1; i <= signature; i++)
        {
            cout << "signature " << i << '\n';
            
            deque<int> pages;
            for (int p = startPage; p <= endPage; p++)
                pages.push_back(p);
                
            startPage = endPage + 1;
            endPage = startPage + 4 * m - 1;
            
            for (int j = 1; j <= m; j++)
            {
                cout << " sheet " << j << ":";
                
                int page1 = pages.front(); pages.pop_front();
                int page2 = pages.front(); pages.pop_front();
                int page3 = pages.back(); pages.pop_back();
                int page4 = pages.back(); pages.pop_back();
                
                cout << " pages " << page2 << " and " << page4 << " (front);";
                cout << " pages " << page3 << " and " << page1 << " (back)\n";
            }
        }
    }
    
    return 0;
}
