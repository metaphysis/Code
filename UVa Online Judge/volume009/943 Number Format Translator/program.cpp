// Number Format Translator
// UVa ID: 943
// Verdict: Accepted
// Submission Date: 2017-03-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    map<string, int> digits = {
    {"zero", 0}, {"um", 1}, {"dois", 2}, {"tres", 3}, {"quatro", 4}, {"cinco", 5}, {"seis", 6}, {"sete", 7}, {"oito", 8}, {"nove", 9},
    {"dez", 10}, {"onze", 11}, {"doze", 12}, {"treze", 13}, {"catorze", 14}, {"quatorze", 14}, {"quinze", 15}, {"dezasseis", 16},
    {"dezesseis", 16}, {"dezassete", 17}, {"dezessete", 17}, {"dezoito", 18}, {"dezanove", 19}, {"dezenove", 19}, {"vinte", 20},
    {"trinta", 30}, {"quarenta", 40}, {"cinquenta", 50}, {"sessenta", 60}, {"setenta", 70}, {"oitenta", 80}, {"noventa", 90},
    {"cem", 100}, {"cento", 100}, {"duzentos", 200}, {"trezentos", 300}, {"quatrocentos", 400}, {"quinhentos", 500},
    {"seiscentos", 600}, {"setecentos", 700}, {"oitocentos", 800}, {"novecentos", 900}, {"mil", 1000},
    {"milhao", 1000000}, {"milhoes", 1000000}, {"biliao", 1000000000}, {"bilioes", 1000000000},
    {"bilhao", 1000000000}, {"bilhoes", 1000000000}
    };
    
    int cases = 0;
    
    cin >> cases;
    cout << cases << '\n';
    
    cin.ignore(1024, '\n');
    
    for (int c = 1; c <= cases; c++)
    {
        string line;
        getline(cin, line);
        
        istringstream iss(line);
        
        long long total = 0;
        queue<long long> number;
        
        string word;
        while (iss >> word)
        {
            if (digits.find(word) == digits.end()) continue;

            long long current = digits[word];
            if (!number.empty() && current > number.front())
            {
                long long prefix = 0;
                while (!number.empty())
                {
                    prefix += number.front();
                    number.pop();
                }
                total += prefix * current;
            }
            else
                number.push(current);
        }
        
        long long remainder = 0;
        while (!number.empty())
        {
            remainder += number.front();
            number.pop();
        }
        total += remainder;
        
        cout << total << '\n';
    }
    
    return 0;
}
