// Variable Radix Huffman Encoding
// UVa ID: 240
// Verdict: Accepted
// Submission Date: 2016-05-25
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct symbol
{
    int frequency;
    char letter;
    string code;

    bool operator<(symbol y) const
    {
        return letter < y.letter;
    }
};

struct node
{
    int index, frequency;
    vector < symbol > symbols;

    bool operator<(node y) const
    {
        if (frequency != y.frequency)
            return frequency > y.frequency;
        else
            return index > y.index;
    }
};

int main(int argc, char *argv[])
{
    int R, N, cases = 0;

    while (cin >> R, R)
    {
        cin >> N;

        priority_queue <node> H;

        int frequency;
        for (int i = 0; i < N; i++)
        {
            cin >> frequency;

            symbol aSymbol;
            aSymbol.frequency = frequency;
            aSymbol.letter = 'A' + i;

            node aNode;
            aNode.index = i;
            aNode.frequency = frequency;
            aNode.symbols.push_back(aSymbol);

            H.push(aNode);
        }

        int nullNumber = N - R;

        if (nullNumber <= 0)
        {
            while (nullNumber < 0)
            {
                node aNode;
                aNode.index = N;
                aNode.frequency = 0;
                H.push(aNode);
                nullNumber++;
            }
        }
        else
        {
            nullNumber %= (R - 1);
            if (nullNumber > 0)
            {
                while (nullNumber < (R - 1))
                {
                    node aNode;
                    aNode.index = N;
                    aNode.frequency = 0;
                    H.push(aNode);
                    nullNumber++;
                }
            }
        }

        while (H.size() > 1)
        {
            node last;
            last.index = H.top().index;

            int frequencies = 0;
            vector <symbol> collection;
            for (int i = 0; i < R; i++)
            {
                node front = H.top();
                H.pop();

                if (front.index < last.index)
                    last.index = front.index;

                frequencies += front.frequency;

                for (int j = 0; j < front.symbols.size(); j++)
                {
                    string code = front.symbols[j].code;
                    code.insert(code.begin(), '0' + i);
                    front.symbols[j].code = code;
                    collection.push_back(front.symbols[j]);
                }
            }

            last.frequency = frequencies;
            last.symbols = collection;
            H.push(last);
        }

        node result = H.top();
        sort(result.symbols.begin(), result.symbols.end());

        int total = 0, frequencies = 0;
        for (int i = 0; i < result.symbols.size(); i++)
        {
            total += result.symbols[i].frequency * result.symbols[i].code.length();
            frequencies += result.symbols[i].frequency;
        }

        double aveLength = (double)total / frequencies;
        cout << "Set " << ++cases << "; average length ";
        cout << fixed << setprecision(2) << aveLength << endl;
        for (int i = 0; i < result.symbols.size(); i++)
        {
            cout << "    " << result.symbols[i].letter;
            cout << ": " << result.symbols[i].code << endl;
        }
        cout << endl;
    }

    return 0;
}
