// Instant Complexity
// UVa ID: 586
// Verdict: Accepted
// Submission Date: 2016-08-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct term
{
    int coefficient, degree;
};

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0, coefficients[11];
    cin >> cases;
    
    string token;
    for (int c = 1; c <= cases; c++)
    {
        memset(coefficients, 0, sizeof(coefficients));
        
        cout << "Program #" << c << '\n';
        
        stack<term> terms;
        while (cin >> token)
        {
            if (token == "END")
            {
                terms.pop();
                if (terms.empty())
                    break;
            }
            else if (token == "BEGIN")
            {
                term t;
                t.coefficient = 1, t.degree = 0;
                terms.push(t);
            }
            else if (token == "LOOP")
            {
                cin >> token;
                if (token == "n")
                {
                    term t;
                    t.coefficient = terms.top().coefficient;
                    t.degree = terms.top().degree + 1;
                    terms.push(t);
                }
                else
                {
                    int n = stoi(token);
                    term t;
                    t.coefficient = terms.top().coefficient * n;
                    t.degree = terms.top().degree;
                    terms.push(t);
                }
            }
            else if (token == "OP")
            {
                cin >> token;
                int n = stoi(token);
                coefficients[terms.top().degree] += n * terms.top().coefficient;
            }
        }
        
        cout << "Runtime = ";
        bool outputed = false;
        for (int i = 10; i >= 0; i--)
        {
            if (outputed && coefficients[i] > 0)
                cout << '+';

            if (coefficients[i] > 0)
                outputed = true;

            if (coefficients[i] > 1)
            {
                cout << coefficients[i];
                if (i > 0)
                    cout << '*';
            }
            else
            {
                if (i == 0 && (!outputed || coefficients[i] == 1))
                    cout << coefficients[i];
            }
            
            if (coefficients[i] > 0 && i > 0)
            {
                cout << 'n';
                if (i > 1)
                    cout << '^' << i;
            }
        }

        cout << "\n\n";
    }
    
	return 0;
}
