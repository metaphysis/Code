// TEX Quotes
// UVa ID: 272
// Verdict: Accepted
// Submission Date: 2016-05-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cin.sync_with_stdio(false);
    
    char input;
    bool firstQuote = false;

    cin.unsetf(ios::skipws);

    while (cin >> input)
    {
        if (input == '\"')
        {
            cout << (firstQuote ? "''" : "``");
            firstQuote = !firstQuote;
        }
        else cout << input;
    }
        
	return 0;
}
