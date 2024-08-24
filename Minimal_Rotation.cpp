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
    I am thinking to use the hashing for checking the lexicographically smallest string
    the hashing algorithm is as follows
        hash(s) = s[0] + s[1] * p + s[2] * p^2 + ... + s[n-1] * p^(n-1) mod m
    so, we can see that first character is multiplied by smallest factor and then the multiplying factor increases
    so, we can suppose that the lexicographically smallest string would have the smallest hash
    and while traversing the string, we would change the hash to make rotated string a proper string
        hash(s) = s[0] * p^(n-1) + s[1] + s[2] * p + ... + s[n-1] * p^(n-2) mod m
    for this, we would have to multiply the hash(s[0..i-1]) = hsh[i-1], with p^(n-i)
    and multiply the hash(s[i..n-1]) = (hsh[n-1] - hsh[i-1]), with p^(-1)
    then, we can add both and we would have the hash of string s[i..n-1] + s[0..i-1]
    and we can compare it with smallest hash till now

    PROBLEM
    we cannot compare hash value, we can only equate them
    for ex, hash(i) = i % n
    then, hash(n+1) < hash(2), which would not be true if n > 2

    Solution - Booth's algorithm(https://en.wikipedia.org/wiki/Lexicographically_minimal_string_rotation)
    the essenece of booth's algorithm is similar
    it is based on modified KMP algorithm
    we can see following problems might arise, if we would try to use KMP algorithm
        - when we would update the index of minimum rotated string, the pointer would come at that index at which the lps values would be wrong
        for ex, string = a b c d ... a b   c   a   ...
                index    0 1 2 3 ... i i+1 i+2 i+3 ...
                lps      0 0 0 0 ... 1 2   3   1   ...
        now, the minimum string index would come at i, but lps at i, i+1, and so on, would become wrong
        - for simplicity, we can store the index value at which we should go if current prefix does not matches with minimum rotation

    how we should modify KMP algorithm
        - we would only store the lps values in 0 to n indices, that is, the values would be stored with respect to minimum rotation index
        for ex, string = a b c d ... a b   c   a   ...
                index    0 1 2 3 ... i i+1 i+2 i+3 ...
                lps      0 0 0 0 ... 1 2   3   1   ...
            would become,
                string = a b c d ... a b   c   a   ...
                index    0 1 2 3 ... i i+1 i+2 i+3 ...
                lps      0 0 0 1 ...
        but, we would have to take lps array of size 2*n, because if string is aaaaa, then till 2*n, the minimum stirng index would be 0 and lps array size would keep increasing
        - we would store the index at which we should go if current prefix does not matches with minimum rotation, in other words we would fail to that index, maybe that's why it is called failure array ;)

    explanation should be with code

*/
string ps = "\n";

int power(int b, int e, int mod) {
    if(e == 0) {
        return 1;
    }

    if(e == 1) {
        return b;
    }

    int hp = power(b, e>>1, mod);
    hp = (1ll * hp * hp) % mod;
    if(e&1) {
        hp = (1ll * hp * b) % mod;
    }

    return hp;
}

