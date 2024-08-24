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
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif
 
 

/*
    
    I approach
    approach is like Subarray Sums II, in which we maintain a set of previously occured prefix sums
    and at every index see which are the prefix sums that have occured before it
    and subtract the target to check whether the current_sum - target has occured, if it is count the times and that many times target can also be formed from that subarray sum

    similarly, we can maintain a window of size ranging from length a to b, and find the minimum prefix sum occured in it
    and then subtract that prefix sum from current prefix sum
    and find maximum over all indices

*/
const int MAXN = 2e5+5;
int a[MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    cout.tie(NULL);

    int n, a, b;
    cin >> n >> a >> b;
    // a--;
    b++;
    debug(a,b);

    int arr[n+1], i;
    for(i=0;i<n;i++) {
        cin >> arr[i+1];
    }

    ll psm[n+1];
    psm[0] = 0;
    multiset<ll> mps;
    // mps.insert(0);

    int l=0, r=0;
    ll csm = 0ll, ans=LONG_LONG_MIN;
    for(r=1;r<=n;r++) {
        csm += arr[r];
        psm[r] = csm;

        if(r - a >= 0) {
            mps.insert(psm[r - a]);
        }
        if(r - b >= 0) {
            mps.erase(mps.find(psm[r - b]));
        }

        debug(r, arr[r], mps, csm);

        if(!mps.empty()) {
            ans = max(ans, csm - *mps.begin());
        }
    }

    cout << ans << "\n";
    return 0;
}