#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int cases = 100;
    cout << cases << "\n\n";
    
    for (int cs = 1; cs <= cases; cs++)
    {
        if (cs > 1) cout << '\n';
        int N = rand() % 101;
        cout << N << '\n';
        string push = "LRTB";
        for (int i = 1; i <= 100 && N; i++)
        {
            cout << push[rand() % 4];
            cout << rand() % N + 1;
            cout << '\n';
        }
        cout << "QUIT\n";
    }

    return 0;
}
