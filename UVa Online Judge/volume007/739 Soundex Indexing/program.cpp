// Soundex Indexing
// UVa ID: 739
// Verdict: Accepted
// Submission Date: 2016-11-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    int digits[26] = {0, 1, 2, 3, 0, 1, 2, 0, 0, 2, 2, 4, 5, 5, 0, 1, 2, 6, 2, 3, 0, 1, 0, 2, 0, 2};
    cout << string(9, ' ') << setw(25) << left << "NAME" << "SOUNDEX CODE\n";
    string name;
    while (cin >> name) {
        string code;
        code += name.front();
        int last = digits[name.front() - 'A'];
        for (int i = 1; i < name.length(); i++) {
            int d = digits[name[i] - 'A'];
            if (d == 0) last = 0;
            else if (d != last) {
                code += char('0' + d);
                last = d;
            }
        }
        while (code.length() < 4) code.push_back('0');
        if (code.length() > 4) code = code.substr(0, 4);
        cout << string(9, ' ') << setw(25) << left << name << code << '\n';
    }
    cout << string(19, ' ') << "END OF OUTPUT\n";
    return 0;
}
