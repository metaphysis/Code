// Bug Hunt
// UVa ID: 1596
// Verdict: Accepted
// Submission Date: 2025-10-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 存储数组名到大小的映射
map<string, int> arraySize;
// 存储数组元素的实际值
map<pair<string, int>, int> arrayValues;
// 记录数组元素是否被赋值过
map<pair<string, int>, bool> assigned;

// 表达式求值函数
// 参数：expr - 表达式字符串，currentLine - 当前行号，bugLine - 引用参数，用于记录错误行号
// 返回值：表达式的值，如果出错返回 -1
int evaluateExpression(const string& expr, int currentLine, int& bugLine) {
    // 如果是数字，直接转换为整数
    if (isdigit(expr[0])) {
        return stoi(expr);
    }
    
    // 数组访问表达式：name[inner_expr]
    size_t bracketPos = expr.find('[');
    string arrayName = expr.substr(0, bracketPos);
    string innerExpr = expr.substr(bracketPos + 1, expr.size() - bracketPos - 2);
    
    // 递归计算内部表达式（索引）
    int index = evaluateExpression(innerExpr, currentLine, bugLine);
    if (bugLine != 0) return -1; // 如果内部表达式已出错，直接返回
    
    // 检查索引是否越界
    if (index < 0 || index >= arraySize[arrayName]) {
        bugLine = currentLine;
        return -1;
    }
    
    // 检查该元素是否被赋值过（惰性检查）
    if (assigned.find({arrayName, index}) == assigned.end() || !assigned[{arrayName, index}]) {
        bugLine = currentLine;
        return -1;
    }
    
    // 返回数组元素的实际值
    return arrayValues[{arrayName, index}];
}

int main() {
    string line;
    
    // 读取多组测试数据，直到遇到单独的 "." 
    while (getline(cin, line) && line != ".") {
        vector<string> programLines;
        programLines.push_back(line);
        // 读取一个完整程序，直到遇到 "."
        while (getline(cin, line) && line != ".") {
            programLines.push_back(line);
        }
        
        // 清空数据结构，为新程序做准备
        arraySize.clear();
        arrayValues.clear();
        assigned.clear();
        int bugLine = 0; // 记录第一个错误的行号
        
        // 逐行处理程序
        for (int lineNum = 0; lineNum < programLines.size(); lineNum++) {
            const string& statement = programLines[lineNum];
            size_t equalPos = statement.find('=');
            
            if (equalPos == string::npos) {
                // 声明语句：array_name[size]
                size_t bracketPos = statement.find('[');
                string arrayName = statement.substr(0, bracketPos);
                string sizeStr = statement.substr(bracketPos + 1, statement.size() - bracketPos - 2);
                int size = stoi(sizeStr);
                arraySize[arrayName] = size;
                // 注意：不预先初始化元素，避免大数组问题
            } else {
                // 赋值语句：left = right
                string leftPart = statement.substr(0, equalPos);
                string rightPart = statement.substr(equalPos + 1);
                
                // 解析左值：array_name[index_expr]
                size_t bracketPos = leftPart.find('[');
                string leftArrayName = leftPart.substr(0, bracketPos);
                string leftIndexExpr = leftPart.substr(bracketPos + 1, leftPart.size() - bracketPos - 2);
                
                // 计算左值索引
                int leftIndex = evaluateExpression(leftIndexExpr, lineNum + 1, bugLine);
                if (bugLine != 0) break; // 如果计算过程出错，终止处理
                
                // 检查左值索引是否越界
                if (leftIndex < 0 || leftIndex >= arraySize[leftArrayName]) {
                    bugLine = lineNum + 1;
                    break;
                }
                
                // 计算右值表达式
                int rightValue = evaluateExpression(rightPart, lineNum + 1, bugLine);
                if (bugLine != 0) break; // 如果计算过程出错，终止处理
                
                // 执行赋值：标记元素已赋值并存储值
                assigned[{leftArrayName, leftIndex}] = true;
                arrayValues[{leftArrayName, leftIndex}] = rightValue;
            }
            
            // 如果已发现错误，提前终止
            if (bugLine != 0) break;
        }
        
        // 输出结果
        cout << bugLine << endl;
    }
    
    return 0;
}
