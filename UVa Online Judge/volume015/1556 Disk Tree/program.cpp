// Disk Tree
// UVa ID: 1556
// Verdict: Accepted
// Submission Date: 2025-11-07
// UVa Run Time: 0.030s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

// 目录树节点
struct Directory {
    map<string, Directory*> children;
    
    ~Directory() {
        for (auto& child : children) {
            delete child.second;
        }
    }
};

// 分割路径
vector<string> splitPath(const string& path) {
    vector<string> result;
    stringstream ss(path);
    string item;
    
    while (getline(ss, item, '\\')) {
        result.push_back(item);
    }
    
    return result;
}

// 插入路径到目录树
void insertPath(Directory* root, const vector<string>& path) {
    Directory* current = root;
    
    for (const string& dir : path) {
        if (current->children.find(dir) == current->children.end()) {
            current->children[dir] = new Directory();
        }
        current = current->children[dir];
    }
}

// 递归打印目录树
void printTree(Directory* node, int depth = 0) {
    // 按字典序排序子目录名
    vector<string> dirNames;
    for (const auto& child : node->children) {
        dirNames.push_back(child.first);
    }
    sort(dirNames.begin(), dirNames.end());
    
    // 打印当前深度的所有目录
    for (const string& dirName : dirNames) {
        // 输出缩进
        for (int i = 0; i < depth; i++) {
            cout << " ";
        }
        // 输出目录名
        cout << dirName << endl;
        // 递归打印子目录
        printTree(node->children[dirName], depth + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    bool firstDataset = true;
    
    while (cin >> N) {
        // 跳过数据集之间的空行
        if (!firstDataset) {
            cout << endl;
        }
        firstDataset = false;
        
        // 读取换行符
        cin.ignore();
        
        Directory root;
        
        // 读取并处理所有路径
        for (int i = 0; i < N; i++) {
            string path;
            getline(cin, path);
            
            vector<string> pathComponents = splitPath(path);
            insertPath(&root, pathComponents);
        }
        
        // 打印目录树
        printTree(&root);
    }
    
    return 0;
}
