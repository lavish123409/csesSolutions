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
    it would be O(n * k * logk)

    I approach
    we can use silding window technique, just if we can get sorted k elements, in which we can insert elements at right and delete left elements
    if we would use set data structure to store k elements, we can get sorted elements but we would not be able to get the middle element
    instead, we can use 2 sets, one for smaller elements and another for greater elements
    the smaller elements set can have at most one more element than greater elements set
    when both sets size combined would become equal to k, we can access largest element in smaller element which would be median, because from above property if both sets' size are equal then both contains k/2 elements
    we can remove elements from left using another pointer

    we would have to use multiset otherwise, we cannot have duplicate elements

    TLE1 - didn't realised that we can use median to separate incoming elements
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

    // int a[n];
    for(i=0;i<n;i++) {
        cin >> a[i];
    }

    // multiset<int> smel, grel;
    int l=0, r;
    for(r=0;r<n;r++) {
        // if(smel.empty() || *smel.rbegin() >= a[r]) {
        //     smel.insert(a[r]);
        // }
        // else if(grel.empty() || *grel.begin() <= a[r]) {
        //     grel.insert(a[r]);
        // }
        // smel.insert(a[r]);
        // if(!grel.empty() && *grel.begin() <= a[r]) {
        //     grel.insert(a[r]);
        // }
        // else {
        //     smel.insert(a[r]);
        // }
        if(smel.empty() || *smel.rbegin() >= a[r]) {
            smel.insert(a[r]);
            if(grel.size()+1 < smel.size()) {
                grel.insert(*smel.rbegin());
                multiset<int>::iterator itr = smel.end();
                itr--;
                smel.erase(itr);
                // if(ind++ == 10) {
                //     cout << 1/0 << "\n";
                // }
            }
        }
        else {
            grel.insert(a[r]);
            if(grel.size() > smel.size()) {
                smel.insert(*grel.begin());
                grel.erase(grel.begin());
                // if(ind++ == 5) {
                //     cout << 1/0 << "\n";
                // }
            }
        }
        // debug(r);
        // debug(smel);           
        // debug(grel);

        // while(!smel.empty() && *smel.rbegin() > *grel.begin()) {
        //     grel.insert(*smel.rbegin());
        //     multiset<int>::iterator itr = smel.end();
        //     itr--;
        //     smel.erase(itr);
        // }

        // int ind=0;
        // we would use while instead of if because it can happen that we removed some element in last step
        // and this time we inserted one element, so smel can have greater than one size than smaller elements
        // if(grel.size() > smel.size()) {
        //     smel.insert(*grel.begin());
        //     grel.erase(grel.begin());
        //     // if(ind++ == 5) {
        //     //     cout << 1/0 << "\n";
        //     // }
        // }

        // if(grel.size()+1 < smel.size()) {
        //     grel.insert(*smel.rbegin());
        //     multiset<int>::iterator itr = smel.end();
        //     itr--;
        //     smel.erase(itr);
        //     // if(ind++ == 10) {
        //     //     cout << 1/0 << "\n";
        //     // }
        // }
        // cout << smel.size() << " , " << grel.size() << "\n";

        // if(smel.empty()) {
        //     smel.insert(a[r]);
        // }

        // int median = *smel.rbegin();
        // if(a[r] > median) {
        //     grel.insert(a[r]);
        // }

        if(r >= k-1) {
            // debug(l, a[l]);
            // debug(smel);           
            // debug(grel);
            cout << *smel.rbegin() << " ";
            // if(!smel.empty() && smel.count(a[l])) {
            //     smel.erase(smel.find(a[l]));
            // }
            // else if(!grel.empty() && grel.count(a[l])) {
            //     grel.erase(grel.find(a[l]));
            // }
            if(smel.find(a[l]) != smel.end()) smel.erase(smel.find(a[l]));
            else grel.erase(grel.find(a[l]));

            if(smel.empty() && !grel.empty()) {
                smel.insert(*grel.begin());
                grel.erase(grel.begin());
            }

            l++;
        }
    }
    cout << "\n";
    return 0;
}

// #include <algorithm>
// #include <iostream>
// #include <set>
// using namespace std;

// long N, M;
// long arr[200010];
// multiset<long> up;
// multiset<long> low;

// void ins(long val) {         // insert val into sets
// 	long a = *low.rbegin();  // current median
// 	if (a < val) {
// 		up.insert(val);
// 		if (up.size() > M / 2) {
// 			low.insert(*up.begin());
// 			up.erase(up.find(*up.begin()));
// 		}
// 	} else {
// 		low.insert(val);
// 		if (low.size() > (M + 1) / 2) {
// 			up.insert(*low.rbegin());
// 			low.erase(low.find(*low.rbegin()));
// 		}
// 	}
// }

// void er(long val) {  // erase from sets
// 	if (up.find(val) != up.end()) up.erase(up.find(val));
// 	else low.erase(low.find(val));
// 	if (low.empty()) {
// 		low.insert(*up.begin());
// 		up.erase(up.find(*up.begin()));
// 	}
// }

// int main() {
// 	cin >> N >> M;
// 	for (int i = 0; i < N; i++) cin >> arr[i];
// 	low.insert(arr[0]);
// 	for (int i = 1; i < M; i++) ins(arr[i]);
// 	cout << *low.rbegin() << " ";
// 	for (long i = M; i < N; i++) {
// 		if (M == 1) {
// 			ins(arr[i]);
// 			er(arr[i - M]);
// 		} else {
// 			er(arr[i - M]);
// 			ins(arr[i]);
// 		}
// 		cout << *low.rbegin() << " ";
// 	}
// 	cout << endl;
// }