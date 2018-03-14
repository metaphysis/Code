// Not so Mobile
// UVa ID: 839
// Verdict: Accepted
// Submission Date: 2016-12-03
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool balanced = true;

int parse()
{
    int tWl, tDl, tWr, tDr;
 
    cin >> tWl >> tDl >> tWr >> tDr;

    if (tWl == 0) tWl = parse();
    if (tWr == 0) tWr = parse();
    if (balanced) balanced = (tWl * tDl == tWr * tDr);

    return (tWl + tWr);
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';
        
        balanced = true;
        parse();
        cout << (balanced ? "YES\n" : "NO\n");
    }
    
	return 0;
}
