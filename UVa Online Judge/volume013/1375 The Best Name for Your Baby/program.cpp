// The Best Name for Your Baby
// UVa ID: 1375
// Verdict: Accepted
// Submission Date: 2026-06-17
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_RULES = 55;
const int MAX_LEN = 25;
const int MAX_SYMS = 50 * 20 + 100;

struct Transform {
    int target;
    int emptyPart;
    Transform(int t, int e) : target(t), emptyPart(e) {}
};

int n, L;
int symCnt;
string rules[MAX_RULES];
string symStr[MAX_SYMS];
map<string, int> symToId;
string dp[MAX_SYMS][MAX_LEN];
vector<Transform> trans[MAX_SYMS];
int head[MAX_SYMS], tail[MAX_SYMS];

struct Node {
    int id;
    string str;
    Node(int i, string s) : id(i), str(s) {}
    bool operator<(const Node& other) const {
        return str > other.str;
    }
};

int getId(const string& s) {
    if (symToId.count(s)) return symToId[s];
    symStr[symCnt] = s;
    return symToId[s] = symCnt++;
}

void addIntermediateSymbol(const string& str) {
    int id = getId(str);
    int len = str.length();
    if (len < 2) return;
    int h = getId(str.substr(0, 1));
    int t = getId(str.substr(1));
    trans[h].push_back(Transform(id, t));
    trans[t].push_back(Transform(id, h));
    head[id] = h;
    tail[id] = t;
}

bool isLowercaseOnly(const string& s) {
    for (char c : s) {
        if (!(c >= 'a' && c <= 'z')) return false;
    }
    return true;
}

string minString(const string& a, const string& b) {
    if (a == "-") return b;
    if (b == "-") return a;
    return (a < b) ? a : b;
}

bool visited[MAX_SYMS];

void searchSameLevel(int len) {
    memset(visited, 0, sizeof(visited));
    priority_queue<Node> pq;
    
    for (int i = 0; i < symCnt; i++) {
        if (dp[i][len] != "-") {
            pq.push(Node(i, dp[i][len]));
        }
    }
    
    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();
        int x = cur.id;
        string s = cur.str;
        if (visited[x]) continue;
        visited[x] = true;
        
        for (const Transform& t : trans[x]) {
            int target = t.target;
            int empty = t.emptyPart;
            if (dp[empty][0] == "" && (dp[target][len] == "-" || s < dp[target][len])) {
                dp[target][len] = s;
                pq.push(Node(target, s));
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (cin >> n >> L && (n != 0 || L != 0)) {
        symToId.clear();
        symCnt = 0;
        getId("");
        
        for (int i = 0; i < MAX_SYMS; i++) {
            trans[i].clear();
        }
        
        for (int i = 0; i < n; i++) {
            cin >> rules[i];
            int left = getId(rules[i].substr(0, 1));
            int right = getId(rules[i].substr(2));
            
            trans[right].push_back(Transform(left, getId("")));
            
            int len = rules[i].length();
            for (int k = 2; k < len; k++) {
                addIntermediateSymbol(rules[i].substr(k));
            }
        }
        
        for (int i = 0; i < symCnt; i++) {
            for (int j = 0; j <= L; j++) {
                dp[i][j] = "-";
            }
        }
        dp[0][0] = "";
        
        for (int len = 0; len <= L; len++) {
            for (int i = 0; i < symCnt; i++) {
                if ((int)symStr[i].length() == len && isLowercaseOnly(symStr[i])) {
                    dp[i][len] = symStr[i];
                }
                
                if ((int)symStr[i].length() < 2) continue;
                
                int first = head[i];
                int second = tail[i];
                for (int k = 1; k < len; k++) {
                    if (dp[first][k] != "-" && dp[second][len - k] != "-") {
                        dp[i][len] = minString(dp[i][len], dp[first][k] + dp[second][len - k]);
                    }
                }
            }
            searchSameLevel(len);
        }
        
        cout << dp[getId("S")][L] << "\n";
    }
    
    return 0;
}
