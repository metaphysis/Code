
> **摘要**：本题要求编写程序验证西班牙语十四行诗的格式，核心是判断全诗是否为 $14$ 行、每行末尾单词能否匹配给定后缀列表，以及由此得到的韵脚序列是否符合 `ABBAABBA` 加三种后六行变体（`CDCDCD`、`CDECDE`、`CDEDCE`）的固定模式。解法依次完成文本清洗、末尾单词提取、忽略复数 `s` 的后缀匹配与模式校验，时间复杂度为 $O(T \times 14 \times s \times L)$，实现简洁高效。

## 题目描述

十四行诗（$\texttt{sonnet}$）是一种具有固定格式的诗歌体裁。西班牙语十四行诗必须满足三条规则：全诗共 $14$ 行；韵脚结构符合特定模式；每行为十一音节。本题要求编写程序验证前两条规则，其中韵脚匹配规则根据后缀定义。

给定若干测试实例，每个实例包含一组后缀列表、标题和 $14$ 行诗句。判定这些诗句是否满足以下条件：
- 共有 $14$ 行。
- 将每行末尾的有效单词（去除空格与标点后得到的最后一个连续字母串）与给定后缀列表中的后缀进行匹配。若一行末尾单词以某一后缀结尾（或该单词去掉末尾字母 `s` 后以该后缀结尾），则认为该行属于该后缀对应的韵脚类。
- 按顺序得到的 $14$ 个韵脚类别索引必须满足：
  前 $8$ 个为 $A, B, B, A, A, B, B, A$（即索引序列 $0,1,1,0,0,1,1,0$）。
  后 $6$ 个必须为下列模式之一：
  - $C, D, C, D, C, D$（即索引序列 $2,3,2,3,2,3$）
  - $C, D, E, C, D, E$（即索引序列 $2,3,4,2,3,4$）
  - $C, D, E, D, C, E$（即索引序列 $2,3,4,3,2,4$）

其中 $A, B, C, D, E$ 按后缀列表中的出现顺序依次对应 $0,1,2,3,4$。当后缀总数 $s=4$ 时，只有 $C, D$ 可用，故只允许第一种后六模式；当 $s=5$ 时，三种后六模式均可。

若满足所有条件，输出标题和匹配到的韵脚结构字符串（`ABBAABBACDCDCD`、`ABBAABBACDECDE` 或 `ABBAABBACDEDCE`）；否则输出 `<标题>: Not a chance!`。

## 输入格式

输入包含多个测试实例。每个实例由若干行组成，数据之间可能穿插空行。每个实例的格式为：
- 第一行为 $s$ 个后缀（$4 \le s \le 5$），以空格分隔。这些后缀按顺序命名为 $A, B, C, D, E$。
- 第二行为作品标题（可能包含空格）。
- 接下来的 $14$ 行为诗句，每行至多 $80$ 个字符。诗句行不为空，且不同实例之间用空行分隔。

保证同一实例中任意一个后缀都不是另一个的后缀。

## 输出格式

对于每个测试实例，按输入顺序输出一行。若该实例满足规则，输出格式为：
```text
<标题>: <结构>
```
其中 `<标题>` 为原标题，`<结构>` 为上述三种结构之一。若不满足，输出：
```text
<标题>: Not a chance!
```

## 样例

### 样例输入
```text
ida é amo ella
ES ELLA
Locura, intensa y sin medida
andando errante te avisté,
una nota en tus manos encontré:
rumor de un amor y su partida.
Adelante, te diré de su vida
aunque en mi regazo ya no esté,
fueron sus labios con que tropecé
los que te llamaron despavorida.
Ojos negros, pestañas en un ramo,
rizos finos, humor, siempre bella;
!`es ella, amiga, a quien amo!
Zagales de secretos sus estrellas,
cómplices la lluvia y el álamo;
... es ella, nuestra musa, !`es ella!

ura ima illa eto
OTrO
Esta composición posiblemente rima
pero nunca será un soneto
con esta frase ya no sirve
ni tampoco porque está incompleto.
```

### 样例输出
```text
ES ELLA: ABBAABBACDCDCD
OTrO: Not a chance!
```

## 题目分析

本题的核心任务是对给定诗句进行文本清洗、后缀匹配和模式验证。需要特别注意两点：

