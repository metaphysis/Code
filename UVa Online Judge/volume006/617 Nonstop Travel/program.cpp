// Nonstop Travel
// UVa ID: 617
// Verdict: Accepted
// Submission Date: 2016-08-31
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct signal
{
    double L, G, Y, R, P, Rs;
};

int main(int argc, char *argv[])
{
    //cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n, cases = 0, speed[100];
    signal signals[10];
    
    while (cin >> n, n >= 0)
    {
        cout << "Case " << ++cases << ':';

        for (int i = 0; i < n; i++)
        {
            cin >> signals[i].L >> signals[i].G >> signals[i].Y >> signals[i].R;
            signals[i].P = signals[i].G + signals[i].Y + signals[i].R;
            signals[i].Rs = signals[i].G + signals[i].Y;
        }
        
        memset(speed, 0, sizeof(speed));
        for (int i = 30; i <= 60; i++)
        {
            bool acceptable = true;
            for (int j = 0; j < n; j++)
            {
                double arrived = fmod(signals[j].L * 3600 / i, signals[j].P);
                if (arrived > signals[j].Rs + 1e-7)
                {
                    acceptable = false;
                    break;
                }
            }
            speed[i] = acceptable ? 1 : 0;
        }
        
        bool outputed = false;
        int k = 30;
        while (k <= 60)
        {
            if (speed[k] == 1)
            {
                if (outputed)
                    cout << ',';
                else
                    outputed = true;
                
                cout << ' ' << k;
                int length = 0;
                while (k <= 60 && speed[k] == 1)
                    length++, k++;
                if (length > 1)
                    cout << '-' << (k - 1);
            }
            else
                k++;
        }
        if (!outputed)
            cout << " No acceptable speeds.";
        cout << '\n';
    }
    
	return 0;
}
