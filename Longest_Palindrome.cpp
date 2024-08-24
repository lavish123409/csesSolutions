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
 
/*
 
    Solution
    based on z algorithm - Manacher's algorithm
    the idea is similar to bounding box in z-algorithm, i.e
        - at every index, try to get the value from previous values related to bounding box, so that while extending we do not have to start from minimum value
        - try to extend the bounding box as much as possible
    for normal z-algorithm, it was
        - at every index, try to get the value from the prefix of string and get some greater value to start the longest prefix from current index which is similar to prefix of complete string
        - try to extend the bounding box as much as possible

    first, we would change string such that we do not have to handle edge cases for odd and even separately
    s=babbabbabc -> t=#b#a#b#b#a#b#b#a#b#c#
    now, for odd string at index 4, palindrome in s would be 9
    and in t the number of characters which is common in prefix starting at index 9 and reverse of suffix ending at i, that is, rev(t[i-10..i]) == t[i..i+10] meaning s[i-10..i+10] is palindrome
    so, we have to find out the way that we can get some better values from previous values
    here, we would have to see this fact that if there is some palindrome of length x
    and it is a part of a bigger palindrome of length y
    then, that palindrome would dalso occur on the otther side of y string
    for ex, ...aabaa...a...aabaa...
            |----------y----------|
               |-x-|       |-x-|

    so, if we are considering center at some character at index i, and there exist a palindrome of length p[i] at i
    then, we can make a bounding box of i-p[i] and i+p[i], and populate the values ahead of index i

    p[i] = max(0, min(r - i, p[l + r - i]))
    while s[i-p[i]] == s[i+p[i]]:
        p[i]++
    if i + p[i] > r:
        l = i - p[i]
        r = i + p[i]

*/
string ps = "\n";

// void solve() {
    
//     string s;
//     cin >> s;

//     int i, n=s.size();
//     string t="#";

//     for(i=0;i<n;i++) {
//         t.push_back(s[i]);
//         t.push_back('#');
//     }

//     n=t.size();
//     int p[n]={0}, l=-1, r=1;
//     for(i=0;i<n;i++) {
//         p[i] = max(0, min(r-i, p[l+r-i]));
//         while(i-p[i] >= 0 && i+p[i] < n && t[i-p[i]] == t[i+p[i]]) {
//             p[i]++;
//         }

//         if(i+p[i] > r) {
//             l = i - p[i];
//             r = i + p[i];
//         }
//     }
//     debug(t);
//     debuga(p, 0, n-1);

//     // cout << *max_element(p, p+n) - 1 << "\n";
//     // int ind = max_element(p, p+n) - p;
//     int ind=-1, len=0;
//     for(i=0;i<n;i++) {
//         if(p[i] > len) {
//             ind = i;
//             len = p[i]-1;
//         }
//     }

//     ind = (ind - 1) / 2;
//     int hl=(len - 1)/2;
//     debug(hl, ind);
//     // for(i=0;i<hl;i++) {
//     //     cout << s[ind - (hl-i-1)];
//     // }
//     // if(len&1) {
//     //     cout << s[ind];
//     // }
//     // for(i=1;i<=hl;i++) {
//     //     cout << s[ind+i];
//     // }
//     cout << s.substr(ind - hl, len) << "\n";

// }

void solve() {
    
    string s;
    cin >> s;

    int i, n=s.size();
    int dp[n][2];
    memset(dp, 0, sizeof(dp));

    int l1=0,r1=-1;
    int l2=0,r2=-1;
    int ans=0, mxl=1;
    for(i=0;i<n;i++) {
        int k=0;
        if(i > r1) k=1;
        else k = min(r1 - i + 1, dp[l1 + r1 - i][0]);
        while(i-k >= 0 && i+k < n && s[i-k] == s[i+k]) {
            k++;
        }
        dp[i][0] = k--;
        if(2 * dp[i][0] - 1 > mxl) {
            ans = i - (dp[i][0] - 1);
            mxl = 2 * dp[i][0] - 1;
        }
        debug(ans);

        if(i + k > r1) {
            l1 = i - k;
            r1 = i + k;
        }

        k=0;
        if(i <= r2) k = min(r2 - i + 1, dp[l2 + r2 - i + 1][1]);
        while(i-k-1 >= 0 && i+k < n && s[i-k-1] == s[i+k]) {
            k++;
        }
        dp[i][1] = k--;
        if(2 * dp[i][1] > mxl) {
            ans = i - dp[i][1];
            mxl = 2 * dp[i][1];
        }
        debug(ans);

        if(i + k > r2) {
            l2 = i - k - 1;
            r2 = i + k;
        }
    }
    debug(ans, mxl);

    cout << s.substr(ans, mxl) << "\n";

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