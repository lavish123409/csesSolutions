// #include <bits/stdc++.h>
// using namespace std;

// typedef long long ll;

// string ps = "\n";

// // 4 5 1 3
// /*
//     4, 3
// */

// ll solve(int a[], int l, int r, bool isFirstPlayerChance, vector<vector<vector<ll>>>& dp) {
//     if(l > r) {
//         return 0;
//     }

//     if(dp[l][r][isFirstPlayerChance] != -1) {
//         return dp[l][r][isFirstPlayerChance];
//     }

//     if(isFirstPlayerChance) {
//         return dp[l][r][isFirstPlayerChance] = max(
//             solve(a, l+1, r, !isFirstPlayerChance, dp) + a[l],
//             solve(a, l, r-1, !isFirstPlayerChance, dp) + a[r]
//         );
//     }
//     else {
//         return dp[l][r][isFirstPlayerChance] = min(
//             solve(a, l+1, r, !isFirstPlayerChance, dp),
//             solve(a, l, r-1, !isFirstPlayerChance, dp)
//         );
//     }
// }


// int main()
// {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     int i, n;
//     cin >> n;

//     int a[n];
//     for(i=0;i<n;i++) {
//         cin >> a[i];
//     }

//     vector<vector<vector<ll>>> dp(n, vector<vector<ll>>(n, vector<ll>(2)));

//     // for(i=0;i<n;i++)
    // int l, r;
    // for(l=n-1;l>=0;l--) {
    //     for(r=l;r<n;r++) {
    //         dp[l][r][1] = max(
    //             l == n-1 ? 0 : a[l] + dp[l+1][r][0],
    //             r == 0 ? 0 : a[r] + dp[l][r-1][0]
    //         );
    //         dp[l][r][0] = min(
    //             l == n-1 ? 0 : dp[l+1][r][1],
    //             r == 0 ? 0 : dp[l][r-1][1]
    //         );
    //     }
    // }
    // cout << dp[0][n-1][1] << "\n";

//     // cout << solve(a, 0, n-1, 1, dp) << "\n";
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> x(n);
  long long sum = 0;
  for (int&v : x) {
    cin >> v;
    sum += v;
  }

  vector<vector<long long>> dp(n,vector<long long>(n));
  for (int l = n-1; l >= 0; l--) {
    for (int r = l; r < n; r++) {
      if (l == r) {
	dp[l][r] = x[l];
      } else {
	dp[l][r] = max(x[l]-dp[l+1][r],
		       x[r]-dp[l][r-1]);
      }
    }
  }
  cout << (sum+dp[0][n-1])/2 << endl;
}

// #include <bits/stdc++.h>
// using namespace std;

// typedef long long ll;

// int main()
// {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     int n;
//     cin >> n;

//     vector<int> a(n);
//     for(int i = 0; i < n; i++) {
//         cin >> a[i];
//     }

//     vector<vector<ll>> dp(n, vector<ll>(n, 0));
//     vector<vector<ll>> dp_min(n, vector<ll>(n, 0));

//     // Base cases for the dp arrays
//     for(int i = 0; i < n; i++) {
//         dp[i][i] = a[i];
//     }

//     // Fill the dp arrays
//     for(int length = 2; length <= n; length++) {
//         for(int l = 0; l <= n - length; l++) {
//             int r = l + length - 1;
//             dp[l][r] = max(a[l] + dp_min[l + 1][r], a[r] + dp_min[l][r - 1]);
//             dp_min[l][r] = min(dp[l + 1][r], dp[l][r - 1]);
//         }
//     }

//     cout << dp[0][n - 1] << "\n";

//     return 0;
// }
