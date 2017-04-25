#include<iostream>
#include<map>
#include<string>
using namespace std;
string mor[256];
map<string,string>m;
char c;
string t;
int diff(const string&ta,const string&tb)
{
	string a,b;
	if(ta.size()>tb.size())a=ta,b=tb;
	else a=tb,b=ta;
	if(a.find(b)==0)
		return a.size()-b.size();
	else return 0x7fffffff;
}
void encode(const string&w)
{
	string y;
	for(int i=0;i<w.size();i++)
		y+=mor[w[i]];
	m[w]=y;
}
void solve(const string&t)
{
	string ans=m.begin()->first;
	int d,mdiff=0x7fffffff;
	bool exc=false;
	for(map<string,string>::iterator i=m.begin();i!=m.end();i++)
	{
		d=diff(i->second,t);
		if(d==0&&mdiff==0)exc=true;
		if(d<mdiff)
		{
			ans=i->first;
			mdiff=d;
		}
	}
	if(mdiff)ans+='?';
	else if(exc)ans+='!';
	cout<<ans<<endl;
}
int main()
{
	while(cin>>c&&c!='*')cin>>mor[c];
	while(cin>>t&&t[0]!='*')encode(t);
	while(cin>>t&&t[0]!='*')solve(t);
	return 0;
}
