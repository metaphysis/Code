#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    for (int i = 1; i <= 100; i++)
    {
        int N = rand() % 30 + 2;
        
        vector<string> items;
        
        int S = 1, E = 2;
        for (int j = 1; j <= N; j++)
        {
            if (j == 1 || rand() % 2 == 1)
            {
                int T = max(S, E);
                S = rand() % T + 1;
                E = rand() % T + 1;
                while (E == S)
                    E = rand() % T + 1;
            }
            else
            {
                if (rand() % 2 == 1)
                {
                    E = max(S, E) + 1;
                }
                else
                {
                    S = max(S, E);
                    E = S + 1;
                }
            }
            
            items.push_back(to_string(S) + ' ' + to_string(E) + ' ' + to_string((rand() % 10000 + 1)));
        }
        
        int T = max(S, E);
        S = rand() % T + 1;
        E = rand() % T + 1;
        while (E == S)
            E = rand() % T + 1;

        items.insert(items.begin(), to_string(N) + ' ' + to_string(S) + ' ' + to_string(E));
        
        for (auto item : items)
            cout << item << '\n';
    }
    
    cout << "0 0 0\n";
    
    return 0;
}
