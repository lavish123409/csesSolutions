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
    it is a standard problem of Nim game, in which 
        - if xor sum of all heap sizes is 0, then it is losing position for first person
        - if xor sum of all heap sizes is non 0, then it is losing position for second person
    in this game if we can observe carefully, then we can see that in every move we are indeed changing the xor sum only, by changing any heap size
    if the xor sum is non-zero, then first person can make it 0 by decreasing a heap by a significant amount
    then, second person would have no other choice other than to make xor sum as non-zero, which the first person can again make 0
    and finally, the losing position would be 0 0 0 ... 0, whose xor sum is 0, so first person would win the game
    
    and the first person can only lose, if and only if the xor sum is already 0
    in that case, first person would make it non-zero and second person would make it 0 again

    https://en.wikipedia.org/wiki/Nim#Proof_of_the_winning_formula
    to make the xor sum as 0, we can follow this approach
        - take the xor of xor sum with every number
        - and the number whose, xor value with xor sum is less than the number, then decrease that number to the xor value
        number ^ xor_sum = xor_value
        number = xor_value

*/
// #define double long double

string ps = "\n";

void solve() {
    int i, n;
    cin >> n;

    int xr = 0;
    for(i=0;i<n;i++) {
        int x;
        cin >> x;

        xr ^= x;
    }

    cout << (xr ? "first" : "second") << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t;
 
    while(t--)
    {
        solve();
    }
 
    return 0;
}