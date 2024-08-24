#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
 
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}

template<typename T>
void printa(T a[], int l, int r) {int f = 0; cerr << '{'; for (int i=l;i<=r;i++) cerr << (f++ ? "," : ""), __print(a[i]); cerr << "}]\n";}
template<typename T>
void printma(T a[], T b[], int l, int r, function<ll(ll,ll)> merge) {int f = 0; cerr << '{'; for (int i=l;i<=r;i++) cerr << (f++ ? "," : ""), __print(merge(a[i],b[i])); cerr << "}]\n";}
// #define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#define debuga(x, l, r) cerr << "[" << #x << "] = ["; printa(x, l, r)
#define debugma(x, y, l, r, merge) cerr << "[" << #x << "," << #y << "] = ["; printma(x, y, l, r, merge)
#define debugpdd(s, x...) cerr << s; debug(x)
#else
#define debug(x...)
#define debuga(x, l, r)
#define debugma(x, y, l, r, merge)
#define debugpdd(s, x...)
#endif
 
/*
 
    peeked the solution
    we have to make aho-corasick automaton
    then, at those nodes in which some pattern string is ending, we would store the index of pattern
    and make the value at that index as 1, otherwise 0
    we would have a problem that every node in trie corresponds to the string covered till that index, what about all those strings which are starting from other indices > starting index of string
    for ex, s = dabc
    now, if we would traverse in trie, then maybe 5th node would correspond to string dabc
    but what about strings abc, bc, c
    so, at every node or we can say that at every string we have to consider all its strings
    this we can do by traversing to every suffix node of that node which we would visit during traversing the string
    
    but, going through all suffixes would take O(len), where len is length of currently covered string
    and we would do this for O(n) times, where n is length of string
    so, it would take O(n * len), not ideal for given constraints

    on seeing the solution from cp algo, we can use exit links that is the nearest node which correspond to a string in patterns and is the suffix of the currently covered string
    we can get that in O(1) using path compression just like we are doing with finding suffix and go value

    TLE1
    we are unnecessarily visiting all those vertices, if we have already visited them
    we can take a covered flag for every vertex and make it true when we would mark all its pattern indices
    and do not visit a vertex if it is already visited
    if a vertex is visited, it means all of its exit suffixes are also visited
    [it reduced time a lot but not sure whether it was needed]

    TLE2
    we are putting wrong value for exit node
    we are storing -1 if the exit node is not yet known for any node or there is no exit node
    it becomes problematic if we would try to find the exit node every time, even when we know exit node does not exists
    it would check till last point going to O(n) suffixes and resulting in -1 at last

    WA1
    did mistake while changing code
    changed this
        int suffix = getSuffix(ni);
        if(ni == suffix) {
            nodes[ni].go[ch] = ni;    
        }
        else {
            nodes[ni].go[ch] = getGoVal(suffix, ch);
        }
    to this
        nodes[ni].go[ch] = (ni == 0 ? 0 : getGoVal(getSuffix(ni), nodes[ni].parChar));
    instead of this
        nodes[ni].go[ch] = (ni == 0 ? 0 : getGoVal(getSuffix(ni), ch));


*/
string ps = "";

const int mod = int(1e9 + 21);

const int MAXN = int(1e5+5);

typedef struct Vertex {
    vector<int> next;
    vector<int> pind;

    int par;
    int parChar;
    int suffixLink;

    vector<int> go;
    int exit;

    bool covered;

    Vertex(int par, int ch = '$' - 'a') {
        next.resize(26, -1);
        
        this->par = par;
        parChar = ch;
        suffixLink = -1;

        go.resize(26, -1);
        exit = -2;
        covered = 0;
    }
} Vertex;

vector<Vertex> nodes(1, Vertex(0));
// vector<Vertex> nodes;
// nodes.push_back();

void add(string& s, int ind) {
    int c=0;
    int n=s.size();

    for(int i=0;i<n;i++) {
        int ch = s[i] - 'a';
        // cout << c << " , " << ch << " : " << nodes.size() << "\n";
        if(nodes[c].next[ch] == -1) {
            nodes[c].next[ch] = nodes.size();
            nodes.emplace_back(Vertex(c, ch));
        }

        c = nodes[c].next[ch];
    }

    nodes[c].pind.push_back(ind);
}

