// Message Decoding
// UVa ID: 213
// Verdict: Accepted
// Submission Date: 2016-04-28
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

map<string, int> indexer;

int main(int argc, char *argv[])
{
    for (int i = 2, idx = 0, length = 1; length < 8; i *= 2, length++)
        for (int j = 0; j < (i - 1); j++)
        {
            bitset<8> n(j);
            indexer[n.to_string().substr(8 - length, length)] = idx++;
        }

    string line, head, buffer;
    bool headReaded = false;
    bool segmentEnded = false, segmentStartReaded = false;
    int keyLength;

    while (getline(cin, line))
    {
        if (!headReaded)
        {
            head = line;
            headReaded = true;
        }
        else
        {
            buffer += line;

            nextReading:
            if (!segmentStartReaded)
            {
                if (buffer.length() >= 3)
                {
                    keyLength = stoi(buffer.substr(0, 3), NULL, 2);
                    if (keyLength == 0)
                    {
                        headReaded = false;
                        segmentStartReaded = false;
                        buffer.clear();
                        cout << "\n";
                    }
                    else
                    {
                        buffer.erase(0, 3);
                        segmentStartReaded = true;
                        segmentEnded = false;
                    }
                }
            }

            if (!segmentEnded)
            {
                while (buffer.length() >= keyLength)
                {
                    string key = buffer.substr(0, keyLength);
                    if (key == string(keyLength, '1'))
                    {
                        segmentEnded = true;
                        segmentStartReaded = false;
                        buffer.erase(0, keyLength);
                        goto nextReading;
                    }
                    else
                    {
                        cout << head[indexer[key]];
                        buffer.erase(0, keyLength);
                    }
                }
            }
        }
    }

    return 0;
}
