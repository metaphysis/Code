#include <bits/stdc++.h>
using namespace std;

int getWin(const array<int, 6>& a, const array<int, 6>& b) {
    int res = 0;
    for (int x : a)
        for (int y : b)
            if (x > y) res++;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int gameCnt;
    cin >> gameCnt;
    while (gameCnt--) {
        char firstName, secondName;
        array<array<int, 6>, 3> dice;
        int win[3][3], bestScore = -INT_MAX;
        cin >> firstName;
        secondName = firstName == 'A' ? 'B' : 'A';
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 6; j++)
                cin >> dice[i][j];
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                win[i][j] = getWin(dice[i], dice[j]);
        for (int i = 0; i < 3; i++) {
            int worstScore = INT_MAX;
            for (int j = 0; j < 3; j++)
                if (i != j) worstScore = min(worstScore, win[i][j] - win[j][i]);
            bestScore = max(bestScore, worstScore);
        }
        if (bestScore == 0) cout << "fair\n";
        else if (bestScore > 0) cout << firstName << '\n';
        else cout << secondName << '\n';
    }
    return 0;
}
