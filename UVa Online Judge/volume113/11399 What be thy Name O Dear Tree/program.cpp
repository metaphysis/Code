#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while (getline(cin, s)) {
        map<pair<int, int>, char> pic;
        vector<pair<int, int>> st;
        int x = 0, y = 0, minX = INT_MAX, maxX = INT_MIN, minY = INT_MAX, maxY = INT_MIN;
        auto draw = [&](int px, int py, char ch) {
            pic[{px, py}] = ch;
            minX = min(minX, px);
            maxX = max(maxX, px);
            minY = min(minY, py);
            maxY = max(maxY, py);
        };
        for (char c : s) {
            if (c == '[') st.push_back({x, y});
            else if (c == ']') {
                x = st.back().first;
                y = st.back().second;
                st.pop_back();
            } else if (c == 'U') {
                draw(x, y, '|');
                ++y;
            } else if (c == 'L') {
                draw(x - 1, y, '_');
                x -= 2;
            } else if (c == 'R') {
                draw(x + 1, y, '_');
                x += 2;
            } else if (c == 'l') {
                draw(x - 1, y, '\\');
                x -= 2;
                ++y;
            } else if (c == 'r') {
                draw(x + 1, y, '/');
                x += 2;
                ++y;
            } else if (c == 'f') draw(x, y, '*');
            else if (c == 'p') draw(x, y, 'o');
            else if (c == 'P') draw(x, y, 'O');
        }
        cout << '.' << string(maxX - minX + 1, '-') << ".\n";
        for (int i = maxY; i >= minY; --i) {
            cout << '|';
            for (int j = minX; j <= maxX; ++j) {
                auto it = pic.find({j, i});
                cout << (it == pic.end() ? ' ' : it->second);
            }
            cout << "|\n";
        }
        cout << '.' << string(maxX - minX + 1, '-') << ".\n";
    }
    return 0;
}
