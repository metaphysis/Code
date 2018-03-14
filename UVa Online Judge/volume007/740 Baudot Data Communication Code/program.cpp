// Baudot Data Communication Code
// UVa ID: 740
// Verdict: Accepted
// Submission Date: 2016-11-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string down_characters, up_characters;
    getline(cin, down_characters);
    getline(cin, up_characters);
    
    string line;

    while (getline(cin, line))
    {
        int i = 0;
        bool is_down = true;

        while (i < line.length())
        {
            string piece = line.substr(i, 5);

            if (piece == "11011")
                is_down = true;
            else if (piece == "11111")
                is_down = false;
            else
            {
                bitset<5> indexer(piece);
                if (is_down) cout << down_characters[indexer.to_ulong()];
                else cout << up_characters[indexer.to_ulong()];
            }

            i += 5;
        }

        cout << '\n';
    }
    
	return 0;
}
