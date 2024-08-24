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
    I am thinking that for a path either the path would be in
        - from a node to another node in a subtree -> we can directly go to this node
        - or, from a node to another node in a different subtree -> we would have to go towards ancestors, or in other words towards the lca, and then to that node

    so, in both the cases the path would go from lca of both nodes
    and if we would look at the structure of tree, lca would be at same level or above both nodes in level
    so, we can add the path count to every node
    that is, add 1 to lca for a and b
    and add -1 to children of a and b
    from root to leaves and count every path while traversing

    PROBLEM
    how would we know that we have to traverse +1 along which path to children?
    for ex, suppose node 1 have children 2,3,4 and there is one path along 2
    then we would also pass +1 to 3 and 4 also
    if we would maintain the array for it that we need to traverse [+1, 0, 0], according to children [2, 3, 4]
    then, how would we know that we have to traverse +1 to which children of 2?

    FIX
    we can do +1 at leaves and -1 at parent of lca, or -2 if lca != a and lca != b
    and traverse the tree from leaves to root
    and also, we should also traverse the tree in topoplogical sort, so that we process any node only then, when traversal from all leaves have reached it

    WA
    didn't realized that we are passing number of paths from leaves to parents, if some path is ending at some node, i.e, lca then its parent also should nullify the paths coming from its child
    that is, if lca is one of the nodes, then it is 1 path going from lca to its parent, so we should nullify it with -1
    and if lca is not one of the nodes, then 2 paths were coming from both nodes, but we cancelled 1 at lca, and second one we should nullify at parent
    in essence, we have to cancel all paths at parent which are ending at its child

*/
string ps = "\n";

void dfs(vector<int> adj[], int u, int par, int lgn, vector<vector<int>>& anc, vector<int>& depth) {

    depth[u] = par == -1 ? 0 : depth[par] + 1;
    anc[u][0] = par;
    for(int i=1;i<lgn;i++) {
        if(anc[u][i-1] != -1) {
            anc[u][i] = anc[anc[u][i-1]][i-1];
        }
    }
    for(int v : adj[u]) {
        if(v != par) {
            dfs(adj, v, u, lgn, anc, depth);
        }
    }
}

int findAnc(int node, int dis, vector<vector<int>>& anc) {
    for(int i=0;(1 << i) <= dis; i++) {
        if((1 << i) & dis) {
            node = anc[node][i];
        }
        if(node == -1) {
            break;
        }
    }

    return node;
}

int findLca(int a, int b, int lgn, vector<vector<int>>& anc, vector<int>& depth) {
    if(depth[a] > depth[b]) {
        swap(a, b);
    }

    int i;
    b = findAnc(b, depth[b] - depth[a], anc);

    if(a == b) {
        return a;
    }

    for(i=lgn-1;i>=0;i--) {
        int ancA = findAnc(a, (1 << i), anc);
        int ancB = findAnc(b, (1 << i), anc);
        if(ancA != ancB) {
            a = ancA;
            b = ancB;
        }
    }

    return anc[a][0];
}

void solve() {
    
    int n, m;
    cin >> n >> m;

    int lgn = ceil(log2(n)) + 1;
    // int anc[n][lgn];
    // memset(anc, -1, sizeof(anc));

    int i;
    vector<int> adj[n], depth(n), deg(n);
    vector<vector<int>> anc(n, vector<int>(lgn, -1));
    for(i=0;i<n-1;i++) {
        int u, v;
        cin >> u >> v;

        --u, --v;
        deg[u]++;
        deg[v]++;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    deg[0]++;
    debug(deg);

    dfs(adj, 0, -1, lgn, anc, depth);

    vector<int> ans(n);
    while(m--) {
        int u, v;
        cin >> u >> v;
        --u, --v;

        int lca = findLca(u, v, lgn, anc, depth);
        debug(u, v, lca);
        ans[u]++;
        ans[v]++;
        ans[lca]--;

        if(anc[lca][0] != -1) {
            // int par = anc[lca][0];
            // ans[par] += (lca != u && lca != v) ? -2 : -1;
            ans[anc[lca][0]] += -1;
        }
    }
    debug(ans);

    queue<array<int,2>> q;
    // vector<int> ans2(n);
    for(i=0;i<n;i++) {
        if(deg[i] == 1) {
            deg[i]--;
            q.push({i, ans[i]});
            // ans[i] = 0;
        }
    }

    while(!q.empty()) {
        int u = q.front()[0];
        int np = q.front()[1];
        q.pop();

        // ans[u] += np;

        int par = anc[u][0];
        if(par != -1) {
            deg[par]--;
            ans[par] += np;
            if(deg[par] == 1) {
                debug(u, par, ans[u]);
                q.push({par, ans[par]});
                // q.push({par, np});
            }
        }
        debug(u, np, par, deg, ans);
    }

    for(i=0;i<n;i++) {
        cout << ans[i] << " ";
    }
    cout << "\n";

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