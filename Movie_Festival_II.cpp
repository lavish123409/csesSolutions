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
    we can order the intervals of every movie according to the ending time
    then, take a set determining number of people watching movies (movies in set would be sorted according to the ending time)
    we would traverse the array and keep on adding every interval of movie, if it is not overlapping with first movie according to the ending time
    if it is not overlapping, remove the first movie and add it to the set
    if it is overlapping, we can add it to set only if set's size < k

*/
const int MAXN = 2e5+5;
int a[MAXN];

void printQ(queue<int> q) {
    while(!q.empty()) {
        cerr << q.front() << " , ";
        q.pop();
    }
    cerr << "]\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    cout.tie(NULL);

    int i, n, k;
    cin >> n >> k;

    array<int,2> a[n];
    for(i=0;i<n;i++) {
        cin >> a[i][0] >> a[i][1];
    }

    sort(a, a+n, [](const array<int,2>& a, const array<int,2>& b) {
        return a[1] < b[1] || (a[1] == b[1] && a[0] < b[0]);
    });

    // for(i=0;i<n;i++) {
    //     cerr << a[i][0] << "," << a[i][1] << " - ";
    // }
    // cerr << "\n";

    multiset<int> rmv;
    int ans = 0;
    for(i=0;i<n;i++) {
        debug(a[i]);
        if(!rmv.empty() && *rmv.begin() <= a[i][0]) {
            auto itr = rmv.upper_bound(a[i][0]);
            itr--;
            rmv.erase(itr);
            rmv.insert(a[i][1]);
            debug(1, rmv);
            // cerr << "1\n";
            // printQ(rmv);
            ans++;
        }
        else {
            if(rmv.size() < k) {
                rmv.insert(a[i][1]);
                ans++;
            }
            debug(2, rmv);
            // cerr << "2\n";
            // printQ(rmv);
        }
        debug(i,ans);
    }

    cout << ans << "\n";

    return 0;
}