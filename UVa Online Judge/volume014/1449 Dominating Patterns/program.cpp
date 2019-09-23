// Dominating Patterns
// UVa ID: 1449
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10240, CHARSET = 128, FAIL = -1;

int times[256];

class AhoCorasick
{
private:
    int cnt, root, go[MAXN][CHARSET], fail[MAXN];
    vector<string> keywords;
    vector<int> output[MAXN];

    void buildGotoFunction()
    {
        for (int i = 0; i < keywords.size(); i++)
        {
            int *current = &root;
            for (auto c : keywords[i])
            {
                current = &go[*current][c];
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
        memset(go[0], FAIL, sizeof(go[0]));
        keywords.clear();
        root = cnt = 0;
    }

    void add(string s) { keywords.push_back(s); }

    void match(string &s)
    {
        buildGotoFunction();
        buildFailureFunction();

        int current = root;
        for (auto c : s)
        {
            while (go[current][c] == FAIL) current = fail[current];
            current = go[current][c];
            if (output[current].size() > 0)
                for (auto i : output[current])
                    times[i]++;
        }
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    string key, text;
    AhoCorasick ac;
    vector<string> patterns;

    while (cin >> n, n > 0)
    {
        ac.initialize();
        patterns.clear();
        for (int i = 0; i < n; i++)
        {
            cin >> key;
            ac.add(key);
            patterns.push_back(key);
        }
        cin.ignore(256, '\n');
        getline(cin, text);
        memset(times, 0, sizeof(times));
        ac.match(text);
        int maxTimes = *max_element(times, times + 128);
        cout << maxTimes << '\n';
        for (int i = 0; i < n; i++)
            if (times[i] == maxTimes)
                cout << patterns[i] << '\n';
    }

    return 0;
}
