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
    tip: see the question clearly, lost a lot of time because of reading question wrong
    the question is basically asking that if you are given n sticks, then is the first perso winning or losing
    and we have to give answer for every number of stick from 1 to n
    and we are given some possible moves p1, p2, ... pn, that we can remove these many sticks from the heap at once

    if we would see from the perspective of Game Theory,
        - if we would try all possbile moves from current position, and we are getting to a losing position from at least one of the possible moves, then current position is winning
        - if we are getting to a winning position for every possible move which we can try, then current position is losing position

    so, we can run a loop for every number of sticks, and see whether we can land to any losing position, after removing p1 or p2 or ... pn sticks
        - if we can, then current position is winning position
        - otherwise, current position is losing position
    0 is the losing position because if there are no sticks to remove then first person to do a move would lose, because he would not able to make a move
    we can then use a dp solution to find the answer for every position

    for number_of_sticks from 1 to n:
        for sticks_to_remove in possible_moves:
            if number_of_sticks - sticks_to_remove >= 0 and dp[number_of_sticks - sticks_to_remove] == 0:
                dp[number_of_sticks] = 1
                break


*/
// #define double long double

string ps = "\n";
void solve() {
    int i, n, k;
    cin >> n >> k;

    bool dp[n+1] = {0};
    dp[0] = 0;
    int am[k];
    for(i=0;i<k;i++) {
        cin >> am[i];
    }

    for(i=1;i<=n;i++) {
        for(int j=0;j<k;j++) {
            if(i - am[j] >= 0 && !dp[i - am[j]]) {
                dp[i] = 1;
                break;
            }
        }
    }

    for(i=1;i<=n;i++) {
        if(dp[i]) {
            cout << "W";
        }
        else {
            cout << "L";
        }
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