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
    in brute force, we can collect k elements at every index and sort it and find median for it
    and then trverse through all elements in window and find the cost for all elements
    it would be O(n * (k * logk + k))

    I approach
    we can use silding window technique, just if we can get sorted k elements, in which we can insert elements at right and delete left elements
    if we would use set data structure to store k elements, we can get sorted elements but we would not be able to get the middle element
    instead, we can use 2 sets, one for smaller elements and another for greater elements
    the smaller elements set can have at most one more element than greater elements set
    when both sets size combined would become equal to k, we can access largest element in smaller element which would be median, because from above property if both sets' size are equal then both contains k/2 elements
    we can remove elements from left using another pointer

    we would have to use multiset otherwise, we cannot have duplicate elements

    for finding cost for smaller elements we can take sum of all left elements and subtract it from number_of_small_elements * median
    it would give us median - a_i, when i < median_index for every smaller element

    for finding cost for greater elements we can take sum of all right elements and subtract number_of_large_elements * median from it
    it would give us a_i - median, when i < median_index for every greater element

    every time, if any element is inserted or deleted, we should reorder elements in both sets

*/
const int MAXN = 2e5+5;
multiset<int> smel, grel;
int a[MAXN];
int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    cout.tie(NULL);

    int i, n, k;
    cin >> n >> k;

    int a[n];
    for(i=0;i<n;i++) {
        cin >> a[i];
    }

    multiset<int> low, up;
    int l=0;
    ll lsum=0ll, rsum=0ll;
    for(i=0;i<n;i++) {
        if(low.empty() || *(low.rbegin()) >= a[i]) {
            low.insert(a[i]);
            lsum += a[i];
            if(low.size() > k / 2 + 1) {
                rsum += *low.rbegin();
                lsum -= *low.rbegin();
                up.insert(*low.rbegin());
                low.erase(low.find(*low.rbegin()));
            }
        }
        else {
            up.insert(a[i]);
            rsum += a[i];
            if(up.size() > k / 2) {
                lsum += *up.begin();
                rsum -= *up.begin();
                low.insert(*up.begin());
                up.erase(up.begin());
            }
        }
        // debug(i);
        // debug(low);
        // debug(up);

        if(i >= k-1) {
            int median = *low.rbegin();
            ll lcost = 1ll * median * low.size() - lsum;
            ll rcost = rsum - 1ll * median * up.size();

            cout << lcost + rcost << " ";

            if(low.find(a[l]) != low.end()) low.erase(low.find(a[l])), lsum -= a[l];
            else up.erase(up.find(a[l])), rsum -= a[l];
            l++;

            if(low.empty() && !up.empty()) {
                lsum += *up.begin();
                rsum -= *up.begin();
                low.insert(*up.begin());
                up.erase(up.begin());
            }
        }
    }
    cout << "\n";

    return 0;
}