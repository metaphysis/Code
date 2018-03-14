// LC-Display （液晶显示屏）
// PC/UVa IDs: 110104/706, Popularity: A, Success rate: average Level: 1
// Verdict: Accepted 
// Submission Date: 2011-04-09
// UVa Run Time: 0.012s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

void lcdDisplay(int size, string number)
{
    // 定义每个数字的关键笔划。
    string outline[5][10] = {
        " - ", "   ", " - ", " - ", "   ", " - ", " - ", " - ", " - ", " - ",
        "| |", "  |", "  |", "  |", "| |", "|  ", "|  ", "  |", "| |", "| |",
        "   ", "   ", " - ", " - ", " - ", " - ", " - ", "   ", " - ", " - ",
        "| |", "  |", "|  ", "  |", "  |", "  |", "| |", "  |", "| |", "  |",
        " - ", "   ", " - ", " - ", "   ", " - ", " - ", "   ", " - ", " - "
    };

    // 根据指定size将关键笔划扩大显示，实际上就是将关键笔划重复size次。
    for (int row = 1; row <= (2 * size + 3); row++)
    {
        for (int i = 0; i < number.length(); i++)
        {
            string line;
            int column = number[i] - '0';
            if (row == 1) line = outline[0][column];
            if (2 <= row && row < (size + 2)) line = outline[1][column];
            if (row == (size + 2)) line = outline[2][column];
            if ((size + 3) <= row && row <= (2 * size + 2)) line = outline[3][column];
            if (row == (2 * size + 3)) line = outline[4][column];

            // 输出关键笔划。
            cout << line[0];
            for (int j = 0; j < size; j++) cout << line[1];
            cout << line[2];

            // 在两个数字间要有一列空行。
            if (i < 7) cout << " ";
        }

        cout << '\n';
    }
}

int main(int argc, char *argv[])
{
    int size;
    string number;

    while (cin >> size >> number, size)
    {
        lcdDisplay(size, number);
        cout << endl;
    }

    return 0;
}
