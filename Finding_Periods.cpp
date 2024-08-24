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
    using KMP algorithm - 
    I am thinking that we can use prefix function to solve this question
    for any prefix to satisfy that condition, we would first look at the longest prefix satisfying that condition
    for ex, if string is abc and complete string is abcabcabcabc, then longest prefix would be abcabc, and after that we can go to abc
    after finding longest prefix, total string would be string = prefix + prefix + partial
    so, the prefix would also be the suffix, and its length would be >= length of prefix / 2
    the, we can update current prefix to its lps, because we know that its length >= length of current prefix / 2, so its structure would be prefix + prefix and not prefix + some_other_string + prefix
    then, we can do same recursively for every prefix until we find some prefix whose length < length of prefix / 2, because in that case its structure would become prefix + some_other_string + prefix, and we cannot break the string recursively now

    find lps
    find the index in string at which lps[i] >= (i + 1) / 2
    increment the answer and make i = lps[i-1] recursively
    do this until lps[i] < (i + 1) / 2

    PROBLEM
    how would we know the length of last partial prefix?
    for ex, consider a string with prefix length a, 2a, 3a, then last partial prefix can have length from 0 to a-1
    aaaaaaaaaaa
    -> a + a + a + a + a + a + a + a + a + a + a, 1 is a period
    -> aa + aa + aa + aa + aa + a, 2 is a period
    -> aaa + aaa + aaa + aa, 3 is a period
    -> aaaa + aaaa + aaa, 4 is a period
    -> aaaaa + aaaaa + a, 5 is a period

    peekeing the solution
    form peeking into the solution of USACO, it seems that in this question we have to use Z algorithm
    in Z algorithm, we have to make z array which tells for every index in string s, i from 0 to n-1 what is the maximum length of prefix starting from i, i.e, s[i..n-1], which is equal to s[0..n-1]
    we can make Z array (also peeked), by taking 2 pointers l and r
    we would extend r as much as possible till it is matching some prefix of s, and if it does not matches
    then, increment l till r and put zarr[l] = (r - l)
    if i was 0, then current character is not even matching first character of string, so we can increment current character index, that is, r
    make i=0, to start the prefix in current string

    PROBLEM
    consider string abcabc, here for index 3, z value would be 3 because prefix of length 3 "abc" at index 3 is same as "abc..." prefix at index 0
    but for index 4, z value would be 0 but according to your algorithm, z value would come as 2, which is wrong

    Solution for Z array - https://cp-algorithms.com/string/z-function.html
    we have to think in terms of subsegments which is a prefix of complete string
    suppose we are currently at segment [l,r) which would be similar to s[0..(r-l)] because of the algorithm
    now, at current index i, if it less that r, then it means the minimum value which it can have would z[i-l] but to stop the length from going beyond right boundary, we should see which comes first in (r - i) or z[i - l]
    and increase the segment if it can be increased
    and update the z length

    in total, the idea for Z algorithm is
    increase the Z value from pre-computed values
    increase the segment if we can
    and also update the Z value

    then, after Z array is calculated then, we can see that if some string is a period then, if that string would come as prefix then the string ahead of it would be similar to the complete string till the end
    for ex, consider string "abcabca" and prefix as "abc", then the string ahead of it "abca" completely is similar to the full string upto its length, i.e, 4
    so, we can check if i + z[i] >= n, then i is a length of a period



*/
string ps = "\n";

void solve() {
    string s;
    cin >> s;

    int i, n=s.size();
    // int zarr[n] = {0};

    // int l=1, r=1;
    // // for(int l=0, r=0; r < n; )
    // while(r < n) {
    //     i=0;
    //     while(r < n && s[i] == s[r]) {
    //         i++;
    //         r++;
    //     }

    //     while(l < r) {
    //         zarr[l] = (r - l);
    //         l++;
    //     }

    //     if(i == 0) l++, r++;
    // }

    // for(i=0;i<n;i++) {
    //     cout << zarr[i] << " ";
    // }
    // cout << "\n";

    int z[n] = {0};

    int l=0, r=0;
    for(i=1;i<n;i++) {
        if(i < r) {
            z[i] = min(r - i, z[i - l]);
        }

        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }

        if(i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }

    for(i=0;i<n;i++) {
        if(i + z[i] >= n) {
            cout << i << " ";
        }
    }
    cout << n << "\n";
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