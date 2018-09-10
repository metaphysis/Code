// Equations in Disguise
// UVa ID: 11199
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int debug = 1, debug1 = 1;
string exps[24];
int n, used[16], oops, cnt;
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

bool error()
{
    if (debug)
    {
        cout << "Debug: ----------\n";
    }
    for (int i = 0; i < n; i++)
    {
        if (debug)
        {
            cout << exps[i] << ' ';
            for (int j = 0; j < exps[i].length(); j++)
            {
                char now = cache[exps[i][j] - 'a'];
                if (now == -1) cout << '#';
                else cout << now;
            }
            cout << '\n';
        }
        for (int j = 0; j < exps[i].length(); j++)
        {
            char now = cache[exps[i][j] - 'a'];
            if (now != -1)
            {
                if (now == '*' || now == '+' || now == '=')
                {
                    if (j == 0 || j == exps[i].length() - 1)
                    {
                        cout << "ERROR1\n";
                        return true;
                    }
                    if (j + 1 < exps[i].length())
                    {
                        char after = cache[exps[i][j + 1] - 'a'];
                        if (after == '0')
                        {
                            if (j + 2 < exps[i].length())
                            {
                                char next = cache[exps[i][j + 2] - 'a'];
                                if (next != -1)
                                {
                                    if (isdigit(next))
                                    {
                                        cout << "ERROR2\n";
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
                if (now == '0' && j == 0)
                {
                    if (j + 1 < exps[i].length())
                    {
                        char after = cache[exps[i][j + 1] - 'a'];
                        if (after != -1)
                        {
                            if (isdigit(after))
                            {
                                cout << "ERROR3\n";
                                return true;
                            }
                        }
                    }
                }
                if (j > 0)
                {
                    char pre = cache[exps[i][j - 1] - 'a'];
                    if (now == '*' || now == '+' || now == '=')
                        if (pre == '*' || pre == '+' || pre == '=')
                        {
                            cout << "ERROR4\n";
                            return true;
                        }
                }
            }
        }
    }
    return false;
}

bool validate()
{
    for (int i = 0; i < n; i++)
    {
        string leftPart, rightPart;
        bool equalMeeted = false;
        for (int j = 0; j < exps[i].length(); j++)
        {
            if (cache[exps[i][j] - 'a'] == '=')
            {
                equalMeeted = true;
                continue;
            }
            if (equalMeeted)
                rightPart += cache[exps[i][j] - 'a'];
            else
                leftPart += cache[exps[i][j] - 'a'];
        }
        if (evaluate(leftPart) != evaluate(rightPart)) return false;
    }
    return true;
}

void dfs(int depth)
{
    if (oops) return;
    if (depth == 13)
    {
        if (validate())
        {
            if (debug1)
            {
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < exps[i].length(); j++)
                        cout << cache[exps[i][j] - 'a'];
                    cout << '\n';
                }
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
        }
        return;
    }
    
    if (cache[depth] != -1)
    {
        if (error()) return;
        dfs(depth + 1);
    }
    else
    {
        for (int i = 0; i < 12; i++)
        {
            if (used[i]) continue;
            cache[depth] = letter[i];
            if (error())
            {
                cache[depth] = -1;
                continue;
            }
            cache[depth] = letter[i], used[i] = 1;
            dfs(depth + 1);
            cache[depth] = -1, used[i] = 0;
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
            used[12] = 1;
            dfs(0);
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
