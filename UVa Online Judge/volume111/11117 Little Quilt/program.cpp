// Little Quilt
// UVa ID: 11117
// Verdict: Accepted
// Submission Date: 2026-01-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Quilt {
    vector<string> grid;
    
    // 默认构造函数
    Quilt() = default;
    
    // 构造函数
    Quilt(const vector<string> &g) : grid(g) {}
    
    // 创建基本被子 A
    static Quilt makeA() {
        return Quilt({"//", "/+"});
    }
    
    // 创建基本被子 B
    static Quilt makeB() {
        return Quilt({"--", "--"});
    }
    
    // 顺时针旋转 90 度
    Quilt turn() const {
        int h = grid.size();
        int w = grid[0].size();
        vector<string> res(w, string(h, ' '));
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                char c = grid[i][j];
                if (c == '/') c = '\\';
                else if (c == '\\') c = '/';
                else if (c == '-') c = '|';
                else if (c == '|') c = '-';
                // + 保持不变
                res[j][h-1-i] = c;
            }
        }
        return Quilt(res);
    }
    
    // 拼接两个被子，将当前被子缝在左侧
    bool sew(const Quilt &other, Quilt &result) const {
        if (grid.size() != other.grid.size()) return false;
        int h = grid.size();
        vector<string> res(h);
        for (int i = 0; i < h; i++)
            res[i] = grid[i] + other.grid[i];
        result = Quilt(res);
        return true;
    }
    
    // 转换为字符串输出
    string toString() const {
        string s;
        for (size_t i = 0; i < grid.size(); i++) {
            if (i > 0) s += '\n';
            s += grid[i];
        }
        return s;
    }
};

class Parser {
    string input;
    size_t pos;
    int quiltId;
    
    // 跳过空白字符
    void skipSpaces() {
        while (pos < input.size() && isspace(input[pos])) pos++;
    }
    
    // 解析表达式
    bool parseExpr(Quilt &result) {
        skipSpaces();
        if (pos >= input.size()) return false;
        
        // 处理基本图案 A 或 B
        if (input[pos] == 'A' || input[pos] == 'B') {
            result = input[pos] == 'A' ? Quilt::makeA() : Quilt::makeB();
            pos++;
            return true;
        }
        
        // 读取函数名
        string func;
        while (pos < input.size() && isalpha(input[pos])) func += input[pos++];
        
        skipSpaces();
        if (pos >= input.size() || input[pos] != '(') return false;
        pos++;
        
        // 处理 turn 操作
        if (func == "turn") {
            Quilt q;
            if (!parseExpr(q)) return false;
            skipSpaces();
            if (pos >= input.size() || input[pos] != ')') return false;
            pos++;
            result = q.turn();
            return true;
        } 
        // 处理 sew 操作
        else if (func == "sew") {
            Quilt left, right;
            if (!parseExpr(left)) return false;
            skipSpaces();
            if (pos >= input.size() || input[pos] != ',') return false;
            pos++;
            if (!parseExpr(right)) return false;
            skipSpaces();
            if (pos >= input.size() || input[pos] != ')') return false;
            pos++;
            return left.sew(right, result);
        }
        
        return false;
    }
    
public:
    Parser(const string &s) : input(s), pos(0), quiltId(1) {}
    
    // 解析所有表达式
    void parseAll() {
        while (pos < input.size()) {
            Quilt q;
            if (parseExpr(q)) {
                cout << "Quilt " << quiltId++ << ":" << endl;
                cout << q.toString() << endl;
            } else {
                cout << "Quilt " << quiltId++ << ":" << endl;
                cout << "error" << endl;
            }
            
            // 跳过表达式后的分号
            skipSpaces();
            if (pos < input.size() && input[pos] == ';') {
                pos++;
                skipSpaces();
            } else break;
        }
    }
};

int main() {
    // 读取整个输入
    string input, line;
    while (getline(cin, line)) input += line + " ";
    Parser parser(input);
    parser.parseAll();
    return 0;
}
