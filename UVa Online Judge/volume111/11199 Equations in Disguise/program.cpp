// Equations in Disguise
// UVa ID: 11199
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int debug1 = 0, debug2 = 0, debug3 = 1;

int n, used[16], oops, cnt;
string exps[24], clean[24];
char cache[16], mapping[16];
char letter[12] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '*'};

bool cmp1(string &a, string b)
{
    if (a.length() != b.length()) return a.length() < b.length();
    return a < b;
}

bool cmp2(string &a, string b)
{
    if (a.length() != b.length()) return a.length() > b.length();
    return a < b;
}

int maxNumber[24], leftPart[24], rightPart[24];
int nopd1, nopd2, nopd3;
char nopr1, nopr2;

int evaluate(int opd1, int opd2, char opr1)
{
    if (opr1 == '*') return opd1 * opd2;
    return opd1 + opd2;
}

int calculate(int opd1, int opd2, int opd3, char opr1, char opr2)
{
    if (opr2 == '*')
        return evaluate(opd1, evaluate(opd2, opd3, opr2), opr1);
    else
        return evaluate(evaluate(opd1, opd2, opr1), opd3, opr2);
}

void update(int depth, int opd1, int opd2, int opd3, char opr1, char opr2, char opr3)
{
    nopd1 = opd1, nopd2 = opd2, nopd3 = opd3, nopr1 = opr1, nopr2 = opr2;
    if (isdigit(opr3))
    {
        nopd3 = opd3 * 10 + opr3 - '0';
    }
    else if (opr3 == '=')
    {
        leftPart[depth] = calculate(opd1, opd2, opd3, opr1, opr2);
        nopd1 = nopd2 = nopd3 = 0;
        nopr1 = nopr2 = '+';
    }
    else if (opr3 == '#')
    {
        rightPart[depth] = calculate(opd1, opd2, opd3, opr1, opr2);
        nopd1 = nopd2 = nopd3 = 0;
        nopr1 = nopr2 = '+';
    }
    else if (opr3 == '*')
    {
        if (opr2 == '*')
        {
            if (opr1 == '*')
            {
                nopd1 = opd1 * opd2;
                nopd2 = opd3;
                nopd3 = 0;
                nopr1 = '*';
                nopr2 = '*';
            }
            else if (opr1 == '+')
            {
                nopd1 = opd1;
                nopd2 = opd2 * opd3;
                nopd3 = 0;
                nopr1 = '+';
                nopr2 = '*';
            }
        }
        else if (opr2 == '+')
        {
            if (opr1 == '*')
            {
                nopd1 = opd1 * opd2;
                nopd2 = opd2;
                nopd3 = 0;
                nopr1 = '+';
                nopr2 = '*';
            }
            else if (opr1 == '+')
            {
                nopd1 = opd1 + opd2;
                nopd2 = opd3;
                nopd3 = 0;
                nopr1 = '+';
                nopr2 = '*';
            }
        }
    }
    else if (opr3 == '+')
    {
        if (opr2 == '*')
        {
            if (opr1 == '*')
            {
                nopd1 = opd1 * opd2;
                nopd2 = opd3;
                nopd3 = 0;
                nopr1 = '*';
                nopr2 = '+';
            }
            else if (opr1 == '+')
            {
                nopd1 = opd1;
                nopd2 = opd2 * opd3;
                nopd3 = 0;
                nopr1 = '+';
                nopr2 = '+';
            }
        }
        else if (opr2 == '+')
        {
            if (opr1 == '*')
            {
                nopd1 = opd1 * opd2;
                nopd2 = opd3;
                nopd3 = 0;
                nopr1 = '+';
                nopr2 = '+';
            }
            else if (opr1 == '+')
            {
                nopd1 = opd1 + opd2;
                nopd2 = opd3;
                nopd3 = 0;
                nopr1 = '+';
                nopr2 = '+';
            }
        }
    }
}

