// Sub-Dictionary
// UVa ID: 1229
// Verdict: Accepted
// Submission Date: 2025-10-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <sstream>
#include <stack>
#include <cstring>

using namespace std;

const int MAXN = 105;

vector<int> graph[MAXN];      // 图的邻接表，存储单词间的依赖关系
map<string, int> wordToId;    // 单词到ID的映射
vector<string> idToWord;      // ID到单词的映射
int n;                        // 单词数量

// Tarjan算法相关变量
int dfsIndex;                 // DFS访问计数器
int dfn[MAXN];                // 每个节点的DFS访问序号
int low[MAXN];                // 每个节点能回溯到的最小DFS序号
bool inStack[MAXN];           // 标记节点是否在栈中
bool inAnswer[MAXN];          // 标记节点是否在最终答案中
stack<int> stk;               // Tarjan算法使用的栈
vector<vector<int>> sccList;  // 存储所有强连通分量

void tarjan(int u) {
    // 设置当前节点的DFS序号和low值
    dfn[u] = low[u] = ++dfsIndex;
    stk.push(u);              // 节点入栈
    inStack[u] = true;        // 标记节点在栈中
    
    // 遍历所有邻接节点
    for (int v : graph[u]) {
        if (!dfn[v]) {
            // 如果邻接节点未被访问，递归访问
            tarjan(v);
            // 回溯时更新当前节点的low值
            low[u] = min(low[u], low[v]);
        } else if (inStack[v]) {
            // 如果邻接节点在栈中，更新当前节点的low值
            low[u] = min(low[u], dfn[v]);
        }
    }
    
    // 如果当前节点是强连通分量的根节点
    if (dfn[u] == low[u]) {
        vector<int> scc;      // 存储当前强连通分量
        int v;
        do {
            v = stk.top();    // 取出栈顶元素
            stk.pop();        // 弹出栈顶
            inStack[v] = false; // 标记节点已出栈
            scc.push_back(v); // 将节点加入强连通分量
        } while (v != u);     // 直到遇到根节点
        sccList.push_back(scc); // 保存强连通分量
    }
}

// 深度优先搜索，标记所有可达节点
void dfs(int u) {
    if (!inAnswer[u]) {
        inAnswer[u] = true;   // 标记当前节点在答案中
        // 递归标记所有邻接节点
        for (int v : graph[u]) {
            dfs(v);
        }
    }
}

int main() {
    // 处理多个测试用例
    while (cin >> n && n) {
        // 初始化数据结构
        wordToId.clear();
        idToWord.clear();
        sccList.clear();
        for (int i = 0; i < n; i++) {
            graph[i].clear();
        }
        
        // 重置算法变量
        dfsIndex = 0;
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(inStack, false, sizeof(inStack));
        memset(inAnswer, false, sizeof(inAnswer));
        while (!stk.empty()) stk.pop();
        
        // 读取输入数据
        cin.ignore();  // 忽略换行符
        for (int i = 0; i < n; i++) {
            string line;
            getline(cin, line);     // 读取一行
            stringstream ss(line);  // 使用字符串流解析
            string word;
            ss >> word;             // 第一个单词是当前定义的单词
            
            // 为单词分配ID
            if (wordToId.find(word) == wordToId.end()) {
                int id = wordToId.size();
                wordToId[word] = id;
                idToWord.push_back(word);
            }
            int currentId = wordToId[word];
            
            // 处理定义中的单词
            string defWord;
            while (ss >> defWord) {
                // 为定义中的单词分配ID
                if (wordToId.find(defWord) == wordToId.end()) {
                    int id = wordToId.size();
                    wordToId[defWord] = id;
                    idToWord.push_back(defWord);
                }
                int defId = wordToId[defWord];
                // 建立依赖边：当前单词 -> 定义中的单词
                graph[currentId].push_back(defId);
            }
        }
        
        // 使用Tarjan算法寻找强连通分量
        for (int i = 0; i < n; i++) {
            if (!dfn[i]) {
                tarjan(i);
            }
        }
        
        // 处理强连通分量：对大小大于1的SCC进行DFS标记
        for (const auto& scc : sccList) {
            if (scc.size() > 1) {
                dfs(scc[0]);  // 从SCC中任意节点开始DFS
            }
        }
        
        // 收集答案
        vector<string> result;
        for (int i = 0; i < n; i++) {
            if (inAnswer[i]) {
                result.push_back(idToWord[i]);
            }
        }
        
        // 输出结果
        sort(result.begin(), result.end());
        cout << result.size() << endl;
        for (size_t i = 0; i < result.size(); i++) {
            if (i > 0) cout << " ";
            cout << result[i];
        }
        cout << endl;
    }
    
    return 0;
}
