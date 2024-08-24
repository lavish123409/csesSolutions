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
ll segTree[4 * MAXN];
int arraySize;

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

    segTree[in] = min(segTree[2*in+1], segTree[2*in+2]);
}

int queryUtil(int in, int cl, int cr, int ql, int qr) {
    if(ql <= cl && cr <= qr) {
        return segTree[in];
    }

    if(cr < ql || cl > qr) {
        return INT_MAX;
    }

    int m = cl + (cr - cl) / 2;
    return min(
        queryUtil(2*in+1, cl, m, ql, qr),
        queryUtil(2*in+2, m+1, cr, ql, qr)
    );
}

int query(int l, int r) {
    return queryUtil(0, 0, arraySize-1, l, r);
}

void updateUtil(int in, int cl, int cr, int ain, int val) {
    if(cl == cr) {
        segTree[in] = val;
        arr[ain] = val;
        return;
    }

    int m = cl + (cr - cl) / 2;
    if(cl <= ain && ain <= m) {
        updateUtil(2*in+1, cl, m, ain, val);
    }
    else {
        updateUtil(2*in+2, m+1, cr, ain, val);
    }

    segTree[in] = min(segTree[2*in+1], segTree[2*in+2]);
}

void update(int ind, int val) {
    updateUtil(0, 0, arraySize-1, ind, val);
}

void solve() {

    int n, q, i;
    cin >> n >> q;
    arraySize = n;

    for(i=0;i<n;i++) {
        cin >> arr[i];
    }

    createSegmentTree(0, 0, n-1);
    while(q--) {
        int qt, a, b;
        cin >> qt >> a >> b;
        switch(qt) {
            case 1:
                a--;
                update(a, b);
                break;
            case 2:
                a--;
                b--;

                cout << query(a, b) << "\n";
                break;
        }
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