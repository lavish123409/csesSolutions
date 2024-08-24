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
 
 
 
/*
 
    make a prefix array from given array
    make a segment tree on prefix array, and when updating index k, do range update from k to end
    max query would not have any change
 
*/
string ps = "\n";
 
 
const int MAXN = 2e5+5;
ll arr[MAXN];
ll segTree[4 * MAXN];
ll lazy[4 * MAXN];
int arraySize;
 
void createSegmentTree(int in, int cl, int cr) {
    if(cl == cr) {
        segTree[in] = arr[cl];
        lazy[in] = 0;
        return;
    }
 
    int m = cl + (cr - cl) / 2;
    createSegmentTree(2*in+1, cl, m);
    createSegmentTree(2*in+2, m+1, cr);
 
    segTree[in] = max(segTree[2*in+1], segTree[2*in+2]);
}
 
void updateUtil(int in, int cl, int cr, int ql, int qr, int dff) {
    // cout << cl << " , " << cr << " : ";
    // cout << ql << " , " << qr << " = ";
    // cout << dff << "\n";
    if(lazy[in] != 0) {
        segTree[in] += (1ll * lazy[in]);
        if(cl != cr) {
            lazy[2*in+1] += lazy[in];
            lazy[2*in+2] += lazy[in];
        }
        else {
            arr[cl] += dff;
        }
        lazy[in] = 0;
    }
 
    if(cr < ql || cl > qr) {
        return;
    }
 
    if(ql <= cl && cr <= qr) {
        segTree[in] += (1ll * dff);
        if(cl != cr) {
            lazy[2*in+1] += dff;
            lazy[2*in+2] += dff;
        }
        return;
    }
 
    int m = cl + (cr - cl) / 2;
    updateUtil(2*in+1, cl, m, ql, qr, dff);
    updateUtil(2*in+2, m+1, cr, ql, qr, dff);
 
    segTree[in] = max(segTree[2*in+1], segTree[2*in+2]);
}
 
void update(int ql, int qr, int dff) {
    updateUtil(0, 0, arraySize-1, ql, qr, dff);
}
 
ll queryUtil(int in, int cl, int cr, int ql, int qr) {
    if(lazy[in] != 0) {
        segTree[in] += (1ll * lazy[in]);
        if(cl != cr) {
            lazy[2*in+1] += lazy[in];
            lazy[2*in+2] += lazy[in];
        }
        lazy[in] = 0;
    }
 
    if(cr < ql || cl > qr) {
        return LONG_LONG_MIN;
    }
 
    if(ql <= cl && cr <= qr) {
        return segTree[in];
    }
 
    int m = cl + (cr - cl) / 2;
    return max(
        queryUtil(2*in+1, cl, m, ql, qr),
        queryUtil(2*in+2, m+1, cr, ql, qr)
    );
}
 
ll query(int ql, int qr) {
    return queryUtil(0, 0, arraySize-1, ql, qr);
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
 
void printLazyTree() {
    int layer = arraySize; // n smallest power of 2 that great than or equal to the size of seg_tree
    for (int i = 0; i < 2 * arraySize - 1; i++) {
        cout << setw(layer) << lazy[i] << " ";
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
 
    int ar[n];
    ll psm[n];
    for(i=0;i<n;i++) {
        int x;
        cin >> x;
 
        ar[i] = x;
        arr[i] = x + (i == 0 ? 0 : arr[i-1]);
        psm[i] = arr[i];
    }
    createSegmentTree(0, 0, n-1);
    arraySize = n;
    // for(int k=0;k<n;k++) {
    //     ll cans = query(k,k);
    //     // if(psm[k] != cans) {
    //         cout << k << " : " << ar[k] << " = " << psm[k] << " , " << cans << "\n";
    //         // if(k > 0) {
    //         //     cout << k-1 << " : " << psm[k-1] << " , " << query(k-1, k-1) << "\n";
    //         // }
    //     // }
    // }
 
    while(q--) {
        int t, a, b;
        cin >> t >> a >> b;
        t--;
        a--;
        // int a1 = a;
        // int b1 = b;

        // if(!t) {
        //     // cout << b1 << " - " << ar[a1] << " :: " << b1 - ar[a1] << "\n";
        //     for(int k=a1;k<n;k++) {
        //         psm[k] += (1ll * b1 - ar[a1]);
        //     }
        // }
        // else {
        //     b1--;
        //     // ll ans = query(a1, b1);
        //     ll mxans = 0ll;
        //     for(int k=a1;k<=b1;k++) {
        //         // psm[k] += (1ll * b1 - ar[a]);
        //         mxans = max(mxans, psm[k]);
        //     }
        //     if(a1 > 0) {
        //         mxans -= psm[a1-1];
        //     }
        //     cout << max(mxans, 0ll) << "\n";
        // }
 
        // printSegTree();
        // printLazyTree();
        if(!t) {
            // cout << b << " - " << ar[a] << " :: " << b - ar[a] << "\n";
            update(a, n-1, b - ar[a]);
            ar[a] = b;
            // for(int k=0;k<n;k++) {
            //     ll cans = query(k,k);
            //     // if(psm[k] != cans) {
            //         cout << k << " : " << ar[k] << " = " << psm[k] << " , " << cans << "\n";
            //         // if(k > 0) {
            //         //     cout << k-1 << " : " << psm[k-1] << " , " << query(k-1, k-1) << "\n";
            //         // }
            //     // }
            // }
        }
        else {
            b--;
            ll ans = query(a, b);
            if(a > 0) {
                ans -= query(a-1, a-1);
            }
            cout << max(ans, 0ll) << "\n";
        }

        // for(int k=0;k<n;k++) {
        //     ll cans = query(k,k);
        //     // if(psm[k] != cans) {
        //         cout << k << " : " << psm[k] << " , " << cans << "\n";
        //         // if(k > 0) {
        //         //     cout << k-1 << " : " << psm[k-1] << " , " << query(k-1, k-1) << "\n";
        //         // }
        //     // }
        // }
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