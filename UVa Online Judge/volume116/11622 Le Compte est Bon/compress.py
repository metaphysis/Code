import re, base64, textwrap

src = open('main.cpp', encoding='utf-8').read()
m = re.search(r'answers\s*\[\s*8001\s*\]\s*=\s*\{(.*?)\};', src, re.S)
nums = list(map(int, re.findall(r'-?\d+', m.group(1))))
assert len(nums) == 8001, len(nums)

first = nums[0]
diffs = [nums[i] - nums[i-1] for i in range(1, len(nums))]
zz = [(d << 1) if d >= 0 else ((-d << 1) - 1) for d in diffs]

def total_bits(k):
    return sum((v >> k) + 1 + k for v in zz)

best_k = min(range(0, 24), key=total_bits)
total = total_bits(best_k)
print(f"best_k={best_k}, bits={total}, bytes={total//8}")

bits = []
for i in range(23, -1, -1):
    bits.append((first >> i) & 1)

for v in zz:
    q = v >> best_k
    r = v & ((1 << best_k) - 1)
    for _ in range(q):
        bits.append(0)
    bits.append(1)
    for i in range(best_k - 1, -1, -1):
        bits.append((r >> i) & 1)

while len(bits) % 8:
    bits.append(0)

data = bytearray()
for i in range(0, len(bits), 8):
    b = 0
    for j in range(8):
        b = (b << 1) | bits[i+j]
    data.append(b)

DATA_LEN = len(data)
print(f"DATA_LEN={DATA_LEN}")

# Base85 编码
b85 = base64.b85encode(data).decode('ascii')
b85_lines = '\n'.join(textwrap.wrap(b85, 200))

cpp = r'''#include <bits/stdc++.h>
using namespace std;

static const char* S = R"B85X(
''' + b85_lines + r'''
)B85X";

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto dec=[](char c)->int{
        if(c>='0'&&c<='9')return c-'0';
        if(c>='A'&&c<='Z')return c-'A'+10;
        if(c>='a'&&c<='z')return c-'a'+36;
        const char* e="!#$%&()*+-;<=>?@^_`{|}~";
        for(int i=0;e[i];i++)if(e[i]==c)return i+62;
        return -1;
    };

    vector<unsigned char> d;
    d.reserve(''' + str(DATA_LEN) + r''');
    unsigned long long v=0; int cnt=0;
    for(const char* p=S;*p;p++){
        int x=dec(*p);
        if(x<0)continue;
        v=v*85+x;
        if(++cnt==5){
            d.push_back((v>>24)&0xFF);
            d.push_back((v>>16)&0xFF);
            d.push_back((v>>8)&0xFF);
            d.push_back(v&0xFF);
            v=0; cnt=0;
        }
    }
    d.resize(''' + str(DATA_LEN) + r''');

    int bp=0;
    auto rb=[&]()->int{
        int byte=d[bp>>3];
        int bit=7-(bp&7);
        bp++;
        return (byte>>bit)&1;
    };

    int first=0;
    for(int i=0;i<24;i++) first=(first<<1)|rb();

    const int K=''' + str(best_k) + r''';
    vector<int> ans;
    ans.reserve(8001);
    ans.push_back(first);

    while((int)ans.size()<8001){
        int q=0;
        while(rb()==0)q++;
        int r=0;
        for(int i=0;i<K;i++) r=(r<<1)|rb();
        int val=(q<<K)|r;
        int diff=(val&1)? -((val>>1)+1) : (val>>1);
        ans.push_back(ans.back()+diff);
    }

    int T; cin>>T;
    while(T--){
        int t; cin>>t;
        cout<<ans[t]<<'\n';
    }
    return 0;
}
'''

open('compressed.cpp', 'w', encoding='utf-8').write(cpp)
print('cpp bytes:', len(cpp.encode('utf-8')))
