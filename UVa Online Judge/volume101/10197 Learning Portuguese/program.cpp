// Learning Portuguese
// UVa ID: 10197
// Verdict: Accepted
// Submission Date: 2018-03-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int NONE = -1, FIRST = 0, SECOND = 1, THIRD = 2;
const string NOS = "n" + string(1, 243) + 's';
const string VOS = "v" + string(1, 243) + 's';

int getCategory(string &pw)
{
    if (pw.length() < 2 || pw.back() != 'r') return NONE;
    if (pw[pw.length() - 2] == 'a') return FIRST;
    if (pw[pw.length() - 2] == 'e') return SECOND;
    if (pw[pw.length() - 2] == 'i') return THIRD;
    return NONE;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    string pw, ee;
    while (cin >> pw >> ee)
    {
        if (cases++ > 0) cout << '\n';
        cout << pw << " (to " << ee << ")\n";
        int category = getCategory(pw);
        if (category == NONE)
        {
            cout << "Unknown conjugation\n";
            continue;
        }
        
        string root = pw.substr(0, pw.length() - 2);
        if (category == FIRST)
        {
            cout << left << setw(10) << "eu" << root << "o\n";
            cout << left << setw(10) << "tu" << root << "as\n";
            cout << left << setw(10) << "ele/ela" << root << "a\n";
            cout << left << setw(10) << NOS << root << "amos\n";
            cout << left << setw(10) << VOS << root << "ais\n";
            cout << left << setw(10) << "eles/elas" << root << "am\n";
        }
        else if (category == SECOND)
        {
            cout << left << setw(10) << "eu" << root << "o\n";
            cout << left << setw(10) << "tu" << root << "es\n";
            cout << left << setw(10) << "ele/ela" << root << "e\n";
            cout << left << setw(10) << NOS << root << "emos\n";
            cout << left << setw(10) << VOS << root << "eis\n";
            cout << left << setw(10) << "eles/elas" << root << "em\n";
        }
        else
        {
            cout << left << setw(10) << "eu" << root << "o\n";
            cout << left << setw(10) << "tu" << root << "es\n";
            cout << left << setw(10) << "ele/ela" << root << "e\n";
            cout << left << setw(10) << NOS << root << "imos\n";
            cout << left << setw(10) << VOS << root << "is\n";
            cout << left << setw(10) << "eles/elas" << root << "em\n";
        }
    }

    return 0;
}
