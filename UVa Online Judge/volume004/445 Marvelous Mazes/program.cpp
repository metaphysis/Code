// Marvelous Mazes
// UVa ID: 445
// Verdict: Accepted
// Submission Date: 2016-07-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    cin.unsetf(ios::skipws);
    
    char control;
    int letter_readed = 0, draw_time = 0;
    while (cin >> control)
    {
        if (control == '\n')
        {
            if (letter_readed == 0)
            {
                cout << '\n';
                continue;
            }
        }
        
        letter_readed++;
        if (isdigit(control)) draw_time += control - '0';
        else if (isblank(control)) continue;
        else if (control == '!') cout << '\n';
        else if (control == '\n')
        {
            cout << '\n';
            letter_readed = 0;
        }
        else
        {
            for (int i = 1; i <= draw_time; i++)
                cout << (control == 'b' ? ' ' : control);
            draw_time = 0;
        }
    }
    
	return 0;
}
