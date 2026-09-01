#include <bits/stdc++.h>
using namespace std;

struct Prediction {
    string word, key;
    int id;
};

string getKey(const string &word, int limit) {
    int m = word.size();
    vector<int> pi(m, 0);
    string key(limit, '0');
    for (int i = 1; i < m; i++) {
        int j = pi[i - 1];
        while (j > 0 && word[i] != word[j])
            j = pi[j - 1];
        if (word[i] == word[j])
            j++;
        pi[i] = j;
    }
    int border = pi[m - 1];
    while (border > 0) {
        int distance = m - border;
        if (distance <= limit)
            key[distance - 1] = '1';
        border = pi[border - 1];
    }
    return key;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, s;
    while (cin >> n >> s) {
        vector<Prediction> predictions(s);
        int m = 0;
        for (int i = 0; i < s; i++) {
            cin >> predictions[i].word;
            predictions[i].id = i;
            m = predictions[i].word.size();
        }
        int limit = min(m - 1, n - m);
        for (int i = 0; i < s; i++)
            predictions[i].key = getKey(predictions[i].word, limit);
        sort(predictions.begin(), predictions.end(), [](const Prediction &a, const Prediction &b) {
            if (a.key != b.key)
                return a.key < b.key;
            return a.id < b.id;
        });
        for (int i = 0; i < s; i++)
            cout << predictions[i].word << '\n';
    }
    return 0;
}
