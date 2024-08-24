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

    I approach
    we would have to use segment tree, with range updates
    Basic essence
        - for update we have to go to single element for update and it would take significant amount of time
        - so we can update the biggest range which lies inside query range and put rest updates for later period(laziness)
        - whenever we would visit a vertex, we can check if there are any pending updates and do them first, and then
            - if it is query, then we can do query procedure
            - if it is update, repeat same procedure of laziness

        - in query, we would have to update earlier and then query, maybe we can check whether it lies in query range and if not, then return without updating, but if it lies we would have to update
        - in update, we can update before checking the range or after checking it
            - if we would check before,
                -  we can return without updating
                - or we can update and then return
            - if we would check after, then we would have to update with current update

        in YT approach, it was said to update pending changes first, and then do other work, like checking ranges, updating, querying
    

*/
string ps = "\n";


const int MAXN = 2e5+5;
int arr[MAXN];
ll segTree[4 * MAXN];
ll lazy[4 * MAXN];
int arraySize;

bool isLeafNode(int n) {
    int p2gn = 0;
    while((1 << p2gn) < arraySize) {
        p2gn++;
    }

    return n >= ((1 << p2gn)-1);
}

void createSegmentTree(int in, int cl ,int cr) {
    if(cl == cr) {
        segTree[in] = arr[cl];
        lazy[in] = 0;
        return;
    }

    int m = cl + (cr - cl) / 2;
    createSegmentTree(2*in+1, cl, m);
    createSegmentTree(2*in+2, m+1, cr);

    segTree[in] = segTree[2*in+1] + segTree[2*in+2];
    lazy[in] = 0;
}


void updateUtil(int in, int cl, int cr, int ql, int qr, int dff) {
    if(lazy[in] > 0) {
        segTree[in] += (1ll * (cr - cl + 1) * lazy[in]);
        // if(!isLeafNode(in)) {
        if(cl != cr) {
            lazy[2*in+1] += lazy[in];
            lazy[2*in+2] += lazy[in];
        }
        lazy[in] = 0;
    }

    // ps.push_back('\t');
    // cout << ps << cl << " , " << cr << " : " << ql << " , " << qr;
    if(ql <= cl && cr <= qr) {
        segTree[in] += (1ll * (cr - cl + 1) * dff);
        // cout << ps << "insiderange: " << cl << " , " << cr << " : " << ql << " , " << qr << " = " << isLeafNode(in);
        if(cl != cr) {
            lazy[2*in+1] += dff;
            lazy[2*in+2] += dff;
        }
        else {
            arr[cl] += dff;
        }
        lazy[in] = 0;
        // ps.pop_back();
        return;
    }

    if(cl > qr || cr < ql) {
        // ps.pop_back();
        return;
    }

    int m = cl + (cr - cl) / 2;
    updateUtil(2*in+1, cl, m, ql, qr, dff);
    updateUtil(2*in+2, m+1, cr, ql, qr, dff);

    // cout << ps << "l: " << segTree[2*in+1];
    // cout << ps << "r: " << segTree[2*in+2];
    segTree[in] = segTree[2*in+1] + segTree[2*in+2];
    // cout << ps << "sm: " << segTree[in];
    // ps.pop_back();
}

void update(int l, int r, int dff) {
    updateUtil(0, 0, arraySize-1, l, r, dff);
}

ll queryUtil(int in, int cl, int cr, int ind) {
    // cout << in << " : " << cl << " , " << cr << " ; " << ind << " <-q\n";
    if(lazy[in] > 0) {
        // cout << in << " : " << lazy[in] << " <- lt\n";
        segTree[in] += (1ll * (cr - cl + 1) * lazy[in]);
        // if(!isLeafNode(in)) {
        if(cl != cr) {
            lazy[2*in+1] += lazy[in];
            lazy[2*in+2] += lazy[in];
        }
        lazy[in] = 0;
    }

    if(cl == ind && cr == ind) {
        return segTree[in];
    }

    if(cr < ind || cl > ind) {
        return 0;
    }

    int m = cl + (cr - cl) / 2;
    if(cl <= ind && ind <= m) {
        return queryUtil(2*in+1, cl, m, ind);
    }
    else {
        return queryUtil(2*in+2, m+1, cr, ind);
    }
    // return queryUtil(2*in+1, cl, m, ind) + queryUtil(2*in+2, m+1, cr, ind);
}

ll query(int ind) {
    return queryUtil(0, 0, arraySize-1, ind);
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
    arraySize = n;

    for(i=0;i<n;i++) {
        cin >> arr[i];
    }

    createSegmentTree(0, 0, n-1);
    // printSegTree();
    while(q--) {
        int qt;
        cin >> qt;

        switch(qt) {
            case 1:
                int a, b, u;
                cin >> a >> b >> u;

                a--;
                b--;

                update(a, b, u);
                // printSegTree();
                // printLazyTree();
                break;
            case 2:
                int k;
                cin >> k;

                k--;

                cout << query(k) << "\n";
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