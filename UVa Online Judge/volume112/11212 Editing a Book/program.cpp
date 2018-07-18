// Editing a Book
// UVa ID: 11212
// Verdict: Accepted
// Submission Date: 2018-07-18
// UVa Run Time: 0.540s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct package
{
    int number, move;
    package (int number = 0, int move = 0): number(number), move(move) {}
} pack;

unordered_map<int, int> cache[10];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int lot[10], multiple[10] = {0, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
    for (int book = 2; book <= 9; book++)
    {
        int d = 0;
        for (int i = 1; i <= book; i++) d = d * 10 + i;

        queue<package> q;
        q.push(package(d, 0));
        cache[book][d] = 0;
        while (!q.empty())
        {
            pack = q.front(); q.pop();
            if (pack.move >= book / 2) continue;

            int idx = book;
            while (pack.number)
            {
                lot[--idx] = pack.number % 10;
                pack.number /= 10;
            }

            for (int i = 0; i < book; i++)
            {
                for (int j = 1; j <= book - i; j++)
                {
                    int cutted = 0;
                    for (int k = 0; k < j; k++)
                        cutted = cutted * 10 + lot[i + k];
                    for (int k = i + j + 1; k <= book; k++)
                    {
                        int combined = 0;
                        for (int x = 0; x < book; x++)
                        {
                            if (x < i) combined = combined * 10 + lot[x];
                            else if (x < i + j) continue;
                            else if (x < k) combined = combined * 10 + lot[x];
                            else
                            {
                                if (x == k) combined = combined * multiple[j] + cutted;
                                combined = combined * 10 + lot[x];
                            }
                        }
                        if (k == book) combined = combined * multiple[j] + cutted;
                        if (cache[book].find(combined) == cache[book].end())
                        {
                            cache[book][combined] = pack.move + 1;
                            q.push(package(combined, pack.move + 1));
                        }
                    }
                }
            }
        }
    }

    int n, cases = 0;
    while (cin >> n, n)
    {
        cout << "Case " << ++cases << ": ";

        int digit, d = 0;
        for (int i = 1; i <= n; i++)
        {
            cin >> digit;
            d = d * 10 + digit;
        }

        queue<package> q;
        q.push(package(d, 0));
        unordered_set<int> closed;

        while (!q.empty())
        {
            pack = q.front(); q.pop();

            if (cache[n].find(pack.number) != cache[n].end())
            {
                cout << pack.move + cache[n][pack.number] << '\n';
                break;
            }

            int idx = n;
            while (pack.number)
            {
                lot[--idx] = pack.number % 10;
                pack.number /= 10;
            }

            for (int i = 0; i < n; i++)
            {
                for (int j = 1; j <= n - i; j++)
                {
                    int cutted = 0;
                    for (int k = 0; k < j; k++)
                        cutted = cutted * 10 + lot[i + k];
                    for (int k = i + j + 1; k <= n; k++)
                    {
                        int combined = 0;
                        for (int x = 0; x < n; x++)
                        {
                            if (x < i) combined = combined * 10 + lot[x];
                            else if (x < i + j) continue;
                            else if (x < k) combined = combined * 10 + lot[x];
                            else
                            {
                                if (x == k) combined = combined * multiple[j] + cutted;
                                combined = combined * 10 + lot[x];
                            }
                        }
                        if (k == n) combined = combined * multiple[j] + cutted;
                        if (closed.find(combined) == closed.end())
                        {
                            closed.insert(combined);
                            q.push(package(combined, pack.move + 1));
                        }
                    }
                }
            }
        }
    }

    return 0;
}
