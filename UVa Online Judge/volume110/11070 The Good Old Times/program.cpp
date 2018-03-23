// The Good Old Times
// UVa ID: 11070
// Verdict: Accepted
// Submission Date: 2018-03-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct term
{
    char c;
    double v;
    term (char c = 0, double v = 0): c(c), v(v) {}
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    double variable;
    char separator;

    while (getline(cin, line))
    {
        vector<term> terms;
        istringstream iss(line);
        while (iss >> variable)
        {
            terms.push_back(term(0, variable));
            if (iss >> separator)
                terms.push_back(term(separator, 0));
            else break;
        }
        
        while (true)
        {
            bool updated = false;
            for (int i = 0; i < terms.size(); i++)
            {
                if (terms[i].c == '*')
                {
                    terms[i - 1].v *= terms[i + 1].v;
                    terms.erase(terms.begin() + i, terms.begin() + i + 2);
                    updated = true;
                    break;
                }
                if (terms[i].c == '/')
                {
                    terms[i - 1].v /= terms[i + 1].v;
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
                if (terms[i].c == '+')
                {
                    terms[i - 1].v += terms[i + 1].v;
                    terms.erase(terms.begin() + i, terms.begin() + i + 2);
                    updated = true;
                    break;
                }
                if (terms[i].c == '-')
                {
                    terms[i - 1].v -= terms[i + 1].v;
                    terms.erase(terms.begin() + i, terms.begin() + i + 2);
                    updated = true;
                    break;
                }
            }
            if (!updated) break;
        }
        
        cout << fixed << setprecision(3) << terms.front().v << '\n';
    }

    return 0;
}
