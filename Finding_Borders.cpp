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
    I believe we have to find the prefix array 
    and recursivly find all proper prefixes which are prefix and suffix both

    WA1 (bug)
    while finding out the length of prefixes, j should determine the length of prefix and j-1 index
    but when I was starting the loop, I was initilazing j = n-1, but it should be j = n

    little better solution on github
    we can initialise j with lps[n-1], in that way it would be the length
*/
string ps = "\n";

void solve() {
    
    string s;
    cin >> s;

    int n=s.size();
    int lps[n] = {0};

    for(int i=1;i<n;i++) {
        int j=lps[i-1];
        while(j > 0 && s[i] != s[j]) {
            j=lps[j-1];
        }
        if(s[i] == s[j]) {
            j++;
        }

        lps[i] = j;
    }
    debuga(lps, 0, n-1);

    stack<int> ans;
    int j=lps[n-1];
    // while(j > 0) {
    // while(1) {
    //     debug(j, lps[j]);
    //     j = lps[j-1];
    //     if(j == 0) {
    //         break;
    //     }
    //     // if(lps[j] > 0) {
    //     ans.push(j);
    //     // }
    // }
    while(j > 0) {
        ans.push(j);
        j = lps[j-1];
    }

    while(!ans.empty()) {
        cout << ans.top() << " ";
        ans.pop();
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