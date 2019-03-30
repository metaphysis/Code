// Towers of Hanoi
// UVa ID: 254
// Verdict: Accepted
// Submission Date: 2016-05-13
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<int> moves;

void parseMovesToBinary(string m)
{
    moves.clear();
    
    vector<int> digits;
    for (int i = 0; i < m.length(); i++)
        digits.push_back(m[i] - '0');
        
    while (digits.size())
    {
        int remain = 0;
        for (int i = 0; i < digits.size(); i++)
        {
            digits[i] = remain * 10 + digits[i];
            remain = digits[i] % 2;
            digits[i] /= 2;
        }
        moves.insert(moves.begin(), remain);
        
        while (digits.size() && digits.front() == 0)
            digits.erase(digits.begin());
    }
}

int findMaxK()
{
    int k = moves.size();

    if (moves.size() == 0)
        return k;

    bool allOne = true;
    for (int i = 0; i < moves.size(); i++)
        if (moves[i] == 0)
        {
            allOne = false;
            break;
        }

    if (allOne)
    {
        moves.erase(moves.begin(), moves.end());
        return k;
    }

    int borrow = 0; 
    for (int i = moves.size() - 1; i >= 1; i--)
    {
        moves[i] -= (borrow + 1);
        if (moves[i] < 0)
        {
            moves[i] += 2;
            borrow = 1;
        }
        else
            borrow = 0;
    }
    moves[0] -= borrow;

    while (moves.size() && moves.front() == 0)
        moves.erase(moves.begin());

    return (k - 1);
}

void subtract()
{
    vector<int> one(moves.size());

    for (int i = 0; i < one.size(); i++)
        one[i] = 0; 
    one.back() = 1;

    int borrow = 0; 
    for (int i = moves.size() - 1; i >= 0; i--)
    {
        moves[i] -= (borrow + one[i]);
        if (moves[i] < 0)
        {
            moves[i] += 2;
            borrow = 1;
        }
        else
            borrow = 0;
    }

    while (moves.size() && moves.front() == 0)
        moves.erase(moves.begin());
}

vector<vector<int>> disks(3);

int main(int argc, char *argv[])
{
    int n;
    string m;

    while (cin >> n >> m, n > 0)
    {
        parseMovesToBinary(m);

        disks.clear();
        disks.resize(3);

        for (int i = 1; i <= n; i++)
            disks[0].push_back(i);

        int i = 0, A, B, C;
        while (true)
        {
            int k = findMaxK();

            if (k == 0)
                break;

            if (k % 2 == 1)
            {
                A = i, B = (i + 1) % 3, C = (i + 2) % 3;

                disks[B].insert(disks[B].begin(), disks[A].begin(), disks[A].begin() + k);
                disks[A].erase(disks[A].begin(), disks[A].begin() + k);

                if (moves.size())
                {
                    subtract();

                    if (disks[C].size() == 0 || disks[C].front() > disks[A].front())
                    {
                        disks[C].insert(disks[C].begin(), disks[A].front());
                        disks[A].erase(disks[A].begin());
                    }
                    else
                    {
                        disks[A].insert(disks[A].begin(), disks[C].front());
                        disks[C].erase(disks[C].begin());
                    }
                }

                i = B;
            }
            else
            {
                A = i, B = (i + 1) % 3, C = (i + 2) % 3;

                disks[C].insert(disks[C].begin(), disks[A].begin(), disks[A].begin() + k);
                disks[A].erase(disks[A].begin(), disks[A].begin() + k);

                if (moves.size())
                {
                    subtract();
                    
                    if (disks[B].size() == 0 || disks[B].front() > disks[A].front())
                    {
                        disks[B].insert(disks[B].begin(), disks[A].front());
                        disks[A].erase(disks[A].begin());
                    }
                    else
                    {
                        disks[A].insert(disks[A].begin(), disks[B].front());
                        disks[B].erase(disks[B].begin());
                    }
                }
                
                i = C;
            }
        }
        
        cout << disks[0].size() << " " << disks[1].size() << " " << disks[2].size() << "\n";
    }
    
	return 0;
}