- **标点与空格处理**：诗句中的标点符号（逗号、句号、感叹号、引号等）以及空格均需忽略。每行末尾的有效单词是指从行末倒数第一个非分隔符字符开始，向左连续的非分隔符字符序列。分隔符包括空格和所有常见英文及西班牙语标点。
- **西班牙语复数形式**：在西班牙语中，名词复数通常以字母 `s` 结尾。押韵时，复数名词与单数形式可视为同韵，因此匹配后缀时允许忽略单词末尾的 `s`。例如 `estrellas` 可以匹配后缀 `ella`。

韵脚结构共有三种可能的模式，其中前 $8$ 行固定为 `ABBAABBA`，后 $6$ 行有三种变体。当后缀数量为 $4$ 时，只有 `CDCDCD` 可用；当后缀数量为 $5$ 时，三种均可能。验证过程需依次检查这些条件。

此外，输入中不同实例之间可能存在空行，读取时需正确处理，避免将空行误认为诗句。

## 解题思路

本解法按以下步骤处理每个测试实例：

**步骤 $\texttt{1}$.** 读取非空后缀行，将其按空格分割，存入字符串数组 `suffixes`，并记录数量 $s$。

**步骤 $\texttt{2}$.** 读取标题行，存入变量 `title`。

**步骤 $\texttt{3}$.** 循环读入后续非空行，直至遇到空行或文件结束，将这些行存入 `lines` 容器。若 `lines` 的大小不为 $14$，则直接判定失败。

**步骤 $\texttt{4}$.** 对每一行 `lines[i]`，调用函数 `getLastWord` 提取末尾有效单词。该函数从行尾反向扫描，跳过所有分隔符，然后截取连续的非分隔符子串。若提取结果为空，标记失败。

**步骤 $\texttt{5}$.** 将提取的单词与每个后缀 `suffixes[j]` 进行匹配，使用函数 `endsWithIgnorePlural`。该函数首先检查单词是否直接以该后缀结尾；若不是且单词末尾为 `s`，则去掉这个 `s` 后再检查一次。若匹配成功，记录索引 `j` 到序列 `seq[i]`，否则标记失败。

**步骤 $\texttt{6}$.** 若步骤 $\texttt{4}$ 或 $\texttt{5}$ 失败，输出 `Not a chance!` 并继续下一实例。

**步骤 $\texttt{7}$.** 验证 `seq` 的前 $8$ 个元素是否依次为 $0,1,1,0,0,1,1,0$。若不满足，输出失败信息。

**步骤 $\texttt{8}$.** 根据 $s$ 的值选择验证后 $6$ 个元素：
- 若 $s=4$，只检查是否等于 $2,3,2,3,2,3$。
- 若 $s=5$，依次尝试三种模式：$2,3,2,3,2,3$；$2,3,4,2,3,4$；$2,3,4,3,2,4$。匹配到第一种则结构为 `ABBAABBACDCDCD`，第二种为 `ABBAABBACDECDE`，第三种为 `ABBAABBACDEDCE`。若三种均不匹配，则失败。

**步骤 $\texttt{9}$.** 若步骤 $\texttt{8}$ 成功，输出 `<标题>: <结构>`，否则输出 `<标题>: Not a chance!`。

算法的时间复杂度为 $O(T \times 14 \times s \times L)$，其中 $T$ 为实例数，$L$ 为单词平均长度，$s \le 5$，故常数极小。空间复杂度为 $O(14)$ 用于存储行和序列，可视为常数。

## 代码实现

```cpp
// Sonnet Rhyme Verifier
// UVa ID: 11339
// Verdict: Accepted
// Submission Date: 2026-07-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 判断字符是否为分隔符（空格或常见标点）
bool isSeparator(char c) {
    return isspace((unsigned char)c) ||
           c == ',' || c == '.' || c == '!' || c == '?' ||
           c == ';' || c == ':' || c == '"' || c == '\'' ||
           c == '(' || c == ')' || c == '[' || c == ']' ||
           c == '{' || c == '}' || c == '`' || c == '-' ||
           c == '_' || c == '/' || c == '\\' || c == '|' ||
           c == '*' || c == '&' || c == '^' || c == '%' ||
           c == '$' || c == '#' || c == '@' || c == '~' ||
           c == '¡' || c == '¿' || c == '«' || c == '»' ||
           c == '—' || c == '…';
}

// 提取行末尾的单词（去除尾部标点和空格）
string getLastWord(const string& line) {
    int n = (int)line.size();
    int i = n - 1;
    while (i >= 0 && isSeparator(line[i])) --i;
    if (i < 0) return "";
    int end = i;
    while (i >= 0 && !isSeparator(line[i])) --i;
    return line.substr(i + 1, end - i);
}

