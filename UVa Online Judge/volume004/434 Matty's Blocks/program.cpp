// Matty's Blocks
// UVa ID: 434
// Verdict: Accepted
// Submission Date: 2016-07-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0;
    cin >> cases;

    for (int i = 1; i <= cases; i++)
    {
        int row;
        cin >> row;

        vector<int> front_view(row), right_view(row);

        for (int j = 0; j < row; j++)
            cin >> front_view[j];
        for (int j = 0; j < row; j++)
            cin >> right_view[j];

        int max_blocks = 0;
        for (int j = 0; j < row; j++)
            for (int k = 0; k < row; k++)
                max_blocks += min(right_view[j], front_view[k]);

        int min_blocks = 0;
        for (int j = 0; j < row; j++)
            for (int k = 0; k < row; k++)
                if (front_view[j] == right_view[k])
                {
                    min_blocks += front_view[j];
                    front_view[j] = 0;
                    right_view[k] = 0;
                    break;
                }

        for (int j = 0; j < row; j++)
            min_blocks += front_view[j] + right_view[j];
                   
        cout << "Matty needs at least " << min_blocks;
        cout << " blocks, and can add at most ";
        cout << (max_blocks - min_blocks) << " extra blocks.\n";
    }

	return 0;
}
