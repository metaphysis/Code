// CDVII （CDVII 高速公路）
// PC/UVa IDs: 110406/10138, Popularity: C, Success rate: low Level: 2
// Verdict: Accepted
// Submission Date: 2011-05-23
// UVa Run Time: 0.024s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
	
#include <bits/stdc++.h>

using namespace std;
	
#define MAXSIZE 	1000    // 照片的最大数量。
#define FARE_TYPES	24	    // 时段收费的种类。
#define ACCOUNT_FEE	200	    // 月租费用，美分。
#define TRIP_FEE	100	    // 单次通过费用，美分。
	
#ifndef DEBUG_MODE
// #define DEBUG_MODE
#endif
	
struct license_photo
{
	string license;	// 车辆牌照
	int time;	    // 进入时间，为：日 * 24 * 60 + 小时 * 60 + 分钟。
	string status;	// 车辆状态：enter，exit。
	int location;	// 距离高速公路一端的距离。
	int fare;	    // 收费标准，根据进入时间确定，美分。
};
	
#ifdef DEBUG_MODE
ostream& operator<<(ostream &out, license_photo &photo)
{
	cout << photo.license << " " << photo.time << " ";
	cout << photo.status << " ";
	cout << photo.location << " " << photo.fare << endl;
	
	return out;
}
#endif
	
// 如果牌照相同，记录时间早的排在前面。
bool cmp(license_photo x, license_photo y)
{
	if (x.license != y.license)
		return x.license < y.license;
	return x.time < y.time;
}
	
// 输出一个账单。
void bill(string license, int fee)
{
	if (fee > 0)
	{
		fee += ACCOUNT_FEE;
		cout.precision(2);
		cout.setf(ios::fixed | ios::showpoint);
		cout << license << " $" << (fee / 100.00) << endl;
	}
}
	
// 根据照片产生账单列表。
void bill_list(license_photo photos[], int capacity)
{
	// 对照片进行排序。
	sort(photos, photos + capacity, cmp);
	
	// 测试用。
	#ifdef DEBUG_MODE
	for (int i = 0; i < capacity; i++)
	cout << "[" << i << "]" << photos[i];
	#endif
	
	int current = 0;
	while (current < capacity)
	{
		// 当前计费的车辆牌照号码。
		string license = photos[current].license;
		int fee = 0;
		bool entered = false;
		
		// 找到一辆车的进入/离开记录对。不成对记录忽略。
		for (; current < capacity && (photos[current].license == license); current++)
		{
			// 找到一条进入记录。
			if (!entered)
			{
				if (photos[current].status[1] == 'n')
					entered = true;
				else
					continue;
			}
			
			// 找到了进入记录，找到一个离开记录以成对。
			if (entered)
			{
				if (photos[current].status[1] == 'x')
				{
					// 找到了配对记录，根据收费标准计费。
					entered = false;
					fee += TRIP_FEE;
					fee += photos[current - 1].fare * 
						abs(photos[current].location - photos[current - 1].location);
					
					// 测试用。
					#ifdef DEBUG_MODE
					cout << "<Debug Begin>" << endl;
					cout << "ENTER: " << (current - 1) << " "  << photos[current - 1];
					cout << "EXIT: " << current << " " << photos[current];
					cout << "FEE: " << fee << endl;
					cout << "<Debug End>" << endl;
					#endif
				}
				else
					continue;
			}
		}
		
		bill(license, fee);
	}
}
	
int main(int ac, char *av[])
{
	int cases;
	license_photo photos[MAXSIZE];
	int toll[FARE_TYPES];
	string line;
	
	cin >> cases;
	while (cases--)
	{
		for (int i = 0; i < FARE_TYPES; i++)
			cin >> toll[i];
			
		cin.ignore();
		
		int capacity = 0;
		while (getline(cin, line), line.length() > 0)
		{
			istringstream iss(line);
			string date;
			
			// 牌照。
			iss >> photos[capacity].license >> date;
			// 记录车辆进入和离开的相关信息。
			photos[capacity].time = atoi(date.substr(3, 2).data()) * 24 * 60;
			photos[capacity].time += atoi(date.substr(6, 2).data()) * 60;
			photos[capacity].time += atoi(date.substr(9, 2).data());
						
			// 车辆状态。
			iss >> photos[capacity].status >> photos[capacity].location;
			
			// 收费标准。
			photos[capacity].fare = toll[atoi(date.substr(6, 2).data())];
			
			capacity++;
		}
		
		bill_list(photos, capacity);
		
		// 无成对记录的测试数据不输出任何内容，仅输出一个换行。需要注意。
		if (cases) cout << endl;
	}
	
	return 0;
}
