// Snap
// UVa ID: 10388
// Verdict: Accepted
// Submission Date: 2021-12-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2021，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 0; cs < cases; cs++)
    {
        if (cs) cout << '\n';
        string JaneFaceDown, JohnFaceDown, JaneFaceUp, JohnFaceUp;
        cin >> JaneFaceDown >> JohnFaceDown;
        int turns = 0;
        while (true)
        {
            turns++;
            JaneFaceUp += JaneFaceDown.front();
            JohnFaceUp += JohnFaceDown.front();
            JaneFaceDown.erase(JaneFaceDown.begin());
            JohnFaceDown.erase(JohnFaceDown.begin());
            if (JaneFaceUp.back() == JohnFaceUp.back())
            {
                cout << "Snap! for ";
                if (rand() / 141 % 2 == 0)
                {
                    cout << "Jane: ";
                    JaneFaceUp += JohnFaceUp;
                    JohnFaceUp.clear();
                    for (int i = JaneFaceUp.length() - 1; i >= 0; i--)
                        cout << JaneFaceUp[i];
                    cout << '\n';
                }
                else
                {
                    cout << "John: ";
                    JohnFaceUp += JaneFaceUp;
                    JaneFaceUp.clear();
                    for (int i = JohnFaceUp.length() - 1; i >= 0; i--)
                        cout << JohnFaceUp[i];
                    cout << '\n';
                }
            }
            if (JaneFaceDown.length() == 0)
            {
                if (JaneFaceUp.length() == 0)
                {
                    cout << "John wins.\n";
                    break;
                }
                else swap(JaneFaceDown, JaneFaceUp);
            }
            if (JohnFaceDown.length() == 0)
            {
                if (JohnFaceUp.length() == 0)
                {
                    cout << "Jane wins.\n";
                    break;
                }
                else swap(JohnFaceDown, JohnFaceUp);
            }
            //cout << "Jane: " << JaneFaceDown << ' ' << JaneFaceUp << '\n';
            //cout << "John: " << JohnFaceDown << ' ' << JohnFaceUp << '\n';
            if (turns >= 1000)
            {
                cout << "Keeps going and going ...\n";
                break;
            }
        }
    }

    return 0;
}
