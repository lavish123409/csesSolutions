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
template<typename T>
void printa2(T* a, int l1, int r1, int l2, int r2, int m) {int f = 0; cerr << '{'; for (int i=l1;i<=r1;i++) cerr << (f++ ? "," : ""), printa(a + i * m, l2, r2); cerr << "}]\n";}
// #define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#define debuga(x, l, r) cerr << "[" << #x << "] = ["; printa(x, l, r)
#define debuga2(x, l1, r1, l2, r2, m) cerr << "[" << #x << "] = [\n"; printa2(x, l1, r1, l2, r2, m); cerr << "}]\n";
#define debugma(x, y, l, r, merge) cerr << "[" << #x << "," << #y << "] = ["; printma(x, y, l, r, merge)
#else
#define debug(x...)
#define debuga(x, l, r)
#define debuga2(x, l1, r1, l2, r2, m)
#define debugma(x, y, l, r, merge)
#endif
 
 
 
/*
 
    I approach
    just like we do lazy propagation for update, we can do same for polynomial queries with some tweaks
    while updating node, if current range is completly inside the query range, then update it with starting number as follows
        last_number = cr - cl + startingNumber;
        segTree[in] += sumN(last_number) - sumN(starting_number-1)
    and push it to children like this
        m = (cr - cl) / 2
        lazy[left_child] += starting_number
        lazy[right_child] += starting_number + m - cl + 1
    and do same with children, when those nodes are visited

    while coming to a node, if there are pending lazy updates, just consider the lazy value as starting number because we have updated lazy value like that while updating
        starting_number = lazy[in]
        last_number = cr - cl + startingNumber;
        segTree[in] += sumN(last_number) - sumN(starting_number-1)
    and push it to children like this
        m = (cr - cl) / 2
        lazy[left_child] += starting_number
        lazy[right_child] += starting_number + m - cl + 1

    here, sumN(n) = n * (n+1) / 2
    
    WA1 - 
    if in a segment the query left is after m, then this code for updating right child would not work
        update(2*in+2, m+1, cr, ql, qr, dff + (m - ql + 1));
    change to
        if(ql <= m) {
            update(2*in+1, cl, m, ql, qr, dff);
            update(2*in+2, m+1, cr, ql, qr, dff + (m - ql + 1));
        }
        else {
            update(2*in+2, m+1, cr, ql, qr, dff);
        }

    WA2 - 
    1. when we are on leaf node, the array value should be updated with lazy value and not set
        arr[cl] = sn; 
    change to
        arr[cl] += sn;
    
    2. in order for lazy to work, we should visit both children nodes, before updating current node
        if(ql <= m) {
            update(2*in+1, cl, m, ql, qr, dff);
            update(2*in+2, m+1, cr, ql, qr, dff + (m - ql + 1));
        }
        else {
            update(2*in+2, m+1, cr, ql, qr, dff);
        }
    change to
        if(ql <= m) {
            update(2*in+1, cl, m, ql, qr, dff);
            update(2*in+2, m+1, cr, ql, qr, dff + (m - ql + 1));
        }
        else {
            update(2*in+1, cl, m, ql, qr, 0);
            update(2*in+2, m+1, cr, ql, qr, dff);
        }

    WA3 - same as above; missed one line

    WA4 -
    the lazy values can go beyond INT_MAX
    the array values can go beyond INT_MAX
    both should be ll

    WA5 -
    the starting and last number, for a segment to be updated can also go beyond INT_MAX


    PROBLEM
    suppose index 54 is updated with 36, then index 55 will be updated with 37
    and then, index 54 is updated with 11, then index 55 will be updated with 12
    now, in total index 54 is updated with 36+11=47, but index 55 will be updated with 37+12=49

    we can take an extra array for counting how many times a node has been updated
    and find through the formula what would be the value
        segTree[in] += (sumN(ln) - sumN(sn-1)) + ((updCount[in]-1) * sumN(cr - cl));
    and propagate the update count to both children
        updCount[2*in+1] += (updCount[in]);
        updCount[2*in+2] += (updCount[in]);
    update count would remain mostly 0, only when we are updating the lazy value for a node first time, only then it would become 1
    and it would increment whenever it would be updated again
    the children would also be incremented by the amount of times the current node has been incremented


*/
string ps = "\n";
 
