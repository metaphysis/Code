// 2D Hieroglyphs Decoder
// UVa ID: 10851
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    cin.ignore(1024, '\n');
    
    for (int c = 1; c <= cases; c++)
    {
        string line;
        int length = -1, lineNumber = 0;
        bitset<8> letter[MAXN] = {0};
        while (getline(cin, line), line.length() > 0)
        {
            while (isblank(line.front())) line.erase(line.begin());
            while (isblank(line.back())) line.pop_back();

            line.erase(line.begin());
            line.pop_back();

            if (length == -1) length = line.length();

            if (lineNumber != 0 && lineNumber != 9)
            {
                for (int i = 0; i < line.length(); i++)
                    letter[i].set(lineNumber - 1, line[i] == '/' ? 0 : 1);
            }
            lineNumber++;
        }
        for (int i = 0; i < length; i++)
            cout << (char)letter[i].to_ulong();
        cout << '\n';
    }
    return 0;
}