void dfs(int depth, int level, int opd1, int opd2, int opd3, char opr1, char opr2)
{
    if (level == 0) leftPart[depth] = rightPart[depth] = -1;

    // Puring
    if (depth && leftPart[depth] >= maxNumber[depth - 1]) return;
    if (oops) return;

    // All expression matched
    if (depth == n)
    {
        if (debug3)
        {
            cout << "----------\n";
            for (int i = 0; i < depth; i++)
            {
                for (int j = 0; j < exps[i].length(); j++)
                    cout << cache[exps[i][j] - 'a'];
                cout << '\n';
            }
            cout << "----------\n";
        }
        for (int i = 0; i < 13; i++)
        {
            if (mapping[i] == -2) continue;
            if (cache[i] == -1) continue;
            if (mapping[i] == -1)
            {
                mapping[i] = cache[i];
            }
            else
            {
                if (mapping[i] != cache[i])
                    mapping[i] = -2;
            }
        }
        oops = (count(mapping, mapping + 13, -2) == cnt);
        return;
    }

    // At the end of an expression
    if (level == exps[depth].length())
    {
        update(depth, opd1, opd2, opd3, opr1, opr2, '#');
        if (debug2)
        {
            cout << "# ";
            for (int j = 0; j < exps[depth].length(); j++)
                cout << cache[exps[depth][j] - 'a'];
            cout << '\n';
            cout << "L = " << leftPart[depth] << " R = " << rightPart[depth] << '\n';
        }
        if (leftPart[depth] == rightPart[depth])
        {
            dfs(depth + 1, 0, nopd1, nopd2, nopd3, nopr1, nopr2);
        }
    }
    else
    {       
        // A symbol have matched, continue to next char of expression
        if (cache[exps[depth][level] - 'a'] != -1)
        {
            char now = cache[exps[depth][level] - 'a'];
            char pre = cache[exps[depth][level - 1] - 'a'];
            if (level)
            {
                if (!isdigit(pre) && !isdigit(now))
                    return;
            }
            if (level == 1)
            {
                if (pre == '0')
                    return;
            }
            if (level >= 2)
            {
                if (now != '=')
                    if (pre == '0' && !isdigit(cache[exps[depth][level - 2] - 'a']))
                        return;
            }
            if (level == 0 || level == exps[depth].length() - 1)
            {
                if (!isdigit(now))
                    return;
            }

            update(depth, opd1, opd2, opd3, opr1, opr2, now);
            dfs(depth, level + 1, nopd1, nopd2, nopd3, nopr1, nopr2);
        }
        // Unmatched, try mapping a char to a symbol
        else
        {
            for (int i = 0; i < 12; i++)
            {
                if (used[i]) continue;
                
                // The start of an expression can't be a operator
                if (level == 0)
                {
                    if (!isdigit(letter[i]))
                        continue;
                }
                // The end of an expression can't be a operator
                if (level == exps[depth].length() - 1)
                {
                    if (!isdigit(letter[i]))
                        continue;
                }
                // After a operator must be a non operator
                if (level && !isdigit(cache[exps[depth][level - 1] - 'a']))
                {
                    if (!isdigit(letter[i]))
                        continue;
                }
                // Before a operator must be a digit
                if (level < exps[depth].length() - 1)
                {
                    if (cache[exps[depth][level + 1] - 'a'] == '=')
                    {
                        if (!isdigit(letter[i]))
                            continue;
                    }
                }
                if (level == 1)
                {
                    if (cache[exps[depth][level - 1] - 'a'] == '0')
                        continue;
                }
                if (level >= 2)
                {
                    if (cache[exps[depth][level - 1] - 'a'] == '0' && !isdigit(cache[exps[depth][level - 2] - 'a']))
                        continue;
                }

                cache[exps[depth][level] - 'a'] = letter[i];
                used[i] = 1;
                update(depth, opd1, opd2, opd3, opr1, opr2, letter[i]);
                dfs(depth, level + 1, nopd1, nopd2, nopd3, nopr1, nopr2);
                used[i] = 0;
                cache[exps[depth][level] - 'a'] = -1;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> n, n > 0)
    {
        cout << "Case " << ++cases << ": ";

        // Check equal sign exist or not
        set<char> appeared;
        int available[16];
        memset(available, -1, sizeof(available));
        for (int i = 0; i < n; i++)
        {
            cin >> exps[i];
            for (int j = 0; j < exps[i].length(); j++)
            {
                appeared.insert(exps[i][j]);
                if (available[exps[i][j] - 'a'] == -2) continue;
                // Start and end of expression can't be a equal sign
                if (j == 0 || j == exps[i].length() - 1) continue;
                available[exps[i][j] - 'a']++;
            }
            for (int j = 0; j < 16; j++)
                if (available[j] != i)
                    available[j] = -2;
        }

        // Get the shortest expression and possible equal sign
        sort(exps, exps + n, cmp1);
        string equal = exps[0];
        sort(equal.begin(), equal.end());
        equal.erase(unique(equal.begin(), equal.end()), equal.end());
        for (int i = 0; i < equal.length(); i++)
            if (available[equal[i] - 'a'] != -2)
                available[equal[i] - 'a'] = 1;

        // Get equal sign
        string possible;
        for (int i = 0; i < 16; i++)
            if (available[i] >= 0)
                possible += (char)('a' + i);

        if (possible.length() == 0)
        {
            cout << "No\n";
            continue;
        }

        // Backtracking
        sort(exps, exps + n, cmp2);
        oops = 0, cnt = appeared.size();
        memset(mapping, -1, sizeof(mapping));

        for (auto es : possible)
        {
            memset(cache, -1, sizeof(cache));
            memset(used, 0, sizeof(used));
            cache[es - 'a'] = '=';

            for (int i = 0; i < n; i++)
            {
                int posOfEqual = exps[i].find(es);
                maxNumber[i] = pow(10, exps[i].length() - 1 - posOfEqual);
            }

            dfs(0, 0, 0, 0, 0, '+', '+');
        }

        // Check the solution exist or not
        if (oops)
        {
            cout << "Oops\n";
            continue;
        }
        
        bool printed = false;
        for (int i = 0; i < 16; i++)
        {
            if (mapping[i] > 0)
            {
                if (printed) cout << ' ';
                cout << (char)('a' + i);
                cout << mapping[i];
                printed = true;
            }
        }
        if (!printed) cout << "No";
        cout << '\n';
    }

    return 0;
}
