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
    we would try to extend it to support multiple values
    we can make segment tree array an array of vectors and put the sum of that range in that vector
    when we need to make copy of a vector, we would pass index of that array(parent) from which we have to copy the array
    we would do copying lazily because we would have to update multiple elements
    when we would come to a vertex, we would first copy the parent's array value for that range and pass it to node's children
    after that we would handle update or query
    if it is update, if it is parent array's value, current array's value or some other array's value, we can do it safely
    if it is query, we can do that similar to normal segment tree

    different thing - 
    the different thing would be to handle multiple updates
    suppose we copied 1st array, and then 2nd array
    so, we would have to make the lazy array as an array of vectors, and copy those arrays first which came first
    here, lazy[0] = {1, 2}, means first we have to copy value of array 1 and of array 2 for current range of segment tree

    PROBLEM
    would it not give TLE because if most queries are of copy and at last there are sum queries, then every node of segment tree would have 1e5 size vectors, which is not possible in RAM

    II approach
    after hearing william lin about persistent segment tree and seeing its article
    it seems like it can be done by implementing segment tree with pointer
    and in copying, just copying the root address to another index in the array of segment tree pointers
    and then updating and querying according to the index of segment tree

    WA - sample
    if we would only copy the vertices then when we would make any change to second segment tree, we would also change the first or that tree from which current tree is copied
    to resolve we can make a new vertex for all those vertices which have been modified for current update query


*/
string ps = "\n";
 
const int MAXN = 2e5+5;
// vector<ll> segTree[4*MAXN];
// vector<int> lazy[4*MAXN];
int arr[MAXN];
int arraySize;

class Vertex {
public:
    ll sum;
    Vertex *left, *right;

    Vertex() {
        sum = 0ll;
        left = 0;
        right = 0;
    }

    Vertex* copyVertex() {
        Vertex *nw = new Vertex();

        nw->sum = this->sum;
        nw->left = this->left;
        nw->right = this->right;

        return nw;
    }

    // void update(Vertex* node, int cl, int cr, int ind, ll dff) {
    Vertex* update(int cl, int cr, int ind, ll dff) {
        debug(cl, cr, ind, dff);
        if(cl > ind || cr < ind) {
            debug("u1");
            return this;
        }

        Vertex *node = copyVertex();
        // cerr << node->sum << " : " << node->left << " , " << node->right << "\n";
        if(cl == cr) {
            debug("u2");
            node->sum = this->sum + dff;
            return node;
        }

        // cerr << node->sum << " : " << node->left << " , " << node->right << "\n";
        int m = cl + (cr - cl) / 2;
        if(ind <= m) {
            // update(this->left, cl, m, ind, dff);
            node->left = this->left->update(cl, m, ind, dff);
        }
        else {
            // update(this->right, m+1, cr, ind, dff);
            node->right = this->right->update(m+1, cr, ind, dff);
        }

        debug("u3");
        node->sum = node->left->sum + node->right->sum;
        // cerr << node->sum << " : " << node->left << " , " << node->right << "\n";
        return node;
    }

    // ll query(Vertex* node, int cl, int cr, int ql, int qr) {
    ll query(int cl, int cr, int ql, int qr) {
        debug(cl, cr, ql, qr);
        if(ql <= cl && cr <= qr) {
            return this->sum;
        }

        if(cl > qr || cr < ql) {
            return 0;
        }

        int m = cl + (cr - cl) / 2;
        // return query(node->left, cl, m, ql, qr) + query(node->right, m+1, cr, ql, qr);
        return this->left->query(cl, m, ql, qr) + this->right->query(m+1, cr, ql, qr);
    }

};

Vertex* create(int cl, int cr, int arr[]) {
    Vertex *node = new Vertex();
    if(cl == cr) {
        node->sum = arr[cl];
        return node;
    }

    int m = cl + (cr - cl) / 2;
    node->left = create(cl, m, arr);
    node->right = create(m+1, cr, arr);

    node->sum = node->left->sum + node->right->sum;
    return node;
}

vector<Vertex*> segTree;


void printBT(Vertex* node, const std::string& prefix, bool isLeft)
{
    if( node->left && node->right )
    {
        std::cerr << prefix;

        std::cerr << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cerr << node->sum << " : " << node << std::endl;

        // enter the next tree level - left and right branch
        printBT( node->left, prefix + (isLeft ? "│   " : "    "), true);
        printBT( node->right, prefix + (isLeft ? "│   " : "    "), false);
    }
    else {
        std::cerr << prefix;

        std::cerr << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cerr << node->sum << " : " << node << std::endl;
    }
}

void printBT(Vertex* node)
{
    printBT(node, "", false);
}

void solve() {
 
    int i, j, n, q;
    cin >> n >> q;
    debug(n, q);
    
    for(i=0;i<n;i++) {
        cin >> arr[i];
    }

    Vertex* root = create(0, n-1, arr);
    segTree.push_back(root);

    while(q--) {
        int t;
        cin >> t;
        debug(t);

        int k, a, b, x;
        switch(t) {
            case 1: {
                cin >> k >> a >> x;

                ll old = segTree[k-1]->query(0, n-1, a-1, a-1);
                debug(old);
                segTree[k-1] = segTree[k-1]->update(0, n-1, a-1, x - old);
                // for(auto& node : segTree) {
                //     printBT(node);
                //     cerr << "\n\n";
                // }
                break;
            }
            case 2:
                cin >> k >> a >> b;

                cout << segTree[k-1]->query(0, n-1, a-1, b-1) << "\n";
                break;
            case 3:
                cin >> k;
                segTree.push_back(segTree[k-1]->copyVertex());
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