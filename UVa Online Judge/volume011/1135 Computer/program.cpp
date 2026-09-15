#include <bits/stdc++.h>
using namespace std;

struct NodeKey {
    int Var, Lo, Hi;
    bool operator == (const NodeKey &Other) const {
        return Var == Other.Var && Lo == Other.Lo && Hi == Other.Hi;
    }
};

struct NodeKeyHash {
    size_t operator () (const NodeKey &Key) const {
        size_t Hash = Key.Var;
        Hash = Hash * 1000003 + Key.Lo;
        Hash = Hash * 1000003 + Key.Hi;
        return Hash;
    }
};

struct ApplyKey {
    int Op, A, B;
    bool operator == (const ApplyKey &Other) const {
        return Op == Other.Op && A == Other.A && B == Other.B;
    }
};

struct ApplyKeyHash {
    size_t operator () (const ApplyKey &Key) const {
        size_t Hash = Key.Op;
        Hash = Hash * 1000003 + Key.A;
        Hash = Hash * 1000003 + Key.B;
        return Hash;
    }
};

class BddManager {
private:
    struct Node {
        int Var, Lo, Hi;
    };
    vector<Node> Nodes;
    unordered_map<NodeKey, int, NodeKeyHash> UniqueTable;
    unordered_map<ApplyKey, int, ApplyKeyHash> ApplyTable;
    unordered_map<int, int> NotTable;
public:
    BddManager() {
        Nodes.push_back({-1, 0, 0});
        Nodes.push_back({-1, 1, 1});
    }
    int MakeNode(int Var, int Lo, int Hi) {
        if (Lo == Hi)
            return Lo;
        NodeKey Key = {Var, Lo, Hi};
        unordered_map<NodeKey, int, NodeKeyHash>::iterator It = UniqueTable.find(Key);
        if (It != UniqueTable.end())
            return It->second;
        int Id = (int)Nodes.size();
        Nodes.push_back({Var, Lo, Hi});
        UniqueTable[Key] = Id;
        return Id;
    }
    int GetVar(int Var) {
        return MakeNode(Var, 0, 1);
    }
    int GetValue(int Id, int VarValue) {
        if (Id <= 1)
            return Id;
        return Nodes[Id].Var == VarValue ? Nodes[Id].Hi : Nodes[Id].Lo;
    }
    int Apply(int Op, int A, int B) {
        if (A > B && Op != 2)
            swap(A, B);
        if (A <= 1 && B <= 1) {
            if (Op == 0)
                return A & B;
            if (Op == 1)
                return A | B;
            return A ^ B;
        }
        if (Op == 0) {
            if (A == 0 || B == 0)
                return 0;
            if (A == 1)
                return B;
            if (B == 1)
                return A;
            if (A == B)
                return A;
        } else if (Op == 1) {
            if (A == 1 || B == 1)
                return 1;
            if (A == 0)
                return B;
            if (B == 0)
                return A;
            if (A == B)
                return A;
        } else {
            if (A == 0)
                return B;
            if (B == 0)
                return A;
            if (A == B)
                return 0;
        }
        ApplyKey Key = {Op, A, B};
        unordered_map<ApplyKey, int, ApplyKeyHash>::iterator It = ApplyTable.find(Key);
        if (It != ApplyTable.end())
            return It->second;
        int Va = A <= 1 ? INT_MAX : Nodes[A].Var, Vb = B <= 1 ? INT_MAX : Nodes[B].Var;
        int Var = min(Va, Vb);
        int ALo = Va == Var ? Nodes[A].Lo : A, AHi = Va == Var ? Nodes[A].Hi : A;
        int BLo = Vb == Var ? Nodes[B].Lo : B, BHi = Vb == Var ? Nodes[B].Hi : B;
        int Result = MakeNode(Var, Apply(Op, ALo, BLo), Apply(Op, AHi, BHi));
        ApplyTable[Key] = Result;
        return Result;
    }
    int Not(int A) {
        if (A == 0)
            return 1;
        if (A == 1)
            return 0;
        unordered_map<int, int>::iterator It = NotTable.find(A);
        if (It != NotTable.end())
            return It->second;
        int Result = MakeNode(Nodes[A].Var, Not(Nodes[A].Lo), Not(Nodes[A].Hi));
        NotTable[A] = Result;
        return Result;
    }
    int And(int A, int B) {
        return Apply(0, A, B);
    }
    int Or(int A, int B) {
        return Apply(1, A, B);
    }
    int Xor(int A, int B) {
        return Apply(2, A, B);
    }
};

struct Instruction {
    int Type, A, B;
};

struct State {
    int Pc, Cond;
    array<int, 32> Reg;
    bool operator == (const State &Other) const {
        return Pc == Other.Pc && Cond == Other.Cond && Reg == Other.Reg;
    }
};

