#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    int M, N, D, start, end, height, linked[410][410];
    
    int cases = 1000;
    cout << cases << '\n';
    for (int c = 1; c <= cases; c++)
    {
        M = rand() % 200 + 1;

        do
        {
            N = rand() % 400 + 1;
        } while (N < (M + 50));
        
        D = rand() % 9999 + 1;
        
        cout << M << '\n' << N << '\n' << D << '\n';
        
        memset(linked, 0, sizeof(linked));
        for (int i = 1; i <= M; i++)
        {
            do
            {
                start = rand() % N + 1, end = rand() % N + 1;
            } while (start == end || linked[start][end] || linked[end][start]);
            
            linked[start][end] = linked[end][start] = 1;
            height = rand() % 1000 + 1;
            cout << start << ' ' << end << ' ' << height << '\n';
        }
    }
    
    return 0;
}
