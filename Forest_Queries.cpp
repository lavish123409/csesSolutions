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
    we can use 2d prefix sum to store number of trees present in subrectangle (1,1) to (i,j) in psm2d[i+1][j+1] // we can consider that it is stored in psm2d[i][j] by using 1 based indexing for prefix sum and 0 based indexing for grid

    to make prefix sum we need to find number of trees in rectangle (1,1) to (i,j)
        - count how many trees are there in subrectangle (1,1) to (i-1,j)
        - count how many trees are there in subrectangle (1,1) to (i,j-1)
        - subtract how many trees are there in subrectangle (1,1) to (i-1,j-1) as we would have overcounted them
        - add if there is a tree in current cell (i,j)

    to find number of trees in subrectangle from (x1,y1) to (x2,y2)
        - we can find number of trees from (1,1) to (x2,y2)
        - subtract number of trees from (1,1) to (x1-1,y2)
        - subtract number of trees from (1,1) to (x2,y1-1)
        - add number of trees from (1,1) to (x1-1,y1-1) as we would have subtracted them twice
    

*/
string ps = "\n";


const int MAXN = 2e5+5;
int arr[MAXN];
ll segTree[4 * MAXN];
ll lazy[4 * MAXN];
int arraySize;

void solve() {

    int n, i, j, q;
    cin >> n >> q;

    int psm2d[n+1][n+1];
    memset(psm2d, 0, sizeof(psm2d));

    for(i=1;i<=n;i++) {
        for(j=1;j<=n;j++) {
            char x;
            cin >> x;

            psm2d[i][j] = psm2d[i-1][j]
                          + psm2d[i][j-1]
                          - psm2d[i-1][j-1]
                          + (x == '*');
        }
    }

    while(q--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        int ans = psm2d[x2][y2]
                  - psm2d[x1-1][y2]
                  - psm2d[x2][y1-1]
                  + psm2d[x1-1][y1-1];

        cout << ans << "\n";
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