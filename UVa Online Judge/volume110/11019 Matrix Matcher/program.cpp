// Matrix Matcher
// UVa ID: 11019
// Verdict: Accepted
// Submission Date: 2019-09-24
// UVa Run Time: 0.980s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define GET(x, y, z) (MASK[x][y][z >> 5] & (1 << (z & 0x1F)))
#define SET(x, y, z) (MASK[x][y][z >> 5] |= (1 << (z & 0x1F)))

const int MAXN = 10240, CHARSET = 128, FAIL = -1;

int T, N, M, X, Y;
int MASK[1010][1010][4];

class AhoCorasick
{
private:
    int cnt, root;
    int go[MAXN][CHARSET], fail[MAXN];
    vector<string> keywords;
    vector<int> output[MAXN];

    void buildGotoFunction()
    {
        for (int i = 0; i < keywords.size(); i++) {
            int *current = &root;
            for (auto c : keywords[i]) {
                current = &go[*current][c];
                if (*current == FAIL) {
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
            if (go[0][i] != 0) {
                q.push(go[0][i]);
                fail[go[0][i]] = 0;
            }
        while (!q.empty()) {
            int r = q.front(); q.pop();
            for (int i = 0; i < CHARSET; i++)
                if (go[r][i] != FAIL) {
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

    void match(vector<string> &ss)
    {
        buildGotoFunction();
        buildFailureFunction();

        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                for (int k = 0; k < 4; k++)
                    MASK[i][j][k] = 0;

        for (int i = 0; i < ss.size(); i++)
        {
            int current = root;
            for (int j = 0; j < ss[i].length(); j++)
            {
                char c = ss[i][j];
                while (go[current][c] == FAIL) current = fail[current];
                current = go[current][c];
                if (output[current].size() > 0)
                    for (auto k : output[current])
                        if (i + X - k - 1 < N)
                            SET(i + X - k - 1, j, k);
            }
        }
        
        int KEY[4];
        bitset<128> bits;
        for (int i = 0; i < X; i++) bits.set(i);
        string binary = bits.to_string();
        for (int i = 0; i < 4; i++)
        {
            bitset<32> n(binary.substr((3 - i) * 32, 32));
            KEY[i] = (int)(n.to_ulong());
        }

        int times = 0;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
            {
                int matched = 1;
                for (int k = 0; k < 4 && matched; k++)
                    if (MASK[i][j][k] != KEY[k])
                        matched = 0;
                times += matched;
            }            
        cout << times << '\n';
    }
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    AhoCorasick ac;
    vector<string> MA;

    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> N >> M;
        MA.clear();
        for (int i = 0; i < N; i++)
        {
            cin >> line;
            MA.push_back(line);
        }
        cin >> X >> Y;
        ac.initialize();
        for (int i = 0; i < X; i++)
        {
            cin >> line;
            ac.add(line);
        }
        ac.match(MA);
    }

    return 0;
}
