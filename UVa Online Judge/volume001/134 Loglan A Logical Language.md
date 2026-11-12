[UVa 134 Loglan A Logical Language](https://blog.csdn.net/metaphysis/article/details/156788658)

## 题目描述
$\texttt{Loglan}$ 是一种人造的逻辑语言，用于测试语言学中的一些基本问题（如 $\texttt{Sapir-Whorf}$ 假设）。它的语法明确，文化中立，形而上简洁。题目要求判断给定的字符串是否为合法的 $\texttt{Loglan}$ 句子。

句子由单词和名字组成，以句点 `.` 结束。单词以元音结尾，名字以辅音结尾。单词分为两类：
- **小词（$\texttt{little words}$）** ：定义句子结构。
- **谓词（$\texttt{predicates}$）** ：形式为 `CCVCV` 或 `CVCCV`，其中 `C` 表示辅音，`V` 表示元音。

给出的语法规则如下（已简化）：
```
A      ⇒ a | e | i | o | u
MOD    ⇒ ga | ge | gi | go | gu
BA     ⇒ ba | be | bi | bo | bu
DA     ⇒ da | de | di | do | du
LA     ⇒ la | le | li | lo | lu
NAM    ⇒ {all names}
PREDA  ⇒ {all predicates}
<sentence>   ⇒ <statement> | <predclaim>
<predclaim>  ⇒ <predname> BA <preds> | DA <preds>
<preds>      ⇒ <predstring> | <preds> A <predstring>
<predname>   ⇒ LA <predstring> | NAM
<predstring> ⇒ PREDA | <predstring> PREDA
<statement>  ⇒ <predname> <verbpred> <predname> | <predname> <verbpred>
<verbpred>   ⇒ MOD <predstring>
```

**输入**：多个句子，每句以 `.` 结尾，输入以 `#` 结束。句子可跨行，单词间可有多个空格。

**输出**：对每个句子输出 `Good` 或 `Bad!`。

## 解题思路
本题是一个**语法分析**问题，适合使用**自顶向下**或**自底向上**的解析方法。由于规则较为复杂且涉及递归，我们可以采用**递归下降**或**表驱动**的解析方法。

### 关键点分析
1. **单词分类**：首先需要识别每个单词的类型（如 `A`、`MOD`、`BA`、`DA`、`LA`、`NAM`、`PREDA`）。
2. **递归结构**：多个语法规则是递归定义的，例如 `<preds>` 和 `<predstring>`。
3. **句子结构**：最终句子要么是 `<statement>`，要么是 `<predclaim>`。

### 方法选择
两种实现代码都使用了**自顶向下的递归判断**，但实现方式不同：
- **第一种**：为每个语法规则编写独立的判断函数，通过递归和拆分单词向量进行验证。
- **第二种**：使用**表驱动**的方法，将规则编码在表中，通过状态转换进行归约，类似于一个简单的**下推自动机**。

### 算法步骤（以第一种为例）
1. **读取输入**：按行读入，去掉句点，分割单词。
2. **分类判断**：
   - `isPREDA(word)`：检查是否为 `CCVCV` 或 `CVCCV`。
   - `isPredstring(words)`：检查是否全部为 `PREDA`。
   - `isPreds(words)`：递归检查 `<preds>` 结构。
   - `isPredname(words)`：检查 `LA <predstring>` 或 `NAM`。
   - `isStatement(words)`：检查 `<predname> <verbpred> <predname>` 或 `<predname> <verbpred>`。
   - `isPredclaim(words)`：检查 `<predname> BA <preds>` 或 `DA <preds>`。
3. **最终判断**：句子为 `<statement>` 或 `<predclaim>` 即合法。

## 代码实现
### 第一种：递归函数法
```cpp
// Loglan-A Logical Language
// UVa ID: 134
// Verdict: Accepted
// Submission Date: 2016-01-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// A => a | e | i | o | u
bool isA(char c) {
    string vowel = "aeiou";
    return vowel.find(c) != string::npos;
}

// MOD => ga | ge | gi | go | gu
bool isMOD(string word) {
    return word.length() == 2 && word[0] == 'g' && isA(word[1]);
}

// BA => ba | be | bi | bo | bu
bool isBA(string word) {
    return word.length() == 2 && word[0] == 'b' && isA(word[1]);
}

// DA => da | de | di | do | du
bool isDA(string word) {
    return word.length() == 2 && word[0] == 'd' && isA(word[1]);
}

// LA => la | le | li | lo | lu
bool isLA(string word) {
    return word.length() == 2 && word[0] == 'l' && isA(word[1]);
}

// NAM => { all names }，最后一个字母为辅音字母。
bool isNAM(string word) {
    return !isA(word.at(word.length() - 1));
}

// PREDA => { all predicates }，满足 CCVCV 或者 CVCCV 的模式，C 为辅音字母，
// V 为元音字母。使用位操作，将字符位置编为一个二进制数进行判断。
bool isPREDA(string word) {
    if (word.length() != 5) return false;
    int bitOr = 0;
    for (int i = 0; i < 5; i++) bitOr |= ((isA(word[i]) ? 1 : 0) << (4 - i));
    return (bitOr == 5 || bitOr == 9);
}

// <predstring> => PREDA | <predstring> PREDA
bool isPredstring(vector<string> words) {
    if (words.size() == 0) return false;
    for (int i = 0; i < words.size(); i++)
        if (!isPREDA(words[i]))
            return false;
    return true;
}

// <preds> => <predstring> | <preds> A <predstring>
bool isPreds(vector<string> words) {
    if (words.size() == 0) return false;
    // 找到起始的 PREDA 或 A
    for (int i = words.size() - 1; i >= 0; i--) {
        if (isPREDA(words[i])) continue;
        else if (words[i].length() == 1 && isA(words[i][0])) {
            if (i > 0) {
                vector<string> preds(words.begin(), words.begin() + i);
                return isPreds(preds);
            } else return false;
        } else return false;
    }
    return true;
}

// <predname> => LA <predstring> | NAM
bool isPredname(vector<string> words) {
    if (words.size() == 0) return false;
    if (!isLA(words.front()) && !isNAM(words.front())) return false;
    if (words.size() == 1 && isNAM(words.front())) return true;
    if (isLA(words.front())) {
        vector<string> predstring(words.begin() + 1, words.end());
        return isPredstring(predstring);
    } else return false;
    return true;
}

// <statement> => <predname> <verbpred> <predname> | <predname> <verbpred>
bool isStatement(vector<string> words) {
    // 找到 <verbpred>
    int i, j;
    for (i = 0; i <= (words.size() - 2); i++)
        if (isMOD(words.at(i))) {
            // 提取 <verbpred> 之前的 <predname>
            vector<string> predname(words.begin(), words.begin() + i);
            // 找到构成 <verbpred> 在 MOD 之后的所有 PREDA，若未到 words 的末端，
            // 则句子可能是 statement 的第一种模式，否则可能是第二种模式
            for (j = i + 1; j < words.size(); j++)
                if (!isPREDA(words[j]))
                    break;
            if (j < (words.size() - 1)) {
                vector<string> nextPredname(words.begin() + j, words.end());
                return isPredname(predname) && isPredname(nextPredname);
            } else return isPredname(predname);
        }
    return false;
}

// <predclaim> => <predname> BA <preds> | DA <preds>
bool isPredclaim(vector<string> words) {
    // DA <preds>
    if (isDA(words.front())) {
        vector<string> preds(words.begin() + 1, words.end());
        return isPreds(preds);
    }
    // <predname> BA <preds>
    for (int i = 0; i < words.size(); i++) {
        if (isBA(words[i])) {
            vector<string> predname(words.begin(), words.begin() + i);
            vector<string> preds(words.begin() + i + 1, words.end());
            return isPredname(predname) && isPreds(preds);
        }
    }
    return false;
}

// <sentence> => <statement> | <predclaim>
bool isSentence(vector<string> words) {
    if (words.size() == 0) return false;
    return isStatement(words) || isPredclaim(words);
}

int main() {
    vector<string> words;
    string line, word;
    while (getline(cin, line), line != "#") {
        // 读入字符串，将其转换为单词数组以便判定。
        string newLine(line);
        if (line.find('.') != string::npos)
            newLine = newLine.substr(0, newLine.find('.'));
        istringstream iss(newLine);
        while (iss >> word) words.push_back(word);
        if (line.find('.') != string::npos) {
            cout << (isSentence(words) ? "Good" : "Bad!") << endl;
            words.clear();
        }
    }
    return 0;
}
```

### 第二种：表驱动法
```cpp
// Loglan-A Logical Language
// UVa ID: 134
// Verdict: Accepted
// Submission Date: 2016-04-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int GROUPS = 14;
const int NONE = -1, A = 0, MOD = 1, BA = 2, DA = 3, LA = 4, NAM = 5,
    PREDA = 6, PREDSTRING = 7, PREDNAME = 8, PREDS = 9, VERBPRED = 10,
    PREDVERB = 11, PREDCLAIM = 12, STATEMENT = 13, SENTENCE = 14;

vector<int> S; vector<string> W;

int T[GROUPS][4] = {
    {PREDA, NONE, PREDA, PREDA}, {PREDA, NONE, NONE, PREDSTRING},
    {NAM, NONE, NONE, PREDNAME}, {LA, NONE, PREDSTRING, PREDNAME},
    {MOD, NONE, PREDSTRING, VERBPRED}, {A, PREDSTRING, PREDSTRING, PREDSTRING},
    {PREDSTRING, NONE, NONE, PREDS}, {DA, NONE, PREDS, PREDCLAIM},
    {BA, PREDNAME, PREDS, PREDCLAIM}, {VERBPRED, PREDNAME, NONE, PREDVERB},
    {PREDVERB, NONE, PREDNAME, STATEMENT}, {PREDVERB, NONE, NONE, STATEMENT},
    {STATEMENT, NONE, NONE, SENTENCE}, {PREDCLAIM, NONE, NONE, SENTENCE}
};

int getSymbol(string word) {
    string vowel = "aeiou";
    if (word.length() == 1 && vowel.find(word[0]) != word.npos) return A;
    if (word.length() == 2 && vowel.find(word[1]) != word.npos) {
        if (word[0] == 'g') return MOD;
        if (word[0] == 'b') return BA;
        if (word[0] == 'd') return DA;
        if (word[0] == 'l') return LA;
        return NONE;
    }
    if (vowel.find(word.back()) == word.npos) return NAM;
    if (word.length() == 5) {
        int bitOr = 0;
        for (int i = 0; i < 5; i++)
            bitOr |= ((vowel.find(word[i]) != word.npos ? 1 : 0) << (4 - i));
        if (bitOr == 5 || bitOr == 9)
            return PREDA;
    }
    return NONE;
}

bool parse() {
    S.clear();
    for (int i = 0; i < W.size(); i++) {
        int symbol = getSymbol(W[i]);
        if (symbol == NONE) return false;
        else S.push_back(symbol);
    }
    return true;
}

bool good() {
    if (!parse()) return false;
    for (int i = 0; i < GROUPS; i++)
        for (int j = 0; j < S.size(); ) {
            if ((S[j] != T[i][0]) ||
                (~T[i][1] && (!j || S[j - 1] != T[i][1])) ||
                (~T[i][2] && (j == (S.size() - 1) || S[j + 1] != T[i][2]))) {
                j++;
                continue;
            }
            j = ~T[i][1] ? S.erase(S.begin() + j - 1) - S.begin() : j;
            j = ~T[i][2]? S.erase(S.begin() + j + 1) - S.begin() - 1 : j;
            S[j] = T[i][3];
        }
    return (S.size() == 1 && S[0] == SENTENCE);
}

int main() {
    string line, word;
    while (getline(cin, line), line != "#") {
        string temp(line);
        if (line.find('.') != string::npos) temp = temp.substr(0, temp.find('.'));
        istringstream iss(temp);
        while (iss >> word) W.push_back(word);
        if (line.find('.') != string::npos) {
            cout << (good()? "Good" : "Bad!") << endl;
            W.clear();
        }
    }
    return 0;
}
```

## 总结
本题考察了**语法分析**的基本能力，适合作为编译原理的练习题。两种解法各有特点：
- **递归函数法**：直观易理解，适合规则较少的情况。
- **表驱动法**：代码简洁，易于扩展，适合规则较多且结构清晰的情况。

在实际解题时，建议先理解语法规则，再选择合适的解析方法。本题的难点在于递归规则的判断和单词类型的准确识别。