int getSuffix(int ni);
int getGoVal(int ni, int ch);

int getSuffix(int ni) {
    if(nodes[ni].suffixLink == -1) {
        if(ni == 0 || nodes[ni].par == 0) {
            nodes[ni].suffixLink = 0;
        }
        else {
            nodes[ni].suffixLink = getGoVal(getSuffix(nodes[ni].par), nodes[ni].parChar);
        }
    }

    return nodes[ni].suffixLink;
}

int getGoVal(int ni, int ch) {
    if(nodes[ni].go[ch] == -1) {
        if(nodes[ni].next[ch] != -1) {
            nodes[ni].go[ch] = nodes[ni].next[ch];
        }
        else {
            // int suffix = getSuffix(ni);
            // if(ni == suffix) {
            //     nodes[ni].go[ch] = ni;    
            // }
            // else {
                // nodes[ni].go[ch] = getGoVal(suffix, ch);
            // }
            nodes[ni].go[ch] = (ni == 0 ? 0 : getGoVal(getSuffix(ni), ch));
        }
    }

    return nodes[ni].go[ch];
}

void createAutomaton() {
    int cn = 0;
    nodes[cn].suffixLink = 0;

    for(int i=0;i<26;i++) {
        if(nodes[cn].next[i] != -1) {
            nodes[nodes[cn].next[i]].suffixLink = 0;
        }
    }

    for(int i=0; i<nodes.size(); i++) {
        for(int j=0; j<26; j++) {
            nodes[i].suffixLink = getSuffix(i);
            nodes[i].go[j] = getGoVal(i, j);
        }
    }
}

void printTrie(int ni, string& s) {
    if(ni == -1) {
        // cout << "-1\n";
        return;
    }
    cout << "\n";
    s.push_back(nodes[ni].parChar + 'a');

    cout << ni << " : ";
    cout << s << " : ";
    cout << nodes[ni].suffixLink << " : ";
    // cout << nodes[ni].par << " : ";

    for(int i=0;i<26;i++) {
        printTrie(nodes[ni].next[i], s);
    }
    s.pop_back();
}

int getExitNode(int ni) {

    if(ni == 0) return -1;

    if(nodes[ni].exit == -2) {
        int nsi = getSuffix(ni);
        int ens = getExitNode(nsi);
        if(nodes[nsi].pind.size() > 0) {
            nodes[ni].exit = nsi;
        }
        else {
            nodes[ni].exit = ens;
        }
    }

    return nodes[ni].exit;
}

void printTrie() {
    string ss;
    printTrie(0, ss);
}

void solve() {
    string s;
    cin >> s;

    int i, k, n=s.size();
    cin >> k;

    for(i=0;i<k;i++) {
        string ptrn;
        cin >> ptrn;

        add(ptrn, i);
    }
    // createAutomaton();

    // string ss = "";
    // printTrie(0, ss);

    // cout << "\n";
    int cn = 0;
    bool ans[k] = {0};
    for(i=0;i<n;i++) {
        int ch = s[i] - 'a';
        // cout << i << "\n";
        // cout << cn << " <- cn\n";
        cn = getGoVal(cn, ch);
        // cout << cn << " <- cn\n";
        if(nodes[cn].pind.size() > 0 && !nodes[cn].covered) {
            nodes[cn].covered = 1;
            for(int ind : nodes[cn].pind) {
                ans[ind] = 1;
            }
        }

        int cnp = cn;
        while(1) {
            cnp = getExitNode(cnp);
            // cout << cnp << " <- cnp\n";
            if(cnp == -1 || nodes[cnp].covered) break;
            nodes[cnp].covered = 1;
            for(int ind : nodes[cnp].pind) {
                ans[ind] = 1;
            }
        }
    }

    for(i=0;i<k;i++) {
        cout << (ans[i] ? "YES" : "NO") << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    cout.tie(NULL);
    // int t;
    // cin >> t;
 
    // while(t--)
    // {
        solve();
    // }
 
    return 0;
}