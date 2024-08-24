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
 
// tip: try to think about recursive solutions for Mathematical problems
// sometimes it becomes too complex to use just 1 formula to calculate complete answer
 
/*
 
    I approach
    I am thinking that if we would see the bits of numbers
    for ex, n=9
    in first iteration, those numbers would be eliminated whose first bit is 0
    2->0010, 4->0100, 6->0110, 8->1000
    in second iteration, those numbers would be eliminated whose second bit is 0
    1->0001, 5->0101, 9->1001
    but, in third iteration 7 would be eliminated whose third bit is 1 and not 0
    it is maybe because we have eliminated last number in last iteration, so maybe the bit to check would flip if last number is eliminated in current iteration
    also, the number from which we would start would also change based on last number elimination

    PROBLEM - it is becoming too complex to code

    Solution - codeforces
    we can solve this problem recursively
    check if kth number is present in current iteration, i.e, k < n/2
    if it is answer is 2k
    otherwise, we can run second iteration on 1,2...n/2 recursively and whatever is the answer return the 2*ans-1

    MY THINKING
    we would pass whether we are eliminating numbers from first position or second position, so all cases would be
    if total number is odd
        if we are eliminating numbers from 1st position
            if we can get kth number in current iteration
                then it would be a odd number, which can be represented by 2*k-1
            otherwise, we would have eliminated ceil(n/2) numbers, and can recurse over remaining numbers
                so total number would decrease to n/2 numbers, numbers remaining
                k would decrease by numbers eliminated, i.e, ceil(n/2)
                and last number would be removed, so we would have to start eliminating from second number

    Similaraly, all other 7 cases also be written

    ACTUAL SOLUTION
    the idea is to make odd numbers also handlable like even numbers
    we would always consider that numbers are even and we are eliminating from second position
    for even numbers, we do not have to do anything, the recursion would be that total number would be halved and k would be halved
    and we can pass numbers 1,3,5... to next iteration, then mapping would be
    1->1, 2->3, 3->5...
    for odd numbers. we can consider the starting number of next iteration in current iteration
    for ex, consider n=5, k=3
    now while eliminating, we would eliminate 2 then 4
    and then we would have to go to next iteration
    but we know that the starting number only would be the answer as k=1, after current iteration
    so, without going to next iteration we can directly return that number, i.e, 1 from current iteration
    otherwise, if k is greater, than
    we would pass 3,5,7.... to next iteration and map them as 2*ans+1
    because mapping would be
    1->3, 2->5, 3->7....
    and we can decrease k by ceil(n/2)

*/
string ps = "\n";


// int recurse(int n, int k, bool startFromFirstPosition) {

//     debug(n, k, startFromFirstPosition);
//     if(n == 1) {
//         return 1;
//     }

//     if(n&1) {
//         if(startFromFirstPosition) {
//             if(k <= (n+1)/2) {
//                 return 2 * k - 1;
//             }

//             return 2 * recurse(n>>1, k - (n >> 1) - 1, 0);
//         }
//         else {
//             if(k <= n/2) {
//                 return 2 * k;
//             }

//             return 2 * recurse((n>>1) + 1, k - (n >> 1), 1) - 1;
//         }
//     }
//     else {
//         if(startFromFirstPosition) {
//             if(k <= n/2) {
//                 return 2 * k - 1;
//             }

//             return 2 * recurse(n>>1, k - (n >> 1), 1);
//         }
//         else {
//             if(k <= n/2) {
//                 return 2 * k;
//             }

//             return 2 * recurse(n>>1, k - (n >> 1), 0) - 1;
//         }
//     }
// }

int recurse(int n, int k) {

    if(n == 1) {
        return 1;
    }

    if(k <= (n+1)/2) {
        if(2*k > n) return (2 * k) % n;
        else return 2*k;
    }

    int ans = recurse(n/2, k - (n+1)/2);
    if(n&1) return 2 * ans + 1;
    else return 2 * ans - 1;
}

void solve() {
    int i, n, k;
    cin >> n >> k;

    cout << recurse(n, k) << "\n";

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