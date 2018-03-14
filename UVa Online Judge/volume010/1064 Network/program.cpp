// Network
// UVa ID: 1064
// Verdict: Accepted
// Submission Date: 2017-11-09
// UVa Run Time: 0.010s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int messageId, waiting, buffered, consumeMost;
int n, m;
int bytes[8];
int packetIdx;

struct packet
{
    int mid, start, end;
    
    bool operator<(const packet &p) const
    {
        return start > p.start;
    }
} packets[1024];

priority_queue<packet> buffer[8];

void process()
{
    while (waiting <= bytes[messageId])
    {
        if ((buffer[messageId].empty() || buffer[messageId].top().start != waiting))
        {
            while (packets[packetIdx].mid != messageId || packets[packetIdx].start != waiting)
            {
                buffered += packets[packetIdx].end - packets[packetIdx].start + 1;
                consumeMost = max(consumeMost, buffered);
                buffer[packets[packetIdx].mid].push(packets[packetIdx]);
                packetIdx++;
            }
            waiting = packets[packetIdx].end + 1;
            packetIdx++;
        }
        else
        {
            packet p = buffer[messageId].top(); buffer[messageId].pop();
            buffered -= p.end - p.start + 1;
            waiting = p.end + 1;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    
    while (cin >> n >> m, n > 0)
    {
        for (int i = 1; i <= n; i++)
            cin >> bytes[i];

        for (int i = 0; i < m; i++)
            cin >> packets[i].mid >> packets[i].start >> packets[i].end;

        vector<int> number(n);
        iota(number.begin(), number.end(), 1);
        
        int least = 0x3fffffff;
        do
        {
            consumeMost = buffered = packetIdx = 0;
            for (int i = 0; i < number.size(); i++)
            {
                messageId = number[i], waiting = 1;
                process();
            }
            least = min(least, consumeMost);
        } while (next_permutation(number.begin(), number.end()));
        cout << "Case " << ++cases << ": " << least << "\n\n";
    }
    
    return 0;
}
