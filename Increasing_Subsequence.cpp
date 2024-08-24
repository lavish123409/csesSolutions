#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string ps = "\n";

// 7 3 5 3 6 2 9 8
/*
    7, 8 -> 2
        3, 5, 6, 9 -> 4

    // even with dp it would be O(n^2)
    recurse(arr, in, lse):

        take = 0
        if(arr[in] > lse):
            take = 1 + recurse(arr, in+1, arr[in])
        
        notTake = recurse(arr, in+1, lse)

        return max(take, notTake)

    1 -> ... j .. i ...

    // n log(n) Approach
    7 -> [7]
    3 -> [7][3]
    5 -> [7][3 5]
    3 -> [7][3 5][3]
    6 -> [7][3 5 6][3] => [3 5 6]


    for element in array: // O(n)
        ind = find minimum element in lis list >= element // O(logn)
        if ind >= lis.size:
            lis.push_back(element)
        else
            lis[ind] = element

    print lis.size


*/

int solve(int arr[], int in, int lsi, int n, vector<vector<int>>& dp) {
    if(in == n) {
        return 0;
    }

    cerr << in << "\n";
    cout << in << "\n";
    if(dp[in][lsi+1] != -1) {
        return dp[in][lsi+1];
    }

    int take = 0;
    if(lsi == -1 || arr[in] > arr[lsi]) {
        take = 1 + solve(arr, in+1, in, n, dp);
    }
    int notTake = solve(arr, in+1, lsi, n, dp);

    return dp[in][lsi+1] = max(take, notTake);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i, n, j;
    
    cin >> n;
    // cout << n << "\n";

    int a[n];
    for(i=0;i<n;i++) {
        cin >> a[i];
    }

    vector<int> lis;
    for(i=0;i<n;i++) {
        int in = lower_bound(lis.begin(), lis.end(), a[i]) - lis.begin();
        if(in >= lis.size()) {
            lis.push_back(a[i]);
        }
        else {
            lis[in] = a[i];
        }
    }

    cout << lis.size() << "\n";

    // Tabulation O(n^2)
    // vector<int> dp(n);
    // for(i=0;i<n;i++) {
    //     dp[i] = 1;
    //     for(j=0;j<i;j++) {
    //         if(a[j] < a[i]) {
    //             dp[i] = max(dp[i], 1 + dp[j]);
    //         }
    //     }
    // }

    // cout << *max_element(dp.begin(), dp.end()) << "\n";

    // Memoization - not working because of constarints in n, cannot create 2d vector of (10^5 * 10^5)
    // vector<vector<int>> dp(n, vector<int>(n+1, -1));

    // cout << solve(a, 0, -1, n, dp) << "\n";

    return 0;
}