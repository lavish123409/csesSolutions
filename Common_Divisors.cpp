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
 
    did a very silly mistake in thinking about the problem
    I thought that if we would store the divisors of all elements in a frequency array, then the gretest common divisor can be the product of any 2 divisors
    so, it can happen that some divisor came in more than 2 numbers
    then, how would we find that some divisors occured in exactly 2 indices, and take their product to make greatest common divisor

    MISTAKE
    if we are finding divisor, and suppose answer is a * b, then a * b would also be the divisor of those 2 numbers of which a and b are the divisors
    for ex, suppose 2 and 3 are divisors of 2 numbers, then 6 would also be the divisor of those 2 numbers
    we can take a frequency array and the highest number which have frequency >= 2, that is our gcd

    TLE (not knowing)
    I was doing multiplication of j*j to check the square root, which might be taking lot of time
    instead, we can find put square root, and run loop till that

*/
string ps = "\n";

const int MAXN = 1e6+1;
int cnt[MAXN];

int gcd(int a, int b) {
    if(b == 0) return a;

    return gcd(b, a%b);
}

void solve() {
    
    int i, n;
    cin >> n;

    for(i=0;i<n;i++) {
        int x;
        cin >> x;

        int up = (int)sqrt(x);
        for(int j=1;j<=up;j++) {
            if(x % j == 0) {
                cnt[j]++;
                debug(x, j);
                if(j != x/j) {
                    cnt[x/j]++;
                    debug(x, x/j);
                }
            }
        }
    }

    for(i=MAXN-1;i>=1;i--) {
        if(cnt[i] >= 2) {
            cout << i << "\n";
            break;
        }
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

// #include <cmath>
// #include <iostream>
// using namespace std;

// const int MAX_VAL = 1e6;

// // divisors[i] = stores the count of numbers that have i as a divisor
// int divisors[MAX_VAL + 1];

// int main() {
// 	ios_base::sync_with_stdio(0);
// 	cin.tie(0);

// 	int n;
// 	cin >> n;
// 	for (int i = 0; i < n; i++) {
// 		int a;
// 		cin >> a;

// 		const int up = (int)sqrt(a);
// 		for (int div = 1; div <= up; div++) {
// 			if (a % div == 0) {
// 				// the divisor and quotient are both divisors of a
// 				divisors[div]++;
// 				// make sure not to double count!
// 				if (div != a / div) { divisors[a / div]++; }
// 			}
// 		}
// 	}

// 	for (int i = MAX_VAL; i >= 1; i--) {
// 		if (divisors[i] >= 2) {
// 			cout << i << endl;
// 			break;
// 		}
// 	}
// }