struct StateHash {
    size_t operator () (const State &Value) const {
        size_t Hash = Value.Pc * 1000003 + Value.Cond;
        for (int X : Value.Reg)
            Hash = Hash * 1000003 + X;
        return Hash;
    }
};

int GetType(const string &Op) {
    if (Op == "AND") return 0;
    if (Op == "OR") return 1;
    if (Op == "XOR") return 2;
    if (Op == "NOT") return 3;
    if (Op == "MOV") return 4;
    if (Op == "SET") return 5;
    if (Op == "RANDOM") return 6;
    if (Op == "JMP") return 7;
    if (Op == "JZ") return 8;
    return 9;
}

int Solve(const vector<Instruction> &Ins, BddManager &Bdd) {
    State Start;
    Start.Pc = 0;
    Start.Cond = 1;
    for (int I = 0; I < 32; ++I)
        Start.Reg[I] = Bdd.GetVar(I);
    queue<pair<State, int> > Que;
    unordered_set<State, StateHash> Visited;
    Que.push({Start, 0});
    Visited.insert(Start);
    while (!Que.empty()) {
        State Cur = Que.front().first;
        int Dis = Que.front().second;
        Que.pop();
        const Instruction &Now = Ins[Cur.Pc];
        if (Now.Type == 9)
            return Dis + 1;
        vector<State> Next;
        if (Now.Type == 0 || Now.Type == 1 || Now.Type == 2) {
            State Tmp = Cur;
            if (Now.Type == 0)
                Tmp.Reg[Now.A] = Bdd.And(Cur.Reg[Now.A], Cur.Reg[Now.B]);
            if (Now.Type == 1)
                Tmp.Reg[Now.A] = Bdd.Or(Cur.Reg[Now.A], Cur.Reg[Now.B]);
            if (Now.Type == 2)
                Tmp.Reg[Now.A] = Bdd.Xor(Cur.Reg[Now.A], Cur.Reg[Now.B]);
            Tmp.Pc++;
            Next.push_back(Tmp);
        } else if (Now.Type == 3) {
            State Tmp = Cur;
            Tmp.Reg[Now.A] = Bdd.Not(Cur.Reg[Now.A]);
            Tmp.Pc++;
            Next.push_back(Tmp);
        } else if (Now.Type == 4) {
            State Tmp = Cur;
            Tmp.Reg[Now.A] = Cur.Reg[Now.B];
            Tmp.Pc++;
            Next.push_back(Tmp);
        } else if (Now.Type == 5) {
            State Tmp = Cur;
            Tmp.Reg[Now.A] = Now.B;
            Tmp.Pc++;
            Next.push_back(Tmp);
        } else if (Now.Type == 6) {
            State Tmp = Cur;
            Tmp.Reg[Now.A] = 0;
            Tmp.Pc++;
            Next.push_back(Tmp);
            Tmp.Reg[Now.A] = 1;
            Next.push_back(Tmp);
        } else if (Now.Type == 7) {
            State Tmp = Cur;
            Tmp.Pc = Now.A;
            Next.push_back(Tmp);
        } else {
            int ZeroCond = Bdd.And(Cur.Cond, Bdd.Not(Cur.Reg[Now.B]));
            if (ZeroCond != 0) {
                State Tmp = Cur;
                Tmp.Pc = Now.A;
                Tmp.Cond = ZeroCond;
                Next.push_back(Tmp);
            }
            int OneCond = Bdd.And(Cur.Cond, Cur.Reg[Now.B]);
            if (OneCond != 0) {
                State Tmp = Cur;
                Tmp.Pc++;
                Tmp.Cond = OneCond;
                Next.push_back(Tmp);
            }
        }
        for (const State &Tmp : Next)
            if (Visited.insert(Tmp).second)
                Que.push({Tmp, Dis + 1});
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    BddManager Bdd;
    bool First = true;
    int N;
    while (cin >> N) {
        vector<Instruction> Ins(N);
        for (int I = 0; I < N; ++I) {
            string Op;
            cin >> Op;
            Ins[I].Type = GetType(Op);
            Ins[I].A = Ins[I].B = 0;
            if (Ins[I].Type == 0 || Ins[I].Type == 1 || Ins[I].Type == 2 || Ins[I].Type == 4)
                cin >> Ins[I].A >> Ins[I].B;
            else if (Ins[I].Type == 3 || Ins[I].Type == 6)
                cin >> Ins[I].A;
            else if (Ins[I].Type == 5)
                cin >> Ins[I].A >> Ins[I].B;
            else if (Ins[I].Type == 7)
                cin >> Ins[I].A;
            else if (Ins[I].Type == 8)
                cin >> Ins[I].A >> Ins[I].B;
        }
        int Ans = Solve(Ins, Bdd);
        if (!First)
            cout << '\n';
        First = false;
        if (Ans == -1)
            cout << "HANGS\n";
        else
            cout << Ans << '\n';
    }
    return 0;
}
