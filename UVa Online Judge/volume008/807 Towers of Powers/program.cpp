// Towers of Powers
// UVa ID: 807
// Verdict: Accepted
// Submission Date: 2026-07-19
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

struct Grid {
    int rows, cols;
    vector<string> data;
};

// 前向声明
vector<Grid> buildItems(ull n, ull b);

// 构造幂的网格：底数在最下行，指数网格放在底数之后
Grid makePower(ull coef, ull base, const Grid& expGrid) {
    string baseStr = to_string(base);
    string coefStr = (coef == 1 ? "" : to_string(coef) + "*");
    string bottom = coefStr + baseStr;
    int offset = (int)coefStr.size() + (int)baseStr.size();
    int expRows = expGrid.rows, expCols = expGrid.cols;
    int totalRows = expRows + 1;
    int totalCols = max((int)bottom.size(), offset + expCols);
    Grid g{totalRows, totalCols, vector<string>(totalRows, string(totalCols, ' '))};
    for (int r = 0; r < expRows; ++r)
        for (int c = 0; c < expCols; ++c)
            g.data[r][offset + c] = expGrid.data[r][c];
    for (int c = 0; c < (int)bottom.size(); ++c)
        g.data[expRows][c] = bottom[c];
    return g;
}

// 合并前缀和若干项（项间用'+'连接，'+'放在最底行）
Grid concatWithPrefix(const Grid& prefix, const vector<Grid>& items) {
    if (items.empty()) return prefix;
    int totalRows = max(prefix.rows, 1);
    int totalCols = prefix.cols;
    for (size_t i = 0; i < items.size(); ++i) {
        totalCols += items[i].cols;
        if (i > 0) ++totalCols;
        totalRows = max(totalRows, items[i].rows);
    }
    Grid res{totalRows, totalCols, vector<string>(totalRows, string(totalCols, ' '))};
    int prefixRow = totalRows - prefix.rows;
    for (int r = 0; r < prefix.rows; ++r)
        for (int c = 0; c < prefix.cols; ++c)
            res.data[prefixRow + r][c] = prefix.data[r][c];
    int curCol = prefix.cols;
    for (size_t i = 0; i < items.size(); ++i) {
        if (i > 0) {
            res.data[totalRows - 1][curCol] = '+';
            ++curCol;
        }
        const Grid& item = items[i];
        int itemRow = totalRows - item.rows;
        for (int r = 0; r < item.rows; ++r)
            for (int c = 0; c < item.cols; ++c)
                res.data[itemRow + r][curCol + c] = item.data[r][c];
        curCol += item.cols;
    }
    return res;
}

// 递归构建n在b下的完整展开，返回各项的网格列表
vector<Grid> buildItems(ull n, ull b) {
    vector<pair<ull, ull>> terms;
    ull tmp = n, e = 0;
    while (tmp > 0) {
        ull r = tmp % b;
        tmp /= b;
        if (r != 0) terms.push_back({r, e});
        ++e;
    }
    reverse(terms.begin(), terms.end());
    vector<Grid> items;
    for (auto& p : terms) {
        ull coef = p.first, exp = p.second;
        if (exp == 0) {
            items.push_back(Grid{1, (int)to_string(coef).size(), {to_string(coef)}});
        } else if (exp == 1) {
            string s = (coef == 1 ? "" : to_string(coef) + "*") + to_string(b);
            items.push_back(Grid{1, (int)s.size(), {s}});
        } else {
            vector<Grid> expItems = buildItems(exp, b);
            Grid emptyPrefix{1, 0, {""}};
            Grid expGrid = concatWithPrefix(emptyPrefix, expItems);
            items.push_back(makePower(coef, b, expGrid));
        }
    }
    return items;
}

// 输出网格，去掉行末空格
void printGrid(const Grid& g) {
    for (int r = 0; r < g.rows; ++r) {
        string s = g.data[r];
        while (!s.empty() && s.back() == ' ') s.pop_back();
        cout << s << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ull n, b;
    bool firstCase = true;
    while (cin >> n >> b && (n != 0 || b != 0)) {
        if (!firstCase) cout << string(80, '-') << '\n';
        firstCase = false;
        cout << n << " in complete base " << b << ":\n\n";
        vector<Grid> items = buildItems(n, b);
        string prefixStr = to_string(n) + " = ";
        Grid prefix{1, (int)prefixStr.size(), {prefixStr}};
        int prefWidth = prefix.cols;

        vector<Grid> lines;
        int idx = 0;
        bool firstLine = true;
        while (idx < (int)items.size()) {
            int usedPrefix = firstLine ? prefWidth : (prefWidth + 1);
            int curCol = usedPrefix;
            int k = idx;
            while (k < (int)items.size()) {
                int add = (k == idx ? 0 : 1);
                if (curCol + add + items[k].cols <= 80) {
                    curCol += add + items[k].cols;
                    ++k;
                } else break;
            }
            if (k == idx) k = idx + 1;
            vector<Grid> curItems(items.begin() + idx, items.begin() + k);
            Grid line;
            if (firstLine) {
                line = concatWithPrefix(prefix, curItems);
            } else {
                Grid plusPrefix{1, 1, {"+"}};
                Grid raw = concatWithPrefix(plusPrefix, curItems);
                // 整体右移 prefWidth 列
                line = raw;
                if (prefWidth > 0) {
                    line.cols += prefWidth;
                    for (auto& row : line.data) row = string(prefWidth, ' ') + row;
                }
            }
            lines.push_back(line);
            idx = k;
            firstLine = false;
        }

        // 统一所有行的高度（顶部对齐）
        int maxRows = 0;
        for (auto& g : lines) maxRows = max(maxRows, g.rows);
        for (auto& g : lines) {
            if (g.rows < maxRows) {
                int addRows = maxRows - g.rows;
                vector<string> newData(addRows, string(g.cols, ' '));
                newData.insert(newData.end(), g.data.begin(), g.data.end());
                g.data = newData;
                g.rows = maxRows;
            }
        }

        // 输出各行，行间空行
        for (size_t i = 0; i < lines.size(); ++i) {
            if (i > 0) cout << '\n';
            printGrid(lines[i]);
        }
    }
    return 0;
}
