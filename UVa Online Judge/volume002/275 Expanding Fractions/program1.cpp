// Expanding Fractions
// UVa ID: 275
// Verdict: Accepted
// Submission Date: 2016-05-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector < int > digits(1001), position(1001);
vector < bool > appeared(1001);

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); cout.sync_with_stdio(false);
    
    while (cin >> n >> m, n && m)
    {
        fill(appeared.begin(), appeared.end(), false);
        
        int index = 0;
        while (!appeared[n] && n > 0)
        {
            appeared[n] = true;
            digits[index] = 10 * n / m;
            position[n] = index++;
            n = 10 * n % m;
        }

        cout << ".";
        for (int i = 0; i < index; i++)
        {
            if (i % 50 == 49)
                cout << "\n";
            cout << digits[i];
        }
        
        if (n == 0)
            cout << "\nThis expansion terminates.\n\n";
        else
        {
            cout << "\nThe last " << (index - position[n]);
            cout << " digits repeat forever.\n\n";
        }
    }
    
    return 0;
}
