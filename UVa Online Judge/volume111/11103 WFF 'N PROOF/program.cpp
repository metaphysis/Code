// WFF 'N PROOF
// UVa ID: 11103
// Verdict: Accepted
// Submission Date: 2017-12-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

bool isLogical(char c)
{
    return c == 'k' || c == 'a' || c == 'n' || c == 'c' || c == 'e';
}

bool isVariable(char c)
{
    return 'p' <= c && c <= 't';
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string symbol;
    while (cin >> symbol, symbol.front() != '0') {
        vector<char> nots, logicals, variables;
        for (int i = 0; i < symbol.length(); i++) {
            char c = tolower(symbol[i]);
            if (isLogical(c)) {
                if (c == 'n') nots.push_back('N');
                else logicals.push_back(toupper(c));
            }
            if (isVariable(c)) variables.push_back(c);
        }

        string wff;
        while (variables.size() > 0) {
            if (wff.length())
            {
                wff.insert(wff.begin(), logicals.back());
                logicals.pop_back();
            }
            wff.push_back(variables.back());
            variables.pop_back();
            if (!logicals.size()) break;
        }

        if (wff.length() > 0) {
            while (nots.size() > 0) {
                wff.insert(wff.begin(), 'N');
                nots.pop_back();
            }
        }

        if (wff.length() == 0) cout << "no WFF possible\n";
        else cout << wff << '\n';
    }

    return 0;
}
