#include <bits/stdc++.h>

using namespace std;

string c[10] = {
    "@@@00", "@@0@0", "@0@@0", "0@@@0", "@@00@",
    "@00@@", "00@@@", "@0@0@", "0@0@@", "0@@0@"
};

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    for (int i = 1; i <= 20; i++)
    {
        int t = rand() % 998 + 3;

        cout << t << '\n';
        
        int m = rand() % 10;
        for (int n = 0; n < 5; n++)
        {
            cout << c[m][n];
            for (int j = 2; j <= t; j++)
            {
                int k = rand() % 100;
                if (k < 30)
                    k = rand() % 9 + 1;
                else
                    k = 0;
                
                cout << k;
            }
            cout << '\n';
        }
    }

    cout << 0 << '\n';
    
    return 0;
}
