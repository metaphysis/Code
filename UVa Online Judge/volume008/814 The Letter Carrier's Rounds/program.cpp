// The Letter Carrier's Rounds
// UVa ID: 814
// Verdict: Accepted
// Submission Date: 2025-10-19
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>

using namespace std;

// 存储MTA信息的结构
struct MTA {
    string name;
    set<string> users;
};

// 解析用户@MTA格式
void parseAddress(const string& address, string& user, string& mta) {
    size_t atPos = address.find('@');
    user = address.substr(0, atPos);
    mta = address.substr(atPos + 1);
}

int main() {
    vector<MTA> mtas;
    string line;
    
    // 读取MTA信息
    while (getline(cin, line) && line != "*") {
        if (line[0] == 'M' && line[1] == 'T' && line[2] == 'A') {
            istringstream iss(line);
            string mta, name;
            int userCount;
            iss >> mta >> name >> userCount;
            
            MTA newMTA;
            newMTA.name = name;
            
            for (int i = 0; i < userCount; i++) {
                string user;
                iss >> user;
                newMTA.users.insert(user);
            }
            
            mtas.push_back(newMTA);
        }
    }
    
    // 创建MTA名称到索引的映射，便于查找
    map<string, int> mtaMap;
    for (int i = 0; i < mtas.size(); i++) {
        mtaMap[mtas[i].name] = i;
    }

    // 处理消息
    while (getline(cin, line) && line != "*") {
        // 解析发送者和接收者（都在同一行）
        istringstream iss(line);
        string sender;
        iss >> sender;
        
        string senderUser, senderMTA;
        parseAddress(sender, senderUser, senderMTA);
        
        // 读取所有接收者（同一行的剩余部分）
        vector<string> allRecipients;
        string recipient;
        while (iss >> recipient) {
            allRecipients.push_back(recipient);
        }
        
        // 忽略消息的起始标志*
        getline(cin, line);
    
        // 读取消息内容（直到下一个*）
        vector<string> messageLines;
        while (getline(cin, line) && line != "*") {
            messageLines.push_back(line);
        }
        
        // 按目标MTA分组接收者
        map<string, vector<string>> mtaRecipients;
        vector<string> lineMtas;
        set<string> mtasCache;
        map<string, set<string>> userCache;
        for (const auto& recipient : allRecipients) {
            string user, mta;
            parseAddress(recipient, user, mta);
            if (!userCache[mta].count(user)) {
                mtaRecipients[mta].push_back(user);
                userCache[mta].insert(user);
            }
            if (!mtasCache.count(mta)) {
                mtasCache.insert(mta);
                lineMtas.push_back(mta);
            }
        }

        for (const string mta : lineMtas) {
            const string& targetMTA = mta;
            const vector<string>& users = mtaRecipients[mta];
            
            // 检查目标MTA是否存在
            if (mtaMap.find(targetMTA) == mtaMap.end()) {
                continue;
            }
            
            const MTA& destMTA = mtas[mtaMap[targetMTA]];
            
            // 输出连接信息
            cout << "Connection between " << senderMTA << " and " << targetMTA << endl;
            
            // HELO命令
            cout << "     HELO " << senderMTA << endl;
            cout << "     250" << endl;
            
            // MAIL FROM命令
            cout << "     MAIL FROM:<" << senderUser << "@" << senderMTA << ">" << endl;
            cout << "     250" << endl;
            
            // 检查有效接收者
            bool hasValidRecipient = false;
            for (const string& user : users) {
                cout << "     RCPT TO:<" << user << "@" << targetMTA << ">" << endl;
                if (destMTA.users.find(user) != destMTA.users.end()) {
                    cout << "     250" << endl;
                    hasValidRecipient = true;
                } else {
                    cout << "     550" << endl;
                }
            }
            
            // 如果有有效接收者，发送DATA
            if (hasValidRecipient) {
                cout << "     DATA" << endl;
                cout << "     354" << endl;
                
                // 输出消息内容
                for (const string& msgLine : messageLines) {
                    cout << "     " << msgLine << endl;
                }
                
                // 结束消息
                cout << "     ." << endl;
                cout << "     250" << endl;
            }
            
            // QUIT命令
            cout << "     QUIT" << endl;
            cout << "     221" << endl;
        }
    }
    
    return 0;
}
