#include <bits/stdc++.h>
using namespace std;

struct Obj {
    double weight, result;
};

string text;
int pos;
bool valid;

void skipSpace() {
    while (pos < (int)text.size() && text[pos] == ' ')
        pos++;
}

double readNum() {
    int start;
    skipSpace();
    start = pos;
    while (pos < (int)text.size() && (isdigit(text[pos]) || text[pos] == '.'))
        pos++;
    return stod(text.substr(start, pos - start));
}

Obj parseObj() {
    Obj cur;
    double second, sum, res;
    int rule;
    vector<Obj> child;
    skipSpace();
    pos++;
    cur.weight = readNum();
    pos++;
    second = readNum();
    skipSpace();
    if (text[pos] == ')') {
        pos++;
        cur.result = second;
        return cur;
    }
    rule = (int)second;
    pos++;
    skipSpace();
    pos++;
    while (true) {
        child.push_back(parseObj());
        skipSpace();
        if (text[pos] == ',')
            pos++;
        else
            break;
    }
    pos++;
    skipSpace();
    pos++;
    sum = 0.0;
    for (int i = 0; i < (int)child.size(); i++)
        sum += child[i].weight;
    if (fabs(sum - 100.0) > 0.01 + 1e-9)
        valid = false;
    if (rule == 1) {
        res = 0.0;
        for (int i = 0; i < (int)child.size(); i++)
            res += child[i].weight * child[i].result / 100.0;
    } else {
        res = 100.0;
        for (int i = 0; i < (int)child.size(); i++)
            res = min(res, child[i].result);
    }
    cur.result = res;
    return cur;
}

int solve() {
    int testCount, rootRule;
    double sum, ans;
    vector<Obj> child;
    cin >> testCount;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (testCount--) {
        getline(cin, text);
        pos = 0;
        valid = true;
        child.clear();
        rootRule = (int)readNum();
        while (true) {
            skipSpace();
            if (pos >= (int)text.size())
                break;
            child.push_back(parseObj());
        }
        sum = 0.0;
        for (int i = 0; i < (int)child.size(); i++)
            sum += child[i].weight;
        if (fabs(sum - 100.0) > 0.01 + 1e-9)
            valid = false;
        if (!valid) {
            cout << "Unbalanced\n";
            continue;
        }
        if (rootRule == 1) {
            ans = 0.0;
            for (int i = 0; i < (int)child.size(); i++)
                ans += child[i].weight * child[i].result / 100.0;
        } else {
            ans = 100.0;
            for (int i = 0; i < (int)child.size(); i++)
                ans = min(ans, child[i].result);
        }
        cout << fixed << setprecision(2) << ans + 1e-9 << '\n';
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return solve();
}