const int MAXN = 2e5+5;
ll segTree[4*MAXN];
ll lazy[4*MAXN];
int updCount[4*MAXN];
ll arr[MAXN];
int arraySize;

void printBT(ll segTree[], int in, const std::string& prefix, bool isLeft, int cl, int cr)
{
    if( cl != cr )
    {
        std::cerr << prefix;

        std::cerr << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cerr << segTree[in] << std::endl;

        // enter the next tree level - left and right branch
        int m = cl + (cr - cl) / 2;
        printBT( segTree, 2*in+1, prefix + (isLeft ? "│   " : "    "), true, cl, m);
        printBT( segTree, 2*in+2, prefix + (isLeft ? "│   " : "    "), false, m+1, cr);
    }
    else {
        std::cerr << prefix;

        std::cerr << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cerr << segTree[in] << std::endl;
    }
}

void printBT(ll segTree[], int in, int cl, int cr)
{
    printBT(segTree, in, "", false, cl, cr);
}

ll sumN(ll n) {
    return (1ll * n * (n + 1)) / 2;
}
 
void createSegmentTree(int in, int cl, int cr) {
    if(cl == cr) {
        segTree[in] = arr[cl];
        updCount[in] = 0;
        lazy[in] = 0;
        return;
    }

    int m = cl + (cr - cl) / 2;
    createSegmentTree(2*in+1, cl, m);
    createSegmentTree(2*in+2, m+1, cr);

    segTree[in] = segTree[2*in+1] + segTree[2*in+2];
}

void update(int in, int cl, int cr, int ql, int qr, int dff) {
    int m = cl + (cr - cl) / 2;
    debug("u", cl, cr, ql, qr, dff);
    if(lazy[in] != 0) {
        debug(cl, cr, "r0: ", lazy[in], updCount[in], segTree[in]);
        ll sn = lazy[in];
        ll ln = sn + (cr - cl);
        segTree[in] += (sumN(ln) - sumN(sn-1)) + ((updCount[in]-1) * sumN(cr - cl));
        if(cl == cr) {
            arr[cl] += sn;
        }
        else {
            // if(lazy[2*in+1] > 0) updCount[2*in+1] += (updCount[in]);
            updCount[2*in+1] += (updCount[in]);
            lazy[2*in+1] += sn;
            debug(updCount[2*in+1], lazy[2*in+1]);
            // if(lazy[2*in+2] > 0) updCount[2*in+2] += (updCount[in]);
            updCount[2*in+2] += (updCount[in]);
            lazy[2*in+2] += (sn + (m - cl + 1) * (updCount[in]));
            debug(updCount[2*in+2], lazy[2*in+2]);
        }
        lazy[in] = 0;
        updCount[in] = 0;
        debug(cl, cr, "r0: ", segTree[in]);
    }

    if(cr < ql || cl > qr) {
        debug(cl, cr, "r1");
        return;
    }

    if(ql <= cl && cr <= qr) {
        debug(cl, cr, "r2: ", segTree[in]);
        ll sn = dff;
        ll ln = sn + (cr - cl);
        segTree[in] += (sumN(ln) - sumN(sn-1));
        if(cl == cr) {
            arr[cl] += sn;
        }
        else {
            // if(lazy[2*in+1] > 0) updCount[2*in+1]++;
            updCount[2*in+1]++;
            lazy[2*in+1] += sn;
            debug(updCount[2*in+1], lazy[2*in+1]);
            // if(lazy[2*in+2] > 0) updCount[2*in+2]++;
            updCount[2*in+2]++;
            lazy[2*in+2] += (sn + (m - cl + 1) * (updCount[in] + 1));
            debug(updCount[2*in+2], lazy[2*in+2]);
        }
        debug(cl, cr, "r2: ", segTree[in]);
        return;
    }

    if(ql <= m) {
        update(2*in+1, cl, m, ql, qr, dff);
        update(2*in+2, m+1, cr, ql, qr, dff + (m - max(ql, cl) + 1));
    }
    else {
        update(2*in+1, cl, m, ql, qr, 0);
        update(2*in+2, m+1, cr, ql, qr, dff);
    }

    segTree[in] = segTree[2*in+1] + segTree[2*in+2];
}

