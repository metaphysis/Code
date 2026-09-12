#include <bits/stdc++.h>  
using namespace std;  
  
struct Node {  
    long long w;  
    long long up;  
    long long down;  
  
    long long h() const {  
        return up + down + 1;  
    }  
};  
  
string s;  
int pos;  
  
void skipWs() {  
    while (pos < (int)s.size() && (s[pos] == ' ' || s[pos] == '\t')) {  
        ++pos;  
    }  
}  
  
Node parse() {  
    skipWs();  
  
    if (s[pos] == '"') {  
        ++pos;  
        int len = 0;  
        while (s[pos] != '"') {  
            ++len;  
            ++pos;  
        }  
        ++pos;  
        return {(long long)len + 8, 1, 1};  
    }  
  
    if (s[pos] == '(') {  
        ++pos;  
        Node a = parse();  
        Node b = parse();  
        skipWs();  
        ++pos; // ')'  
        return {a.w + b.w, max(a.up, b.up), max(a.down, b.down)};  
    }  
  
    if (s[pos] == '{') {  
        ++pos;  
        Node a = parse();  
        Node b = parse();  
        skipWs();  
        ++pos; // '}'  
        return {max(a.w, b.w) + 4, a.up, a.down + 1 + b.h()};  
    }  
  
    // '[' expression ']'  
    ++pos;  
    Node a = parse();  
    skipWs();  
    ++pos; // ']'  
    return {a.w + 4, a.up + 1, a.down};  
}  
  
int main() {  
    ios::sync_with_stdio(false);  
    cin.tie(nullptr);  
  
    int t;  
    cin >> t;  
    getline(cin, s);  
  
    while (t--) {  
        getline(cin, s);  
        pos = 0;  
        Node root = parse();  
        cout << root.w + 4 << 'x' << root.h() << '\n';  
    }  
  
    return 0;  
}
