// 23 Out of 5
// UVa ID: 10344
// Verdict: Accepted
// Submission Date: 2017-11-12
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

inline int calculate(int a, int b, int c)
{
    if (c == 0) return a + b;
    if (c == 1) return a - b;
    if (c == 2) return a * b;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    vector<int> operand(5);

    while (true)
    {
        int total = 0;
        for (int i = 0; i < 5; i++)
        {
            cin >> operand[i];
            total += operand[i];
        }
        if (total == 0) break;
        
        sort(operand.begin(), operand.end());
        
        int flag = 0;
        do
        {
            for (int i = 0; i < 3; i++)
            {
                int r1 = calculate(operand[0], operand[1], i);
                for (int j = 0; j < 3; j++)
                {
                    int r2 = calculate(r1, operand[2], j);
                    for (int k = 0; k < 3; k++)
                    {
                        int r3 = calculate(r2, operand[3], k);
                        for (int l = 0; l < 3; l++)
                        {
                            if (calculate(r3, operand[4], l) == 23)
                            {
                                flag = 1;
                                goto print;
                            }
                        }
                    }
                }
            }
        } while (next_permutation(operand.begin(), operand.end()));
        
        print:
        if (flag) cout << "Possible";
        else cout << "Impossible";
        
        cout << '\n';
    }

    return 0;
}
