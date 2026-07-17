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
