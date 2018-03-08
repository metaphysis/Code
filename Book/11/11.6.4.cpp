#include <iostream>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

// 定义结构表示字符，频度，编码。
struct letter
{
    char ascii;
    int frequency;
    string code;

    bool operator<(letter x) const
    {
        return ascii < x.ascii;
    }
};

// 定义一个符号结构，方便编码的实现。
struct symbol
{
    int frequency;
    vector <letter> letters;

    bool operator<(symbol x) const
    {
        return frequency > x.frequency;
    }
};

void huffman(string line)
{
    // 统计各个字符出现的次数。
    map <char, int> counter;
    for (int i = 0; i < line.length(); i++)
        counter[line[i]]++;

    // 将字符放入最小优先队列中。
    priority_queue <symbol> symbols;
    for (auto it = counter.begin(); it != counter.end(); it++)
    {
        letter l;
        l.ascii = (*it).first;
        l.frequency = (*it).second;

        symbol s;
        s.frequency = (*it).second;
        s.letters.push_back(l);

        symbols.push(s);
    }

    // 使用贪心策略将具有最小频度的两个字符进行合并。
    while (symbols.size() > 1)
    {
        int sumOfFrequency = 0;
        vector <letter> merge;
    
        for (int i = 0; i < 2; i++)
        {
            symbol s = symbols.top();
            symbols.pop();

            sumOfFrequency += s.frequency;

            for (int j = 0; j < s.letters.size(); j++)
            {
                s.letters[j].code.insert(s.letters[j].code.begin(), '0' + i);
                merge.push_back(s.letters[j]);
            }
        }

        // 合并后的字符放入优先队列中。
        symbol s;
        s.frequency = sumOfFrequency;
        s.letters = merge;
        
        symbols.push(s);
    }

    // 输出编码。
    if (symbols.size())
    {
        symbol s = symbols.top();
        symbols.pop();

        sort(s.letters.begin(), s.letters.end());

        for (int i = 0; i < s.letters.size(); i++)
            cout << s.letters[i].ascii << " " << s.letters[i].code << endl;
    }
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line))
        huffman(line);

    return 0;
}
