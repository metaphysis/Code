#include <bits/stdc++.h>
using namespace std;

struct Box {
    int lvc, wid, hei;
    vector<string> grid;

    Box() : lvc(0), wid(0), hei(0) {}

    void initGrid(int w, int h) {
        wid = w;
        hei = h;
        grid.assign(hei, string(wid, ' '));
    }

    void setAtom(const string &value) {
        wid = (int)value.size();
        hei = 1;
        lvc = 0;
        grid.assign(1, value);
    }

    void addParen() {
        for (int i = 0; i < hei; ++i) grid[i] = "(" + grid[i] + ")";
        wid += 2;
    }

    void addNeg() {
        for (int i = 0; i < hei; ++i) grid[i] = string(i == lvc ? "-" : " ") + grid[i];
        ++wid;
    }
};

void copyBox(Box &dst, const Box &src, int row, int col) {
    for (int i = 0; i < src.hei; ++i)
        for (int j = 0; j < src.wid; ++j)
            dst.grid[row + i][col + j] = src.grid[i][j];
}

Box makeNormalBox(const Box &left, const Box &right, char op) {
    Box result;
    int center = max(left.lvc, right.lvc);
    int leftRow = center - left.lvc;
    int rightRow = center - right.lvc;
    int height = max(
        leftRow + left.hei,
        rightRow + right.hei
    );
    result.initGrid(left.wid + 3 + right.wid, height);
    result.lvc = center;
    copyBox(result, left, leftRow, 0);
    copyBox(result, right, rightRow, left.wid + 3);
    result.grid[result.lvc][left.wid + 1] = op;
    return result;
}

Box makeDivisionBox(const Box &numerator, const Box &denominator) {
    Box result;
    int width = max(numerator.wid, denominator.wid);
    int numeratorCol = (width - numerator.wid + 1) / 2;
    int denominatorCol = (width - denominator.wid + 1) / 2;
    result.initGrid(
        width,
        numerator.hei + 1 + denominator.hei
    );
    result.lvc = numerator.hei;
    copyBox(result, numerator, 0, numeratorCol);
    for (int i = 0; i < width; ++i) {
        result.grid[result.lvc][i] = '-';
    }
    copyBox(result, denominator, numerator.hei + 1, denominatorCol);
    return result;
}

Box makePowerBox(const Box &base, const Box &exponent) {
    Box result;
    result.initGrid(
        base.wid + exponent.wid,
        base.hei + exponent.hei
    );
    result.lvc = base.lvc + exponent.hei;
    copyBox(result, exponent, 0, base.wid);
    copyBox(result, base, exponent.hei, 0);
    return result;
}

class Parser {
private:
    string text;
    int pos;

    void skipSpaces() {
        while (pos < (int)text.size() &&
               text[pos] == ' ') {
            ++pos;
        }
    }

    char current() {
        skipSpaces();
        if (pos >= (int)text.size()) {
            return '\0';
        }
        return text[pos];
    }

    bool accept(char ch) {
        if (current() == ch) {
            ++pos;
            return true;
        }
        return false;
    }

    Box parsePrimary() {
        skipSpaces();
        char ch = current();
        if (ch == '(') {
            ++pos;
            Box result = parseEquality();
            accept(')');
            result.addParen();
            return result;
        }
        if (ch == '{') {
            ++pos;
            Box result = parseEquality();
            accept('}');
            return result;
        }
        string value;
        if (isdigit((unsigned char)ch) || ch == '.') {
            while (true) {
                char now = current();
                if (!isdigit((unsigned char)now) && now != '.') {
                    break;
                }
                value += now;
                ++pos;
            }
        } else if (ch != '\0') {
            value += ch;
            ++pos;
        }
        Box result;
        result.setAtom(value);
        return result;
    }

    Box parseUnary() {
        if (accept('-')) {
            Box result = parseUnary();
            result.addNeg();
            return result;
        }
        return parsePrimary();
    }

    Box parsePower() {
        Box base = parseUnary();
        if (accept('^')) {
            Box exponent = parsePower();
            return makePowerBox(base, exponent);
        }
        return base;
    }

    Box parseMultiplication() {
        Box result = parsePower();
        while (true) {
            if (accept('*')) {
                Box right = parsePower();
                result = makeNormalBox(result, right, '*');
            } else if (accept('/')) {
                Box right = parsePower();
                result = makeDivisionBox(result, right);
            } else break;
        }
        return result;
    }

    Box parseAddition() {
        Box result = parseMultiplication();
        while (true) {
            if (accept('+')) {
                Box right = parseMultiplication();
                result = makeNormalBox(result, right, '+');
            } else if (accept('-')) {
                Box right = parseMultiplication();
                result = makeNormalBox(result, right, '-');
            } else break;
        }
        return result;
    }

    Box parseEquality() {
        Box result = parseAddition();
        while (accept('=')) {
            Box right = parseAddition();
            result = makeNormalBox(result, right, '=');
        }
        return result;
    }

public:
    Box parse(const string &input) {
        text = input;
        pos = 0;
        return parseEquality();
    }
};

bool isBlank(const string &str) {
    for (char ch : str)
        if (ch != ' ')
            return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Parser parser;
    string line;
    bool firstOutput = true;
    while (getline(cin, line)) {
        Box result = parser.parse(line);
        if (!firstOutput) cout << '\n';
        firstOutput = false;
        for (const string &row : result.grid) cout << row << '\n';
    }
    return 0;
}
