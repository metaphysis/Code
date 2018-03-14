// Barbarian Tribes
// UVa ID: 10771
// Verdict: Accepted
// Submission Date: 2017-12-23
// UVa Run Time: 0.530s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, m, k;
    while (cin >> n >> m >> k)
    {
        if (n == 0 && m == 0 && k == 0) break;

        vector<char> circle;
        for (int i = 1; i <= n; i++) circle.push_back('G');
        for (int i = 1; i <= m; i++) circle.push_back('K');
        
        if (circle.size() > 1)
        {
            int step = 1, c = 0;
            char head1 = 0, head2 = 0;
            while (true)
            {
                c = (c + k - 1) % circle.size();
                if (step == 1)
                {
                    head1 = head2, head2 = circle[c];
                    c = circle.erase(circle.begin() + c) - circle.begin();
                    c %= circle.size();
                }
                else
                {
                    head1 = head2, head2 = circle[c];
                    if (head1 == head2) circle[c] = 'G';
                    else circle[c] = 'K';
                    c = (c + 1) % circle.size();
                    
                    if (circle.size() == 1) break;
                }
                step = 3 - step;
            }
        }

        if (circle.front() == 'G') cout << "Gared\n";
        else cout << "Keka\n";
    }

    return 0;
}
