// A Special “Happy Birthday” Song!!!
// UVa ID: 12554
// Verdict: Accepted
// Submission Date: 2017-12-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string song[] = {"Happy", "birthday", "to", "you", "Happy", "birthday", "to", "you", "Happy", "birthday", "to", "Rujia", "Happy", "birthday", "to", "you"};
    int n;
    cin >> n;
    string name[110];
    for (int i = 0; i < n; i++) cin >> name[i];
    
    int k = 16;
    while (k < n) k += 16;
    for (int i = 0; i < k; i++)
    {
        cout << name[i % n] << ": " << song[i % 16] << '\n';
    }
    
    return 0;
}
