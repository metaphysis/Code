// Big Math
// UVa ID: 10875
// Verdict: Accepted
// Submission Date: 2018-03-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int ADD = 0, SUB = 1, MUL = 2, DIV = 3, OPA = 4;
const string letters = "0123456789+-*/";
    
string dots[5] = {
    "000 .0. 000 000 0.0 000 0.. 000 000 000 .0. ... 0.0 .0.",
    "0.0 .0. ..0 ..0 0.0 0.. 0.. ..0 0.0 0.0 .0. ... 0.0 ...",
    "0.0 .0. 000 000 000 000 000 ..0 000 000 000 000 .0. 000",
    "0.0 .0. 0.. ..0 ..0 ..0 0.0 ..0 0.0 ..0 .0. ... 0.0 ...",
    "000 .0. 000 000 ..0 000 000 ..0 000 ..0 .0. ... 0.0 .0."
};
string line, symbol[5];

bool equal(int idx1, int idx2)
{
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 3; j++)
            if (symbol[i][idx1 + j] != dots[i][idx2 + j])
                return false;
    return true;
}

bool zero()
{
    if (symbol[0].length() != 3) return false;
    return equal(0, 0);
}

string parse()
{
    string equation;
    int length = symbol[0].length();
    for (int i = 0; i < length; i += 4)
    {
        for (int j = 0; j < letters.length(); j++)
            if (equal(i, 4 * j))
            {
                equation += letters[j];
                break;
            }
    }
    return equation;
}

int calculate(string equation)
{
    int number; char operators;
    vector<pair<int, int>> terms;

    istringstream iss(equation);
    iss >> number; terms.push_back(make_pair(number, OPA));
    while (iss >> operators)
    {
        if (operators == '+') terms.push_back(make_pair(0, ADD));
        if (operators == '-') terms.push_back(make_pair(0, SUB));
        if (operators == '*') terms.push_back(make_pair(0, MUL));
        if (operators == '/') terms.push_back(make_pair(0, DIV));
        iss >> number; terms.push_back(make_pair(number, OPA));
    }
    
    while (true)
    {
        bool updated = false;
        for (int i = 0; i < terms.size(); i++)
        {
            if (terms[i].second == MUL || terms[i].second == DIV)
            {
                if (terms[i].second == MUL)
                    terms[i - 1].first *= terms[i + 1].first;
                else
                    terms[i - 1].first /= terms[i + 1].first;
                terms.erase(terms.begin() + i, terms.begin() + i + 2);
                updated = true;
                break;
            }
        }
        if (!updated) break;
    }
    while (true)
    {
        bool updated = false;
        for (int i = 0; i < terms.size(); i++)
        {
            if (terms[i].second == ADD || terms[i].second == SUB)
            {
                if (terms[i].second == ADD)
                    terms[i - 1].first += terms[i + 1].first;
                else
                    terms[i - 1].first -= terms[i + 1].first;
                terms.erase(terms.begin() + i, terms.begin() + i + 2);
                updated = true;
                break;
            }
        }
        if (!updated) break;
    }
    
    return terms.front().first;
}

void render(int n)
{
    string nn = to_string(n);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < nn.length(); j++)
        {
            if (j) cout << ' ';
            for (int k = 0; k < 3; k++)
            {
                if (nn[j] == '-') cout << dots[i][44 + k];
                else cout << dots[i][4 * (nn[j] - '0') + k];
            }
        }
        cout << '\n';
    }
    cout << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (true)
    {
        int idx = 0;
        while (getline(cin, line), line.length() > 0)
        {
            while (isblank(line.back())) line.pop_back();
            symbol[idx++] = line;
        }
        if (zero()) break;

        render(calculate(parse()));
    }

    return 0;
}
