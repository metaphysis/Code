#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    map<char, string> letters;
    
    string block;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cin >> block;
            letters['A' + j] += block;
        }
    }
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 9; j < 18; j++)
        {
            cin >> block;
            letters['A' + j] += block;
        }
    }
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 18; j < 27; j++)
        {
            cin >> block;
            letters['A' + j] += block;
        }
    }
    
    for (auto g : letters)
        cout << "{\'" << g.first << "\', \"" << g.second << "\"},\n";
    
    return 0;
}
