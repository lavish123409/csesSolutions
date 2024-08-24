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
int arr[MAXN];
int segTree[4 * MAXN];
int arraySize;

string ps = "\n";

/*

    I approach
    we would have to use segment tree
    

*/

void createSegmentTree(int in, int cl, int cr) {
    if(cl == cr) {
        segTree[in] = arr[cl];
        return;
    }

    int m = cl + (cr - cl) / 2;
    createSegmentTree(2*in+1, cl, m);
    createSegmentTree(2*in+2, m+1, cr);

    segTree[in] = segTree[2*in+1] ^ segTree[2*in+2];
}

int queryUtil(int in, int cl, int cr, int ql, int qr) {
    // ps.push_back('\t');
    // cout << ps << cl << " , " << cr << " : " << ql << " , " << qr;
    if(ql <= cl && cr <= qr) {
        // cout << ps << "f: " << segTree[in];
        // ps.pop_back(); 
        return segTree[in];
    }

    if(cr < ql || cl > qr) {
        // cout << "o: ";
        // ps.pop_back(); 
        return 0;
    }

    int m = cl + (cr - cl) / 2;
    int lxor = queryUtil(2*in+1, cl, m, ql, qr);
    int rxor = queryUtil(2*in+2, m+1, cr, ql, qr);

    // cout << ps << "lxor: " << lxor;
    // cout << ps << "rxor: " << rxor;
    // ps.pop_back();
    return lxor ^ rxor;
}

int query(int l, int r) {
    return queryUtil(0, 0, arraySize-1, l, r);
}

void printSegTree() {
    int layer = arraySize; // n smallest power of 2 that great than or equal to the size of seg_tree
    for (int i = 0; i < 2 * arraySize - 1; i++) {
        cout << setw(layer) << segTree[i] << " ";
        if (__builtin_popcount(i + 2) == 1) {
            layer /= 2;
            cout << "\n";
        }

    }
    cout << "\n";
}

void solve() {

    int i, n, q;
    cin >> n >> q;
    arraySize = n;

    for(i=0;i<n;i++) {
        cin >> arr[i];
    }

    createSegmentTree(0, 0, n-1);
    // printSegTree();
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