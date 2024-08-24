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
 
    I approach
    use the aho corasick  algorithm and use exit links to get all suffixes ending at current node
    increment all indices coming in the path of following the exit nodes    

    TLE1
    going to every node and incrementing every pattern index can be time consuming
    we can put a cnt variable inside every node and increment it for every output node coming in the way of following exit path
    at last increment the indices of all those patterns whose output vertices have greater count

*/
#define K 26

string ps = "";

class Vertex {
public:
    int next[K], go[K];
    int sl, ol, cnt;
    vector<int> ptin;

    Vertex() {
        memset(next, 0, sizeof(next));
        memset(go, 0, sizeof(go));
        sl = 0;
        ol = 0;
        cnt = 0;
    }
};

vector<Vertex> nodes(1);

void ins(string& s, int ind) {
    int i, cn=0, n=s.size();
    for(i=0;i<n;i++) {
        int ch = s[i] - 'a';
        if(!nodes[cn].next[ch]) {
            nodes[cn].next[ch] = nodes.size();
            nodes.emplace_back();
        }
        cn = nodes[cn].next[ch];
    }

    nodes[cn].ol = cn;
    nodes[cn].ptin.push_back(ind);
}

void ac() {
    // cout << "yo\n";
    queue<int> q;
    q.push(0);

    while(q.size()) {
        // cout << q.size() << "\n";
        int u = q.front();
        q.pop();

        for(int i=0;i<K;i++) {
            if(nodes[u].next[i]) {
                int v = nodes[u].next[i];
                nodes[u].go[i] = v;

                nodes[v].sl = u == 0 ? 0 : nodes[nodes[u].sl].go[i];
                if(!nodes[u].ol) {
                    nodes[u].ol = nodes[nodes[u].sl].ol;
                }

                q.push(v);
            }
            else {
                nodes[u].go[i] = nodes[nodes[u].sl].go[i];
            }
        }
    }
}

void printTrie(int ni, string& s) {
    cout << "\n";
    cout << ni << " : ";
    cout << s << " : ";
    cout << nodes[ni].sl << " : ";
    cout << nodes[ni].ol << " : ";

    for(int i=0;i<K;i++) {
        if(nodes[ni].next[i]) {
            s.push_back(char(i + 'a'));
            printTrie(nodes[ni].next[i], s);
            s.pop_back();
        }
    }
}

void solve() {
    int i, n;
    string s;

    cin >> s;
    n = s.size();

    int k;
    cin >> k;

    string ss;
    for(i=0;i<k;i++) {
        cin >> ss;

        ins(ss, i);
    }
    // ss = "$";
    // printTrie(0, ss);
    ac();
    // printTrie(0, ss);

    int ans[k]={0};
    int u = 0;
    for(i=0;i<n;i++) {
        u = nodes[u].go[s[i] - 'a'];

        int v = nodes[u].ol;
        while(v) {
            // for(int in : nodes[v].ptin) {
            //     ans[in]++;
            // }
            nodes[v].cnt++;
            v = nodes[nodes[v].sl].ol;
        }
    }

    for(i=0;i<nodes.size();i++) {
        if(nodes[i].ol == i) {
            for(int in : nodes[i].ptin) {
                ans[in] += nodes[i].cnt;
            }
        }
    }
    for(i=0;i<k;i++) {
        cout << ans[i] << "\n";
    }
    // cout << "\n";
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