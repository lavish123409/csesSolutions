#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string ps = "\n";

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


// void printPQ(auto pq) {
//     cout << "[";
//     while(!pq.empty()) {
//         int d = pq.top().first;
//         int u = pq.top().second;
//         pq.pop();
//         cout << "(" << d << " : " << u << ") , ";
//     }
//     cout << "]\n";
// }

/*

    brute force would be to
    start from node 1, and visit all adjacent nodes
    keep visiting all nodes if it is not visited, and check in visited array whether all nodes are covered
    if it is, then increment the counter
    otherwise, backtrack since all the nodes are visited
    O(n!), for n = 8 * 8 = 64, it would give TLE

    we can use dp to prevent solving subproblems again
    use n-length bitmask to represent visited for nodes
    when coming to any vertex, make it visited in bitmask
    traverse all adjacent nodes, if they are not visted
    if mask is full, increment counter and return
    store it in dp[nodes][mask], mask = 2^n
    O(n * 2^n), for n = 64 it would also give TLE 

    working for 5x5 but not for 8x8

    GFG Solution 
    we should use Warnsdorff’s algorithm, which says for current point P
        - let S be the set of positions accessible from P.
        - Set P to be the position in S with minimum accessibility
        - Mark the board at P with the current move number
    here, minimum accessibility means that from that point all the points which are reachable most of them are non-valid or occupied
    we can store all points in a min queue and then pop them one by one to see which point would lead to knight tour


*/

// const int MAXN = 2e5+5;
// const int MAXD = 30;
// int anc[MAXN][MAXD];

#define SIZE 8

int rd[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int cd[] = {-1, 1, -2, 2, -2, 2, -1, 1};

bool isValid(int x, int y) {
    return !(x < 0 || y < 0 || x >= SIZE || y >= SIZE);
}

bool isVisited(int x, int y, ll mask) {
    int flin = x * SIZE + y;
    return mask & (1ll << flin);
}

int getAccessibility(int x, int y, ll mask) {
    // int i, ans=8;
    // for(i=0;i<8;i++) {
    //     int nx = x + rd[i];
    //     int ny = y + cd[i];
    //     int flin = nx * SIZE + ny;
    //     if(!isValid(nx, ny)) ans--;
    //     else ans -= (mask & (1ll << flin));
    // }
    int i, ans=0;
    for(i=0;i<8;i++) {
        int nx = x + rd[i];
        int ny = y + cd[i];
        int flin = nx * SIZE + ny;
        if(isValid(nx, ny) && !(mask & (1ll << flin))) ans++;
    }

    return ans;
}

bool dfs(int x, int y, vector<vector<int>>& ans, int ind, ll mask) {
    debug(x, y, ind, __builtin_popcountll(mask));
    // cerr << "mask: " << bitset<64>(mask) << "\n";
    debug(ans);
    // if(x < 0 || y < 0 || x >= SIZE || y >= SIZE) return 0;
    // if((long double)mask == ((1.0L << 64) - 1)) {

    int flin = x * SIZE + y;
    if(mask & (1ll << flin)) {
        return 0;
    }

    mask |= (1ll << flin);
    ans[x][y] = ind;

    if(__builtin_popcountll(mask) == SIZE * SIZE) {
        for(int i=0;i<SIZE;i++) {
            for(int j=0;j<SIZE;j++) {
                cout << ans[i][j] << " ";
            }
            cout << "\n";
        }
        return 1;
    }

    // int nx=-1, ny=-1, minAcc=9;
    priority_queue<array<int,3>, vector<array<int,3>>, greater<array<int,3>>> mnq;
    // vector<array<int,3>> mnq;

    for(int i=0;i<8;i++) {
        // if(dfs(x + rd[i], y + cd[i], ans, ind+1, mask)) {
        //     return 1;
        // }
        if(!isValid(x+rd[i], y+cd[i]) || isVisited(x+rd[i], y+cd[i], mask)) continue;
        int currAcc = getAccessibility(x+rd[i], y+cd[i], mask);
        mnq.push({currAcc, x+rd[i], y+cd[i]});
        // mnq.push_back({currAcc, x+rd[i], y+cd[i]});
        // if(currAcc < minAcc) {
        //     minAcc = currAcc;
        //     nx = x+rd[i];
        //     ny = y+cd[i];
        // }
    }

    // if(nx == -1 || ny == -1) {
    //     return 0;
    // }

    // return dfs(nx, ny, ans, ind+1, mask);

    // sort(mnq.begin(), mnq.end());
    // for(auto [ac, nx, ny] : mnq) {
    //     if(dfs(nx, ny, ans, ind+1, mask)) return 1;
    // }
    while(!mnq.empty()) {
        int nx = mnq.top()[1];
        int ny = mnq.top()[2];
        mnq.pop();
        if(dfs(nx, ny, ans, ind+1, mask))
            return 1;
    }

    mask &= ~(1ll << flin);
    ans[x][y] = 0;

    return 0;
}

bool dfs1(int x, int y, vector<vector<int>>& ans, int ind, ll mask) {
    debug(x, y, ind);
    cerr << "mask: " << bitset<64>(mask) << "\n";
    if(!isValid(x,y)) return 0;

    if(__builtin_popcount(mask) == SIZE * SIZE) {
        for(int i=0;i<SIZE;i++) {
            for(int j=0;j<SIZE;j++) {
                cout << ans[i][j] << " ";
            }
            cout << "\n";
        }
        return 1;
    }

    int flin = x * SIZE + y;
    if(mask & (1ll << flin)) {
        return 0;
    }

    mask |= (1ll << flin);
    ans[x][y] = ind;

    for(int i=0;i<8;i++) {
        if(dfs1(x + rd[i], y + cd[i], ans, ind+1, mask)) {
            return 1;
        }
    }

    mask &= ~(1ll << flin);
    ans[x][y] = 0;

    return 0;        
}

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    
    int x, y;
    cin >> x >> y;
    x--;
    y--;

    ll mask = 0ll;
    vector<vector<int>> ans(SIZE, vector<int>(SIZE));

    dfs(y, x, ans, 1, mask);
    return 0;

}