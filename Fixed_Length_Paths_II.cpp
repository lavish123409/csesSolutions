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

    Solution
    we can use previous question's solution
    just instead of storing the count of nodes in an array, we would store its prefix sums in the array
    and find the count of nodes having depth k2 - d and subtract the count of nodes having depth k1-d - 1, if d <= k1

    WA1
    submitted wrong code

    TLE1
    although main problem for TLE was the extra log factor coming in computations of fenwick trees, but also was not initializing maxdepth to 0, when calling main findAns function
    if we would not initialize max depth, then it would remain maximum possible for all smaller trees also, increasing time to clean the fenwick tree

    ultimately, copying the USACO code of using partial sums made it accepted
    idea of partial sums
        - first, get the count of node values having depth d, for current child's subtree
        - then in starting, partial sum would have the sum of nodes having depths in range [a-1, b-1], encountered till now
        - then, as we would increase the depth, we would add count[depth[a-2]] and subtract count[depth[b-1]], making partial sum representing range of [a-2, b-2]
        - then after going through all ranges, add the count of nodes having depths in range [a-1, b-1] to the partial_sum_init, to initialise for next iteration
        - and, also add the current node depth values to total count array
*/
string ps = "\n";

const int MAXN = int(2e5+5);
const int MAXDEPTH = 18;

int sbt[MAXN], isRemoved[MAXN], cnt[MAXN];
ll ans=0ll;
int a, b, maxDepth;

void upd(int ind, int val) {
    for(ind++; ind < MAXN; ind += (ind & -ind)) {
        cnt[ind] += val;
    }
}

int qry(int ind) {
    int ans = 0;
    for(ind++; ind > 0; ind -= (ind & -ind)) {
        ans += cnt[ind];
    }

    return ans;
}

int dfs(vector<int> adj[], int u, int par) {
    sbt[u] = 1;
    for(int v : adj[u]) {
        if(v == par || isRemoved[v]) continue;

        sbt[u] += dfs(adj, v, u);
    }

    return sbt[u];
}

int findCentroid(vector<int> adj[], int u, int par, int tn) {
    for(int v : adj[u]) {
        if(v != par && !isRemoved[v] && sbt[v] * 2 > tn) {
            return findCentroid(adj, v, u, tn);
        }
    }

    return u;
}

void findAns(vector<int> adj[], int u, int par, int depth, bool contri) {

    if(b < depth) return;
    maxDepth = max(maxDepth, depth);

    if(contri) {
        // cnt[depth] += cnt[depth-1];
        // ans += cnt[b - depth];
        debug(u, par);
        debug(qry(b - depth));
        debug(qry(a - depth - 1));
        ans += qry(b - depth);
        if(a > depth) {
            // ans -= cnt[a - depth - 1];
            ans -= qry(a - depth - 1);
        }
    }
    else {
        // cnt[depth] = (cnt[depth] + 1 + cnt[depth-1]);
        // cnt[depth]++;
        upd(depth, 1);
    }

    for(int v : adj[u]) {
        if(v != par && !isRemoved[v]) {
            findAns(adj, v, u, depth+1, contri);
        }
    }

}



void findAns(vector<int> adj[], int u, int par) {

    int tn = dfs(adj, u, par);
    int centroid = findCentroid(adj, u, par, tn);
    // cnt[0] = 1;
    maxDepth = 0;
    upd(0, 1);

    for(int v : adj[centroid]) {
        if(!isRemoved[v]) {
            findAns(adj, v, centroid, 1, 1);
            findAns(adj, v, centroid, 1, 0);
        }
    }
    debug(u, par);
    debug(centroid);
    debug(ans);
    isRemoved[centroid] = 1;
    upd(0, -1);
    for(int i=1;i<=maxDepth; i++) {
        // cnt[i] = 0;
        upd(i, qry(i-1)-qry(i));
    }
    // for(int i=0;i<=maxDepth;i++) {
        // cnt[i] = 1;
    //     cnt[i] = 0;
    // }

    for(int v : adj[centroid]) {
        if(!isRemoved[v]) {
            findAns(adj, v, centroid);
        }
    }
}

int totalCnt[MAXN]{1};
int subtreeDepth = 0;

void getCount(vector<int> adj[], int u, int par, int d=1) {
    if(d > b) return;
    cnt[d]++;
    subtreeDepth = max(subtreeDepth, d);

    for(int v : adj[u]) {
        if(v != par && !isRemoved[v]) getCount(adj, v, u, d+1);
    }
}