// 判断 word 是否以 suffix 结尾（允许末尾's'被忽略）
bool endsWithIgnorePlural(const string& word, const string& suffix) {
    if (suffix.size() > word.size()) return false;
    if (word.compare(word.size() - suffix.size(), suffix.size(), suffix) == 0)
        return true;
    // 若单词以 's' 结尾，尝试去掉 's' 再比较
    if (!word.empty() && word.back() == 's') {
        string trimmed = word.substr(0, word.size() - 1);
        if (trimmed.size() >= suffix.size() &&
            trimmed.compare(trimmed.size() - suffix.size(), suffix.size(), suffix) == 0)
            return true;
    }
    return false;
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string suffixLine;
    while (getline(cin, suffixLine)) {
        // 解析后缀列表
        vector<string> suffixes;
        istringstream iss(suffixLine);
        string token;
        while (iss >> token) suffixes.push_back(token);
        int s = (int)suffixes.size();
        // 读取标题
        string title;
        getline(cin, title);
        // 读取诗
        vector<string> lines;
        string line;
        while (getline(cin, line)) {
            if (line.empty()) break;
            lines.push_back(line);
        }
        if ((int)lines.size() != 14) {
            cout << title << ": Not a chance!\n";
            continue;
        }
        // 提取每行末尾单词并匹配后缀
        vector<int> seq(14, -1);
        bool ok = true;
        for (int i = 0; i < 14 && ok; i++) {
            string word = getLastWord(lines[i]);
            if (word.empty()) { ok = false; break; }
            bool matched = false;
            for (int j = 0; j < s; j++) {
                if (endsWithIgnorePlural(word, suffixes[j])) {
                    seq[i] = j;
                    matched = true;
                    break;
                }
            }
            if (!matched) ok = false;
        }
        if (!ok) {
            cout << title << ": Not a chance!\n";
            continue;
        }
        // 检查前 8 个是否为 A B B A A B B A (0 1 1 0 0 1 1 0)
        vector<int> first8 = {0, 1, 1, 0, 0, 1, 1, 0};
        bool matchFirst = true;
        for (int i = 0; i < 8; i++) {
            if (seq[i] != first8[i]) { matchFirst = false; break; }
        }
        if (!matchFirst) {
            cout << title << ": Not a chance!\n";
            continue;
        }
        // 检查后 6 个模式
        vector<int> cdcdcd = {2, 3, 2, 3, 2, 3};
        vector<int> cdecde = {2, 3, 4, 2, 3, 4};
        vector<int> cdedce = {2, 3, 4, 3, 2, 4};
        bool matchPattern = false;
        string structure;
        if (s == 4) {
            bool good = true;
            for (int i = 0; i < 6; i++) {
                if (seq[8 + i] != cdcdcd[i]) { good = false; break; }
            }
            if (good) { matchPattern = true; structure = "ABBAABBACDCDCD"; }
        } else { // s == 5
            bool good1 = true;
            for (int i = 0; i < 6; i++)
                if (seq[8 + i] != cdcdcd[i]) { good1 = false; break; }
            if (good1) { matchPattern = true; structure = "ABBAABBACDCDCD"; }
            else {
                bool good2 = true;
                for (int i = 0; i < 6; i++)
                    if (seq[8 + i] != cdecde[i]) { good2 = false; break; }
                if (good2) { matchPattern = true; structure = "ABBAABBACDECDE"; }
                else {
                    bool good3 = true;
                    for (int i = 0; i < 6; i++)
                    if (seq[8 + i] != cdedce[i]) { good3 = false; break; }
                    if (good3) { matchPattern = true; structure = "ABBAABBACDEDCE"; }
                }
            }
        }
        if (matchPattern) cout << title << ": " << structure << "\n";
        else cout << title << ": Not a chance!\n";
    }
    return 0;
}
```

## 总结

本题主要考察文本处理、字符串匹配和模式识别。解题关键点包括：

- **精确的标点与空格过滤**，需覆盖完整的标点集合，确保正确提取末尾单词。
- **复数形式的兼容处理**，西班牙语复数 `s` 在押韵中可被忽略，这是样例和隐藏测试中的常见陷阱。
- **三种后六韵脚模式**的全面覆盖，尤其注意 `CDEDCE` 模式的存在，避免遗漏。
- **输入格式的健壮处理**，需妥善处理实例间的空行，避免读入错位。

通过本题，可以加深对字符串清理、多模式匹配和输入流控制的理解。该解法代码简洁，效率高，适合在竞赛环境中直接使用。
