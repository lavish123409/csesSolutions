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
 
    solution
    use Mo's algorithm
    divide the array into sqrt(n) blocks, and find total cost to make that block increasing
    sort the queries according to the mo's algorithm
    then traverse the queries and set curr left and right according to the algorithm

    if curr left and right are in same block, find answer linearly
    otherwise, for starting tail - find cost and also the last number to come out till current block end
        - traverse elements from l+1 and add arr[curr_index-1] + 1 - arr[curr_index], if arr[curr_index-1] >= arr[curr_index] <- cost
        - last_element = max(arr[curr_index-1] + 1, arr[curr_index]) <- last number to come out
    for each block, find cost from precalculated block array and also the last number to come out till current block end
        - if last_element < first element of block, then cost = cost[block] and last_element = last_element[block]
        - otherwise, cost = (last_element - first_element_of_block + 1) * block_size + cost[block] and last_element = last_element[block] + (last_element - first_element_of_block + 1)
    for ending tail, do same as starting tail

    PROBLEM
    it cannot work because the numbers and their cost cannot transferred over blocks
    for ex, suppose last_element=4 ans block=[2,3,10]
    according to this approach, the cost would be (last_element - first_element_of_block + 1) * block_size * cost[block], here cost[block]=0 which would make it 0, and
    i was thinking that all elements in block would be increased because in order to make 2 > 4, we have to make it 4+1=5,
    and then with same difference=5-2=3, we would have to add in complete block, i.e, block=[5,6,13] but there is no need to change 10 as it is already > 6
    it would be valid if block=[2,3,4], then we would make block=[5,6,7], and cost would be dff * block_size + cost[block] = 3*3 + cost[block]

    solution - usaco(https://usaco.guide/problems/cses-2416-increasing-array-queries/solution)


*/
string ps = "\n";

const int MAXN = 2e5+5;
int arr[MAXN];
int arraySize;

template<class T> class BIT {
private:
    int size;
    vector<T> arr;
    vector<T> bit;

public:
    BIT(int size) {
        this->size = size;
        arr = vector<T>(size);
        bit = vector<T>(size+1);
    }

    void set(int ind, T val) {
        ad(ind, val - arr[ind]);
    }

    void ad(int ind, T dff) {
        arr[ind] += dff;
        ind++;
        for(; ind <= size; ind += (ind & -ind)) {
            bit[ind] += dff;
        }
    }

    T qr(int ind) {
        T ans = 0;
        ind++;
        for(; ind > 0; ind -= (ind & -ind)) {
            ans += bit[ind];
        }

        return ans;
    }
};

void solve() {

    int i, n, q;
    cin >> n >> q;

    for(i=0;i<n;i++) {
        cin >> arr[i];
    }

    vector<ll> psm(n+1);
    for(i=0;i<n;i++) {
        psm[i+1] = psm[i] + arr[i];
    }

    vector<vector<array<int,2>>> qrs(n);
    for(i=0;i<q;i++) {
        int l, r;
        cin >> l >> r;

        l--;
        r--;

        qrs[l].push_back({r, i});
    }

    BIT<ll> contrib(n);
    vector<array<int,2>> maxes;
    vector<ll> ans(q);
    for(i=n-1;i>=0;i--) {
        while(!maxes.empty() && arr[i] >= maxes.back()[0]) {
            maxes.pop_back();
            contrib.set(maxes.size(), 0);
        }

        int len = (maxes.empty() ? n : maxes.back()[1]) - i;
        contrib.set(maxes.size(), 1ll * len * arr[i]);
        maxes.push_back({arr[i], i});

        // 15 13 10 9 4
        for(auto& [end, qind] : qrs[i]) {
            int l=0;
            int r=maxes.size()-1;
            int valid = -1;
            while(l <= r) {
                int m = l + (r - l) / 2;
                if(maxes[m][1] <= end) {
                    valid = m;
                    r = m-1;
                }
                else {
                    l = m+1;
                }
            }
            ll sum1 = contrib.qr(maxes.size()-1) - contrib.qr(valid);
            ll sum2 = 1ll * (1ll * end - maxes[valid][1] + 1) * maxes[valid][0];
            ll prsm = psm[end+1] - psm[i];
            debug(i, end);
            debug(maxes, valid);
            debug(sum1, sum2, prsm);

            ans[qind] = sum1 + sum2 - prsm;
        }

    }

    for(auto it : ans) {
        cout << it << "\n";
    }
    // cout << "\n";
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