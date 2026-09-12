#include <bits/stdc++.h>
using namespace std;

struct Array {
    vector<int> shape, data;
};

map<string, Array> vars;

bool isNumber(const string &str) {
    if (str.empty()) return false;
    for (char ch : str)
        if (ch < '0' || ch > '9') return false;
    return true;
}

int toInt(const string &str) {
    int value = 0;
    for (char ch : str) value = value * 10 + ch - '0';
    return value;
}

int sizeOf(const Array &arr) {
    return (int)arr.data.size();
}

void stripParen(const vector<string> &tok, int &left, int &right) {
    while (left < right && tok[left] == "(" && tok[right] == ")") {
        int dep = 0;
        bool whole = true;
        for (int i = left; i <= right; ++i) {
            if (tok[i] == "(") ++dep;
            else if (tok[i] == ")") --dep;
            if (dep == 0 && i < right) {
                whole = false;
                break;
            }
        }
        if (!whole) break;
        ++left;
        --right;
    }
}

int findOp(const vector<string> &tok, int left, int right) {
    int dep = 0;
    for (int i = left; i <= right; ++i) {
        if (tok[i] == "(") ++dep;
        else if (tok[i] == ")") --dep;
        else if (dep == 0 && i > left && (tok[i] == "+" || tok[i] == "-" || tok[i] == "*" || tok[i] == "=" || tok[i] == "rho" || tok[i] == "drop")) return i;
    }
    return -1;
}

Array applyOp(const Array &left, const Array &right, char op) {
    Array result;
    if (sizeOf(right) == 1) {
        result.shape = left.shape;
    } else {
        result.shape = right.shape;
    }
    result.data.resize(max(sizeOf(left), sizeOf(right)));
    for (int i = 0; i < (int)result.data.size(); ++i) {
        int x = sizeOf(left) == 1 ? left.data[0] : left.data[i];
        int y = sizeOf(right) == 1 ? right.data[0] : right.data[i];
        if (op == '+') result.data[i] = x + y;
        if (op == '-') result.data[i] = x - y;
        if (op == '*') result.data[i] = x * y;
    }
    return result;
}

Array makeIota(const Array &arg) {
    Array result;
    int n = arg.data[0];
    result.shape = {n};
    result.data.resize(n);
    for (int i = 0; i < n; ++i) result.data[i] = i + 1;
    return result;
}

Array makeRho(const Array &shape, const Array &src) {
    Array result;
    result.shape = shape.data;
    int total = 1;
    for (int value : result.shape) total *= value;
    result.data.resize(total);
    for (int i = 0; i < total; ++i) result.data[i] = src.data[i % sizeOf(src)];
    return result;
}

Array makeDrop(const Array &count, const Array &src) {
    Array result;
    int skip = count.data[0];
    result.shape = {sizeOf(src) - skip};
    result.data.assign(src.data.begin() + skip, src.data.end());
    return result;
}

Array reduceOp(const Array &src, char op) {
    Array result;
    int last = src.shape.back();
    result.shape = src.shape;
    result.shape.pop_back();
    if (result.shape.empty()) result.shape = {1};
    int groups = sizeOf(src) / last;
    result.data.resize(groups);
    for (int i = 0; i < groups; ++i) {
        int base = i * last;
        int value = src.data[base + last - 1];
        for (int j = last - 2; j >= 0; --j) {
            if (op == '+') value = src.data[base + j] + value;
            if (op == '-') value = src.data[base + j] - value;
            if (op == '*') value = src.data[base + j] * value;
        }
        result.data[i] = value;
    }
    return result;
}

Array evalExpr(const vector<string> &tok, int left, int right) {
    stripParen(tok, left, right);
    Array result;
    bool allNum = true;
    for (int i = left; i <= right; ++i)
        if (!isNumber(tok[i])) allNum = false;
    if (allNum) {
        result.shape = {right - left + 1};
        for (int i = left; i <= right; ++i) result.data.push_back(toInt(tok[i]));
        return result;
    }
    if (tok[left] == "iota") return makeIota(evalExpr(tok, left + 1, right));
    if (left + 1 <= right && tok[left + 1] == "/") return reduceOp(evalExpr(tok, left + 2, right), tok[left][0]);
    if (left == right) return vars[tok[left]];
    int pos = findOp(tok, left, right);
    string oper = tok[pos];
    Array rightVal = evalExpr(tok, pos + 1, right), leftVal;
    if (oper == "=") {
        leftVal = evalExpr(tok, left, pos - 1);
        vars[tok[left]] = rightVal;
        return rightVal;
    }
    leftVal = evalExpr(tok, left, pos - 1);
    if (oper == "+") return applyOp(leftVal, rightVal, '+');
    if (oper == "-") return applyOp(leftVal, rightVal, '-');
    if (oper == "*") return applyOp(leftVal, rightVal, '*');
    if (oper == "rho") return makeRho(leftVal, rightVal);
    return makeDrop(leftVal, rightVal);
}

void printArray(const Array &arr) {
    int dim = arr.shape.size();
    if (dim == 1) {
        for (int i = 0; i < arr.shape[0]; ++i) {
            if (i) cout << ' ';
            cout << arr.data[i];
        }
        cout << '\n';
        return;
    }
    int rows = arr.shape[dim - 2], cols = arr.shape[dim - 1];
    int blocks = arr.data.size() / (rows * cols);
    for (int b = 0; b < blocks; ++b) {
        if (b && dim == 3) cout << '\n';
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (j) cout << ' ';
                cout << arr.data[b * rows * cols + i * cols + j];
            }
            cout << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    int caseNo = 0;
    while (getline(cin, line) && line != "#") {
        stringstream ss(line);
        vector<string> tok;
        string word;
        while (ss >> word) tok.push_back(word);
        cout << "Case " << ++caseNo << ": " << line << '\n';
        printArray(evalExpr(tok, 0, tok.size() - 1));
    }
    return 0;
}