void solve() {
    string s;
    cin >> s;
    s += s;

    int i, n=s.size();
    // int p=31;
    // int mod = int(1e9+9);
    // int hash[n];
    // hash[0] = s[0];
    // int pwr = p;
    // for(i=1;i<n;i++) {
    //     hash[i] = (1ll * hash[i-1] + (1ll * s[i] * pwr) % mod) % mod;
    //     pwr = (1ll * pwr * p) % mod;
    // }
    // int thash=s[1];
    // pwr = p;
    // for(i=1;i<n;i++) {
    //     thash = (1ll * thash + (1ll * s[(i+1) % n] * pwr) % mod) % mod;
    //     pwr = (1ll * pwr * p) % mod;
    // }
    // debug(thash);
    // debuga(hash, 0, n-1);
    // int npow = power(p, n, mod);
    // int invp = power(p, mod-2, mod);

    // int mnhsh = hash[n-1], ans=0;
    // for(i=1;i<n;i++) {
    //     int lhsh = (1ll * hash[i-1] * npow * power(invp, i, mod)) % mod;
    //     debug(npow, power(invp, i, mod));
    //     int rhsh = (1ll * hash[i] * invp) % mod;
    //     debug(lhsh + rhsh, mnhsh);
    //     if(lhsh + rhsh < mnhsh) {
    //         mnhsh = lhsh + rhsh;
    //         ans = i;
    //     }
    // }
    // debug(ans);

    // for(i=0;i<n;i++) {
    //     cout << s[(i + ans) % n];
    // }
    // cout << "\n";

    // int flr[n] = {0};
    // int mri = 0;
    // for(i=1;i<n;i++) {
    //     int j = flr[i-mri-1];
    //     debug("1", i, j, mri);
    //     bool ran=0;
    //     while(j > 0 && s[mri + j] != s[i]) {
    //         if(s[i] < s[mri + j]) {
    //             mri = i - j;
    //             // break;
    //             // mri = i - flr[mri + j - 1];
    //         }
    //         // ran=1;
    //         j = flr[mri + j - 1];
    //     }
    //     debug("2", i, j, mri);
    //     // if(ran && s[i] < s[mri + j])

    //     if(s[mri + j] == s[i]) {
    //         j++;
    //     }
    //     else {
    //         if(s[i] < s[mri + j]) {
    //             mri = i;
    //         }
    //     }
    //     debug("3", i, j, mri);

    //     flr[i] = j;
    // }
    // debug(mri, s);

    // for(i=0;i<n/2;i++) {
    //     cout << s[i + mri];
    // }
    // cout << "\n";

    int flr[n], minimumRotationIndex=0;

    // failure lengths
    // memset(flr, 0, sizeof(flr));
    // for(i=1;i<n;i++) {
    //     int j=flr[i-minimumRotationIndex-1];
    //     while(j > 0 && s[i] != s[minimumRotationIndex+j]) {
    //         if(s[i] < s[minimumRotationIndex+j]) {
    //             minimumRotationIndex = i - j;
    //         }
    //         j = flr[j-1];
    //     }

    //     if(j == 0 && s[i] != s[minimumRotationIndex+j]) {
    //         if(s[i] < s[minimumRotationIndex+j]) {
    //             minimumRotationIndex = i;
    //         }
    //         flr[i - minimumRotationIndex] = 0;
    //     }
    //     else {
    //         flr[i - minimumRotationIndex] = j+1;
    //     }
    // }

    // failure indices
    memset(flr, -1, sizeof(flr));
    for(i=1;i<n;i++) {
        // as we are storing failure indices with respect to minimum string, we should retrieve them like that
        int j=flr[i-minimumRotationIndex-1];
        // here j means the index at which we would go if s[minimumRotationIndex..j+1] != s[i-(j+1 - minimumRotationIndex + 1) .. i]
        while(j != -1 && s[i] != s[minimumRotationIndex+j+1]) {
            // if current string is less than minimum string, then update minimumRotationIndex and go to the failure index
            // because it can happen that we can encounter more small string which is less in length also
            // for ex, aabaac...aabaaa, here "aaa" would be less than "aab"
            if(s[i] < s[minimumRotationIndex+j+1]) {
                minimumRotationIndex = i - j - 1;
            }
            j = flr[j];
        }

        // if we reached till string of length 0, and our current string's first character is still not matching with first character of minimum string
        // then check whether our current string first character, i.e, s[i] is even less than s[minimumRotationIndex]
        if(j == -1 && s[i] != s[minimumRotationIndex+j+1]) {
            // if it is then, update minimumRotationIndex to i
            if(s[i] < s[minimumRotationIndex+j+1]) {
                minimumRotationIndex = i;
            }
            // and make its failure index to -1
            flr[i - minimumRotationIndex] = -1;
        }
        // otherwise, there is some string s[minimumRotationIndex..j+1] != s[i-(j+1 - minimumRotationIndex + 1) .. i], which matched for some j index >= 0
        else {
            flr[i - minimumRotationIndex] = j+1;
        }
    }
    debug(minimumRotationIndex);

    for(i=0;i<n/2;i++) {
        cout << s[(minimumRotationIndex + i) % n];
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