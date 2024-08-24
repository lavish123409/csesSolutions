#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string ps = "\n";

// 4
// 2 4 4
// 3 6 6
// 6 8 2
// 5 7 3
/*
    
    a, b-4 & c-3,d-10
    
    sort all intervals according to start time
    for ind in intervals:
        recurse(intervals, ind)

    recurse(intervals, ind):
        if ind >= intervals.size:
            return 0

        base_ans = intervals[ind].value
        ans = 0
        next_ind = ind+1
        while(next_ind < intervals.size && intervals[ind] and intervals[next_ind] are not overlapping)
            ans += max(ans, base_ans + recurse(intervals, next_ind))

        return ans



*/

bool isOverlapping(array<int, 3> a, array<int,3> b) {
    return (a[0] <= b[0] && b[0] <= a[1]) || (a[0] <= b[1] && b[1] <= a[1]);
}

ll solve(array<int,3> a[], int in, int n, ll dp[]) {
    if(in >= n) {
        return 0;
    }

    if(dp[in] != -1) {
        return dp[in];
    }

    // ll ans = 0ll;
    // int next_ind = in+1;
    // while(next_ind < n && isOverlapping(a[in], a[next_ind])) next_ind++;
    // int next_ind = upper_bound(a+in+1, a+n, {a[in][1], -1, -1}) - a;

    // ps.push_back('\t');

    // cout << ps << in << " : ";
    // cout << a[in][0] << " , ";
    // cout << a[in][1] << " , ";
    // cout << a[in][2] << " - ";
    int next_ind=n, l=in+1, r=n-1;
    while(l <= r) {
        int m = l + (r - l) / 2;
        if(a[m][0] > a[in][1]) {
            next_ind = m;
            r = m-1;
        }
        else {
            l = m+1;
        }
    }
    // cout << ps << next_ind << " : ";
    // cout << a[next_ind][0] << " , ";
    // cout << a[next_ind][1] << " , ";
    // cout << a[next_ind][2] << " - ";


    ll take = a[in][2] + solve(a, next_ind, n, dp);
    ll notTake = solve(a, in+1, n, dp);

    // ps.pop_back();

    return dp[in] = max(take, notTake);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i, n, j;
    
    cin >> n;
    // cout << n << "\n";

    array<int,3> a[n];
    for(i=0;i<n;i++) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
    }

    sort(a, a+n);

    ll dp[n];
    memset(dp, -1, sizeof(dp));

    cout << solve(a, 0, n, dp) << "\n";

    return 0;
}