void getAns(vector<int> adj[], int u, int par) {

    int centroid = findCentroid(adj, u, par, dfs(adj, u, par));
    isRemoved[centroid] = 1;
    ll partial_sum_init = (a == 1 ? 1ll : 0ll), partial_sum;
    int mxDepth = 0;

    for(int v : adj[centroid]) {
        if(!isRemoved[v]) {

            subtreeDepth = 0;
            getCount(adj, v, centroid);

            partial_sum = partial_sum_init;
            for(int depth=1; depth <= subtreeDepth; depth++) {
                ans += partial_sum * cnt[depth];

                int drem = b - depth;
                if(drem >= 0) partial_sum -= totalCnt[drem];

                int dadd = a - depth - 1;
                if(dadd >= 0) partial_sum += totalCnt[dadd];
            }

            for(int depth=a-1; depth <= b-1 && depth <= subtreeDepth; depth++) {
                partial_sum_init += cnt[depth];
            }

            for(int depth=1; depth <= subtreeDepth; depth++) {
                totalCnt[depth] += cnt[depth];
            }

            mxDepth = max(mxDepth, subtreeDepth);
            fill(cnt, cnt+subtreeDepth+1, 0);
        }
    }
    fill(totalCnt+1, totalCnt + mxDepth + 1, 0);
    for(int v : adj[centroid]) {
        if(!isRemoved[v]) {
            getAns(adj, v, centroid);
        }
    }

}

void solve() {
    // for(int i=0;i<MAXN;i++) {
    //     cnt[i] = 1;
    // }

    int i, n;
    cin >> n >> a >> b;

    vector<int> adj[n];
    for(i=1;i<n;i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // findAns(adj, 0, -1);
    getAns(adj, 0, -1);
    cout << ans << "\n";

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

// #include <bits/stdc++.h>
// typedef long long ll;
// using namespace std;

// int n, a, b;
// vector<int> graph[200001];
// int subtree[200001];

// ll ans = 0, bit[200001];
// int total_cnt[200001]{1}, mx_depth;
// int cnt[200001], subtree_depth;
// bool processed[200001];

// int get_subtree_sizes(int node, int parent = 0) {
// 	subtree[node] = 1;
// 	for (int i : graph[node])
// 		if (!processed[i] && i != parent)
// 			subtree[node] += get_subtree_sizes(i, node);
// 	return subtree[node];
// }

// int get_centroid(int desired, int node, int parent = 0) {
// 	for (int i : graph[node])
// 		if (!processed[i] && i != parent && subtree[i] >= desired)
// 			return get_centroid(desired, i, node);
// 	return node;
// }

// void get_cnt(int node, int parent, int depth = 1) {
// 	if (depth > b) return;
// 	subtree_depth = max(subtree_depth, depth);
// 	cnt[depth]++;
// 	for (int i : graph[node])
// 		if (!processed[i] && i != parent) get_cnt(i, node, depth + 1);
// }

// void centroid_decomp(int node = 1) {
// 	int centroid = get_centroid(get_subtree_sizes(node) >> 1, node);
//     debug(centroid);
// 	processed[centroid] = true;
// 	mx_depth = 0;
// 	long long partial_sum_init = (a == 1 ? 1ll : 0ll);
// 	for (int i : graph[centroid])
// 		if (!processed[i]) {
// 			subtree_depth = 0;
// 			get_cnt(i, centroid);
//             debug(i, subtree_depth);
//             debuga(cnt, 0, subtree_depth);

// 			long long partial_sum = partial_sum_init;
//             debug(partial_sum_init, partial_sum);
// 			for (int depth = 1; depth <= subtree_depth; depth++) {
// 				ans += partial_sum * cnt[depth];
//                 debug(depth, cnt[depth], ans, partial_sum);

// 				int dremove = b - depth;
// 				if (dremove >= 0) partial_sum -= total_cnt[dremove];
//                 if (dremove >= 0) debug(total_cnt[dremove]);
//                 debug(dremove, partial_sum);

// 				int dadd = a - (depth + 1);
// 				if (dadd >= 0) partial_sum += total_cnt[dadd];
//                 if (dadd >= 0) debug(total_cnt[dadd]);
//                 debug(dadd, partial_sum);
// 			}

// 			for (int depth = a - 1; depth <= b - 1 && depth <= subtree_depth; depth++) {
//                 debug(depth, cnt[depth], partial_sum_init);
// 				partial_sum_init += cnt[depth];
//                 debug(depth, cnt[depth], partial_sum_init);
//             }

// 			for (int depth = 1; depth <= subtree_depth; depth++) {
//                 debug(depth, cnt[depth], total_cnt[depth]);
// 				total_cnt[depth] += cnt[depth];
//             }
// 			mx_depth = max(mx_depth, subtree_depth);
//             debuga(total_cnt, 0, mx_depth);

// 			fill(cnt, cnt + subtree_depth + 1, 0);
// 		}
// 	fill(total_cnt + 1, total_cnt + mx_depth + 1, 0);
// 	for (int i : graph[centroid])
// 		if (!processed[i]) centroid_decomp(i);
// }

// int main() {
// 	cin.tie(0)->sync_with_stdio(0);
// 	cin >> n >> a >> b;
// 	for (int i = 1; i < n; i++) {
// 		int u, v;
// 		cin >> u >> v;
// 		graph[u].push_back(v);
// 		graph[v].push_back(u);
// 	}
// 	centroid_decomp();
// 	cout << ans;
// 	return 0;
// }