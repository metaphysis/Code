// Accountant Notes
// UVa ID: 1441
// Verdict: Accepted
// Submission Date: 2025-10-26
// UVa Run Time: 1.290s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 特殊标记定义
const int EQ = -1e9 - 1;   // 表示 '=' 分隔符
const int ED = -1e9 - 2;   // 表示行结束符

struct AC {
    struct Node {
        unordered_map<int, int> ch;  // 子节点映射: token -> 节点编号
        int fail = 0;                // 失败指针
        int depth = 0;               // 节点深度
        vector<int> notes;           // 匹配到此节点时对应的记录编号
    };
    vector<Node> nodes;
    
    AC() { 
        nodes.emplace_back(); 
        nodes[0].depth = 1;  // 根节点深度为1
    }
    
    // 插入记录模式到Trie树
    void insert(const vector<int>& pattern, int id) {
        int u = 0;  // 从根节点开始
        for (int token : pattern) {
            // 如果边不存在，创建新节点
            if (!nodes[u].ch.count(token)) {
                nodes.emplace_back();
                nodes.back().depth = nodes[u].depth + 1;
                nodes[u].ch[token] = nodes.size() - 1;
            }
            u = nodes[u].ch[token];
        }
        nodes[u].notes.push_back(id);  // 记录匹配到此节点的记录编号
    }
    
    // 构建Aho-Corasick自动机的失败指针
    void build() {
        queue<int> q;
        // 根节点的所有子节点的失败指针指向根节点
        for (auto& [token, child] : nodes[0].ch) 
            q.push(child);
        
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto& [token, child] : nodes[u].ch) {
                int v = nodes[u].fail;
                // 沿失败链寻找匹配的边（使用归一化）
                while (v && !nodes[v].ch.count(min(nodes[v].depth, token))) 
                    v = nodes[v].fail;
                
                // 设置失败指针
                if (v) {
                    nodes[child].fail = nodes[v].ch[min(nodes[v].depth, token)];
                } else {
                    // 检查根节点是否有匹配的边
                    int norm = min(1, token);  // 根节点的子节点深度为1
                    nodes[child].fail = nodes[0].ch.count(norm) ? nodes[0].ch[norm] : 0;
                }
                q.push(child);
            }
        }
    }
    
    // 在文本中匹配所有记录
    vector<int> match(const vector<int>& text, const vector<int>& noteLen, int k) {
        vector<int> res(k + 1);           // 记录每个记录的匹配结束行
        vector<bool> vis(nodes.size());   // 节点访问标记（去重）
        int u = 0, line = 1;              // 当前节点和行号
        
        for (int token : text) {
            // 对文本token进行归一化
            int norm = min(nodes[u].depth, token);
            int v = u;
            
            // 沿失败链寻找匹配
            while (v && !nodes[v].ch.count(norm)) {
                v = nodes[v].fail;
                norm = min(nodes[v].depth, token);  // 重新计算归一化值
            }
            
            // 转移到匹配的节点或根节点
            if (v) {
                u = nodes[v].ch[norm];
            } else {
                u = nodes[0].ch.count(min(1, token)) ? nodes[0].ch[min(1, token)] : 0;
            }
            
            // 标记所有匹配的记录
            for (v = u; v && !vis[v]; v = nodes[v].fail) {
                vis[v] = true;
                for (int id : nodes[v].notes) {
                    if (!res[id]) res[id] = line;  // 记录第一次匹配的结束行
                }
            }
            
            // 遇到行结束符时更新行号
            if (token == ED) line++;
        }
        return res;
    }
};

// 将文本行编码为token序列
vector<int> encode(int lines) {
    vector<int> res;
    unordered_map<string, int> pos;  // 记录变量名最近出现的位置
    int idx = 0;                     // 当前编码位置
    
    cin.ignore();  // 忽略换行符
    for (int i = 0; i < lines; i++) {
        string line, name, expr1, expr2;
        char _;
        getline(cin, line);
        stringstream ss(line);
        ss >> name >> _ >> expr1;
        
        // 编码lambda函数
        auto enc = [&](const string& s) {
            if (!s.empty() && isdigit(s[0]) && (s.size() == 1 || s[0] != '0')) {
                // 数字字面量：转换为负值
                res.push_back(-stoi(s));
                idx++;
            } else {
                // 变量名：新变量为idx+1，引用变量为位置差
                res.push_back(pos.count(s) ? idx - pos[s] : idx + 1);
                pos[s] = idx++;
            }
        };
        
        enc(name);           // 编码变量名
        res.push_back(EQ);   // 等号分隔符
        idx++;
        enc(expr1);          // 编码第一个表达式
        
        // 如果有第二个表达式
        if (ss >> _ >> expr2) 
            enc(expr2);
        
        res.push_back(ED);   // 行结束符
        idx++;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int Z;
    cin >> Z;
    while (Z--) {
        int k;
        cin >> k;
        AC ac;
        vector<int> noteLen(k + 1);
        
        // 读取并编码所有记录
        for (int i = 1; i <= k; i++) {
            cin >> noteLen[i];
            ac.insert(encode(noteLen[i]), i);
        }
        
        ac.build();  // 构建自动机
        
        // 读取并编码汇总文件
        int sumLines;
        cin >> sumLines;
        auto matchRes = ac.match(encode(sumLines), noteLen, k);
        
        // 输出结果
        for (int i = 1; i <= k; i++) {
            if (matchRes[i]) {
                // 起始行 = 结束行 - 记录行数 + 1
                cout << matchRes[i] - noteLen[i] + 1 << "\n";
            } else {
                cout << "NONE\n";
            }
        }
    }
    return 0;
}
