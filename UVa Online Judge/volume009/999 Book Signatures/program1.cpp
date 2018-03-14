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
        
        if ((n % (4 * m)) != 0) n += (4 * m - (n % (4 * m)));
        
        signature = n / (4 * m);
        
        int startPage = 1, endPage = startPage + 4 * m - 1;
        
        for (int i = 1; i <= signature; i++)
        {
            cout << "signature " << i << '\n';
            
            int leftPage = startPage, rightPage = endPage;

            for (int j = 1; j <= m; j++)
            {
                cout << " sheet " << j << ":";
                
                int page1 = leftPage, page2 = leftPage + 1, page3 = rightPage, page4 = rightPage - 1;
                
                cout << " pages " << page2 << " and " << page4 << " (front);";
                cout << " pages " << page3 << " and " << page1 << " (back)\n";
                
                leftPage += 2, rightPage -= 2;
            }
            
            startPage = endPage + 1;
            endPage = startPage + 4 * m - 1;
        }
    }
    
    return 0;
}
