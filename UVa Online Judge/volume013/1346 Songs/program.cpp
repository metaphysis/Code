// Songs
// UVa ID: 1346
// Verdict: Accepted
// Submission Date: 2025-11-19
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Song {
    int id;
    int length;
    double frequency;
};

bool compare(const Song& a, const Song& b) {
    return (a.frequency / a.length) > (b.frequency / b.length);
}

int main() {
    int n;
    while (cin >> n) {
        vector<Song> songs(n);
        for (int i = 0; i < n; i++)
            cin >> songs[i].id >> songs[i].length >> songs[i].frequency;
        int target;
        cin >> target;
        sort(songs.begin(), songs.end(), compare);
        cout << songs[target - 1].id << endl;
    }
    return 0;
}
