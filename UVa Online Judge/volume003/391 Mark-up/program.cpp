// Mark-up
// UVa ID: 391
// Verdict: Accepted
// Submission Date: 2016-07-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    cin.unsetf(ios::skipws);
    char current, next;
    bool processing = true;
    
    while (cin >> current)
    {
        if (current == '\\')
        {
            cin >> next;
            if (next == '*') { processing = !processing; continue; }
            if (processing)
            {
                if (next == 'b' || next == 'i') continue;
                else if (next == 's')
                {
                    bool pointEncountered = false;
                    while (cin >> next)
                    {
                        if (isdigit(next)) continue;
                        else if (next == '.' && !pointEncountered) pointEncountered = true;
                        else { cin.putback(next); break; }
                    }
                }
                else cout << next;
            }
            else { cout << current; cin.putback(next); }
        }
        else cout << current;
    }
    
	return 0;
}
