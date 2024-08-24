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
    Observation - 
    wew can see that, at every point when an element is removed, the indexes of elements after it decreases by 1
    so, we can use the difference array with segment tree to handle such queries

    we can take 1 for every index of array, and make segment tree of it
    so, every index can be determined by the sum(0, index)
    like for 1 1 1 1 1 index 3 would mean 2
             5 7 2 9 3
    because here, the index at which the sum from first index is 3 would be 3
    now, if we would remove 3rd element, we can make it 0 from 1
    then for 1 1 0 1 1 index 3 would mean 9
             5 7 2 9 3
    because here, the index at which the sum from first index is 3 would be 4

    new observation - we would have to traverse the segment tree based on sum of node
    suppose our index is 4, and we are at root node with 5 elements
    now, on left side there are 3 elements and on right there are 2 elements
    we should go on right side, but the index would become (4 - 3) = 1, because we skipped 3 elements on left side
    

*/
string ps = "\n";


const int MAXN = 2e5+5;
int arr[MAXN];
ll segTree[4 * MAXN];
ll lazy[4 * MAXN];
int arraySize;

void createSegmentTree(int in, int cl, int cr) {
    if(cl == cr) {
        segTree[in] = 1;
        return;
    }

    int m = cl + (cr - cl) / 2;
    createSegmentTree(2*in+1, cl, m);
    createSegmentTree(2*in+2, m+1, cr);

    segTree[in] = segTree[2*in+1] + segTree[2*in+2];
}

int queryUpdate(int in, int cl, int cr, int val) {
    if(cl == cr) {
        segTree[in] = 0;
        // cout << cl << " : " << arr[cl] << "\n";
        return arr[cl];
    }

    int m = cl + (cr - cl) / 2;
    int ans = 0;
    // debug(val);
    // debug(in, cl, cr);
    // debug(segTree[2*in+1], segTree[2*in+2]);
    if(val <= segTree[2*in+1]) {
        ans = queryUpdate(2*in+1, cl, m, val);
    }
    else {
        ans = queryUpdate(2*in+2, m+1, cr, val - segTree[2*in+1]);
    }

    segTree[in] = segTree[2*in+1] + segTree[2*in+2];
    return ans;
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

    int n, m, i;
    cin >> n;
    arraySize = n;

    for(i=0;i<n;i++) {
        cin >> arr[i];
    }

    createSegmentTree(0, 0, n-1);

    for(i=0;i<n;i++) {
        int in;
        cin >> in;

        // printSegTree();
        cout << queryUpdate(0, 0, n-1, in) << " ";
    }
    cout << "\n";
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