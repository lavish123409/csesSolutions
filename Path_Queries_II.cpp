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
 
    peeked the solution, even then also not able to solve the problem
    we just have to think of representing tree paths by the means of array intervals
    thought about one approach
        - enter the node in euler tour before visiting any child
        - then for any node, the root node would be at depth[node] distance left of node in tour
    but the problem was when we would have to update the values, we would have to update it at every position of that node in the tour, which can be O(n)

    the solution is to store the complete sum of paths in euler tour
    and while updating, all descendats value of node to be updated with x, will be updated with x - value[node]

    in fenwick trees, the range update from [l,r] with x would be
        - upd(l, x)
        - upd(r+1, -x)
    

*/
string ps = "\n";

class Segtree {
private:
    vector<int> st;
    int n;

public:
    Segtree(vector<int>& arr) {
        n = arr.size();
        st.resize(2*n+1);
        build(arr, 0, 0, n-1);
    }

    void build(vector<int>& arr, int in, int cl, int cr) {
        if(cl == cr) {
            st[in] = arr[cl];
            return;
        }

        int m = cl + (cr - cl) / 2;
        build(arr, 2*in+1, cl, m);
        build(arr, 2*in+2, m+1, cr);

        st[in] = max(st[2*in+1], st[2*in+2]);
    }

    void updateUtil(int in, int cl, int cr, int ind, int val) {
        if(cl > ind || cr < ind) {
            return;
        }

        if(cl == cr) {
            st[in] = val;
            // arr[cl] = val;
            return;
        }

        int m = cl + (cr - cl) / 2;
        if(ind <= m) {
            updateUtil(2*in+1, cl, m, ind, val);
        }
        else {
            updateUtil(2*in+2, m+1, cr, ind, val);
        }

        st[in] = max(st[2*in+1], st[2*in+2]);
    }

    void update(int ind, int val) {
        updateUtil(0, 0, n-1, ind, val);
    }

    int query(int in, int cl, int cr, int ql, int qr) {
        if(ql <= cl && cr <= qr) {
            return st[in];
        }

        if(cl > qr || cr < ql) {
            return INT_MIN;
        }

        int m = cl + (cr - cl) / 2;
        return max(query(2*in+1, cl, m, ql, qr), query(2*in+2, m+1, cr, ql, qr));
    }

    int qry(int ql, int qr) {
        return query(0, 0, n-1, ql, qr);
    }
};

const int MAXN = int(2e5+5);
const int LOGN = 17;
int tin[MAXN], tout[MAXN];
int subtreeSize[MAXN], heavy[MAXN], value[MAXN], ancestor[MAXN][LOGN];
int chainIndex[MAXN], chainNumber[MAXN];
int depth[MAXN];
// vector<Segtree> segtree;
// vector<vector<array<int,2>>> chains;
// vector<vector<int>> chains;
int timer=0;
int segtree[4*MAXN];

void update(int in, int cl, int cr, int ind, int val) {
    if(cl > ind || cr < ind) {
        return;
    }
    
    if(cl == cr) {
        segtree[in] = val;
        return;
    }

    int m = cl + (cr - cl) / 2;
    if(ind <= m) {
        update(2*in+1, cl, m, ind, val);
    }
    else {
        update(2*in+2, m+1, cr, ind, val);
    }

    segtree[in] = max(segtree[2*in+1], segtree[2*in+2]);
}

int query(int in, int cl, int cr, int ql, int qr) {
    if(cl > qr || cr < ql) {
        return INT_MIN;
    }

    if(ql <= cl && cr <= qr) {
        return segtree[in];
    }

    int m = cl + (cr - cl) / 2;
    return max(
        query(2*in+1, cl, m, ql, qr),
        query(2*in+2, m+1, cr, ql, qr)
    );
}

void dfs(vector<int> adj[], int u, int par) {
    tin[u] = timer++;

    ancestor[u][0] = par;
    // for(int i=1;i<LOGN;i++) {
    //     ancestor[u][i] = ancestor[ancestor[u][i-1]][i-1];
    // }
    subtreeSize[u] = 1;
    int mxstsz = 0;
    // depth[u] = depth[par] + 1;

    for(int v : adj[u]) {
        if(v == par) continue;

        depth[v] = depth[u] + 1;
        dfs(adj, v, u);
        subtreeSize[u] += subtreeSize[v];
        if(subtreeSize[v] > mxstsz) {
            mxstsz = subtreeSize[v];
            heavy[u] = v;
        }
    }

    tout[u] = timer++;
}

int chind = 1;
int head[MAXN];
void getChains(vector<int> adj[], int u, int par, int chead) {
    // chainNumber[u] = chind;
    // if(chind == chains.size()) {
    //     // chains.push_back({{u, value[u]}});
    //     chains.push_back({value[u]});
    //     chainIndex[u] = 0;
    // }
    // else {
    //     // chains[chind].push_back({u, value[u]});
    //     chains[chind].push_back(value[u]);
    //     chainIndex[u] = chains[chind].size() - 1;
    // }
    chainIndex[u] = chind++;
    head[u] = chead;

    if(heavy[u] != -1) {
        getChains(adj, heavy[u], u, chead);
    }

    for(int v : adj[u]) {
        if(v == par || v == heavy[u]) continue;

        getChains(adj, v, u, v);
    }

}