ll query(int in, int cl, int cr, int ql, int qr) {
    debug("q", cl, cr, ql, qr);
    int m = cl + (cr - cl) / 2;
    if(lazy[in] != 0) {
        debug(cl, cr, "1", lazy[in], updCount[in], segTree[in]);
        ll sn = lazy[in];
        ll ln = sn + (cr - cl);
        // segTree[in] += (sumN(ln) - sumN(sn-1));
        segTree[in] += (sumN(ln) - sumN(sn-1)) + ((updCount[in]-1) * sumN(cr - cl));
        if(cl == cr) {
            arr[cl] += sn;
        }
        else {
            // if(lazy[2*in+1] > 0) updCount[2*in+1] += (updCount[in]);
            updCount[2*in+1] += (updCount[in]);
            lazy[2*in+1] += sn;
            debug(updCount[2*in+1], lazy[2*in+1]);
            // if(lazy[2*in+2] > 0) updCount[2*in+2] += (updCount[in]);
            updCount[2*in+2] += (updCount[in]);
            lazy[2*in+2] += (sn + (m - cl + 1) * (updCount[in]));
            debug(updCount[2*in+2], lazy[2*in+2]);
            debug("pass", lazy[2*in+1], lazy[2*in+2]);
        }
        lazy[in] = 0;
        updCount[in] = 0;
        debug(cl, cr, "1", segTree[in]);
    }

    if(cr < ql || cl > qr) {
        debug(cl, cr, "2");
        return 0;
    }

    if(ql <= cl && cr <= qr) {
        debug(cl, cr, "3", segTree[in]);
        return segTree[in];
    }

    return query(2*in+1, cl, m, ql, qr) + query(2*in+2, m+1, cr, ql, qr);
}

void solve() {
 
    int i, j, n, q;
    cin >> n >> q;
    
    // vector<int> tarr(n);
    for(i=0;i<n;i++) {
        cin >> arr[i];
        // cout << "(" << i << ":" << arr[i] << ") , ";
        // tarr[i] = arr[i];
    }
    // cout << "\n";

    createSegmentTree(0, 0, n-1);

    while(q--) {
        int t, a, b;
        cin >> t >> a >> b;
        a--;
        b--;

        switch(t) {
            case 1:
                debug("----------------------------------------------u", a, b);
                update(0, 0, n-1, a, b, 1);
                // printBT(segTree, 0, 0, n-1);
                // printBT(lazy, 0, 0, n-1);
                // for(int i=0;i<n;i++) {
                //     cout << "q: " << query(0, 0, n-1, i, i) << "\n";
                // }
                // cout << "\n";
                // for(int i=a;i<=b;i++) {
                //     // cout << "(" << i << "-" << tarr[i] << " -> ";
                //     tarr[i] += (i - a + 1);
                //     // cout << tarr[i] << ") , ";
                // }
                // cout << "\n";
                // cout << tarr[59] << " : " << query(0, 0, n-1, 59, 59) << "\n";
                // debug("=========================================55");
                // cout << tarr[55] << " : " << query(0, 0, n-1, 55, 55) << "\n";
                debug("=========================================");
                break;
            case 2:
                debug("----------------------------------------------q", a, b);
                // for(i=0;i<=b;i++) {
                //     if(tarr[i] < 10) {
                //         cout << "0";
                //     }
                //     cout << tarr[i] << " ";
                // }
                // cout << "\n";
                // for(i=0;i<=b;i++) {
                //     if(i < 10) {
                //         cout << "0";
                //     }
                //     cout << i << " ";
                // }
                // cout << "\n";
                // for(i=0;i<=b;i++) {
                //     debug(".-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-", i);
                //     ll cans = query(0, 0, n-1, i, i);
                //     if(cans < 10) {
                //         cout << "0";
                //     }
                //     cout << cans << " ";
                // }
                // cout << "\n";
                // cout << query(0, 0, n-1, b+1, b+1);
                cout << query(0, 0, n-1, a, b) << "\n";
                debug("=========================================");
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