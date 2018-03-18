// Eventually Periodic Sequence
// UVa ID: 11036
// Verdict: Accepted
// Submission Date: 2018-03-18
// UVa Run Time: 0.050s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int OPERAND = 0, OPERATOR = 1, UNKNOWN = 2;

struct term
{
    int t;
    long long v;
    int o;
    term (int t = 0, long long v = 0, int o = 0): t(t), v(v), o(o) {}
} terms[110];

int N, n, cnt;

long long eval(int k)
{
    stack<term> r;
    for (int i = 0; i < cnt; i++)
    {
        if (terms[i].t == OPERAND)
        {
            r.push(terms[i]);
        }
        else if (terms[i].t == UNKNOWN)
        {
            r.push(term(OPERAND, k, 0));
        }
        else
        {
            long long b = r.top().v; r.pop();
            long long a = r.top().v; r.pop();
            if (terms[i].o == '+')
            {
                r.push(term(OPERAND, (a + b) % N, 0));
            }
            else if (terms[i].o == '*')
            {
                r.push(term(OPERAND, (a % N) * (b % N), 0));
            }
            else
            {
                r.push(term(OPERAND, a % b, 0));
            }
        }
    }
    return r.top().v;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        istringstream iss(line);
        iss >> N >> n;
        
        if (N == 0) break;

        string block;
        cnt = 0;
        while (iss >> block)
        {
            if (block == "+")
            {
                terms[cnt++] = term(OPERATOR, 0, '+');
            }
            else if (block == "*")
            {
                terms[cnt++] = term(OPERATOR, 0, '*');
            }
            else if (block == "%")
            {
                terms[cnt++] = term(OPERATOR, 0, '%');
            }
            else if (block == "N")
            {
                terms[cnt++] = term(OPERAND, N, 0);
            }
            else if (block == "x")
            {
                terms[cnt++] = term(UNKNOWN, 0, 0);
            }
            else
            {
                terms[cnt++] = term(OPERAND, stoll(block), 0);
            }
        }
        
        int steps = 0;
        map<int, int> cycle;
        while (true)
        {
            n = eval(n);
            if (cycle.find(n) != cycle.end())
            {
                cout << steps - cycle[n] << '\n';
                break;
            }
            cycle[n] = steps++;
        }
    }

    return 0;
}