void modify(int n, int p, int value) {  // set value at position p
  for (segtree[p += n] = value; p > 1; p >>= 1) segtree[p>>1] = max(segtree[p], segtree[p^1]);
}

int query(int n, int l, int r) {  // sum on interval [l, r)
  int res = 0;
  for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = max(res, segtree[l++]);
    if (r&1) res = max(res, segtree[--r]);
  }
  return res;
}

// int getNodeAtK(int node, int dis) {

//     for(int i=0; (1 << i) < LOGN; i++) {
//         if((1 << i) & dis) {
//             node = ancestor[node][i];
//         }
//     }

//     return node;
// }

// bool isAncestor(int u, int v) {
//     return tin[u] <= tin[v] && tout[v] <= tout[u];
// }

// int getLca(int a, int b) {
//     // if(depth[a] > depth[b]) swap(a, b);

//     if(isAncestor(a, b)) return a;
//     if(isAncestor(b, a)) return b;

//     for(int i=LOGN-1; i >= 0; i--) {
//         // int ancNode = getNodeAtK(a, (1 << i));
//         // if(!isAncestor(ancNode, b)) {
//         //     a = ancNode;
//         // }
//         if(!isAncestor(ancestor[a][i], b)) a = ancestor[a][i];
//     }

//     return ancestor[a][0];
// }

// int getMaxValue(int a, int b) {
//     int ans = 0;
//     while(chainNumber[b] != chainNumber[a]) {
//         ans = max(ans, value[b]);
//         b = ancestor[b][0];
//     }

//     // ans = max(ans, segtree[chainNumber[b]].qry(chainIndex[a], chainIndex[b]));

//     return ans;
// }

void solve() {
    
    // memset(heavy, -1, sizeof(heavy));
    int i, n, q;
    cin >> n >> q;

    for(i=0;i<n;i++) {
        cin >> value[i];
        heavy[i] = -1;
    }

    vector<int> adj[n];
    for(i=1;i<n;i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(adj, 0, 0);
    getChains(adj, 0, 0, 0);

    for(i=0;i<n;i++) {
        // cout << i << " -> " << chainIndex[i] << " : " << value[i] << " , " << head[i] << " , " << depth[i] << "\n";
        // update(0, 0, n-1, chainIndex[i], value[i]);
        modify(n, chainIndex[i], value[i]);
    }

    // for(i=0;i<2*n-1;i++) {
    //     // cout << i << " -> " << chainIndex[i] << " : " << value[i] << " , " << head[i] << " , " << depth[i] << "\n";
    //     // update(0, 0, n-1, chainIndex[i], value[i]);
    //     // modify(n, chainIndex[i], value[i]);
    //     cout << segtree[i] << " ";
    // }
    // cout << "\n";

    // delete subtreeSize; 
    // delete heavy;

    // segtree = vector<Segtree>(chains.size());
    // for(i=0;i<chains.size();i++) {
    //     segtree[i] = Segtree(chains[i]);
    // }
    // for(auto& chain : chains) {
    //     segtree.push_back(Segtree(chain));
    // }

    // vector<vector<int>>().swap(chains);
    // for(i=0;i<n;i++) {
    //     cout << chainNumber[i] << " : " << chainIndex[i] << "\n";
    // }
    // for()

    while(q--) {
        int t;
        cin >> t;

        if(t == 1) {
            int node, val;
            cin >> node >> val, --node;

            // segtree[chainNumber[node]].update(chainIndex[node], val);
            // update(0, 0, n-1, chainIndex[node], val);
            modify(n, chainIndex[node], val);
            // cout << query(n, chainIndex[node], chainIndex[node]) << " <- u\n";
            value[node] = val;
        }
        else {
            int u, v;
            cin >> u >> v;
            --u, --v;
            // cout << u << " , " << v << "\n";
            // cout << head[u] << " , " << head[v] << "\n";

            // int lca = getLca(u, v);
            // cout << max(getMaxValue(lca, u), getMaxValue(lca, v)) << " "; 
            int ans = 0;
            for(; head[u] != head[v]; v=ancestor[v][0]) {
                if(depth[head[u]] > depth[head[v]]) swap(u, v);
                // cout << u << " , " << v << "\n";
                // cout << head[u] << " , " << head[v] << "\n";

                // ans = max(ans, query(0, 0, n-1, chainIndex[head[v]], chainIndex[v]));
                ans = max(ans, query(n, chainIndex[head[v]], chainIndex[v]));
                v = head[v];
            }
            if(depth[u] > depth[v]) swap(u, v);
            // cout << u << " , " << v << "\n";

            // ans = max(ans, query(0, 0, n-1, chainIndex[u], chainIndex[v]));
            ans = max(ans, query(n, chainIndex[u], chainIndex[v]));

            cout << ans << " ";

        }
    }


    // for(auto chain : chains) {
    //     for(auto [node, val] : chain) {
    //         cout << node << " : " << val << " , ";
    //     }
    //     cout << "\n";
    // }

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