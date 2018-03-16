// Binomial Theorem
// UVa ID: 11955
// Verdict: Accepted
// Submission Date: 2018-03-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct term
{
    int e1, e2;
    long long c;
    term (int e1 = 0, int e2 = 0, long long c = 0): e1(e1), e2(e2), c(c) {}
} terms[64];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    string line;

    cin >> cases;
    cin.ignore(1024, '\n');
    for (int cs = 1; cs <= cases; cs++)
    {
        // Read.
        getline(cin, line);
        string a, b;
        int k = 0;

        // Parse.
        int current = 0;
        while (line[current] != '(') current++;
        current++;
        while (line[current] != '+') a += line[current++];
        current++;
        while (line[current] != ')') b += line[current++];
        current++;
        while (line[current] != '^') current++;
        current++;
        while (current < line.length()) k = k * 10 + line[current++] - '0';

        // Calculate.
        long long c = 1;
        for (int j = 0, up = k + 1, down = 0; up >= 0; j++, up--, down++)
        {
            if (down) c = c * up / down;
            terms[j].e1 = up - 1, terms[j].e2 = down, terms[j].c = c;
        }

        // Print.
        cout << "Case " << cs << ": ";
        for (int j = 0; j <= k; j++)
        {
            if (j) cout << '+';
            if (terms[j].c > 1) cout << terms[j].c << '*';
            if (terms[j].e1) cout << a;
            if (terms[j].e1 > 1) cout<< '^' << terms[j].e1;
            if (terms[j].e1 && terms[j].e2) cout << '*';
            if (terms[j].e2) cout << b;
            if (terms[j].e2 > 1) cout << '^' << terms[j].e2;
        }
        cout << '\n';
    }

    return 0;
}
