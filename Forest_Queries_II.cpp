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
    just like we use prefix sum for 2d queries, similarly we can use fenwick or segment tree for 2d queries
    we would just make the array of fenwick or segment tree
    and while updating current array of fenwick or segment tree, we would also consider values of previous array of fenwick or segment tree
    I was thinking that individual row of 2d fenwick trees would store prefix sums for that row of original array
    but in 2d queries for prefix sum, recall that prefix sum of current row would include all previous rows

    for fenwick trees - idea is that we would update the indices of array like 2d prefix sum queries
    and the internal functionality would be taken care by the implementation of fenwick tree

    PROBLEM
    the update would not be able to propagate downwards, because we are using arrays for rows and not fenwick tree collectively

    change - consider every row as BIT tree and while updating or querying the row index
    do the operation for every row according to the formula of fenwick
    and for every individual row, do the operation like 1D Bit tree

*/
string ps = "\n";

const int MAXN = 1e3+5;
int arr[MAXN][MAXN];
int arraySize;

template<class T> class BIT {
private:
    int size;
    vector<T> arr;
    vector<T> bit;

public:
    BIT(int size) {
        this->size = size;
        arr = vector<T>(size);
        bit = vector<T>(size+1);
    }

    void set(int ind, T val) {
        ad(ind, val - arr[ind]);
    }

    void ad(int ind, T dff) {
        arr[ind] += dff;
        ind++;
        for(; ind <= size; ind += (ind & -ind)) {
            bit[ind] += dff;
        }
    }

    T qr(int ind) {
        T ans = 0;
        ind++;
        for(; ind > 0; ind -= (ind & -ind)) {
            ans += bit[ind];
        }

        return ans;
    }
};

void ad1D(int r, int c, int dff) {
    c++;
    for(; c < MAXN; c += (c & -c)) {
        arr[r][c] += dff;
    }
}

int qr1D(int r, int c) {
    c++;
    int ans = 0;
    for(; c > 0; c -= (c & -c)) {
        ans += arr[r][c];
    }

    return ans;
}

void ad(int r, int c, int dff) {
    r++;
    for(; r < MAXN; r += (r & -r)) {
        ad1D(r, c, dff);
    }
}

int qr(int r, int c) {
    r++;
    int ans=0;
    for(; r > 0; r -= (r & -r)) {
        ans += qr1D(r, c);
    }

    return ans;
}

void setVal(int r, int c, int val) {
    debug(r,c,arr[r][c],val);
    ad(r, c, val - arr[r][c]);
    // arr[r][c] = val;
}

void solve() {

    int i, j, n, q;
    cin >> n >> q;
    debug(n,q);

    vector<vector<bool>> grid(n, vector<bool>(n));
    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            char x;
            cin >> x;

            grid[i][j] = (x == '*');
            debug(i, j, qr(i, j));
            // int val = qr(i-1, j) + qr(i, j-1) - qr(i-1, j-1) + (x == '*');
            // int val = - qr(i-1, j-1) + (x == '*');
            int val = (x == '*');
            debug(qr(i-1, j));
            debug(qr(i, j-1));
            debug(qr(i-1, j-1));
            debug((x == '*'));
            // setVal(i, j, val);
            ad(i, j, val);
            debuga2((int*)arr, 0, n, 0, n, MAXN);
            debug(i, j, qr(i, j));
        }
    }
    debug(qr(n-1, n-1));

    for(i=0;i<q;i++) {
        int t;
        cin >> t;
        t--;

        if(t) {
            int x1, y1, x2, y2;
            cin >> y1 >> x1 >> y2 >> x2;

            y1--;
            x1--;
            y2--;
            x2--;

            int ans = qr(y2, x2) - qr(y1-1, x2) - qr(y2, x1-1) + qr(y1-1, x1-1);
            cout << ans << "\n";
        }
        else {
            int x, y;
            cin >> y >> x;

            x--;
            y--;

            if(grid[y][x]) {
                ad(y, x, -1);
                grid[y][x] = 0;
            }
            else {
                ad(y, x, 1);
                grid[y][x] = 1;
            }
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