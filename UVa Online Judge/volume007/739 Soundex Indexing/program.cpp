// Soundex Indexing
// UVa ID: 739
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

    int digits[26] = {0, 1, 2, 3, 0, 1, 2, 0, 0, 2, 2, 4, 5, 5, 0, 1, 2, 6, 2, 3, 0, 1, 0, 2, 0, 2};
    
    cout << string(9, ' ') << setw(25) << left << "NAME" << "SOUNDEX CODE\n";
    
    string name;
    while (cin >> name)
    {
        string code, code_next, code_last;
        for (int i = 0; i < name.length(); i++)
            code += (char)('0' + digits[name[i] - 'A']);
                
        code_next += code.front();
        for (int i = 0; i < code.length(); i++)
            if (code[i] != code_next.back())
                code_next += code[i];

        code_last += name.front();
        for (int i = 1; i < code_next.length(); i++)
            if (code_next[i] != '0')
                code_last += code_next[i];
                
        while (code_last.length() < 4) code_last.push_back('0');
        if (code_last.length() > 4) code_last = code_last.substr(0, 4);
        
        cout << string(9, ' ') << setw(25) << left << name << code_last << '\n';
    }
    
    cout << string(19, ' ') << "END OF OUTPUT\n";
    
	return 0;
}
