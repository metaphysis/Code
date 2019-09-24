// Dominating Patterns
// UVa ID: 1449
// Verdict: Accepted
// Submission Date: 2019-09-24
// UVa Run Time: 0.030s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 11000, CHARSET = 26, FAIL = -1, OFFSET = 'a';

class AhoCorasick
{
private:
    int cnt, root, go[MAXN][CHARSET], fail[MAXN], times[256];
    vector<string> keywords;
    vector<int> output[MAXN];

    void buildGotoFunction()
    {
        for (int i = 0; i < keywords.size(); i++)
        {
            int *current = &root;
            for (auto c : keywords[i])
            {
                current = &go[*current][c - OFFSET];
                if (*current == FAIL)
                {
                    *current = ++cnt;
                    memset(go[cnt], FAIL, sizeof(go[cnt]));
                    output[cnt].clear();
                }
            }
            output[*current].push_back(i);
        }
        for (int i = 0; i < CHARSET; i++)
            if (go[0][i] == FAIL)
                go[0][i] = 0;
    }

    void buildFailureFunction()
    {
        queue<int> q;
        for (int i = 0; i < CHARSET; i++)
            if (go[0][i] != 0)
            {
                q.push(go[0][i]);
                fail[go[0][i]] = 0;
            }
        while (!q.empty())
        {
            int r = q.front(); q.pop();
            for (int i = 0; i < CHARSET; i++)
                if (go[r][i] != FAIL)
                {
                    int s = go[r][i], f = fail[r];
                    q.push(s);
                    while (go[f][i] == FAIL) f = fail[f];
                    fail[s] = go[f][i];
                    output[s].insert(output[s].end(),
                        output[fail[s]].begin(), output[fail[s]].end());
                }
        }
    }

public:
    void initialize()
    {
        root = cnt = 0;
        keywords.clear();
        memset(go[0], FAIL, sizeof(go[0]));
        for (int i = 0; i < MAXN; i++) output[i].clear();
    }

    void add(string s) { keywords.push_back(s); }

    void match()
    {
        buildGotoFunction();
        buildFailureFunction();

        char c;
        int current = root;
        memset(times, 0, sizeof(times));

        cin.ignore(256, '\n');
        cin.unsetf(ios::skipws);
        while (cin >> c, c != '\n')
        {
            while (go[current][c - OFFSET] == FAIL) current = fail[current];
            current = go[current][c - OFFSET];
            if (output[current].size() > 0)
                for (auto i : output[current])
                    times[i]++;
        }
        cin.setf(ios::skipws);

        int n = keywords.size();
        int maxTimes = *max_element(times, times + n);
        cout << maxTimes << '\n';
        for (int i = 0; i < n; i++)
            if (times[i] == maxTimes)
                cout << keywords[i] << '\n';
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    AhoCorasick ac;
    string key;

    while (cin >> n, n > 0)
    {
        ac.initialize();
        for (int i = 0; i < n; i++)
        {
            cin >> key;
            ac.add(key);
        }
        ac.match();
    }

    return 0;
}
