[UVa 187 Transaction Processing](https://blog.csdn.net/metaphysis/article/details/160910771)

## 题目分析

本题是一个会计记账系统中的交易平衡检查程序。核心原理是**复式记账法**：每一笔交易中，所有借方（正数）和贷方（负数）的金额总和必须为零。

输入分为两部分：

1. **账户列表**：每行格式为 `nnnxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx`，其中 `nnn` 是三位账户编号，后续最多 $30$ 个字符为账户名称。以 `000` 开头的行表示结束，该行不被视为有效账户。

2. **交易记录**：每行格式为 `sssnnnxxxxxxxxx`，其中 `sss` 是三位交易序号，`nnn` 是账户编号，后续 $9$ 位数字表示金额（单位为分，无小数点）。正数表示借方，负数表示贷方。相同交易序号的所有记录构成一笔交易，交易包含 2 到 10 条记录。以 `000000` 开头的行表示结束。

输出要求：对于不平衡的交易（金额总和不为零），打印异常报告，按输入顺序列出交易中的每条记录（账户编号、名称、金额），最后一行输出 `999 Out of Balance` 和差额（取相反数以保持借方与贷方平衡）。金额输出保留两位小数。

## 解题思路

1. **存储账户信息**：使用 `map<string, string>` 将账户编号映射到账户名称。

2. **分组处理交易**：按交易序号将输入记录分组，相同序号的记录属于同一笔交易。

3. **计算平衡**：对每组交易累加金额（单位为分），若总和不为零则输出异常报告。

4. **格式化输出**：账户名称左对齐占 $30$ 个字符宽度，金额右对齐占 $10$ 个字符宽度并保留两位小数。

## 代码实现

```cpp
// Transaction Processing
// UVa ID: 187
// Verdict: Accepted
// Submission Date: 2016-03-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 交易记录结构体，存储账户编号、账户名称和金额（单位：分）
struct transaction {
    string number, name;
    long long money; 
};

// 账户映射：编号 -> 名称
map<string, string> account;
// 当前交易的所有原始记录行
vector<string> sequences;
// 当前交易的所有结构化记录
vector<transaction> allTransactions;

// 检查指定交易序号的交易是否平衡
void checkBalances(string sequenceNumber) {
    allTransactions.clear();
    
    long long balances = 0;
    // 遍历当前交易的所有记录
    for (int i = 0; i < sequences.size(); i++) {
        // 提取金额（第7位开始，共9位）
        long long money = stoll(sequences[i].substr(6));
        // 提取账户编号（第4-6位）
        string number = sequences[i].substr(3, 3);
        // 存储结构化记录
        allTransactions.push_back((transaction){number, account[number], money});
        // 累加金额以判断平衡
        balances += money;
    }
    
    // 如果金额总和不等于零，则交易不平衡
    if (balances != 0) {
        cout << "*** Transaction " << sequenceNumber << " is out of balance ***\n";
        // 输出交易中的所有记录
        for (int i = 0; i < allTransactions.size(); i++) {
            cout << allTransactions[i].number << " ";
            // 账户名称左对齐，宽度30
            cout << left << setw(30) << allTransactions[i].name << " ";
            // 金额右对齐，宽度10，保留两位小数
            cout << right << setw(10) << fixed << setprecision(2) <<
                 (allTransactions[i].money / 100.0) << "\n";
        }
        // 输出差额调整行（999 Out of Balance）
        cout << "999 Out of Balance                 " << right << setw(10)
             << fixed << setprecision(2) << (-balances / 100.0) << "\n";
        cout << "\n";
    }
}

int main() {
    string line;
    
    // 读取账户列表，直到遇到以"000"开头的行
    while (getline(cin, line)) {
        if (line.substr(0, 3) == "000")
            break; 
        // 提取账户名称（第4位开始），最多30个字符
        string name = line.substr(3);
        if (name.length() > 30)
            name = name.substr(0, 30);
        // 存入账户映射
        account.insert(make_pair(line.substr(0, 3), name));
    }
    
    string oldSequence, newSequence;
    // 读取交易记录，直到遇到以"000000"开头的行
    while (getline(cin, line)) {
        if (line.substr(0, 6) == "000000") {
            // 处理最后一笔交易
            checkBalances(oldSequence);
            break;
        }
           
        newSequence = line.substr(0, 3);
        // 如果是第一条记录，初始化当前交易序号
        if (oldSequence.length() == 0)
            oldSequence = newSequence;
        // 如果切换到了新交易，先检查上一笔交易
        else if (oldSequence != newSequence) {
            checkBalances(oldSequence);
            sequences.clear();
            oldSequence = newSequence;
        }

        // 将当前记录加入当前交易的记录列表
        sequences.push_back(line);
    }
    
	return 0;
}
```

## 注意事项

1. **金额处理**：输入金额为 $9$ 位整数表示“分”，输出时需要除以 $100$ 转换为“元”，保留两位小数。
2. **名称截断**：账户名称最多 $30$ 个字符，超出部分需截断。
3. **终止条件**：账户列表以 `000` 开头行结束，交易记录以 `000000` 开头行结束。
4. **差额符号**：输出 `999 Out of Balance` 行的金额应取 `-balances`，使借方与贷方平衡。
