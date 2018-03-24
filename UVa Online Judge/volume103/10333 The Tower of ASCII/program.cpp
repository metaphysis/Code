// The Tower of ASCII
// UVa ID: 10333
// Verdict: Accepted
// Submission Date: 2018-03-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, H;
    while (cin >> H)
    {
        // Generate pattern.
        int threshold = sqrt(2 * H);
        while (threshold * (threshold + 1) / 2 < H) threshold++;
        while (threshold * (threshold + 1) / 2 >= H) threshold--;
        vector<int> leftPart, rightPart;
        int height = threshold * (threshold + 1) / 2;
        if (height + threshold + 1 == H)
        {
            threshold++;
            for (int i = 1; i <= threshold; i++)
            {
                leftPart.push_back(i);
                rightPart.push_back(i);
            }
        }
        else
        {
            for (int i = 1; i <= threshold; i++)
            {
                leftPart.push_back(i);
                rightPart.push_back(i);
            }
            leftPart.back() += H - height;
            rightPart.back() += H - height;
        }
        int last = rightPart.back();
        rightPart.pop_back();
        rightPart.back() += last;

        // Output.
        cout << "Tower #" << ++cases << '\n';
        string pieces = "#**";
        int rows = H, clns = 2 * (leftPart.size() + rightPart.size() + 1);
        char board[rows][clns];
        memset(board, '0', sizeof(board));
        // Fill left part.
        int rowIdx = 0;
        int leftEdge[rows], rightEdge[rows];
        for (int i = 0; i < leftPart.size(); i++)
        {
            int spaces = 2 * (leftPart.size() - i - 1);
            for (int j = 0; j < leftPart[i]; j++)
            {
                for (int k = 0; k < spaces; k++)
                    board[rowIdx][k] = ' ';
                if (j == 0)
                {
                    for (int k = 0; k < 3; k++)
                        board[rowIdx][spaces + k] = pieces[k];
                    leftEdge[rowIdx] = spaces + 3;
                }
                else
                {
                    board[rowIdx][spaces] = '#';
                    leftEdge[rowIdx] = spaces + 1;
                }
                rowIdx++;
            }
        }
        // Fill right part.
        rowIdx = 0;
        int offset = 2 * leftPart.size() + 3;
        for (int i = 0; i < rightPart.size(); i++)
        {
            int spaces = offset + 2 * i;
            for (int j = 0; j < rightPart[i]; j++)
            {
                if (j == 0)
                {
                    for (int k = 0; k < 3; k++)
                        board[rowIdx][spaces - k] = pieces[k];
                    rightEdge[rowIdx] = spaces - 3;
                }
                else
                {
                    board[rowIdx][spaces] = '#';
                    rightEdge[rowIdx] = spaces - 1;
                }
                rowIdx++;
            }
        }
        // Fill period.
        for (int i = 0; i < rows; i++)
            for (int j = leftEdge[i]; j <= rightEdge[i]; j++)
                board[i][j] = '.';
        // Print.
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < clns; j++)
            {
                if (board[i][j] == '0') break;
                cout << board[i][j];
            }
            cout << '\n';
        }
        cout << '\n';
    }

    return 0;
}
