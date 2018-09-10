// Equations in Disguise
// UVa ID: 11199
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int debug = 1;
int n, used[16], oops, cntOfAppeared;
string exps[24];
char cache[16], mapping[16];
char letter[12] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '*'};

bool cmp(string &a, string b)
{
    if (a.length() != b.length()) return a.length() < b.length();
    return a < b;
}

int evaluate(string &s)
{
    vector<int> r;
    int number = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '*')
        {
            r.push_back(number);
            r.push_back(-1);
            number = 0;
        }
        else if (s[i] == '+')
        {
            r.push_back(number);
            r.push_back(-2);
            number = 0;
        }
        else
        {
            number = number * 10 + s[i] - '0';
        }
    }
    r.push_back(number);
    while (true)
    {
        bool updated = false;
        for (int i = 0; i < r.size(); i++)
            if (r[i] == -1)
            {
                r[i - 1] *= r[i + 1];
                r.erase(r.begin() + i);
                r.erase(r.begin() + i);
                updated = true;
            }
        if (!updated) break;
    }
    while (r.size() > 1)
    {
        for (int i = 0; i < r.size(); i++)
            if (r[i] == -2)
            {
                r[i - 1] += r[i + 1];
                r.erase(r.begin() + i);
                r.erase(r.begin() + i);
            }
    }
    return r.front();
}

bool error(string &s)
{
    if (s.length() == 0) return true;
    if (!isdigit(s.front()) || !isdigit(s.back())) return true;
    for (int i = 0; i < s.length(); i++)
        if (!isdigit(s[i]))
        {
            if (i + 1 < s.length())
            {
                if (s[i + 1] == '0')
                {
                    if (i + 2 < s.length())
                    {
                        if (isdigit(s[i + 2]))
                            return true;
                    }
                }
            }
        }
    return false;
}

bool validate(int depth)
{
    string leftPart, rightPart;
    bool equalMeeted = false;
    for (int i = 0; i < exps[depth].length(); i++)
    {
        if (cache[exps[depth][i] - 'a'] == '=')
        {
            equalMeeted = true;
            continue;
        }
        if (equalMeeted)
            rightPart += cache[exps[depth][i] - 'a'];
        else
            leftPart += cache[exps[depth][i] - 'a'];
    }
    if (error(leftPart) || error(rightPart)) return false;
    return evaluate(leftPart) == evaluate(rightPart);
}

void dfs(int depth, int level)
{
    if (oops) return;
    if (depth == n)
    {
        if (debug)
        {
            for (int i = 0; i < depth; i++)
            {
                for (int j = 0; j < exps[i].length(); j++)
                    cout << cache[exps[i][j] - 'a'];
                cout << endl;
            }
        }
        for (int i = 0; i < 12; i++)
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
        oops = (count(mapping, mapping + 13, -2) == cntOfAppeared);
        return;
    }
    
    if (level == exps[depth].length())
    {
        if (validate(depth))
            dfs(depth + 1, 0);
    }
    else
    {
        // A symbol have matched, continue to next char of expression
        char now = cache[exps[depth][level] - 'a'];
        
        if (now != -1)
        {
            char pre = cache[exps[depth][level - 1] - 'a'];
            if (level == 0 || level == exps[depth].length() - 1)
            {
                if (!isdigit(now))
                    return;
            }
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
                if (pre == '0' && !isdigit(cache[exps[depth][level - 2] - 'a']))
                    return;
            }

            dfs(depth, level + 1);
        }
        // Unmatched
        else
        {
            for (int i = 0; i < 12; i++)
            {
                if (used[i]) continue;
                // The start of an expression can't be a sign or zero
                if (level == 0 || level == exps[depth].length() - 1)
                {
                    if (!isdigit(letter[i]))
                        continue;
                }
                // After a sign must be a non zero digit
                if (level && !isdigit(cache[exps[depth][level - 1] - 'a']))
                {
                    if (letter[i] == '0' || !isdigit(letter[i]))
                        continue;
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
                dfs(depth, level + 1);
                used[i] = 0;
                cache[exps[depth][level] - 'a'] = -1;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    //cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

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
                available[exps[i][j] - 'a']++;
            }
            for (int j = 0; j < 16; j++)
                if (available[j] != i)
                    available[j] = -2;
        }

        sort(exps, exps + n, cmp);
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
        oops = 0, cntOfAppeared = appeared.size();
        memset(mapping, -1, sizeof(mapping));
        for (auto es : possible)
        {
            memset(cache, -1, sizeof(cache));
            memset(used, 0, sizeof(used));
            cache[es - 'a'] = '=';
            dfs(0, 0);
        }

        // Check the solution exist or not
        if (oops)
        {
            cout << "Oops\n";
            continue;
        }
        
        bool outputed = false;
        for (int i = 0; i < 16; i++)
        {
            if (mapping[i] > 0)
            {
                if (outputed) cout << ' ';
                cout << (char)('a' + i);
                cout << mapping[i];
                outputed = true;
            }
        }
        if (!outputed) cout << "No";
        cout << '\n';
    }

    return 0;
}
