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
 
    solution
    use Mo's algorithm
    divide the array into sqrt(n) blocks, and find number of distinct values for every block
    now sort every query in a specific order
    left endpoint according to the block_id and then right endpoint in increasing order
    and then use 2 pointer approach to keep adding elements from right and removing elements from left 

    solution - https://usaco.guide/problems/cses-1734-distinct-values-queries/solution
    idea is to mark 1 only for those indices, which are leftmost index for a number
    in this way, when we are traversing the array from right to left, we are sure that only those indices are marked as 1, which contain a distinct value
    and we would find sum till right endpoint of query, we can find what all indices are marked as 1 from current (which is left endpoint of query) index to right endpoint of query
    thereby, giving us distinct value from left to right endpoint of query


*/
string ps = "\n";

const int MAXN = 2e5+5;
ll arr[MAXN];
// node segTree[4 * MAXN];
int arraySize;

int bit[MAXN];
vector<int> vals;

int getIndex(int n) {
    return upper_bound(vals.begin(), vals.end(), n) - vals.begin();
}

void ad(int x, int dff) {
    x++;
    for(;x < MAXN; x += (x & -x)) {
        bit[x] += dff;
    }
}

int qr(int x) {
    x++;
    int ans = 0;
    for(;x>0;x -= (x & -x)) {
        ans += bit[x];
    }

    return ans;
}

 
void solve1() {
 
    int i, n, q;
    cin >> n >> q;
    // cout << n << " : " << q << "\n";
    arraySize = n;
    
    int sr = sqrt(n);
    // vals.resize(n);
    for(i=0;i<n;i++) {
        cin >> arr[i];
        // vals[i] = arr[i];
    }

    // sort(vals.begin(), vals.end());

    array<int,3> qrs[q];
    for(i=0;i<q;i++) {
        cin >> qrs[i][0] >> qrs[i][1];
        qrs[i][0]--;
        qrs[i][1]--;
        qrs[i][2] = i;
    }
    debuga(qrs,0,q-1);

    sort(qrs, qrs+q, [&](const array<int,3>& a, const array<int,3>& b) {
        // int aid = a[0] / sr;
        // int bid = b[0] / sr;

        // return aid < bid || (aid == bid && a[1] < b[1]);
        return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]);
    });

    debuga(arr,0,n-1);
    debuga(qrs,0,q-1);

    vector<int> ans(q);
    int l=0, r=0;
    multiset<int> el;
    int dt=0;
    for(i=0;i<q;i++) {
        int li = qrs[i][0];
        int ri = qrs[i][1];
        // cout << li+1 << " , " << ri+1 << " : ";
        debug(l,r,li,ri);

        if(ri >= r) {
            while(r <= ri && r < n) {
                debug(1, r, ri, dt, arr[r]);
                debug(el);
                if(el.find(arr[r]) == el.end()) dt++;
                el.insert(arr[r]);
                debug(el);
                debug(1, r, ri, dt);
                // ad(getIndex(arr[r]), 1);
                r++;
            }
            while(l < li) {
                debug(2, l, li, dt, arr[l]);
                debug(el);
                el.erase(el.find(arr[l]));
                if(el.find(arr[l]) == el.end()) dt--;
                debug(el);
                debug(2, l, li, dt);
                // ad(getIndex(arr[l]), -1);
                // dt--;
                l++;
            }
            // ans[qrs[i][2]] = int(el.size());
            // ans[qrs[i][2]] = qr(n);
            ans[qrs[i][2]] = dt;
        }
        else {
            r--;
            while(r >= n) r--;
            while(r > ri) {
                debug(3, r, ri, dt, arr[r]);
                debug(el);
                el.erase(el.find(arr[r]));
                if(el.find(arr[r]) == el.end()) dt--;
                debug(el);
                debug(3, r, ri, dt);
                // ad(getIndex(arr[r]), 1);
                if(r-1 == ri) break;
                r--;
            }
            while(l < li) {
                debug(4, l, li, dt, arr[l]);
                debug(el);
                el.erase(el.find(arr[l]));
                if(el.find(arr[l]) == el.end()) dt--;
                debug(el);
                debug(4, l, li, dt);
                // ad(getIndex(arr[l]), -1);
                l++;
            }
            // ans[qrs[i][2]] = int(el.size());
            // ans[qrs[i][2]] = qr(n);
            ans[qrs[i][2]] = dt;
        }
        // cout << ans[qrs[i][2]] << "\n";
    }

    for(i=0;i<q;i++) {
        cout << ans[i] << "\n";
    }
}

void solve() {
    int i, n, q;
    cin >> n >> q;

    for(i=0;i<n;i++) {
        cin >> arr[i];
    }

    vector<vector<array<int,2>>> qrs(n);
    for(i=0;i<q;i++) {
        int a, b;
        
        cin >> a >> b;
        a--;
        b--;

        qrs[a].push_back({b, i});
    }

    // sort(qrs.begin(), qrs.end());
    debug(qrs);

    map<int,int> last_index;
    vector<int> ans(q);
    for(i=n-1;i>=0;i--) {
        int a = arr[i];
        if(last_index.count(a)) ad(last_index[a], -1); 

        last_index[a] = i;
        ad(i, 1);

        for(auto& [r, ind] : qrs[i]) {
            debug(i, r, ind);
            ans[ind] = qr(r);
        }
    }

    for(i=0;i<q;i++) {
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