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
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

const int MAXN = 2e5+5;
int arr[MAXN], segTree[4 * MAXN];
int arraySize;

/*

    I approach
    unlike sum, we cannot find minimum from prefix array because if some minimum comes in range in [l, r] in prefix array, we cannot be sure that the minimum occured between l and r or before l
    we would have to use segment tree

    - create segment tree for minimums
    - process the queries

*/

void createSegmentTree(int segmentTreeIndex, int arrayLeft, int arrayRight) {
    if(arrayLeft == arrayRight) {
        segTree[segmentTreeIndex] = arr[arrayLeft];
        return;
    }

    int m = arrayLeft + (arrayRight - arrayLeft) / 2;
    createSegmentTree(2*segmentTreeIndex+1, arrayLeft, m);
    createSegmentTree(2*segmentTreeIndex+2, m+1, arrayRight);

    segTree[segmentTreeIndex] = min(segTree[2*segmentTreeIndex+1], segTree[2*segmentTreeIndex+2]);
}

int queryUtil(int segmentTreeIndex, int currentLeft, int currentRight, int queryLeft, int queryRight) {
    if(currentLeft >= queryLeft && currentRight <= queryRight) {
        return segTree[segmentTreeIndex];
    }

    if(queryLeft > currentRight || queryRight < currentLeft) {
        return INT_MAX;
    }

    int mid = currentLeft + (currentRight - currentLeft) / 2;
    int leftMin = queryUtil(2*segmentTreeIndex+1, currentLeft, mid, queryLeft, queryRight);
    int rightMin = queryUtil(2*segmentTreeIndex+2, mid+1, currentRight, queryLeft, queryRight);
    
    return min(leftMin, rightMin);
}

int query(int left, int right) {
    return queryUtil(0, 0, arraySize-1, left, right);
}

void solve() {

    int i, n, q;
    cin >> n >> q;
    arraySize = n;

    for(i=0;i<n;i++) {
        cin >> arr[i];
    }

    createSegmentTree(0, 0, arraySize-1);
    // for(i=0;i<2*n-1;i++) {
    //     if((i&(i-1)) == 0) cout << "\n";
    //     cout << segTree[i] << " , ";
    // }
    // cout << "\n";
    while(q--) {
        int l, r;
        cin >> l >> r;

        l--;
        r--;

        cout << query(l, r) << "\n";
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