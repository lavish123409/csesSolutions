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
 
    I approach
    KMP algorithm - 
    we have to make a longest proper prefix which is also a suffix array for pattern
    suppose we are trying to match our pattern to text and at some character it mismatches, then we would lose all progress made till now, if we start from beginning (from i+1 index) as we do in brute force
    we do not want to go so much back, so what we can do, we know that the string covered till now in pattern was matching with the text
    so, we are sure that the suffix of the string covered till now is similar to text to some extent
    if we can find find some portion in the starting of pattern, i.e, prefix similar to suffix, then we can directly go to next character of prefix and start matching from there
    in this way, we would not have to start from 0 index of pattern and we can start from len(prefix)+1 index of pattern
    for this we would have to make lps or pi array, in which we would store length of longest proper prefix which is also the suffix of pattern
    
    Making lps array
    we can take left pointer at 0 and current pointer at i = 1 to len(pattern)-1
        if current character matches with left pointer, then increment both pointer and store left pointer value in lps[current]
        if it does not matches, then reset left pointer to 0 and see if starting character of pattern matches, and do same as previous point
        if it does not matches store left pointer index and increment just current index

    traverse the text string and pattern string
        if we reached end of pattern or current character does not matches
            if we reached end of pattern, increment the answer
            then, make pattern index = lps[pattern index - 1] if pattern index > 0 else 0
        if current character matches for both, increment both pointers

    TLE1 
    CHANGES
    traverse the text string and pattern string
        if we reached end of pattern or current character does not matches
            if we reached end of pattern, increment the answer
            if pattern index is 0, there is no way we can match any string of pattern to text as first character is only not matching
            then, make pattern index = lps[pattern index - 1]
            decrease current index as we need to match current character with new character in prefix
        if current character matches for both, increment both pointers

    WA
    while matching pattern, we go too far and the second occccurence of pattern also started coming
    consider the example, AAACAAAA and i = 7. The idea is similar to search step.

    cp algo solution - KMP
    finding prefix function
    for i = 1 to n-1:
        j = pi[i-1]
        while j > 0 && pattern[j] != pattern[i]:
            j = pi[j-1]
        if pattern[j] == pattern[i]:
            j++
        pi[i] = j
    

*/
string ps = "\n";

void solve() {
    
    string s, t;
    cin >> s >> t;

    int n=s.size(), m=t.size();
    int lps[m] = {0};
    // memset(lps, -1, sizeof(lps));

    int i,j,l=0;
    // for(i=1;i<m;i++) {
    //     if(t[i] == t[l]) {
    //         l++;
    //     }
    //     else {
    //         // l=0;
    //         // if(t[i] == t[l]) {
    //         //     l++;
    //         // }
    //         if(l != 0) {
    //             l=lps[l-1];
    //             i--;
    //             continue;
    //         }
    //     }
    //     lps[i] = l;
    // }
    for(i=1;i<m;i++) {
        int j = lps[i-1];
        while(j > 0 && t[i] != t[j]) {
            j = lps[j-1];
        }
        if(t[i] == t[j]) {
            j++;
        }
        lps[i] = j;
    }
    debuga(lps, 0, m-1);

    j=0;
    int ans=0;
    for(i=0;i<n;i++) {
        // debug(i, j, s[i], t[j]);
        // if(j >= m || s[i] != t[j]) {
        //     if(j >= m) ans++;
        //     if(j == 0) continue;
        //     j = lps[j-1];
        //     i--;
        // }
        // else {
        //     j++;
        // }
        // debug(i, ans);
        while(j > 0 && s[i] != t[j]) {
            j = lps[j-1];
        }
        if(s[i] == t[j]) {
            j++;
        }
        if(j == m) {
            ans++;
            j = lps[j-1];
        }
    }
    if(j >= m) ans++;

    cout << ans << "\n";

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