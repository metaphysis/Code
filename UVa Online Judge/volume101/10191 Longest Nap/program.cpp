// Longest Nap （最长打盹时间）
// PC/UVa IDs: 110404/10191, Popularity: B, Success rate: average Level: 1
// Verdict: Accepted
// Submission Date: 2014-07-28
// UVa Run Time: 0.008s
//
// 版权所有（C）2014，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define MAX_MINUTES 481
int minutes[MAX_MINUTES];   // 10：00到18：00共480分钟

struct longestNapTime
{
	int startAt;	// 打盹的开始时间，以从00：00开始的分钟数计算
	int duration;	// 打盹的持续时间，以分钟数计算
};

void reset()
{
    memset(minutes, 0, sizeof(minutes));
    minutes[0] = 0; minutes[480] = 1;
}

int getStartTime(string line)
{
	int startTime = atoi(line.substr(0, 2).data()) * 60;
	startTime += atoi(line.substr(3, 2).data());
	return (startTime - 600);
}

int getEndTime(string line)
{
    int endTime = atoi(line.substr(6, 2).data()) * 60;
	endTime += atoi(line.substr(9, 2).data());
	return (endTime - 600);
}

void fill(int counterEvents)
{
	while (counterEvents > 0)
	{
		string line;
		getline(cin, line);
		for (int i = getStartTime(line); i < getEndTime(line); i++)
		{
		   minutes[i] = 1;
		}
		counterEvents--;
	}
}

longestNapTime find()
{
    int startAt = 0, napTime = 0;
    bool startTimeSetted = false;
    longestNapTime theLongest = { startAt, 0 };
    
    for (int index = 0; index < MAX_MINUTES; index++)
    {
        if (minutes[index] == 0)
        {
            if (startTimeSetted == false)
            {
                startAt = index;
                startTimeSetted = true;     
            }
            napTime++;
        }
        else
        {
            if (napTime > theLongest.duration)
            {
                theLongest.startAt = startAt + 600;
                theLongest.duration = napTime;
            }
            napTime = 0;
            startTimeSetted = false;
        }
    }
    
    return theLongest;
}

void print(int counterCases, longestNapTime aNapTime)
{
	cout << "Day #" << counterCases << ": the longest nap starts at ";
	cout << (aNapTime.startAt / 60) << ":";
	cout << (aNapTime.startAt % 60 < 10 ? "0" : "") << (aNapTime.startAt % 60);
	cout << " and will last for ";
	if (aNapTime.duration < 60)
	{
		cout << aNapTime.duration;
	}
	else
	{
		cout << (aNapTime.duration / 60) << " hours and " << (aNapTime.duration % 60);
	}
	cout << " minutes.\n";
}

int main(int ac, char *av[])
{
	int counterCases = 0, counterEvents;
	while (counterCases++, cin >> counterEvents)
	{
	    cin.ignore();
		reset();
        fill(counterEvents);
        print(counterCases, find());
	}
	
	return 0;
}
