#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
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
// #define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#define debuga(x, l, r) cerr << "[" << #x << "] = ["; printa(x, l, r)
#define debugma(x, y, l, r, merge) cerr << "[" << #x << "," << #y << "] = ["; printma(x, y, l, r, merge)
#else
#define debug(x...)
#define debuga(x, l, r)
#define debugma(x, y, l, r, merge)
#endif
 
// tip: try to think about recursive solutions for Mathematical problems
// sometimes it becomes too complex to use just 1 formula to calculate complete answer
// for ex, Josephus Problem
 
// tip: its a good alternative to check the not version of given problem, and think about it to solve first
// for ex, Christmas party
 
/*
 
    I approach
    we can simulate the moving of robots together by the probability
    in starting, the probability of every cell to be filled is 1 and 0 for it being to be empty
    then, we can simulate the moving by going to every cell and distributing its probability to all achievable adjacent cells
    in this process, some cells would have more than 1 probability that it is filled, which is because of the fact that 2 different robots have that much probability to exist in that cell, so to get the probability of that cell to be filled would be at most 1
    for ex, for cell (0,0) there is 0.5 probability that the robot would go to cell (0,1) or (1,0)
    and for cell, (1,1) there is 0.25 probability that the robot would go to cell (0,1), (1,0), (1,2) or (2,1)
    and for cell, (0,2) there is 0.33 probability that the robot would go to cell (0,1), (1,2) or (0,3)
    so, in total the probability that (0,1) is filled is 1.08 > 1, and we would have to make it to 1

    after simulating robots for n times, we would find the probability of every cell being empty by 1 - probability that current is filled, which we have calculated
    and add all the probabilities because the contribution of every cell is 1 for the expected value

    MISTAKE
    did not realize that expected value would be different for each cell
    also, k turns means that we have to run the loop k times, that is we have to take the dp array of size dp[k+1][64]

    Solution
    we have to simulate the moving of robots but not all at once
    we would keep the robot at ecah cell, by making the probability of that cell being filled 1
    then, simulate its moving by calculating probabilities at every step for n times
    and finally calculating the expected value, by summimg the probabilities of all the cells
    and doing same above 3 steps, by keeping robot at every cell and adding the expectation
    
*/
#define double long double

string ps = "\n";

void solve() {

    int i, j, k, n;
    cin >> n;

    const int sz = 64, rc = 8;
    vector<vector<double>> dp;
    vector<double> ans(sz, 1.0);

    for(int robst = 0; robst < sz; robst++) {
        dp = vector<vector<double>>(n+1, vector<double>(sz));
        dp[0][robst] = 1.0;

        for(i=0;i<n;i++) {
            for(j=0;j<sz;j++) {
                int r = j / rc;
                int c = j % rc;
                int totalNumberOfAcheivableCells = (r != 0) + (c != 0) + (r != 7) + (c != 7);
                if(r != 0) {
                    dp[i+1][(r - 1) * rc + c] += dp[i][j] / totalNumberOfAcheivableCells;
                }
                if(c != 0) {
                    dp[i+1][r * rc + (c - 1)] += dp[i][j] / totalNumberOfAcheivableCells;
                }
                if(r != 7) {
                    dp[i+1][(r + 1) * rc + c] += dp[i][j] / totalNumberOfAcheivableCells;
                }
                if(c != 7) {
                    dp[i+1][r * rc + (c + 1)] += dp[i][j] / totalNumberOfAcheivableCells;
                }
                // if(i < 2) {
                //     debug(r, c, totalNumberOfAcheivableCells, dp[i][j]);
                // }
            }
            // debug(i);
            debug(dp[i]);
        }
        for(j=0;j<sz;j++) {
            ans[j] *= (1.0 - dp[n][j]);
        }
    }

    double expVal = 0.0;
    for(j=0;j<sz;j++) {
        expVal += ans[j];
    }

    cout << fixed << setprecision(6) << expVal << "\n";

    // vector<vector<double>> cur(8, vector<double>(8)), prev(8, vector<double>(8, 1.0));
    // for(k=2;k<=n;k++) {
    //     // prev = cur;
    //     // cur = 
    //     for(i=0;i<8;i++) {
    //         for(j=0;j<8;j++) {
    //             // cur[i][j] = 0;
    //             int totalNumberOfAcheivableCells = (i != 0) + (i != 7) + (j != 0) + (j != 7);
    //             if(i != 0) {
    //                 cur[i-1][j] += prev[i][j] / totalNumberOfAcheivableCells;
    //                 cur[i-1][j] = min(cur[i-1][j], 1.0);
    //             }
    //             if(i != 7) {
    //                 cur[i+1][j] += prev[i][j] / totalNumberOfAcheivableCells;
    //                 cur[i+1][j] = min(cur[i+1][j], 1.0);
    //             }
    //             if(j != 0) {
    //                 cur[i][j-1] += prev[i][j] / totalNumberOfAcheivableCells;
    //                 cur[i][j-1] = min(cur[i][j-1], 1.0);
    //             }
    //             if(j != 7) {
    //                 cur[i][j+1] += prev[i][j] / totalNumberOfAcheivableCells;
    //                 cur[i][j+1] = min(cur[i][j+1], 1.0);
    //             }
    //         }
    //     }
    //     prev = cur;
    //     debug(cur);
    //     cur = vector<vector<double>>(8, vector<double>(8));
    // }

    // double ans = 0.0;
    // for(i=0;i<8;i++) {
    //     for(j=0;j<8;j++) {
    //         ans += (1 - prev[i][j]);
    //     }
    // }

    // cout << ans << "\n";
    // // cout << 64.0 - ans << "\n";d

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

// #include <bits/stdc++.h>

// using namespace std;
// const int maxK = 101;
// const int N = 8, SZ = N*N;

// int K;
// double expected, ans[SZ], dp[maxK][SZ];

// int main(){
//     scanf("%d", &K);
//     for(int i = 0; i < SZ; i++)
//         ans[i] = 1.0;

//     for(int start = 0; start < SZ; start++){
//         memset(dp, 0, sizeof(dp));
//         dp[0][start] = 1.0;

//         for(int k = 0; k < K; k++){
//             for(int u = 0; u < SZ; u++){
//                 vector<int> V;
//                 if(N <= u)          V.push_back(u-N);
//                 if(u < N*(N-1))     V.push_back(u+N);
//                 if(u % N != 0)      V.push_back(u-1);
//                 if(u % N != N-1)    V.push_back(u+1);

//                 for(int v : V)
//                     dp[k+1][v] += (dp[k][u] / V.size());
//             }
//             debuga(dp[k], 0, SZ-1);
//         }

//         for(int u = 0; u < SZ; u++)
//             ans[u] *= (1 - dp[K][u]);
//     }

//     for(int i = 0; i < SZ; i++)
//         expected += ans[i];
//     printf("%.6f\n", expected);
// }