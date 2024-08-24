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
 
    approach I - peeked the solution
    suppose current query index is i, and every other index is j
    we can write p_j + (i - j) for j < i and p_j + (j - i) for i < j
    we can se that, we can combine p_j and j, so we need to find
    min( (p_j - j) + i , (p_j + j) - i )
    now, for x+i < y-i, we can say that also z+i < z-i, if z < x but not sure for z > x
    so, we can find minimum of (p_j - j), and it would surely be the minimum (p_j - j) + i
    similarly, for other case

    code
    make segment trees of p_j + j and p_j - j
    for every of index i
    find minimum in pj + j for range (i+1, n-1)
    find minimum in pj - j for range (0, i-1)
    print the minimum of both

    RE1 - wrote wrong condition for returning query answer if current interval lies completely inside query interval
    if(ql <= cl && cr <= qr) {
        return segTree[in];
    }

    WA1 - understood question wrong
    was thinking that current cannot be taken, but it was taken
 
*/
string ps = "\n";
 
 
const int MAXN = 2e5+5;
ll arrA[MAXN];
ll arrS[MAXN];
ll segTreeL[4 * MAXN];
ll segTreeR[4 * MAXN];
ll lazy[4 * MAXN];
int arraySize;
 
void createSegmentTree(ll segTree[], int in, int cl, int cr, ll arr[]) {
    if(cl == cr) {
        segTree[in] = arr[cl];
        return;
    }

    int m = cl + (cr - cl) / 2;
    createSegmentTree(segTree, 2*in+1, cl, m, arr);
    createSegmentTree(segTree, 2*in+2, m+1, cr, arr);

    segTree[in] = min(segTree[2*in+1], segTree[2*in+2]);
}

ll queryUtil(ll segTree[], int in, int cl, int cr, int ql, int qr) {
    if(ql > qr || ql > cr || qr < cl) {
        return LONG_LONG_MAX;
    }

    if(ql <= cl && cr <= qr) {
        return segTree[in];
    }

    int m = cl + (cr - cl) / 2;
    return min(
        queryUtil(segTree, 2*in+1, cl, m, ql, qr),
        queryUtil(segTree, 2*in+2, m+1, cr, ql, qr)
    );
}

ll query(ll segTree[], int ql, int qr) {
    return queryUtil(segTree, 0, 0, arraySize-1, ql, qr);
}

void update(ll segTree[], int in, int cl, int cr, ll arr[], int ind, ll val) {
    if(cl == cr) {
        segTree[in] = val;
        arr[cl] = val;
        return;
    }

    int m = cl + (cr - cl) / 2;
    if(ind <= m) {
        update(segTree, 2*in+1, cl, m, arr, ind, val);
    }
    else {
        update(segTree, 2*in+2, m+1, cr, arr, ind, val);
    }

    segTree[in] = min(segTree[2*in+1], segTree[2*in+2]);
}
 
void solve() {
 
    int i, n, q;
    cin >> n >> q;
    // cout << n << " : " << q << "\n";
    arraySize = n;
    // int ra[n];
 
    for(i=0;i<n;i++) {
        ll x;
        cin >> x;

        arrS[i] = x - i;
        arrA[i] = x + i;
        // ra[i] = x;
    }

    createSegmentTree(segTreeL, 0, 0, n-1, arrS);
    createSegmentTree(segTreeR, 0, 0, n-1, arrA);

    while(q--) {
        int t;
        cin >> t;
        t--;

        if(!t) {
            int ind, val;
            cin >> ind >> val;
            ind--;

            update(segTreeL, 0, 0, n-1, arrS, ind, 1ll * val - ind);
            update(segTreeR, 0, 0, n-1, arrA, ind, 1ll * val + ind);

            // ra[ind] = val;
        }
        else {
            int ind;
            cin >> ind;
            ind--;

            // for(int k=10;k>=1;k--) {
            //     cout << arrS[ind - k]+k << " ";
            // }
            // for(int k=1;k<=10;k++) {
            //     cout << arrS[ind + k]+k << " ";
            // }
            // cout << "\n";
            
            // for(int k=10;k>=1;k--) {
            //     cout << arrA[ind - k]-k << " ";
            // }
            // for(int k=1;k<=10;k++) {
            //     cout << arrA[ind + k]-k << " ";
            // }
            // cout << "\n";

            // cout << "ra->\n";
            // for(i=ind-10;i<=ind+10;i++) {
            //     cout << "(" << ra[i] << "," << i << ") - ";
            // }
            // cout << "\n";

            // for(i=ind-10;i<=ind+10;i++) {
            //     cout << "(" << ra[i] + abs(i - ind) << "," << i << ") - ";
            // }
            // cout << "\n";


            ll lmin = query(segTreeL, 0, ind);
            ll rmin = query(segTreeR, ind+1, n-1);

            cout << min(lmin + ind, rmin - ind) << "\n";
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