// The Snail
// UVa ID: 573
// Verdict: Accepted
// Submission Date: 2016-08-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int H, U, D, F;
    while (cin >> H >> U >> D >> F, H)
    {
        H *= 100, D *= 100;
        
        int height = 0, day = 0, factor = 0;
        while (true)
        {
            day++;
            
            int climbed = U * (100 - factor);
            if (climbed < 0) climbed = 0;

            height += climbed;
            if (height > H)
            {
                cout << "success on day " << day << '\n';
                break;
            }
            
            height -= D;
            if (height < 0)
            {
                cout << "failure on day " << day << '\n';
                break;
            }
            
            factor += F;
        }
    }
    
	return 0;
}
