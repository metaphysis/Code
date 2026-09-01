#include <bits/stdc++.h>
using namespace std;

bool isAlignChar(char ch) {
    return ch == '<' || ch == '=' || ch == '>';
}

bool parseHeader(const string &line, string &header, vector<string> &title) {
    if (line.empty() || !isAlignChar(line[0])) return false;
    int pos = 0;
    while (pos < static_cast<int>(line.size()) && isAlignChar(line[pos])) pos++;
    header = line.substr(0, pos);
    title.clear();
    if (pos < static_cast<int>(line.size())) title.push_back(line.substr(pos));
    return true;
}

vector<string> splitRow(const string &line) {
    vector<string> row;
    int start = 0;
    for (int i = 0; i <= static_cast<int>(line.size()); i++) {
        if (i == static_cast<int>(line.size()) || line[i] == '&') {
            row.push_back(line.substr(start, i - start));
            start = i + 1;
        }
    }
    return row;
}

string formatCell(const string &text, int width, char align) {
    int space = width - static_cast<int>(text.size());
    int left = 0, right = 0;
    if (align == '<') right = space;
    else if (align == '>') left = space;
    else {
        left = space / 2;
        right = space - left;
    }
    return string(left, ' ') + text + string(right, ' ');
}

void printBorder(const vector<int> &width, char left, char right, char middle) {
    cout << left;
    for (int i = 0; i < static_cast<int>(width.size()); i++) {
        if (i > 0) cout << middle;
        cout << string(width[i] + 2, '-');
    }
    cout << right << '\n';
}

void printRow(const vector<string> &row, const string &header, const vector<int> &width) {
    cout << '|';
    for (int i = 0; i < static_cast<int>(row.size()); i++)
        cout << ' ' << formatCell(row[i], width[i], header[i]) << " |";
    cout << '\n';
}

int solve() {
    vector<string> lines;
    string line;
    while (getline(cin, line)) {
        if (!line.empty() && line[0] == '*') break;
        lines.push_back(line);
    }
    int index = 0;
    while (index < static_cast<int>(lines.size())) {
        string header;
        vector<string> title;
        if (!parseHeader(lines[index++], header, title)) continue;
        vector<vector<string>> table;
        if (title.empty()) title = splitRow(lines[index++]);
        table.push_back(title);
        while (index < static_cast<int>(lines.size())) {
            string nextHeader;
            vector<string> nextTitle;
            if (parseHeader(lines[index], nextHeader, nextTitle)) break;
            table.push_back(splitRow(lines[index++]));
        }
        vector<int> width(header.size(), 0);
        for (const vector<string> &row : table)
            for (int i = 0; i < static_cast<int>(row.size()); i++)
                width[i] = max(width[i], static_cast<int>(row[i].size()));
        printBorder(width, '@', '@', '-');
        printRow(table[0], header, width);
        printBorder(width, '|', '|', '+');
        for (int i = 1; i < static_cast<int>(table.size()); i++)
            printRow(table[i], header, width);
        printBorder(width, '@', '@', '-');
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solve();
}
