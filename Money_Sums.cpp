#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

string ps = "\n";

bool solve(int a[], int in, int sum, vector<vector<int>>& dp) {
    if(sum == 0) {
        return 1;
    }

    if(in < 0 || sum < 0) {
        return 0;
    }

    if(dp[in][sum] != -1) {
        return dp[in][sum];
    }

    // ps.push_back('\t');

    // cout << ps << in << "(" << a[in] << ") : " << sum;
    bool taken = solve(a, in-1, sum - a[in], dp);
    // cout << ps << "tk: " << taken;
    bool notTaken = solve(a, in-1, sum, dp);
    // cout << ps << "ntk: " << notTaken;
    
    // ps.pop_back();

    return dp[in][sum] = taken | notTaken;
}

int main()
{
    int i, n;
    cin >> n;

    int a[n], sum=0;
    for(i=0;i<n;i++) {
        cin >> a[i];
        sum += a[i];
    }

    vector<vector<int>> dp(n+1, vector<int>(sum+1));
    // for(i=0;i<n;i++) {
    //     dp[0][a[i]] = 1;
    // }
    // int ind=1;
    // while(ind * a[0] <= sum) {
    //     dp[0][ind * a[0]] = 1;
    // }
    // dp[0][a[0]] = 1;
    dp[0][0] = 1;

    vector<int> ans;

    int j;
    for(i=1;i<=n;i++) {
        dp[i][0] = 1;
        for(j=1;j<=sum;j++) {
            bool taken = 0;
            if(j - a[i-1] >= 0) {
                taken = dp[i-1][j - a[i-1]];
            }
            bool notTaken = dp[i-1][j];
            dp[i][j] = taken | notTaken;

            if(i == n && dp[i][j]) {
                ans.push_back(j);
            }
        }
    }


    cout << ans.size() << "\n";
    for(int it : ans) {
        cout << it << " ";
    }
    cout << "\n";
    // Memoization
    // for(i=1;i<=sum;i++) {
    //     solve(a, n-1, i, dp);
    //     if(dp[n-1][i] == 1) {
    //         // cout << i << " ";
    //         ans.push_back(i);
    //     }
    // }
    // cout << ans.size() << "\n";
    // for(int it : ans) {
    //     cout << it << " ";
    // }
    // cout << "\n";
    // for(i=1;i<=sum;i++) {
    //     if(solve(a, n-1, i)) {
    //         // cout << "\nfans: " << i << "\n";
    //         cout << i << " ";
    //     }
    // }
    
    return 0;
}