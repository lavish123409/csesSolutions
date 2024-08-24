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
#else
#define debug(x...)
#define debuga(x, l, r)
#define debugma(x, y, l, r, merge)
#endif
 
 
 
/*
 
    I approach
    we would use binary lifting on the tree
    like last time we used it to find the kth ancestor
    we can previous solution and do binary search from 1 to nth ancestor to find which ancestor is same for both

    PROBLEM
    it have the complexity of q * logn * logn, but it can also be done in q * logn

    WA1 (bug/failing for large test cases)
    initialised the wrong right bound for binary search, it should be n and not lgn because the maximum ancestor can be nth ancestor

    TLE1
    as expected
    we can do the incremental increase in ancestors for both ancestors
    and change the nodes also if both ancestors are different
    in this way we would reach the last ancetsor nodes for both nodes which are different and there parent would be the least common ancestor

    WA2 (bug)
    implemented wrong code to do binary lifting
    we should go to higher ancestors first and then lower ancestors, I was doing opposite


*/
string ps = "\n";

void solve() {
    
    int i, j, n, q;
    cin >> n >> q;

    int lgn = ceil(log2(n)) + 1;
    debug(lgn);
    vector<vector<int>> anc(n, vector<int>(lgn, -1));

    for(i=1;i<n;i++) {
        int x;
        cin >> x;
        --x;

        anc[i][0] = x;
    }

    for(i=1;i<lgn;i++) {
        for(int node=0;node<n;node++) {
            if(anc[node][i-1] != -1) {
                anc[node][i] = anc[anc[node][i-1]][i-1];
            }
        }
    }

    auto findDis = [&](int node, int dis) {
        for(int i=0; (1 << i) <= dis; i++) {
            if((1 << i) & dis) {
                node = anc[node][i];
                if(node == -1) {
                    break;
                }
            }
        }

        return node;
    };

    int depth[n] = {0};
    for(i=1;i<n;i++) {
        depth[i] = depth[anc[i][0]] + 1;
    }
    debuga(depth, 0, n-1);

    while(q--) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        debug(a, b);

        if(depth[a] > depth[b]) {
            swap(a, b);
        }
        b = findDis(b, depth[b] - depth[a]);

        if(a == b) {
            cout << a+1 << "\n";
            continue;
        }

        debug(a, b);
        // int l=0, r=n-1, ans=-1;
        // while(l <= r) {
        //     int m = l + (r - l) / 2;
        //     debug(l, r, m);
        //     int lca = findDis(a, m);
        //     debug(lca);
        //     if(lca == findDis(b, m)) {
        //         ans = lca;
        //         r = m-1;
        //     }
        //     else {
        //         l = m+1;
        //     }
        // }
        for(int i=lgn-1;i>=0;i--) {
            int dis = 1 << i;
            int anca = findDis(a, dis);
            int ancb = findDis(b, dis);
            if(anca != ancb) {
                a = anca;
                b = ancb;
            }
        }


        cout << anc[a][0]+1 << "\n";

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