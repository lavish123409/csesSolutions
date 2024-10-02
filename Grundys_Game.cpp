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

    Solution
    we would have to use sprague-grundy theorem here to find the answer
    for that first we would have to find the grundy values for every possible state
        x = mex(x_1, x_2, ... x_n), where x_1, x_2...x_n are reachable states

    Grundy values can be considered as the state of an impartial game, it essentially means that we can assign a fully equivalent game of Nim with one pile of size G(game)=x
    it signifies that x is the minimum state that we cannot go to from current state
    we know that current state is winning if any one of the reachable states is losing (we are giving losing state to the opponent)
    and current state is losing, if all of the reachable states are winning (we cannot give the losing state to the opponent)
    
    To calculate the Grundy value of a given state you need to:
        - Get all possible transitions from this state
        - Each transition can lead to a sum of independent games (one game in the degenerate case). Calculate the Grundy value for each independent game and xor-sum them. Of course xor does nothing if there is just one game.
        - After we calculated Grundy values for each transition we find the state's value as the mex  of these numbers.
        - If the value is zero, then the current state is losing, otherwise it is winning.

    In this game, for ex current state = 6
    then reachable states would be {(1,5), (2,4)} 
    (3,3) would not be there because we have to divide a heap into two nonempty heaps that have a different number of coins
    now, we can find grundy value of our current state
        G(6) = mex(XOR(G(1), G(5)), XOR(G(2), G(4)))
    and then determine, if G(6) = 0 it is a losing state, otherwise winning one

    
*/
// #define double long double

string ps = "\n";

int findMex(set<int>& set) {
    for(int i=0;i<3000;i++) {
        if(!set.count(i)) {
            return i;
        }
    }

    return 3000;
}

void solve() {
    // int i, n;
    // cin >> n;

    // // int xr = 0;
    // // for(i=0;i<n;i++) {
    // //     int x;
    // //     cin >> x;

    // //     if(i&1) {
    // //         xr ^= x;
    // //     }
    // // }

    // cout << (!(n&1) ? "first" : "second") << "\n";
    // int i, maxn=int(1e6)+1;
    // int i, maxn=25;
    int i, maxn=2001;
    int dp[maxn+1] = {0};

    // debug((6+1)/2-1);
    // debug((7+1)/2-1);
    for(i=3;i<=maxn;i++) {
        set<int> rs;
        for(int j=1; j <= (i+1)/2-1; j++) {
            // if(dp[j] == dp[i-j]) {
            //     debug(j, i-j);
            //     dp[i] = 1;
            //     break;
            // }
            rs.insert(dp[j] ^ dp[i-j]);
        }
        dp[i] = findMex(rs);
        debug(i, dp[i]);
        // dp[i] = mex;
    }
    debuga(dp, 0, maxn);

    int t, n;
    cin >> t;
    while(t--) {
        cin >> n;
        if(n > 2000) {
            cout << "first\n";
        }
        else {
            cout << (dp[n] ? "first" : "second") << "\n";
        }
        // cout << (dp[n] ? "first" : "second") << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    cout.tie(NULL);
    int t;
    // cin >> t;
 
    // while(t--)
    // {
        solve();
    // }
 
    return 0;
}