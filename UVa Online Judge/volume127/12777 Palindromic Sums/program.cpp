#include <bits/stdc++.h>
using namespace std;

bool isPal(int num) {
    int val = num, rev = 0;
    while (val > 0) {
        rev = rev * 10 + val % 10;
        val /= 10;
    }
    return rev == num;
}

vector<int> buildCards(bool isAlice) {
    vector<int> cards;
    int minA = isAlice ? 0 : 1, maxA = isAlice ? 4 : 5;
    int maxBc = isAlice ? 4 : 5, maxDe = isAlice ? 5 : 4;
    int offset = isAlice ? 1 : -1;
    for (int a = minA; a <= maxA; ++a) {
        for (int b = 0; b <= maxBc; ++b) {
            for (int c = 0; c <= maxBc; ++c) {
                for (int d = 0; d <= maxDe; ++d) {
                    for (int e = 0; e <= maxDe; ++e) {
                        int num = a * 100000001 + b * 10000010 + c * 1000100 + d * 101000 + e * 10000 + offset;
                        if (isPal(num)) continue;
                        cards.push_back(num);
                        if (cards.size() == 4400) return cards;
                    }
                }
            }
        }
    }
    return cards;
}

void printCards(const vector<int>& cards) {
    for (int i = 0; i < (int)cards.size(); ++i) {
        if (i > 0) cout << ' ';
        cout << cards[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<int> alice = buildCards(true), bob = buildCards(false);
    printCards(alice);
    printCards(bob);
    return 0;
}
