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
 
    approach I -
    we can observe that for maximum subarray, the right end would be having maximum prefix sum
    and the left end would be having minimum prefix sum
    if left end's prefix sum is positive then we can ignore it as at index -1, we would be having 0 sum
      3 _ _ _ _ 10 _ _ _
    0 3 _ _ _ _ 12 _ _ _

    so, we can take prefix sum array, and make maximum and minimum segment tree on it
    in query, first we would update all maximums and minimums from k+1 to n-1
    then, we would find maximum in range 0 to n-1, lets say mxi
    and then, we would find minimum in range 0 to mxi
    if minimum is negative, subtract it from maximum
    otherwise, print just the maximum, as (maximum - 0)

    maybe it can happen that maximum subarray sum is not present on left side of maximum prefix sum
    like it can happen that in starting prefix sum is becoming negative, now even if we would add some positive numbers after lot of negative numbers, the prefix sum would still be negative, but positive numbers can result in maximum subarray sum
    for ex
    arr = {-4,-2,-1,-7,3,3,-6,-8,-9,9}
    psm = {-4,-6,-7,-14,-11,-8,-14,-22,-31,-22}
    here, even though maximum subarray sum is 6 from index 4-5, but maximum prefix sum is -4 at index 0
    not correct

    we can take minimum prefix sum also, and try to find any maximum sum on right side
    same problem, what if maximum subarray sum does not exist both at maximum or minimum prefix sum
    for ex
    arr = {-4,-2,-1,-7,3,3,0,-8,-9,2}
    psm = {-4,-6,-7,-14,-11,-8,-8,-16,-25,-23}
    maximum prefix sum is at 0, i.e, -4 and
    minimum prefix sum is at 8, i.e, -25
    but maximum subarray sum is at 4-5, i.e, 6

    Solution - look for Subarray Sum Queries in https://codeforces.com/blog/entry/77128
    Main essence
    we know that, if we want to know max subarray sum for range [l,r]
    - it can be the max subarray sum of [l,mid], or left child
    - it can be the max subarray sum of [mid+1, r], or right child
    - it can be in the range overlapping both children,i.e, [p,q] where p <= mid && mid < q

    for first 2 cases, we cna take max sum from children
    for third case, 
    among all possible, [p,mid] range we can choose p(l<=p<=mid) such that sum of elements in range [p,mid] is maximized and 
    similarly among all possible values of q(mid+1<=q<=r) we should choose q such that sum of elements in range [mid+1,q] is maximized, 
    maximizing these two individually is equivalent to maximizing [p,q].

    lets define
    G = max subarray sum in range [l,r]
    L = max subarray sum in range [l,r] including a_l
    R = max subarray sum in range [l,r] including a_r
    S = total sum in range [l,r]

    now, max sum can be calculated as
    node.G = max(u.G, v.G, u.r+v.L)

    for max subarray sum in range [l,r] including a_l, we can either take 
    u.L - max subarray sum in range [l,mid] including a_l for left child
    other than this, no other maximum subarray sum can end in left child, otherwise it would have already been in u.L
    so, this time the array would have to end in right child subarray
    means, we have to include v.L - max subarray sum in range [mid+1, r] including a_(mid+1) for right child
    node.L = max(u.L, u.S + v.L)

    similarly, for R and S


*/
string ps = "\n";
 
typedef struct {
    ll G;
    ll L;
    ll R;
    ll S;
} node;

const int MAXN = 2e5+5;
ll arr[MAXN];
node segTree[4 * MAXN];
int arraySize;

void createSegmentTree(int in, int cl, int cr) {
    if(cl == cr) {
        segTree[in] = {arr[cl], arr[cl], arr[cl], arr[cl]};
        return;
    }

    int m = cl + (cr - cl) / 2;
    createSegmentTree(2*in+1, cl, m);
    createSegmentTree(2*in+2, m+1, cr);

    int lin = 2*in+1;
    int rin = 2*in+2;
    node n = segTree[in];
    node u = segTree[lin];
    node v = segTree[rin];
    
    n.G = max({u.G, v.G, u.R + v.L});
    n.L = max(u.L, u.S + v.L);
    n.R = max(v.R, u.R + v.S);
    n.S = u.S + v.S;

    segTree[in] = n;
}

void update(int in, int cl, int cr, int ind, ll val) {
    if(cl == cr) {
        segTree[in] = {val, val, val, val};
        arr[cl] = val;
        return;
    }

    int m = cl + (cr - cl) / 2;
    if(ind <= m) {
        update(2*in+1, cl, m, ind, val);
    }
    else {
        update(2*in+2, m+1, cr, ind, val);
    }

    int lin = 2*in+1;
    int rin = 2*in+2;
    node n = segTree[in];
    node u = segTree[lin];
    node v = segTree[rin];
    
    n.G = max({u.G, v.G, u.R + v.L});
    n.L = max(u.L, u.S + v.L);
    n.R = max(v.R, u.R + v.S);
    n.S = u.S + v.S;

    segTree[in] = n;
}

node query(int in, int cl, int cr, int ql, int qr) {
    if(ql <= cl && cr <= qr) {
        return segTree[in];
    }

    if(cl > qr || cr < ql) {
        return {0ll, 0ll, 0ll, 0ll};
    }

    int m = cl + (cr - cl) / 2;
    node u = query(2*in+1, cl, m, ql, qr);
    node v = query(2*in+2, m+1, cr, ql, qr);

    return {
        max({u.G, v.G, u.R + v.L}),
        max(u.L, u.S + v.L),
        max(v.R, u.R + v.S),
        u.S + v.S
    };
}
 
void solve() {
 
    int i, n, q;
    cin >> n >> q;
    // cout << n << " : " << q << "\n";
    arraySize = n;
    
    for(i=0;i<n;i++) {
        cin >> arr[i];
    }

    createSegmentTree(0, 0, n-1);

    while(q--) {
        int k, x;
        cin >> k >> x;
        k--;

        update(0, 0, n-1, k, x);

        cout << max(segTree[0].G, 0ll) << "\n";
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