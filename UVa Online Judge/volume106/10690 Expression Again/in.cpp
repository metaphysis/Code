#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int number[101];

    for (int i = 1; i <= 110; i++)
    {
        int N = rand() % 50; N++;
        int M = rand() % 50; M++;
        int T = (N + M);
        
        cout << N << ' ' << M << '\n';
        
        for (int j = 1; j <= T; j++)
        {
            int K = rand() % 101; K -= 50;
            number[j] = K;
        }
        
        cout << number[1];
        for (int j = 2; j <= T; j++)
            cout << ' ' << number[j];
        cout << '\n';
    }
    
    return 0;
}
