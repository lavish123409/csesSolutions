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
 
/*
 
    I approach
    we can keep on finding next permutation string until there is no more next permutation
    for next permutation, the string should have next greater character at index i and that index i, should be as close to the end as possible
    for ex, s = abc
    and next permutation would be acb, where next greater character is c than b, and we would make change to index 2 before that index 1

    for finding next permutation,
        - we would traverse from right
        - and check, whether there is any bigger character than current character to the right of it
            - for this we can take an index i from right, and search on left side if there is any smaller character, or
            - we can observer that the right portion of the string would be sorted, so for every character we can do binary search to find the bigger character on the right side
        - now, we have found a character on left side at i and a bigger character on right side at j
            s[i] < s[j] and i < j
        - now, we can swap the characters at position i and j and we would get a bigger string than previous
        - and to make it the next string, we have to decrease its distance as much as possible
        - so, we can sort all the characters after index i, but we already know that the right part of string is sorted in decreasing order, so we can just reverse it to sort it in increasing order



*/
string ps = "\n";

bool isNextStringPossible(string& s) {
    int i, j, n=s.size();

    for(i=n-1; ~i; i--) {
        int ri = n-1-i;
        int j = upper_bound(s.rbegin(), s.rbegin()+ri, s[i]) - s.rbegin();
        j = n-1-j;

        if(i != j) {
            swap(s[i], s[j]);
            reverse(s.begin() + i + 1, s.end());
            return 1;
        }
    }

    return 0;
}

int fact(int n) {
    int f = 1;
    for(int i=2;i<=n;i++) {
        f *= i;
    }

    return f;
}

void solve() {
    string s;

    cin >> s;

    // cout << isNextStringPossible(s) << "\n";
    // cout << s << "\n";

    sort(s.begin(), s.end());
    int n=s.size(), ans = fact(n);
    int cnt[26] = {0};
    for(int i=0;i<n;i++) {
        cnt[s[i] - 'a']++;
    }

    for(int i=0;i<26;i++) {
        ans /= fact(cnt[i]);
    }

    cout << ans << "\n";
    while(1) {
        cout << s << "\n";
        if(!isNextStringPossible(s)) break;
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